// base64.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#include <iostream>
using namespace std;

static char CharSet[64]={
'A','B','C','D','E','F','G','H',
'I','J','K','L','M','N','O','P',
'Q','R','S','T','U','V','W','X',
'Y','Z','a','b','c','d','e','f',
'g','h','i','j','k','l','m','n',
'o','p','q','r','s','t','u','v',
'w','x','y','z','0','1','2','3',
'4','5','6','7','8','9','+','/'};
//---------------------------------------------------------------------------
//  Base64 code table
//  0-63 : A-Z(25) a-z(51), 0-9(61), +(62), /(63)
char  Base2Chr( unsigned char n )
{
	n &= 0x3F;
	return CharSet[n];
}
//---------------------------------------------------------------------------
unsigned char Chr2Base( char c )
{

	for(int i=0;i<=63;i++)
	{
		if(c==CharSet[i])
			return i;
	}
	return 64;
}

//---------------------------------------------------------------------------
//  aLen 为 aSrc 的长度， aDest 所指的缓冲区必须至少为 aLen 的 1.33 倍！！！
//  返回 aDest 的长度
int Base64Encode( char * const aDest, const unsigned char * aSrc, int aLen )
{
    char        * p = aDest;
    int           i;
    unsigned char t;

    for ( i = 0; i < aLen; i++ )
    {
        switch ( i % 3 )
        {
        case 0 :
            *p++ = Base2Chr( *aSrc >> 2 );
            t = ( *aSrc++ << 4 ) & 0x3F;
            break;
        case 1 :
            *p++ = Base2Chr( t | ( *aSrc >> 4 ) );
            t = ( *aSrc++ << 2 ) & 0x3F;
            break;
        case 2 :
            *p++ = Base2Chr( t | ( *aSrc >> 6 ) );
            *p++ = Base2Chr( *aSrc++ );
            break;
        }
    }
    if ( aLen % 3 != 0 )
    {
        *p++ = Base2Chr( t );
        if ( aLen % 3 == 1 )
            *p++ = '=';
        *p++ = '=';
    }
    *p = 0;  //  aDest is an ASCIIZ string
    return ( p - aDest );  //  exclude the end of zero
}
//---------------------------------------------------------------------------
//  aDest 所指的缓冲区必须至少为 aSrc 长度的 0.75 倍！！！
//  返回 aDest 的长度
int Base64Decode( unsigned char * const aDest, const char * aSrc )
{
    unsigned char * p = aDest;
    int             i, n = strlen( aSrc );
    unsigned char   c, t;

    for ( i = 0; i < n; i++ )
    {
        if ( *aSrc == '=' )
            break;
        do {
         if ( *aSrc )
        c = Chr2Base( *aSrc++ );
            else
             c = 65;  //  字符串结束
        } while ( c == 64 );  //  跳过无效字符，如回车等
        if ( c == 65 )
         break;
        switch ( i % 4 )
        {
        case 0 :
            t = c << 2;
            break;
        case 1 :
            *p++ = ( unsigned char )( t | ( c >> 4 ) );
            t = ( unsigned char )( c << 4 );
            break;
        case 2 :
            *p++ = ( unsigned char )( t | ( c >> 2 ) );
            t = ( unsigned char )( c << 6 );
            break;
        case 3 :
            *p++ = ( unsigned char )( t | c );
            break;
        }
    }
    return ( p - aDest );
}


int main(int argc, char* argv[])
{
	char text[100]="a1";
	char buff[100]="YTE=";

	char buff2[100];
	char buff3[100]="0";


	Base64Encode(buff2,(const unsigned char *)text,strlen(text));

	cout<<buff2<<endl;

	Base64Decode((unsigned char  *const)buff3,buff);
	cout<<buff3<<endl;
	for(int i=0;i<=8;i++)
	{
		cout<<(unsigned int)((unsigned char)buff3[i])<<endl;
	}


	return 0;
}