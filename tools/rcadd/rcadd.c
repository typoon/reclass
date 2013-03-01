#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "reclass.h"

void usage(char *prog_name) {
    printf("Usage: %s -i <input.class> -o <path> -j <code.jasm>\n", prog_name);
    printf("For information on accepted options use -h\n");
}

void help(char *prog_name) {
    usage(prog_name);
    printf("\n");
    printf("Help:\n");
    printf("  -o <path>         Output path for .class file\n");
    printf("  -i <File.class>   Input .class file\n");
    printf("  -j <File.jasm>    JASM file\n");
    printf("  -n <name>         Renames the class to <name>\n");
    printf("  -h                This help\n");
}

int main(int argc, char **argv)
{
    int i;
    int opt;
    int option_index;

    char output_path[255+1];
    char input_path[255+1];
    char jasm_path[255+1];
    char class_name[255+1];

    struct stat s_file;

    ClassFile cf;

    memset(output_path, 0, sizeof(output_path));
    memset(input_path, 0, sizeof(input_path));
    memset(jasm_path, 0, sizeof(input_path));
    memset(class_name, 0, sizeof(input_path));

    while((opt = getopt(argc, argv, "o:i:j:n:h")) != -1) {
        switch(opt) {
            case 'o':
                if(optarg == 0) {
                    break;
                }

                strncpy(output_path, optarg, sizeof(output_path)-1);
            break;

            case 'i':
                if(optarg == 0) {
                    break;
                }

                strncpy(input_path, optarg, sizeof(input_path)-1);

            break;

            case 'j':
                if(optarg == 0) {
                    break;
                }

                strncpy(jasm_path, optarg, sizeof(jasm_path)-1);
            break;

            case 'n':
                if(optarg == 0) {
                    break;
                }

                strncpy(class_name, optarg, sizeof(class_name)-1);
            break;

            case 'h':
                help(argv[0]);
                exit(0);
            break;

            case '?':
                printf("Unrecognized option %c.\n", optopt);
                printf("Aborting...\n");
                exit(-1);
            break;
        }
    }

    if(output_path[0] == 0) {
        usage(argv[0]);
        printf("A path for the output file needs to be specified.\n");
        exit(-1);
    }

    if(input_path[0] == 0) {
        usage(argv[0]);
        printf("An input file needs to be specified.\n");
        exit(-1);
    }

    if(jasm_path[0] == 0) {
        usage(argv[0]);
        printf("A jasm file needs to be specified.\n");
        exit(-1);
    }

    /* Validate output directory */

    if(stat(output_path, &s_file) < 0) {
        printf("Cannot verify output directory %s.\n", output_path);
        printf("Are you sure about what you are doing?\n");
        exit(-1);
    }

    if(!S_ISDIR(s_file.st_mode)) {
        printf("Path %s is not a valid directory.\n", output_path);
        printf("Aborting...");
        exit(-1);
    }

    if(class_name[0] == 0) {
        strncpy(class_name, basename(input_path), sizeof(class_name)-1);

        for(i = 0; i < strlen(class_name); i++) {
            if(class_name[i] == '.') {
                class_name[i] = '\0';
                break;
            }
        }
    }

    RC_ReadClassFile(input_path, &cf);

    if(RC_AddCodeFromAsm(&cf, jasm_path) != CF_OK) {
        printf("Error modifying ClassFile! Aborting...\n");
        return -1;
    }
    
    RC_BuildClassFile(&cf, output_path, class_name);
    
    return 0;
}
