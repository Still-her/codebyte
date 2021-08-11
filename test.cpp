#include "b7.h"
#include "ucs2.h"
#include <string>
#include <string.h>
#include <iostream>
#include <stdio.h>
using namespace std;

unsigned char MsgContent1[140];
unsigned char MsgContent2[140];

char mymsg1[140];

char mymsg2[140];


int main()
{
	int length = 159;
	int bytee = b7len(length);
	printf("bytee:%d\n\n",bytee);
	
	char* str = "testhelloworldhelloworld";
	str2b7(str, MsgContent1, bytee);
	str2b7(str+length, MsgContent2, b7len(14));
	
	//cout << "str: " << str << endl;
	//cout << "MsgContent1: " << MsgContent1 << endl;
	
	b72str(MsgContent1, length, mymsg1, 140);	
	b72str(MsgContent2, 14,  mymsg2, 140);	
	
	cout << "mymsg1: " << mymsg1 << endl;
	cout << "mymsg2: " << mymsg2 << endl;
	
}