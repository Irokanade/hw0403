//
//  myprintf.h
//  hw0403
//
//  Created by michaelleong on 18/05/2021.
//

#ifndef myprintf_h
#define myprintf_h

#include <stdio.h>

int myprintf(char *format, ...);
int printFormat(char formatSpecifier, va_list arg);
int intToStr(int num, char* str, int base);
int getIntLen(int num);
int intToHexStr(int num, char *str, int base, char letter);
int my_fputs(char *str, FILE *file);
int getAscChar(int num, char letter);

#endif /* myprintf_h */
