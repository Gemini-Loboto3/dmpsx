#include "stdafx.h"
#include "Parse.h"

#define MAGIC(a,b,c,d)	((a)|((b)<<8)|((c)<<16)|((d)<<24))

extern u32 some_dword,
	last_dword,
	prev_dword;
extern u32 GTE_tbl[];

int copy_case(GFile &fin, GFile &fout)
{
	int type;

	type = fin.read_byte();
	fout.write_byte(type);

	switch (type)
	{
	case 0:
		fout.copy_bytes(fin, 4);
		break;
	case 2:
		fout.copy_bytes(fin, 2);
		break;
	case 4:
		fout.copy_bytes(fin, 2);
		break;
	case 6:
		fout.copy_bytes(fin, 2);
		break;
	case 8:
		fout.copy_bytes(fin, 2);
		break;
	case 10:
		fout.copy_bytes(fin, 2);
		break;
	case 12:
		fout.copy_bytes(fin, 2);
		break;
	case 14:
		fout.copy_bytes(fin, 2);
		break;
	case 16:
		fout.copy_bytes(fin, 2);
		break;
	case 18:
		fout.copy_bytes(fin, 2);
		break;
	case 20:
		fout.copy_bytes(fin, 2);
		break;
	case 22:
		fout.copy_bytes(fin, 2);
		break;
	case 24:
		fout.copy_bytes(fin, 2);
		break;
	default:
		copy_case(fin, fout);
		copy_case(fin, fout);
	}

	return 1;
}

int parse_all(GFile &fin, GFile &fout)
{
	u32 magic;
	int some_stats[10];
	int ck0, c, seg_cnt;
	u16 r16;
	char str[256];

	// initialize internal stats
	ck0 = 0;
	seg_cnt = 0;
	for (int i = 0; i<_countof(some_stats); i++)
		some_stats[i] = -1;

	// get signature
	magic=fin.read_u32_LE();
	fout.write_u32_LE(magic);
	if (magic != MAGIC('L','N','K',2))
	{
		_tprintf(_T("DMPSX: Illegal input file format\n"));
		return 0;
	}

	while ((c = fin.read_byte()) != EOF)
	{
		fout.write_byte(c);

		switch (c)
		{
		case 2:
			r16 = fin.read_u16_LE();
			fout.write_u16_LE(r16);
			if (ck0 == 1)
			{
				if (!convert_macros(fin, fout, r16))
					some_dword = 1;
			}
			else
			{
				while (1)
				{
					int tmp = r16--;
					if (!tmp) break;
					fout.copy_bytes(fin, 1);
				}
			}
			break;
		case 4:
			fout.copy_bytes(fin, 6);
			break;
		case 6:
			r16 = fin.read_u16_LE();
			fout.write_u16_LE(r16);
			ck0 = 0;
			for (int i = 0; i < seg_cnt; ++i)
			{
				if (r16 == some_stats[i])
				{
					ck0 = 1;
					break;
				}
			}
			break;
		case 8:
			fout.copy_bytes(fin, 4);
			break;
		case 0xA:
			fout.copy_bytes(fin, 3);
			copy_case(fin, fout);
			break;
		case 0xC:
			fout.copy_bytes(fin, 8);
			fout.copy_pascal(fin);
			break;
		case 0xE:
			fout.copy_bytes(fin, 2);
			fout.copy_pascal(fin);
			break;
		case 0x10:
			r16 = fin.read_u16_LE();
			fout.write_u16_LE(r16);
			fout.copy_bytes(fin, 3);
			c = fin.read_byte();
			fout.write_byte(c);
			if (c >= 100)
				_tprintf(_T("DMPSX: too long section name %d\n"), c);
			for (int i = 0;; ++i)
			{
				int tmp = c--;
				if (!tmp) break;
				int r = fin.read_byte();
				fout.write_byte(r);
				str[i] = r;
				str[i + 1] = '\0';
			}

			if (strcmp(str/*&v11 + i*/, ".text")==0)
			{
				if (seg_cnt >= 10)
					_tprintf(_T("DMPSX: too many sections\n"));
				else
					some_stats[seg_cnt++] = r16;
			}
			break;
		case 0x12:
			fout.copy_bytes(fin, 6);
			fout.copy_pascal(fin);
			break;
		case 0x14:
			fout.copy_bytes(fin, 3);
			fout.copy_pascal(fin);
			break;
		case 0x16:
			copy_case(fin, fout);
			fout.copy_bytes(fin, 2);
			break;
		case 0x18:
			copy_case(fin, fout);
			fout.copy_bytes(fin, 2);
			break;
		case 0x1A:
			copy_case(fin, fout);
			fout.copy_bytes(fin, 2);
			break;
		case 0x1C:	// source file name
			fout.copy_bytes(fin, 2);
			fout.copy_pascal(fin);
			break;
		case 0x1E:
			fout.copy_bytes(fin, 6);
			break;
		case 0x20:
			fout.copy_bytes(fin, 4);
			break;
		case 0x24:
			fout.copy_bytes(fin, 1);
			break;
		case 0x26:
			fout.copy_bytes(fin, 2);
			break;
		case 0x28:
			fout.copy_bytes(fin, 6);
			fout.copy_pascal(fin);
			break;
		case 0x2A:
			copy_case(fin, fout);
			fout.copy_bytes(fin, 2);
			break;
		case 0x2C:
			fout.copy_bytes(fin, 3);
			break;
		case 0x2E:
			fout.copy_bytes(fin, 1);
			break;
		case 0x30:
			fout.copy_bytes(fin, 8);
			fout.copy_pascal(fin);
			break;
		case 0x32:
			fout.copy_bytes(fin, 2);
			break;
		case 0x34:
			fout.copy_bytes(fin, 3);
			break;
		case 0x36:
			fout.copy_bytes(fin, 4);
			break;
		case 0x38:
			fout.copy_bytes(fin, 6);
			break;
		case 0x3A:
			fout.copy_bytes(fin, 8);
			break;
		case 0x3C:
			fout.copy_bytes(fin, 2);
			break;
		case 0x3E:
			copy_case(fin, fout);
			fout.copy_bytes(fin, 4);
			break;
		case 0x40:
			copy_case(fin, fout);
			fout.copy_bytes(fin, 4);
			break;
		case 0x42:
			copy_case(fin, fout);
			fout.copy_bytes(fin, 4);
			break;
		case 0x44:
			fout.copy_bytes(fin, 11);
			break;
		case 0x46:
			fout.copy_bytes(fin, 10);
			break;
		case 0x48:
			copy_case(fin, fout);
			fout.copy_bytes(fin, 4);
			break;
		case 0x4A:
			fout.copy_bytes(fin, 28);
			fout.copy_pascal(fin);
			break;
		case 0x4C:
			fout.copy_bytes(fin, 10);
			break;
		case 0x4E:
			fout.copy_bytes(fin, 10);
			break;
		case 0x50:
			fout.copy_bytes(fin, 10);
			break;
		case 0x52:
			fout.copy_bytes(fin, 14);
			fout.copy_pascal(fin);
			break;
		case 0x54:
			fout.copy_bytes(fin, 14);
			r16 = fin.read_u16_LE();
			fout.write_u16_LE(r16);
			while (1)
			{
				int tmp = r16;
				--r16;
				if (!tmp) break;
				fout.copy_bytes(fin, 4);
			}
			fout.copy_pascal(fin);
			fout.copy_pascal(fin);
			break;
		case 0:
			break;
		}

		if (some_dword) return 0;
	}

	return 1;
}

