#include <stdio.h>
#include "reclass.h"

int main(int argc, char **argv)
{
    ClassFile cf;
    method_info *method;


    if(argc < 2) {
        printf("Usage: %s <File.class>\n", argv[0]);
        return -1;
    }

    RC_ReadClassFile(argv[1], &cf);

    if(RC_AddCodeFromAsm(&cf, "usage_example3.jasm") != CF_OK) {
        printf("Error modifying ClassFile! Aborting...\n");
        return -1;
    }

    RC_BuildClassFile(&cf, "/tmp", "MyRebuiltClass");
    RC_DumpClassFile(&cf);

    return 0;

}
