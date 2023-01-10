// dmpsx.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "parse.h"

enum GteFunc
{
	GFN_RTPS_U,
	GFN_RTPS,
	GFN_NCLIP=6,
	GFN_OP=0xC,
	GFN_DPCS=0x10,
	GFN_INTPL,
	GFN_MVMVA,
	GFN_NCDS,
	GFN_CDP,
	GFN_NCDT=0x16,
	GFN_DPCL_U=0x1A,
	GFN_NCCS,
	GFN_CC,
	GFN_NCS=0x1E,
	GFN_NCT=0x20,
	GFN_SQR=0x28,
	GFN_DPCL,
	GFN_DPCT,
	GFN_AVSZ3=0x2D,
	GFN_AVSZ4,
	GFN_RTPT=0x30,
	GFN_GPF=0x3D,
	GFN_GPL,
	GFN_NCCT
};

#define MAKE_GTE(set,unk,func,lm,cv,_v,mx,sf)		( 0x48000000 | ((set)<<21) | ((unk)<<20) | (func) |\
	((lm)<<10) | ((cv)<<13) | ((_v)<<15) | ((mx) << 17) | ((sf)<<19) )

#define GTE_SET(op)		( ( op >> 21) & 0x1F )
#define GTE_UNK(op)		( ( op >> 20) & 1 )
#define GTE_SF(op)		( ( op >> 19 ) & 1 )
#define GTE_MX(op)		( ( op >> 17 ) & 3 )
#define GTE_V(op)		( ( op >> 15 ) & 3 )
#define GTE_CV(op)		( ( op >> 13 ) & 3 )
#define GTE_LM(op)		( ( op >> 10 ) & 1 )
#define GTE_FUNCT(op)	( op & 0x3F )

#define BUILD_GTE		1

