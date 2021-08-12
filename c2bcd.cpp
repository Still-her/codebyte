#include <stdlib.h>
#include <iostream>
using namespace std;

template <typename Type, size_t N>
inline size_t GetArrayLength(const Type(&)[N])
{
    return N;
}

int c2bcd(char*p,char *num, int len)
{
	string tmp = p;
	char *stop;
	char c ;
	for(int i = 0; i < len ; ++i)
	{
		c = strtol(tmp.substr(2*i,2).c_str(), &stop, 16);
		printf("strtol = %x\n", c);
		num[len-i-1] = c;
	}
}

int main()
{
	char str[21] = "12345678";
	char num[4] = {0};
	c2bcd(str,num,4);
	for(int i = 0; i < sizeof(num) ; ++i)
	{
		printf("num = %x\n", num[i]);
	}
    return 0;
}
