//
//  hw0403.c
//  hw0403
//
//  Created by michaelleong on 14/05/2021.
//

#include <stdio.h>
#include "myprintf.h"


int main(int argc, char *argv[]) {
    int one = 65411;
    myprintf("Hi %X I love %s yes %d she is like a cat\n", one, "xinlin", -321);
    
    return 0;
}