#if BUILD_GTE
u32 GTE_tbl[0x53];
#else
u32 GTE_tbl[]=
{
	0,
	MAKE_GTE(0x10,1, GFN_RTPS,0,0,0,0,1),	// 4a180001
	MAKE_GTE(0x11,0, GFN_RTPT,0,0,0,0,1),	// 4a280030
	MAKE_GTE(0x12,0,GFN_MVMVA,0,0,0,0,1),	// 4a480012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,3,0,0,1),	// 4a486012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,3,1,0,1),	// 4a48e012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,3,2,0,1),	// 4a496012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,3,3,0,1),	// 4a49e012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,3,3,0,0),	// 4a41e012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,0,0,0,1),	// 4a480012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,0,1,0,1),	// 4a488012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,0,2,0,1),	// 4a490012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,0,3,0,1),	// 4a498012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,1,0,0,1),	// 4a482012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,1,1,0,1),	// 4a48a012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,1,2,0,1),	// 4a492012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,1,3,0,1),	// 4a49a012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,2,0,0,1),	// 4a484012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,2,1,0,1),	// 4a48c012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,2,2,0,1),	// 4a494012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,2,3,0,1),	// 4a49c012
	MAKE_GTE(0x12,0,GFN_MVMVA,1,3,0,1,1),	// 4a4a6412
	MAKE_GTE(0x12,0,GFN_MVMVA,0,3,0,1,1),	// 4a4a6012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,3,1,1,1),	// 4a4ae012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,3,2,1,1),	// 4a4b6012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,3,3,1,1),	// 4a4be012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,0,0,1,1),	// 4a4a0012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,0,1,1,1),	// 4a4a8012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,0,2,1,1),	// 4a4b0012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,0,3,1,1),	// 4a4b8012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,1,0,1,1),	// 4a4a2012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,1,1,1,1),	// 4a4aa012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,1,2,1,1),	// 4a4b2012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,1,3,1,1),	// 4a4ba012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,2,0,1,1),	// 4a4a4012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,2,1,1,1),	// 4a4ac012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,2,2,1,1),	// 4a4b4012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,2,3,1,1),	// 4a4bc012
	MAKE_GTE(0x12,0,GFN_MVMVA,1,1,3,2,1),	// 4a4da412
	MAKE_GTE(0x12,0,GFN_MVMVA,0,3,0,2,1),	// 4a4c6012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,3,1,2,1),	// 4a4ce012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,3,2,2,1),	// 4a4d6012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,3,3,2,1),	// 4a4de012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,0,0,2,1),	// 4a4c0012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,0,1,2,1),	// 4a4c8012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,0,2,2,1),	// 4a4d0012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,0,3,2,1),	// 4a4d8012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,1,0,2,1),	// 4a4c2012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,1,1,2,1),	// 4a4ca012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,1,2,2,1),	// 4a4d2012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,1,3,2,1),	// 4a4da012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,2,0,2,1),	// 4a4c4012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,2,1,2,1),	// 4a4cc012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,2,2,2,1),	// 4a4d4012
	MAKE_GTE(0x12,0,GFN_MVMVA,0,2,3,2,1),	// 4a4dc012
	MAKE_GTE(0x13,0, GFN_DPCL,0,0,0,0,1),	// 4a680029
	MAKE_GTE(0x13,1, GFN_DPCS,0,0,0,0,1),	// 4a780010
	MAKE_GTE(0x17,1, GFN_DPCT,0,0,0,0,1),	// 4af8002a
	MAKE_GTE(0x14,1,GFN_INTPL,0,0,0,0,1),	// 4a980011
	MAKE_GTE(0x15,0,  GFN_SQR,1,0,0,0,1),	// 4aa80428
	MAKE_GTE(0x15,0,  GFN_SQR,1,0,0,0,0),	// 4aa00428
	MAKE_GTE(0x16,0,  GFN_NCS,1,0,0,0,1),	// 4ac8041e
	MAKE_GTE(0x16,1,  GFN_NCT,1,0,0,0,1),	// 4ad80420
	MAKE_GTE(0x17,0, GFN_NCDS,1,0,0,0,1),	// 4ae80413
	MAKE_GTE(0x17,1, GFN_NCDT,1,0,0,0,1),	// 4af80416
	MAKE_GTE(0x18,0, GFN_NCCS,1,0,0,0,1),	// 4b08041b
	MAKE_GTE(0x18,1, GFN_NCCT,1,0,0,0,1),	// 4b18043f
	MAKE_GTE(0x19,0,  GFN_CDP,1,0,0,0,1),	// 4b280414
	MAKE_GTE(0x19,1,   GFN_CC,1,0,0,0,1),	// 4b38041c
	MAKE_GTE(0x1a,0,GFN_NCLIP,0,0,0,0,0),	// 4b400006
	MAKE_GTE(0x1a,1,GFN_AVSZ3,0,0,0,0,1),	// 4b58002d
	MAKE_GTE(0x1b,0,GFN_AVSZ4,0,0,0,0,1),	// 4b68002e
	MAKE_GTE(0x1b,1,   GFN_OP,0,0,0,0,1),	// 4b78000c
	MAKE_GTE(0x1b,1,   GFN_OP,0,0,0,0,0),	// 4b70000c
	MAKE_GTE(0x1c,1,  GFN_GPF,0,0,0,0,1),	// 4b98003d
	MAKE_GTE(0x1c,1,  GFN_GPF,0,0,0,0,0),	// 4b90003d
	MAKE_GTE(0x1d,0,  GFN_GPL,0,0,0,0,1),	// 4ba8003e
	MAKE_GTE(0x1d,0,  GFN_GPL,0,0,0,0,0),	// 4ba0003e
	MAKE_GTE(0x12,0,GFN_MVMVA,0,0,0,0,0),	// 4a400012
	MAKE_GTE(0x15,0,  GFN_SQR,1,0,0,0,0),	// 4aa00428
	MAKE_GTE(0x1b,1,   GFN_OP,0,0,0,0,0),	// 4b70000c
	MAKE_GTE(0x1c,1,  GFN_GPF,0,0,0,0,0),	// 4b90003d
	MAKE_GTE(0x1d,0,  GFN_GPL,0,0,0,0,0),	// 4ba0003e
};
#endif

