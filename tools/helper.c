#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reclass.h"
#include "helper.h"

char *name_index_to_str(ClassFile *cf, int index) {
    int length;
    char *ret;

    length = cf->constant_pool[index].utfi.length;

    ret = (char *)malloc(sizeof(char) * (length+1));
    memset(ret, 0, (length+1));

    memcpy(ret, cf->constant_pool[index].utfi.bytes, length);

    return ret;
}


char* access_flags_to_str(u2 flags) {
    char *txt;
    txt = (char *)malloc(sizeof(char) * 128);
    memset(txt, 0, sizeof(char) * 128);

    if(flags & ACC_PUBLIC)    strcat(txt, "public ");
    if(flags & ACC_PRIVATE)   strcat(txt, "private ");
    if(flags & ACC_PROTECTED) strcat(txt, "protected ");

    if(flags & ACC_STATIC)       strcat(txt, "static ");
    if(flags & ACC_FINAL)        strcat(txt, "final ");
    if(flags & ACC_VOLATILE)     strcat(txt, "volatile ");
    if(flags & ACC_TRANSIENT)    strcat(txt, "transient ");
    if(flags & ACC_ABSTRACT)     strcat(txt, "abstract ");
    if(flags & ACC_SYNCHRONIZED) strcat(txt, "synchronized ");
    if(flags & ACC_NATIVE)       strcat(txt, "native ");
    if(flags & ACC_STRICT)       strcat(txt, "strictfp ");

    txt[strlen(txt) - 1] = '\0';

    return txt;
}


char* parse_method_signature(ClassFile *cf, method_info *mi) {
    int cp_index;
    int count = 0;
    int brackets;
    char *dump;
    char *txt;
    unsigned int i;
    unsigned int length;
    char parameters[512];
    char *name;
    char retType[64];
    //char brackets[512];
    u1 bytes[512];

    dump = (char *)malloc(sizeof (char)* 1024);

    memset(dump, 0, 1024);
    memset(parameters, 0, sizeof (parameters));
    memset(retType, 0, sizeof (retType));
    //memset(brackets, 0, sizeof (brackets));


    name = name_index_to_str(cf, mi->name_index);

    cp_index = mi->descriptor_index;
    length = cf->constant_pool[cp_index].utfi.length;
    memcpy(bytes, cf->constant_pool[cp_index].utfi.bytes, length);
    bytes[length] = '\0';

    i = 0;
    while(bytes[i] != ')') {
        switch(bytes[i++]) {
        case 'B':
            if(count > 0) {
                sprintf(parameters, "%s, byte", parameters);
            } else {
                sprintf(parameters, "byte");
            }

            if(brackets == 1) {
                strcat(parameters, "[]");
                brackets = 0;
            }
            count++;
        break;

        case 'C':
            if(count > 0) {
                sprintf(parameters, "%s, char", parameters);
            } else {
                sprintf(parameters, "char");
            }
            
            if(brackets == 1) {
                strcat(parameters, "[]");
                brackets = 0;
            }
            count++;
        break;

        case 'D':
            if(count > 0) {
                sprintf(parameters, "%s, double", parameters);
            } else {
                sprintf(parameters, "double");
            }
            
            if(brackets == 1) {
                strcat(parameters, "[]");
                brackets = 0;
            }
            count++;
        break;

        case 'F':
            if(count > 0) {
                sprintf(parameters, "%s, float", parameters);
            } else {
                sprintf(parameters, "float");
            }
            
            if(brackets == 1) {
                strcat(parameters, "[]");
                brackets = 0;
            }
            count++;
        break;

        case 'I':
            if(count > 0) {
                sprintf(parameters, "%s, int", parameters);
            } else {
                sprintf(parameters, "int");
            }
            
            if(brackets == 1) {
                strcat(parameters, "[]");
                brackets = 0;
            }
            count++;

        break;

        case 'J':
            if(count > 0) {
                sprintf(parameters, "%s, long", parameters);
            } else {
                sprintf(parameters, "long");
            }
            
            if(brackets == 1) {
                strcat(parameters, "[]");
                brackets = 0;
            }
            count++;
        break;

        case 'S':
            if(count > 0) {
                sprintf(parameters, "%s, short", parameters);
            } else {
                sprintf(parameters, "short");
            }
            
            if(brackets == 1) {
                strcat(parameters, "[]");
                brackets = 0;
            }
            count++;
        break;

        case 'Z':
            if(count > 0) {
                sprintf(parameters, "%s, bool", parameters);
            } else {
                sprintf(parameters, "bool");
            }
            
            if(brackets == 1) {
                strcat(parameters, "[]");
                brackets = 0;
            }
            count++;
        break;

        case 'L':
            if(count > 0) {
                parameters[strlen(parameters)] = ',';
                parameters[strlen(parameters)] = ' ';
                while(bytes[i] != ';')
                    parameters[strlen(parameters)] = bytes[i++];
            } else {
                while(bytes[i] != ';')
                    parameters[strlen(parameters)] = bytes[i++];
            }
            
            if(brackets == 1) {
                strcat(parameters, "[]");
                brackets = 0;
            }
            count++;
        break;

        case '[':
            brackets = 1;
        break;

        }
    }

    while(bytes[i] != '\0') {
        switch(bytes[i++]) {
        case 'V':
            sprintf(retType, "void");
            
            if(brackets == 1) {
                strcat(retType, "[]");
                brackets = 0;
            }

        break;

        case 'B':
            sprintf(retType, "byte");
            if(brackets == 1) {
                strcat(retType, "[]");
                brackets = 0;
            }

        break;

        case 'C':
            sprintf(retType, "char");
            if(brackets == 1) {
                strcat(retType, "[]");
                brackets = 0;
            }

        break;

        case 'D':
            sprintf(retType, "double");
            if(brackets == 1) {
                strcat(retType, "[]");
                brackets = 0;
            }

        break;

        case 'F':
            sprintf(retType, "float");
            if(brackets == 1) {
                strcat(retType, "[]");
                brackets = 0;
            }

        break;

        case 'I':
            sprintf(retType, "int");
            if(brackets == 1) {
                strcat(retType, "[]");
                brackets = 0;
            }

        break;

        case 'J':
            sprintf(retType, "long");
            if(brackets == 1) {
                strcat(retType, "[]");
                brackets = 0;
            }

        break;

        case 'S':
            sprintf(retType, "short");
            if(brackets == 1) {
                strcat(retType, "[]");
                brackets = 0;
            }

        break;

        case 'Z':
            sprintf(retType, "bool");
            if(brackets == 1) {
                strcat(retType, "[]");
                brackets = 0;
            }

        break;

        case 'L':
            while(bytes[i] != ';')
                retType[strlen(retType)] = bytes[i++];

            if(brackets == 1) {
                strcat(retType, "[]");
                brackets = 0;
            }

        break;

        case '[':
            brackets = 1;
        break;

        }
    }
//    strcat(retType, brackets);

    txt = access_flags_to_str(mi->access_flags);
    sprintf(dump, "%s %s %s(%s)", txt, retType, name, parameters);
    free(txt);
    free(name);

    return dump;

}
