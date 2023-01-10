#pragma once

static __inline u32 val_to_tbl(u32 val)
{
	return (val & 0x3FFC0) >> 6;
}

int convert_macros(GFile &fin, GFile &fout, int left);
int parse_all(GFile &fin, GFile &fout);