BOOL IsDelayAllowed(u32 op)
{
	u32 cmd = op >> 26;
	return cmd == 0x12 || cmd == 0x32 || cmd == 0x3A;
}

typedef struct tagGteOp
{
	u32 func : 6;	// 0-5
	u32 pad0 : 12;	// 6
	u32 lm : 1;		// 18
	u32 cv : 2;		// 19
	u32 v : 2;		// 21
	u32 mx : 2;		// 23
	u32 sf : 1;		// 25
	u32 pad1 : 6;	// 26-31
} GTE_OPCODE;

int convert_macros(GFile &fin, GFile &fout, int left)
{
	u32 opcode;
	u32 trans;

	while (left > 0)
	{
		opcode = fin.read_u32_LE();
		// detect fake GTE instructions
		if ((opcode & 0xFC00003F) == 0x3F)
		{
			trans = val_to_tbl(opcode);
			// check for illegal GTE opcodes
			if (trans > 0x53 || (trans & 0x80000000) != 0)
			{
				_tprintf(_T("\tDMPSX: Undefined macro %08lx\n"), opcode);
				return 0;
			}
			// delay check
			if (IsDelayAllowed(prev_dword) || IsDelayAllowed(last_dword))
			{
				_tprintf(_T("\tDMPSX: Too few DELAY SLOTS before the macro	%08lx"), opcode);
				return 0;
			}
			// generate a real GTE opcode
			opcode = ((opcode & 0x40000) >> 18 << 10) | // GTE_LM
				((opcode & 0x180000) >> 19 << 13) |		// GTE_CV
				((opcode & 0x600000) >> 21 << 15) |		// GTE_V
				((opcode & 0x1800000) >> 23 << 17) |	// GTE_MX
				((opcode & 0x2000000) >> 25 << 19) |	// GTE_SF
				GTE_tbl[trans];
		}
		fout.write_u32_LE(opcode);
		prev_dword = last_dword;
		last_dword = opcode;
		left -= 4;
	}
	return 1;
}