u32 some_dword,
prev_dword,
last_dword;

void set_table()
{
#if BUILD_GTE
	GTE_tbl[val_to_tbl(0x7F)]  = 0x4A180001;	// rtps
	GTE_tbl[val_to_tbl(0xBF)]  = 0x4A280030;	// rtpt
	GTE_tbl[val_to_tbl(0xFF)]  = 0x4A480012;	// rt
	GTE_tbl[val_to_tbl(0x13F)] = 0x4A486012;	// rtv0
	GTE_tbl[val_to_tbl(0x17F)] = 0x4A48E012;	// rtv1
	GTE_tbl[val_to_tbl(0x1BF)] = 0x4A496012;	// rtv2
	GTE_tbl[val_to_tbl(0x1FF)] = 0x4A49E012;	// rtir
	GTE_tbl[val_to_tbl(0x23F)] = 0x4A41E012;	// rtir_sf0
	GTE_tbl[val_to_tbl(0x27F)] = 0x4A480012;	// rtv0tr
	GTE_tbl[val_to_tbl(0x2BF)] = 0x4A488012;	// rtv1tr
	GTE_tbl[val_to_tbl(0x2FF)] = 0x4A490012;	// rtv2tr
	GTE_tbl[val_to_tbl(0x33F)] = 0x4A498012;	// rtirtr
	GTE_tbl[val_to_tbl(0x37F)] = 0x4A482012;	// rtv0bk
	GTE_tbl[val_to_tbl(0x3BF)] = 0x4A48A012;	// rtv1bk
	GTE_tbl[val_to_tbl(0x3FF)] = 0x4A492012;	// rtv2bk
	GTE_tbl[val_to_tbl(0x43F)] = 0x4A49A012;	// rtivbk
	GTE_tbl[val_to_tbl(0x47F)] = 0x4A484012;	// not in list [mvmva]
	GTE_tbl[val_to_tbl(0x4BF)] = 0x4A48C012;	// not in list [mvmva]
	GTE_tbl[val_to_tbl(0x4FF)] = 0x4A494012;	// not in list [mvmva]
	GTE_tbl[val_to_tbl(0x53F)] = 0x4A49C012;	// not in list [mvmva]
	GTE_tbl[val_to_tbl(0x57F)] = 0x4A4A6412;	// ll
	GTE_tbl[val_to_tbl(0x5BF)] = 0x4A4A6012;	// llv0
	GTE_tbl[val_to_tbl(0x5FF)] = 0x4A4AE012;	// llv1
	GTE_tbl[val_to_tbl(0x63F)] = 0x4A4B6012;	// llv2
	GTE_tbl[val_to_tbl(0x67F)] = 0x4A4BE012;	// llir
	GTE_tbl[val_to_tbl(0x6BF)] = 0x4A4A0012;	// llv0tr
	GTE_tbl[val_to_tbl(0x6FF)] = 0x4A4A8012;	// llv1tr
	GTE_tbl[val_to_tbl(0x73F)] = 0x4A4B0012;	// llv2tr
	GTE_tbl[val_to_tbl(0x77F)] = 0x4A4B8012;	// llirtr
	GTE_tbl[val_to_tbl(0x7BF)] = 0x4A4A2012;	// llv0bk
	GTE_tbl[val_to_tbl(0x7FF)] = 0x4A4AA012;	// llv1bk
	GTE_tbl[val_to_tbl(0x83F)] = 0x4A4B2012;	// llv2bk
	GTE_tbl[val_to_tbl(0x87F)] = 0x4A4BA012;	// llirbk
	GTE_tbl[val_to_tbl(0x8BF)] = 0x4A4A4012;	// not in list [mvmva]
	GTE_tbl[val_to_tbl(0x8FF)] = 0x4A4AC012;	// not in list [mvmva]
	GTE_tbl[val_to_tbl(0x93F)] = 0x4A4B4012;	// not in list [mvmva]
	GTE_tbl[val_to_tbl(0x97F)] = 0x4A4BC012;	// not in list [mvmva]
	GTE_tbl[val_to_tbl(0x9BF)] = 0x4A4DA412;	// lc
	GTE_tbl[val_to_tbl(0x9FF)] = 0x4A4C6012;	// lcv0
	GTE_tbl[val_to_tbl(0xA3F)] = 0x4A4CE012;	// lcv1
	GTE_tbl[val_to_tbl(0xA7F)] = 0x4A4D6012;	// lcv2
	GTE_tbl[val_to_tbl(0xABF)] = 0x4A4DE012;	// lcir
	GTE_tbl[val_to_tbl(0xAFF)] = 0x4A4C0012;	// lcv0tr
	GTE_tbl[val_to_tbl(0xB3F)] = 0x4A4C8012;	// lcv1tr
	GTE_tbl[val_to_tbl(0xB7F)] = 0x4A4D0012;	// lcv2tr
	GTE_tbl[val_to_tbl(0xBBF)] = 0x4A4D8012;	// lcirtr
	GTE_tbl[val_to_tbl(0xBFF)] = 0x4A4C2012;	// lcv0bk
	GTE_tbl[val_to_tbl(0xC3F)] = 0x4A4CA012;	// lcv1bk
	GTE_tbl[val_to_tbl(0xC7F)] = 0x4A4D2012;	// lcv2bk
	GTE_tbl[val_to_tbl(0xCBF)] = 0x4A4DA012;	// lcirbk
	GTE_tbl[val_to_tbl(0xCFF)] = 0x4A4C4012;	// not in list [mvmva]
	GTE_tbl[val_to_tbl(0xD3F)] = 0x4A4CC012;	// not in list [mvmva]
	GTE_tbl[val_to_tbl(0xD7F)] = 0x4A4D4012;	// not in list [mvmva]
	GTE_tbl[val_to_tbl(0xDBF)] = 0x4A4DC012;	// not in list [mvmva]
	GTE_tbl[val_to_tbl(0xDFF)] = 0x4A680029;	// dpcl
	GTE_tbl[val_to_tbl(0xE3F)] = 0x4A780010;	// dpcs
	GTE_tbl[val_to_tbl(0xE7F)] = 0x4AF8002A;	// dpct
	GTE_tbl[val_to_tbl(0xEBF)] = 0x4A980011;	// intpl
	GTE_tbl[val_to_tbl(0xEFF)] = 0x4AA80428;	// sqr12
	GTE_tbl[val_to_tbl(0xF3F)] = 0x4AA00428;	// sqr0
	GTE_tbl[val_to_tbl(0xF7F)] = 0x4AC8041E;	// ncs
	GTE_tbl[val_to_tbl(0xFBF)] = 0x4AD80420;	// nct
	GTE_tbl[val_to_tbl(0xFFF)] = 0x4AE80413;	// ncds
	GTE_tbl[val_to_tbl(0x103F)]= 0x4AF80416;	// ncdt
	GTE_tbl[val_to_tbl(0x107F)]= 0x4B08041B;	// nccs
	GTE_tbl[val_to_tbl(0x10BF)]= 0x4B18043F;	// ncct
	GTE_tbl[val_to_tbl(0x10FF)]= 0x4B280414;	// cdp
	GTE_tbl[val_to_tbl(0x113F)]= 0x4B38041C;	// cc
	GTE_tbl[val_to_tbl(0x117F)]= 0x4B400006;	// nclip
	GTE_tbl[val_to_tbl(0x11BF)]= 0x4B58002D;	// avsz3
	GTE_tbl[val_to_tbl(0x11FF)]= 0x4B68002E;	// avsz4
	GTE_tbl[val_to_tbl(0x123F)]= 0x4B78000C;	// op12
	GTE_tbl[val_to_tbl(0x127F)]= 0x4B70000C;	// op0
	GTE_tbl[val_to_tbl(0x12BF)]= 0x4B98003D;	// gpf12
	GTE_tbl[val_to_tbl(0x12FF)]= 0x4B90003D;	// gpf0
	GTE_tbl[val_to_tbl(0x133F)]= 0x4BA8003E;	// gpl12
	GTE_tbl[val_to_tbl(0x137F)]= 0x4BA0003E;	// gpl0
	GTE_tbl[val_to_tbl(0x13BF)]= 0x4A400012;	// mvmva
	GTE_tbl[val_to_tbl(0x13FF)]= 0x4AA00428;	// not in list [sqr0]
	GTE_tbl[val_to_tbl(0x143F)]= 0x4B70000C;	// not in list [op0]
	GTE_tbl[val_to_tbl(0x147F)]= 0x4B90003D;	// not in list [gpf0]
	GTE_tbl[val_to_tbl(0x14BF)]= 0x4BA0003E;	// not in list [gpl0]
	GTE_tbl[0] = 0;
#endif
}

