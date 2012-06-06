#include <stdio.h>
#include "reclass/reclass.h"

int main(int argc, char **argv)
{
    ClassFile cf;

    if(argc < 3) {
        printf("Usage: %s <file.class> <file.jasm>\n", argv[0]);
        return -1;
    }

    RC_ReadClassFile(argv[1], &cf);

    if(RC_AddCodeFromAsm(&cf, argv[2]) != CF_OK) {
        printf("Error modifying ClassFile! Aborting...\n");
        return -1;
    }

    RC_BuildClassFile(&cf, "/tmp", "MyRebuiltClass");
    RC_DumpClassFile(&cf);

    return 0;

}
