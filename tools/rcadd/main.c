#include <stdio.h>
#include <string.h>
#include "reclass.h"

int main(int argc, char **argv)
{
    ClassFile cf;

    memset(&cf, 0, sizeof (cf));

    if(argc != 2) {
        printf("Use: %s <class_file.class>\n", argv[0]);
        return -1;
    }

    RC_ReadClassFile(argv[1], &cf);
    RC_DumpClassFile(&cf);

    return 0;
}