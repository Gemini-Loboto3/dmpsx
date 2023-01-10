/* ======================================== *
 * Simple FILE helper class.				*
 * ======================================== */
#include "stdafx.h"
#include "GFile.h"

GFile::GFile()
{
	handle = nullptr;
}

GFile::~GFile()
{
	if (handle != nullptr)
		fclose(handle);
}

int GFile::open(TCHAR *name, TCHAR *mode)
{
	handle = _tfopen(name, mode);

	if (!handle)
	{
		handle = nullptr;
		return FALSE;
	}
	return TRUE;
}

void GFile::close()
{
	if (handle != nullptr)
	{
		fclose(handle);
		handle = nullptr;
	}
}

int GFile::write_byte(int buf)
{
	extern u32 some_dword;

	if (some_dword) return 0;

	fputc(buf, handle);
	//--handle->_cnt;
	//if (handle->_cnt < 0)
	//	_flsbuf(buf, handle);
	//else
	//	*handle->_ptr++ = buf;

	return 1;
}

int GFile::read_byte()
{
	return fgetc(handle);
	//--handle->_cnt;
	//if (handle->_cnt < 0)
	//	return _filbuf(handle);

	//return *handle->_ptr++;
}

u16 GFile::read_u16_LE()
{
	u16 read;

	fread(&read, 2, 1);
	return read;
}

int GFile::write_u16_LE(u16 write)
{
	fwrite(&write, 2, 1);
	return 1;
}

u32 GFile::read_u32_LE()
{
	u32 read;

	fread(&read, 4, 1);
	return read;
}

int GFile::write_u32_LE(u32 write)
{
	fwrite(&write, 4, 1);
	return 1;
}

int GFile::copy_bytes(GFile &src, int len)
{
	while (len > 0)
	{
		write_byte(src.read_byte());
		--len;
	}

	return 1;
}

int GFile::copy_pascal(GFile &src)
{
	int byte, len;

	len = src.read_byte();
	write_byte(len);
	while (1)
	{
		byte = len--;
		if (!byte) break;
		copy_bytes(src, 1);
	}
	return 1;
}
