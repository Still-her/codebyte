// b7.h
#pragma once

int str2b7(char *s, unsigned char *buf, int max);
int b72str(unsigned char *p, int len, char *s, int max, int offset = 0);
int b7len(int len);
