#include <stdio.h>
#include <string>
#include <string.h>
using namespace std;
static char g_chs[] = "0123456789*#abcf";
static char g_c2d[256];

void bcd_init()
{
	for (int i = 0; i < 16; ++i)
		g_c2d[(unsigned char)g_chs[i]] = i;
}

//fill=0xf0, 0
int str2bcd(const char *s, unsigned char *buf, unsigned max, unsigned char fill)
{
	unsigned slen = strlen(s);
	unsigned blen = slen >>  1;

	if (blen > max)
		blen = max;

	unsigned char lo, hi;
	for (unsigned i = 0; i < blen; ++i)
	{
		lo = g_c2d[(unsigned char)*s++];
		hi = g_c2d[(unsigned char)*s++];
		buf[i] = lo | (hi << 4);
	}

	if ((slen & 1) && (blen < max))
		buf[blen++] = g_c2d[(unsigned char)*s] | fill;

	return blen;
}


int bcd2str(unsigned char *buf, unsigned len, char *s, unsigned max)
{
	if(buf == NULL || len <= 0)
	{
		*s = 0;
		return 0;
	}
	
	unsigned mm = max >> 1;
	if (len > mm)
		len = mm;

	for (unsigned i = 0; i < len; ++i)
	{
		*s++ = g_chs[buf[i] & 0x0f];
		*s++ = g_chs[buf[i] >> 4];
	}

	if (s[-1] == 'f')
		s[-1] = 0;
	else if ((len << 1) < max)
		*s = 0;
	else
		s[-1] = 0;

	return 0;
}

int main()
{
	char gt[24];
	unsigned char buf[7] = {0x68,0x71,0x14,0x32,0x04,0x00,0xf2};
	
	unsigned char rbuf[24];
	
	bcd2str(buf,7,gt,24);
	
	//printf("%s\n",gt);
	
	bcd_init();
	
	str2bcd(gt, rbuf, 24, 0x00);
	
	//for(int i = 0; i < 24; ++i)
	//{
	//	printf("%x\n",rbuf[i]);
	//}

	unsigned char buf2[7] = {0x68,0x71,0x14,0x32,0x04,0x00,0x52};
	string tmp((char *)buf2, 7);
	for(int i = 0; i < tmp.size(); ++i)
	{
		printf("%x\n",tmp[i]);
	}
}