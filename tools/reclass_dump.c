#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include "reclass.h"

void usage(char *prog_name) {
    printf("Usage: %s <options> <File.class>\n", prog_name);
    printf("For information on accepted options use --help or -h\n");
}

void help(char *prog_name) {
    usage(prog_name);
    printf("Help:\n");
    printf("  -h, --help                      Shows this help\n");
    printf("  -d, --dump-method-code[=METHOD] Dumps the assembly code for METHOD\n");
    printf("                                  Dumps the code for all methods if METHOD\n");
    printf("                                  is not specified\n");
    printf("  -l, --list-methods              Lists all methods found in the class\n");
    printf("  -p, --dump-cpool[=INDEX]        Dumps the constant pool at INDEX or\n");
    printf("                                  the whole constant pool\n");
    printf("  -D, --dump-all                  Dumps all information available\n");
    printf("                                  about <File.class>\n");
}

int main(int argc, char **argv) {

    int opt;
    int option_index;
    ClassFile cf;

    static char *s_ops = "hd:lp::Df";

    static struct option l_ops[] = {
        {"help",             no_argument,       0, 'h'},
        {"dump-method-code", required_argument, 0, 'd'},
        {"list-methods",     no_argument,       0, 'l'},
        {"dump-cpool",       optional_argument, 0, 'p'},
        {"dump-all",         no_argument,       0, 'D'},
        {0,                  0,                 0, 0  }        
    };
    
    if(argc < 2) {
        usage(argv[0]);
        return -1;
    }

    optind = 1;
    while((opt = getopt_long(argc, argv, s_ops, l_ops, &option_index)) != -1) {
        if(opt == 'h') {
            help(argv[0]);
            return 0;
        }

    }

    if(RC_ReadClassFile(argv[argc-1], &cf) != CF_OK) {
        printf("Impossible to open file %s. "
               "Are you sure this is a java class?\n" , argv[argc-1]);
        
        return -1;
    }

    optind = 1;
    while((opt = getopt_long(argc, argv, s_ops, l_ops, &option_index)) != -1) {
        switch(opt) {
            case 'd':
                
            break;

            case 'l':
            break;

            case 'p':
            break;

            case 'D':
                RC_DumpClassFile(&cf);
            break;


            case '?':
            break;
            
        }
        
        
    }
    
    
    
    return 0;
}
