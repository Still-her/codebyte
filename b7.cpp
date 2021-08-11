// b7.cpp
#include "cmn_inc.h"
#include "b7.h"

int str2b7(char *s, unsigned char *buf, int max)
{
	unsigned char *p = buf;
	unsigned char *ep = p + max;
	char          *es = s + strlen(s);

	unsigned short bs = 0;
	unsigned char  n  = 0;

	while (p < ep && s < es)
	{
		if (n < 8)
		{
			bs |= (*s++ & 0x7f) << n;
			n += 7;
		}
		if (n >= 8)
		{
			*p++ = bs & 0xff;
			bs >>= 8;
			n -= 8;
		}
	}

	if (n)
		*p++ = bs;

	return p - buf;
}

int b72str(unsigned char *p, int len, char *s, int max, int off)
{
	if (len >= max)
		len = max -1;

	unsigned char *ep = p + b7len(len);
	char          *es = s + len;

	unsigned short bs = 0;
	unsigned char  n  = 0;

	if (off)
	{
		bs = (*p++) >> off;
		n  = 8 - off;
	}

	while (p < ep && s < es)
	{
		if (n < 7)
		{
			bs |= (*p++) << n;
			n += 8;
		}

		*s++ = bs & 0x7f;
		bs >>= 7;
		n -= 7;
	}

	if (n >= 7 && s < es)
	{
		*s++ = bs & 0x7f;
		bs >>= 7;
		n -= 7;
	}

	*es = 0;

	return 0;
}

int b7len(int len)
{
	return ((len + 1) * 7) >> 3;
}
