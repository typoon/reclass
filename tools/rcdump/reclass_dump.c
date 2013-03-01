#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include "reclass.h"
#include "helper.h"

#include "../opcodes.h"

#define MAX_CODE_SIZE (1024 * 500) // 500Kb should be enough 

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

void dump_method_code(ClassFile *cf, utf8 *name) {

    int i, j, k, l;
    int total;
    int found = 0;
    char *code;
    char *txt;
    char *pchr;
    char opc[32];
    char instruction[32];
    char args[128];
    Code_attribute *ca;
    Utf8_info *attr_name;

    for(i = 0; i < cf->methods_count; i++) {

        if(name != NULL) {
            
            if(memcmp(name->str, cf->constant_pool[cf->methods[i].name_index].utfi.bytes, name->length) != 0) {
                continue;
            }
        }

        found = 1;
        
        txt = parse_method_signature(cf, &cf->methods[i]);
        printf("%s {\n", txt);
        free(txt);

        for(j = 0; j < cf->methods[i].attributes_count; j++) {

            attr_name = &cf->constant_pool[cf->methods[i].attributes[j].attribute_name_index].utfi;

            printf("Reading attr: %s\n\n", attr_name->bytes);

            if(memcmp(attr_name->bytes, ATTR_CODE, attr_name->length) == 0) {

                printf("  // max_stack = %d\n",  cf->methods[i].attributes[j].ca.max_stack);
                printf("  // max_locals = %d\n", cf->methods[i].attributes[j].ca.max_locals);
                printf("  // exception_table_length = %d\n", cf->methods[i].attributes[j].ca.exception_table_length);


                printf("\n");

                ca = &cf->methods[i].attributes[j].ca;

                code = (char *)malloc(sizeof(char) * MAX_CODE_SIZE);
                memset(code, 0, MAX_CODE_SIZE);

                for(k = 0; k < ca->code_length; k++) {

                    memset(opc, 0, sizeof(opc));
                    sprintf(opc, "0x%02X", ca->code[k]);

                    strcpy(instruction, opcodes_str[ca->code[k]]);

                    memset(args, 0, sizeof(args));

                    total = opcodes[ca->code[k]][1];
                    
                    for(l = 0; l < total; l++) {
                        ++k;
                        sprintf(args, "%s 0x%02X", args, ca->code[k]);
                        sprintf(opc, "%s 0x%02X", opc, ca->code[k]);
                    }
                    
                    sprintf(code, "%s [%s] %s %s\n", code, opc, instruction, args);
                }

                pchr = strtok(code, "\n");
                while(pchr != NULL) {
                    printf(" %s\n", pchr);
                    pchr = strtok(NULL, "\n");
                }
                
                free(code);
            } else if(memcmp(attr_name->bytes, ATTR_LOCALVARIABLETABLE, attr_name->length) == 0) {

                for(k = 0; k < cf->methods[i].attributes[j].lvta.local_variable_table_length; k++) {
                    printf("Variable index %d\n", cf->methods[i].attributes[j].lvta.local_variable_table[k].index);
                }
                

            }
            
            //dumpAttributes(cf, cf->methods[i].attributes, cf->methods[i].attributes_count);
        }

        printf("}\n");
    }

    if(!found) {
        printf("Method not found...\n");
    }
}

void list_methods(ClassFile *cf) {

    u2 i;
    char *method_txt;
    method_info *m;

    printf("Methods count: %d\n", cf->methods_count);

    for(i = 0; i < cf->methods_count; i++) {
        m = &cf->methods[i];
        method_txt = parse_method_signature(cf, m);

        printf("  %s\n", method_txt);
        free(method_txt);
    }

}

int main(int argc, char **argv) {

    int opt;
    int option_index;
    ClassFile cf;
    utf8 str;

    static char *s_ops = "hd::lp::Df";

    static struct option l_ops[] = {
        {"help",             no_argument,       0, 'h'},
        {"dump-method-code", optional_argument, 0, 'd'},
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

        if(opt == '?') {
            help(argv[0]);
            return -1;            
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
                if(optarg == 0) {
                    str.length = strlen(optarg);
                    str.str = optarg;
                    dump_method_code(&cf, &str);
                } else {
                    dump_method_code(&cf, NULL);
                }

            break;

            case 'l':
                list_methods(&cf);
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
