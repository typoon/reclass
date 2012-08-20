#include <stdio.h>
#include "reclass.h"

void usage(char *prog_name)
{
    printf("Usage: %s <File.class>\n", prog_name);
}

int main(int argc, char **argv)
{
    
    ClassFile cf;
    
    if(argc < 2) {
        usage(argv[0]);
        return -1;
    }
    
    if(RC_ReadClassFile(argv[1], &cf) != CF_OK) {
        printf("Impossible to open file %s. "
               "Are you sure this is a java class?\n" , argv[1]);
        
        return -1;

    }
    
    RC_DumpClassFile(&cf);
    
    return 0;
}
