//
//  myprintf.c
//  hw0403
//
//  Created by michaelleong on 18/05/2021.
//

#include "myprintf.h"
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int myprintf(char *format, ...) {
    char *formatCopy = (char*)calloc(strlen(format)+1, sizeof(char));
    strncpy(formatCopy, format, strlen(format));
    char *signPos = NULL;
    int signCount = 0;
    va_list arg;
    //puts(formatCopy);
    
    va_start(arg, format);
    signPos = strchr(formatCopy, '%');
       
    while(signPos != NULL) {
        signCount++;
        *signPos = 0;
        my_fputs(formatCopy, stdout);
        signPos++; //skip zero
        printFormat(*signPos, arg);
        signPos++; //skip format specifier
        formatCopy = signPos;
        signPos = strchr(formatCopy, '%');
    }
    
    my_fputs(formatCopy, stdout);
    
    va_end(arg);
    
    return signCount;
}

int printFormat(char formatSpecifier, va_list arg) {
    int integer = 0;
    int hexCap = 0;
    int hexLow = 0;
    int string = 0;
    
    switch(formatSpecifier) {
        case 'd':
            integer = 1;
            break;
        case 'i':
            integer = 1;
            break;
        case 'x':
            hexLow = 1;
            break;
        case 'X':
            hexCap = 1;
            break;
        case 's':
            string = 1;
            break;
        default:
            break;
            return 0;
    }
    
    if(integer) {
        int num = va_arg(arg, int);
        char *numTemp = calloc(getIntLen(num)+1, sizeof(char));
        intToStr(num, numTemp, 10);
        my_fputs(numTemp, stdout);
        free(numTemp);
    }
    
    if(hexLow) {
        int num = va_arg(arg, unsigned int);
        char *numTemp = calloc(getIntLen(num)+1, sizeof(char));
        intToHexStr(num, numTemp, 16, 'a');
        my_fputs(numTemp, stdout);
        free(numTemp);
    }
    
    if(hexCap) {
        int num = va_arg(arg, unsigned int);
        char *numTemp = calloc(getIntLen(num)+1, sizeof(char));
        intToHexStr(num, numTemp, 16, 'A');
        my_fputs(numTemp, stdout);
        free(numTemp);
    }
    
    if(string) {
        my_fputs(va_arg(arg, char*), stdout);
    }
    
    return 1;
}

int intToStr(int num, char *str, int base) {
    
    if(num == 0) {
        str[0] = '0';
        return 1;
    }
    
    if(num < 0) {
        num *= -1;
        char neg[2] = {0};
        neg[0] = '-';
        strncat(str, neg, 1);
    }
    
    int len = getIntLen(num);
    for(int i = len; i > 0; i--) {
        int intTemp = (int)num/(pow(base, i-1));
        num -= intTemp*pow(base, i-1);
        char intChar[2] = {0};
        intChar[0] = intTemp+'0';
        strncat(str, intChar, 1);
    }
    
    
    return 1;
}

int intToHexStr(int num, char *str, int base, char letter) {
    if(num == 0) {
        str[0] = '0';
        return 1;
    }
    
    while(num > 0) {
        char *temp = (char*)calloc(strlen(str)+1, sizeof(char));
        int intTemp = num % base;
        num /= base;
        char hexTemp[2] = {0};
        hexTemp[0] = getAscChar(intTemp, letter);
        strncpy(temp, str, strlen(str));
        memset(str, 0, strlen(str));
        strncpy(str, hexTemp, strlen(hexTemp));
        strncat(str, temp, strlen(temp));
    }
    
    return 1;
}

int getAscChar(int num, char letter) {
    //letter my be captial 'A' or lower case 'a'
    if(num > 9) {
        return num+letter-10;
    }
    
    return num+'0';
}

int getIntLen(int num) {
    int count = 0;
    
    while(num > 0) {
        num /= 10;
        count++;
    }
    
    return count;
}

int my_fputs(char *str, FILE *file) {
    for(char *i = str; *i != 0; i++) {
        fputc(*i, file);
    }
    
    return 1;
}