#ifdef _DEBUG
void print_gte_opcodes()
{
	static LPCTSTR op_name[]=
	{
		_T("GFN_RTPS_U"),
		_T("GFN_RTPS"),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T("GFN_NCLIP"),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T("GFN_OP"),
		_T(""),
		_T(""),
		_T(""),
		_T("GFN_DPCS"),
		_T("GFN_INTPL"),
		_T("GFN_MVMVA"),
		_T("GFN_NCDS"),
		_T("GFN_CDP"),
		_T(""),
		_T("GFN_NCDT"),
		_T(""),
		_T(""),
		_T(""),
		_T("GFN_DPCL_U"),
		_T("GFN_NCCS"),
		_T("GFN_CC"),
		_T(""),
		_T("GFN_NCS"),
		_T(""),
		_T("GFN_NCT"),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T("GFN_SQR"),
		_T("GFN_DPCL"),
		_T("GFN_DPCT"),
		_T(""),
		_T(""),
		_T("GFN_AVSZ3"),
		_T("GFN_AVSZ4"),
		_T(""),
		_T("GFN_RTPT"),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T(""),
		_T("GFN_GPF"),
		_T("GFN_GPL"),
		_T("GFN_NCCT")
	};

	FILE *log = _tfopen(_T("gte.log"), _T("wb+"));
	for (int i = 1; i < _countof(GTE_tbl); i++)
	{
		u32 op = GTE_tbl[i];
		_tprintf(_T("%02d %08x: set %02x, func %9s, lm %d, cv %d, v %d, mx %d, sf %d\n"),
			i, op,
			GTE_SET(op),
			op_name[GTE_FUNCT(op)],
			GTE_LM(op),
			GTE_CV(op),
			GTE_V(op),
			GTE_MX(op),
			GTE_SF(op));
		_ftprintf(log,_T("\tMAKE_GTE(0x%02x,%d,%9s,%d,%d,%d,%d,%d),\t// %08x\r\n"),
			GTE_SET(op),
			GTE_UNK(op),
			op_name[GTE_FUNCT(op)],
			GTE_LM(op),
			GTE_CV(op),
			GTE_V(op),
			GTE_MX(op),
			GTE_SF(op),
			op);
	}
	fclose(log);
}
#endif

