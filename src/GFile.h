#pragma once

class GFile
{
public:
	GFile();
	~GFile();

	int open(TCHAR *name, TCHAR *mode);
	void close();

	// read / write operations
	int read_byte();
	u16 read_u16_LE();
	u32 read_u32_LE();
	int write_byte(int buf);
	int write_u16_LE(u16 write);
	int write_u32_LE(u32 write);

	int copy_bytes(GFile &src, int len);
	int copy_pascal(GFile &src);

	// standard inlines
	__inline int getc()
	{
		return ::getc(handle);
	}

	__inline int putc(int _Ch)
	{
		return ::putc(_Ch, handle);
	}

	__inline size_t fwrite(const void *_Str, size_t Size, size_t Count)
	{
		return ::fwrite(_Str, Size, Count, handle);
	}

	__inline size_t fread(void *_Str, size_t Size, size_t Count)
	{
		return ::fread(_Str, Size, Count, handle);
	}

private:
	FILE *handle;
};
