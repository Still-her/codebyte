// ucs2/h
#pragma once

int utf8_to_ucs2(char *s, unsigned char *p, int max);
int ucs2_to_utf8(unsigned char *p, int len, char *s, int max);
