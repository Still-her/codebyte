//ucs2.h
#include <cmn_inc.h>
#include "ucs2.h"

// 1 0xxxxxxx 
// 2 110xxxxx 10xxxxxx 
// 3 1110xxxx 10xxxxxx 10xxxxxx 

// 4 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx 
// 5 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 
// 6 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 

int utf8_to_ucs2(char *s, unsigned char *p, int max)
{
	unsigned char *p0 = p;
	int len = strlen(s);
	for (int i = 0; i < len && max > 1; )
	{
		if ((*s & 0x80) == 0)
		{
			*p++ = 0;
			*p++ = *s++;
			i++;
		}
		else if ((*s & 0xe0) == 0xc0)
		{
			*p++ = (*s >> 2) & 7;
			*p++ = ((s[0] & 3) << 6) | (s[1] & 0x3f);
			s += 2;
			i += 2;

		}
		else if ((*s & 0xf0) == 0xe0)
		{
			*p++ = (*s << 4) | ((s[1] >> 2) & 0x0f);
			*p++ = (s[1] << 6) | (s[2] & 0x3f);
			s += 3;
			i += 3;
		}
		else if ((*s & 0xf8) == 0xf0)
		{
			s += 4;
			i += 4;
		}
		else if ((*s & 0xfc) == 0xf8)
		{
			s += 5;
			i += 5;
		}
		else if ((*s & 0xfe) == 0xfc)
		{
			s += 6;
			i += 6;
		}
		else
		{
			s++;
			i++;
		}
	}

	return p - p0;
}

int ucs2_to_utf8(unsigned char *p, int len, char *s, int max)
{
	char *s0 = s;
	int i;

	len &= -2;
	for (i = 0; i < len && max > 3; i += 2)
	{
		if (p[i] == 0 && p[i + 1] <= 0x7f)
		{
			*s++ = p[i + 1];
			max--;
		}
		else if ((p[i] & 0xf8) == 0)
		{
			*s++ = 0xc0 | (p[i] << 2) | (p[i + 1] >> 6);
			*s++ = 0x80 | (p[i + 1] & 0x3f);
		}
		else
		{
			*s++ = 0xe0 | (p[i] >> 4);
			*s++ = 0x80 | ((p[i] & 0x0f) << 2) | (p[i + 1] >> 6);
			*s++ = 0x80 | (p[i + 1] & 0x3f);
		}
	}

	if(i < len)
	{
		if (p[i] == 0 && p[i + 1] <= 0x7f && max > 1)
		{
			*s++ = p[1];
			max--;
		}
		else if ((p[i] & 0xf8) == 0 && max > 2)
		{
			*s++ = 0xc0 | (p[i] << 2) | (p[i + 1] >> 6);
			*s++ = 0x80 | (p[i + 1] & 0x3f);
		}
	}

	*s++ = 0;

	return s - s0;
}