void init_vars()
{
	set_table();
	last_dword = 0;
	prev_dword = 0;
	some_dword = 0;
}

void print_info()
{
	_tprintf(_T("DMPSX Version 3.05\n")
		_T("Copyright(C) 1995-1998 by Sony Computer Entertainment Inc.\n")
		_T("All rights reserved.\n"));
}

void print_usage()
{
	_tprintf(_T("usage:\n")
		_T("\t> DMPSX object-file [-b][-o output-file]\n\n")
		_T("\t-b:\tBackup file is not created\n")
#if _DEBUG
		_T("\t-d:\tPrint GTE tables and build macro log.")
#endif
		_T("\t-o:\tDesignation of output file\n\n")
		);
}

void name_fix(TCHAR *dst, TCHAR *src, TCHAR *suffix)
{
	TCHAR *dotpos;
	size_t cpypos;

	dotpos = _tcsrchr(src, _T('.'));
	// terminator found
	if (dotpos) cpypos = (size_t)(dotpos - src);
	// no terminator, just append
	else cpypos = _tcslen(src);

	// copy output name over input
	memcpy(dst, src, cpypos*sizeof(TCHAR));
	// replace extention
	_tcscpy(&dst[cpypos], suffix);
}

int copy_file(TCHAR *filename_in, TCHAR *filename_out)
{
	int result;
	FILE *file_in;
	FILE *file_out;

	file_in = _tfopen(filename_in, _T("rb"));
	if (file_in)
	{
		file_out = _tfopen(filename_out, _T("wb"));
		if (file_out)
		{
			while (1)
			{
				int ch = fgetc(file_in);
				if (ch == EOF) break;
				fputc(ch, file_out);
			//	--file_in->_cnt;
			//	if (file_in->_cnt < 0)
			//		pos = _filbuf(file_in);
			//	else
			//		pos = *file_in->_ptr++;
			//	if (pos == -1)
			//		break;
			//	--file_out->_cnt;
			//	if (file_out->_cnt < 0)
			//		_flsbuf(pos, file_out);
			//	else
			//		*file_out->_ptr++ = pos;
			}
			fclose(file_in);
			fclose(file_out);
			result = 1;
		}
		else
		{
			fclose(file_in);
			result = 0;
		}
	}
	else result = 0;

	return result;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int has_output, has_input, has_backup;
	TCHAR name_in[MAX_PATH] = { 0 }, name_out[MAX_PATH] = { 0 }, name_ex[MAX_PATH] = { 0 };
	GFile f_in, f_out;

	init_vars();
	has_backup = TRUE;
	has_output = FALSE;
	has_input  = FALSE;

	for (int i = 1; i < argc; i++)
	{
		if (*argv[i] == '-')
		{
			TCHAR c = argv[i][1];
			// disable backup
			if (c == 'b')
				has_backup = FALSE;
#ifdef _DEBUG
			if( c == 'd')
			{
				print_gte_opcodes();
				return 0;
			}
#endif
			else
			{
				if (c != 'o')	// no output
				{
					if (c != 'v')	// undocumented option
					{
						_tprintf(_T("\tDMPSX: Illegal option : %s\n"), argv[i]);
						print_usage();
						return 1;
					}
					print_info();
					return 0;
				}
				if (_tcslen(argv[i]) <= 2)
					_tcscpy(name_out, argv[i++ + 1]);
				else _tcscpy(name_out, argv[i] + 2);
				has_output = TRUE;
			}
		}
		else
		{
			if (has_input)
			{
				_tprintf(_T("\tDMPSX: Too many input files\n"));
				print_usage();
				return 1;
			}
			_tcscpy(name_in, argv[i]);
			has_input = TRUE;
		}
	}

	// no input file
	if (!has_input)
	{
		print_info();
		print_usage();
		return 1;
	}
	// needs backup
	if (!has_output)
		name_fix(name_out, name_in, _T(".tmp"));

	if (!f_in.open(name_in, _T("rb+")))
	{
		_tprintf(_T("\tDMPSX: Can't open input file : %s\n"),name_in);
		return 1;
	}

	if (!f_out.open(name_out, _T("wb")))
	{
		_tprintf(_T("\tDMPSX: Can't open output file : %s\n"), name_out);
		return 1;
	}

	// parsing
	if (!parse_all(f_in, f_out))
	{
		// out error, delete and exit
		f_out.close();
		_tremove(name_out);
		return 1;
	}

	// replacement done
	f_in.close();
	f_out.close();

	if (!has_output)
	{
		if (has_backup)
		{
			name_fix(name_ex, name_in, _T(".bak"));
			if (!copy_file(name_in, name_ex))
			{
				_tprintf(_T("\tDMPSX: Can't create bak file : %s\n"), name_ex);
				return 1;
			}
		}
		_tremove(name_in);
		if (!copy_file(name_out, name_in))
		{
			_tprintf(_T("\tDMPSX: Can't create out file : %s\n"), name_in);
			return 1;
		}
		_tremove(name_out);
	}

	return 0;
}

