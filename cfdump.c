#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cfdump.h"
#include "helper.h"

#include "opcodes.h"


#define MAX_CODE_SIZE (1024 * 500)

void dumpAttribute(ClassFile *cf, attribute_info *ai);

char* parseMethodSignature(ClassFile *cf, method_info *mi);
char* parseFieldSignature(ClassFile *cf, field_info *fi);

char* accessFlagsToString(u2 flags);
char *fieldNameAndTypeToString(ClassFile *cf, NameAndType_info *nti);
char *fieldDescriptorIndexToString(ClassFile *cf, int index);
char *fieldrefToString(ClassFile *cf, Fieldref_info *fri);

char *methodNameAndTypeToString(ClassFile *cf, NameAndType_info *nti);
char *methodDescriptorIndexToString(ClassFile *cf, int index);
char *methodrefToString(ClassFile *cf, Methodref_info *mri);

char *nameIndexToString(ClassFile *cf, int index) {
    int length;
    char *ret;

    length = cf->constant_pool[index].utfi.length;

    ret = (char *)malloc(sizeof(char) * (length+1));
    memset(ret, 0, (length+1));

    memcpy(ret, cf->constant_pool[index].utfi.bytes, length);

    return ret;
}

char *descriptorIndexToString(ClassFile *cf, int index) {
    int length;
    char *ret;

    length = cf->constant_pool[index].utfi.length;

    ret = (char *)malloc(sizeof(char) * (length+1));
    memset(ret, 0, (length+1));

    memcpy(ret, cf->constant_pool[index].utfi.bytes, length);

    return ret;
}

char *fieldNameAndTypeToString(ClassFile *cf, NameAndType_info *nti) {
    int length;
    char *name;
    char *type;
    char *ret;

    name = nameIndexToString(cf, nti->name_index);

    type = fieldDescriptorIndexToString(cf, nti->descriptor_index);

    length = strlen(type) + strlen(name);
    ret = (char *)malloc(sizeof(char) * (length + 3));
    sprintf(ret, "%s %s;", type, name);

    free(name);
    free(type);

    return ret;
}

char *methodNameAndTypeToString(ClassFile *cf, NameAndType_info *nti) {
    int cp_index;
    char *ret;
    unsigned int i;
    unsigned int length;
    char parameters[512];
    char *name;
    char retType[64];
    char brackets[512];
    u1 bytes[512];

    ret = (char *)malloc(sizeof (char)* 1024);

    memset(ret, 0, 1024);
    memset(parameters, 0, sizeof (parameters));
    memset(retType, 0, sizeof (retType));
    memset(brackets, 0, sizeof (brackets));

    name = nameIndexToString(cf, nti->name_index);

    cp_index = nti->descriptor_index;
    length = cf->constant_pool[cp_index].utfi.length;
    memcpy(bytes, cf->constant_pool[cp_index].utfi.bytes, length);
    bytes[length] = '\0';

    i = 0;
    while(bytes[i] != ')') {
        switch(bytes[i++]) {
        case 'B':
            sprintf(parameters, "byte");
            break;

        case 'C':
            sprintf(parameters, "char");
            break;

        case 'D':
            sprintf(parameters, "double");
            break;

        case 'F':
            sprintf(parameters, "float");
            break;

        case 'I':
            sprintf(parameters, "int");
            break;

        case 'J':
            sprintf(parameters, "long");
            break;

        case 'S':
            sprintf(parameters, "short");
            break;

        case 'Z':
            sprintf(parameters, "bool");
            break;

        case 'L':
            while(bytes[i] != ';')
                parameters[strlen(parameters)] = bytes[i++];
            break;

        case '[':
            strcat(brackets, "[]");
            break;

        }
    }

    strcat(parameters, brackets);

    memset(brackets, 0, sizeof (brackets));
    while(bytes[i] != '\0') {
        switch(bytes[i++]) {
        case 'V':
            sprintf(retType, "void");
            break;

        case 'B':
            sprintf(retType, "byte");
            break;

        case 'C':
            sprintf(retType, "char");
            break;

        case 'D':
            sprintf(retType, "double");
            break;

        case 'F':
            sprintf(retType, "float");
            break;

        case 'I':
            sprintf(retType, "int");
            break;

        case 'J':
            sprintf(retType, "long");
            break;

        case 'S':
            sprintf(retType, "short");
            break;

        case 'Z':
            sprintf(retType, "bool");
            break;

        case 'L':
            while(bytes[i] != ';')
                retType[strlen(retType)] = bytes[i++];
            break;

        case '[':
            strcat(brackets, "[]");
            break;

        }
    }
    strcat(retType, brackets);

    sprintf(ret, "%s %s(%s)", retType, name, parameters);

    free(name);

    return ret;
}

char *fieldDescriptorIndexToString(ClassFile *cf, int index) {
    int i;
    int length;
    char data[1024 * 10]; // 10K
    char brackets[128];
    char *bytes;
    char *ret;

    length = cf->constant_pool[index].utfi.length;

    bytes = (char *)malloc(sizeof(char) * (length + 1));
    memset(bytes, 0, (length + 1));
    memset(brackets, 0, sizeof(brackets));

    memcpy(bytes, cf->constant_pool[index].utfi.bytes, length);
    bytes[length] = '\0';

    i = 0;

    memset(brackets, 0, sizeof (brackets));
    while(bytes[i] != '\0') {
        switch(bytes[i++]) {
        case 'V':
            sprintf(data, "void");
            break;

        case 'B':
            sprintf(data, "byte");
            break;

        case 'C':
            sprintf(data, "char");
            break;

        case 'D':
            sprintf(data, "double");
            break;

        case 'F':
            sprintf(data, "float");
            break;

        case 'I':
            sprintf(data, "int");
            break;

        case 'J':
            sprintf(data, "long");
            break;

        case 'S':
            sprintf(data, "short");
            break;

        case 'Z':
            sprintf(data, "bool");
            break;

        case 'L':
            while(bytes[i] != ';')
                data[strlen(data)] = bytes[i++];
            break;

        case '[':
            strcat(brackets, "[]");
            break;

        }
    }
    strcat(data, brackets);

    ret = (char *)malloc(sizeof(char) * (strlen(data) + 1));
    memcpy(ret, data, strlen(data));

    return ret;

}


char *fieldrefToString(ClassFile *cf, Fieldref_info *fri) {
    int totalLength;
    char *txt;
    char *className;
    char *nameAndType;

    className = nameIndexToString(cf, cf->constant_pool[fri->class_index].ci.name_index);
    nameAndType = fieldNameAndTypeToString(cf, &cf->constant_pool[fri->name_and_type_index].nti );

    totalLength = strlen(nameAndType) + strlen(className) + 128;

    txt = (char *)malloc(sizeof(char) * totalLength);
    memset(txt, 0, totalLength);

    sprintf(txt, "Class: %s - Field: %s", className, nameAndType);

    free(className);
    free(nameAndType);

    return txt;
}

char *methodrefToString(ClassFile *cf, Methodref_info *mri) {
    int totalLength;
    char *txt;
    char *className;
    char *nameAndType;

    className = nameIndexToString(cf, cf->constant_pool[mri->class_index].ci.name_index);
    nameAndType = methodNameAndTypeToString(cf, &cf->constant_pool[mri->name_and_type_index].nti );

    totalLength = strlen(nameAndType) + strlen(className) + 128;

    txt = (char *)malloc(sizeof(char) * totalLength);
    memset(txt, 0, totalLength);

    sprintf(txt, "Class: %s - Method: %s", className, nameAndType);

    free(className);
    free(nameAndType);

    return txt;
}

void RC_DumpClassFile(ClassFile *cf) {
    int i;
    int j;
    int index = 1;
    long long l;
    char *txt;

    printf("cf->magic = %08X\n", swapendi(cf->magic));
    printf("cf->major_version = %04X\n", swapends(cf->major_version));
    printf("cf->minor_version = %04X\n", swapends(cf->minor_version));

    printf("\n");
    printf("cf->constant_pool_count = %d\n", cf->constant_pool_count);

    for(i = index; i <= cf->constant_pool_count - 1; i++) {

        printf("\tIndex %d\n", index);

        switch(cf->constant_pool[index].tag) {
        case CONSTANT_CLASS:
            printf("\t\tCONSTANT_CLASS: name_index = %d\n",
                    cf->constant_pool[index].ci.name_index);
            txt = nameIndexToString(cf, cf->constant_pool[index].ci.name_index);
            printf("\t\tClass: %s\n", txt);
            free(txt);
            break;

        case CONSTANT_FIELDREF:
            printf("\t\tCONSTANT_FIELDREF: class_index = %d\n",
                    cf->constant_pool[index].fri.class_index);

            printf("\t\tCONSTANT_FIELDREF: name_and_type_index = %d\n",
                    cf->constant_pool[index].fri.name_and_type_index);

            txt = fieldrefToString(cf, &cf->constant_pool[index].fri);
            printf("\t\t%s \n", txt);
            free(txt);

            break;

        case CONSTANT_METHODREF:
            printf("\t\tCONSTANT_METHODREF: class_index = %d\n",
                    cf->constant_pool[index].mri.class_index);

            printf("\t\tCONSTANT_METHODREF: name_and_type_index = %d\n",
                    cf->constant_pool[index].mri.name_and_type_index);

            txt = methodrefToString(cf, &cf->constant_pool[index].mri);
            printf("\t\t%s \n", txt);
            free(txt);

            break;

        case CONSTANT_INTERFACEMETHODREF:
            printf("\t\tCONSTANT_INTERFACEMETHODREF: class_index = %d\n",
                    cf->constant_pool[index].imri.class_index);

            printf("\t\tCONSTANT_INTERFACEMETHODREF: name_and_type_index = %d\n",
                    cf->constant_pool[index].imri.name_and_type_index);
            break;

        case CONSTANT_STRING:
            printf("\t\tCONSTANT_STRING: string_index = %d\n",
                    cf->constant_pool[index].si.string_index);

            txt = nameIndexToString(cf, cf->constant_pool[index].si.string_index);
            printf("\t\tString: %s\n", txt);
            free(txt);

            break;

        case CONSTANT_INTEGER:
            printf("\t\tCONSTANT_INTEGER: bytes = %d\n",
                    cf->constant_pool[index].ii.bytes);
            break;

        case CONSTANT_FLOAT:
            printf("\t\tCONSTANT_FLOAT: bytes = %d\n",
                    cf->constant_pool[index].fi.bytes);
            break;

        case CONSTANT_LONG:
            printf("\t\tCONSTANT_LONG: high_bytes = %d\n",
                    cf->constant_pool[index].li.high_bytes);

            printf("\t\tCONSTANT_LONG: low_bytes = %d\n",
                    cf->constant_pool[index].li.low_bytes);

            l = ((long long)cf->constant_pool[index].li.high_bytes << 32) +
                    cf->constant_pool[index].li.low_bytes;

            printf("\t\tValue: %lld \n", l);

            break;

        case CONSTANT_DOUBLE:
            printf("\t\tCONSTANT_DOUBLE: high_bytes = %d\n",
                    cf->constant_pool[index].li.high_bytes);

            printf("\t\tCONSTANT_DOUBLE: low_bytes = %d\n",
                    cf->constant_pool[index].li.low_bytes);
            break;

        case CONSTANT_NAMEANDTYPE:
            printf("\t\tCONSTANT_NAMEANDTYPE: name_index = %d\n",
                    cf->constant_pool[index].nti.name_index);

            printf("\t\tCONSTANT_NAMEANDTYPE: descriptor_index = %d\n",
                    cf->constant_pool[index].nti.descriptor_index);
            break;

        case CONSTANT_UTF8:
            printf("\t\tCONSTANT_UTF8: length = %d\n",
                    cf->constant_pool[index].utfi.length);

            printf("\t\tCONSTANT_UTF8: bytes: ");

            // Need to use something to print utf-8 accordingly
            // I know nothing about this stuff :|
            for(j = 0; j < cf->constant_pool[index].utfi.length; j++) {
                printf("%c", cf->constant_pool[index].utfi.bytes[j]);
            }
            printf("\n");
            break;
        }


        ++index;
    }

    printf("\n");
    txt = accessFlagsToString(cf->access_flags);
    printf("cf->access_flags = 0x%02X [%s]\n", cf->access_flags, txt);
    free(txt);

    txt = nameIndexToString(cf, cf->constant_pool[cf->this_class].ci.name_index);
    printf("cf->this_class = %d  [%s]\n", cf->this_class, txt);
    free(txt);

    txt = nameIndexToString(cf, cf->constant_pool[cf->super_class].ci.name_index);
    printf("cf->super_class = %d [%s]\n", cf->super_class, txt);
    free(txt);

    printf("\n");
    printf("cf->interfaces_count = %d\n", cf->interfaces_count);
    RC_DumpInterfaces(cf);

    printf("\n");
    printf("cf->fields_count = %d\n", cf->fields_count);

    printf("\n");
    printf("cf->methods_count = %d\n", cf->methods_count);
    RC_DumpMethods(cf);

    printf("\n");
    printf("cf->attributes_count = %d\n", cf->attributes_count);
    for(i = 0; i < cf->attributes_count; i++) {
        dumpAttribute(cf, &cf->attributes[i]);
    }
}

char* accessFlagsToString(u2 flags) {
    char *txt;
    txt = (char *)malloc(sizeof (char)* 128);
    memset(txt, 0, sizeof (char)* 128);

    if(flags & ACC_STATIC)       sprintf(txt, "static ");
    if(flags & ACC_FINAL)        sprintf(txt, "final ");
    if(flags & ACC_VOLATILE)     sprintf(txt, "volatile ");
    if(flags & ACC_TRANSIENT)    sprintf(txt, "transient ");
    if(flags & ACC_ABSTRACT)     sprintf(txt, "abstract ");
    if(flags & ACC_SYNCHRONIZED) sprintf(txt, "synchronized ");
    if(flags & ACC_NATIVE)       sprintf(txt, "native ");
    if(flags & ACC_STRICT)       sprintf(txt, "strictfp ");

    if(flags & ACC_PUBLIC)    sprintf(txt, "public ");
    if(flags & ACC_PRIVATE)   sprintf(txt, "private ");
    if(flags & ACC_PROTECTED) sprintf(txt, "protected ");

    txt[strlen(txt) - 1] = '\0';

    return txt;
}

char* parseFieldSignature(ClassFile *cf, field_info *fi) {
    char *dump;
    char *txt;
    char parameters[512];
    char *name;
    char *retType;
    char brackets[512];

    dump = (char *)malloc(sizeof (char)* 1024);

    memset(dump, 0, 1024);
    memset(parameters, 0, sizeof (parameters));
    memset(brackets, 0, sizeof (brackets));

    name = nameIndexToString(cf, fi->name_index);
    retType = fieldDescriptorIndexToString(cf, fi->descriptor_index);

    txt = accessFlagsToString(fi->access_flags);
    sprintf(dump, "%s %s %s;", txt, retType, name);
    free(txt);
    free(name);
    free(retType);

    return dump;

}

char* parseMethodSignature(ClassFile *cf, method_info *mi) {
    int cp_index;
    char *dump;
    char *txt;
    unsigned int i;
    unsigned int length;
    char parameters[512];
    char *name;
    char retType[64];
    char brackets[512];
    u1 bytes[512];

    dump = (char *)malloc(sizeof (char)* 1024);

    memset(dump, 0, 1024);
    memset(parameters, 0, sizeof (parameters));
    memset(retType, 0, sizeof (retType));
    memset(brackets, 0, sizeof (brackets));


    name = nameIndexToString(cf, mi->name_index);

    cp_index = mi->descriptor_index;
    length = cf->constant_pool[cp_index].utfi.length;
    memcpy(bytes, cf->constant_pool[cp_index].utfi.bytes, length);
    bytes[length] = '\0';

    i = 0;
    while(bytes[i] != ')') {
        switch(bytes[i++]) {
        case 'B':
            sprintf(parameters, "byte");
            break;

        case 'C':
            sprintf(parameters, "char");
            break;

        case 'D':
            sprintf(parameters, "double");
            break;

        case 'F':
            sprintf(parameters, "float");
            break;

        case 'I':
            sprintf(parameters, "int");
            break;

        case 'J':
            sprintf(parameters, "long");
            break;

        case 'S':
            sprintf(parameters, "short");
            break;

        case 'Z':
            sprintf(parameters, "bool");
            break;

        case 'L':
            while(bytes[i] != ';')
                parameters[strlen(parameters)] = bytes[i++];
            break;

        case '[':
            strcat(brackets, "[]");
            break;

        }
    }

    strcat(parameters, brackets);

    memset(brackets, 0, sizeof (brackets));
    while(bytes[i] != '\0') {
        switch(bytes[i++]) {
        case 'V':
            sprintf(retType, "void");
            break;

        case 'B':
            sprintf(retType, "byte");
            break;

        case 'C':
            sprintf(retType, "char");
            break;

        case 'D':
            sprintf(retType, "double");
            break;

        case 'F':
            sprintf(retType, "float");
            break;

        case 'I':
            sprintf(retType, "int");
            break;

        case 'J':
            sprintf(retType, "long");
            break;

        case 'S':
            sprintf(retType, "short");
            break;

        case 'Z':
            sprintf(retType, "bool");
            break;

        case 'L':
            while(bytes[i] != ';')
                retType[strlen(retType)] = bytes[i++];
            break;

        case '[':
            strcat(brackets, "[]");
            break;

        }
    }
    strcat(retType, brackets);

    txt = accessFlagsToString(mi->access_flags);
    sprintf(dump, "%s %s %s(%s)", txt, retType, name, parameters);
    free(txt);
    free(name);

    return dump;

}

char* dumpCodeAssembly(Code_attribute *ca) {
    int j, k;
    int total;
    char *code;
    char opc[32];
    char instruction[32];
    char args[128];

    code = (char *)malloc(sizeof (char)* MAX_CODE_SIZE);
    memset(code, 0, MAX_CODE_SIZE);

    for(j = 0; j < ca->code_length; j++) {

        memset(opc, 0, sizeof(opc));
        sprintf(opc, "0x%02X", ca->code[j]);

        strcpy(instruction, opcodes_str[ca->code[j]]);

        memset(args, 0, sizeof (args));

        total = opcodes[ca->code[j]][1];
        for(k = 0; k < total; k++) {
            ++j;

            sprintf(args, "%s 0x%02X", args, ca->code[j]);
            sprintf(opc, "%s 0x%02X", opc, ca->code[j]);

        }
        sprintf(code, "%s [%s] %s %s\n", code, opc, instruction, args);
    }

    return code;
}

void RC_DumpMethods(ClassFile *cf) {
    int i;
    int j;
    char *txt;
    char *pchr;

    for(i = 0; i < cf->methods_count; i++) {

        printf("cf->methods[%d].attributes_count = %d\n", i, cf->methods[i].attributes_count);
        txt = parseMethodSignature(cf, &cf->methods[i]);
        printf("%s {\n", txt);
        free(txt);

        for(j = 0; j < cf->methods[i].attributes_count; j++) {
            if(memcmp(cf->constant_pool[cf->methods[i].attributes[j].attribute_name_index].utfi.bytes, ATTR_CODE, cf->constant_pool[cf->methods[i].attributes[j].attribute_name_index].utfi.length) == 0) {

                printf("\t// max_stack = %d\n", cf->methods[i].attributes[j].ca.max_stack);
                printf("\t// max_locals = %d\n", cf->methods[i].attributes[j].ca.max_locals);
                printf("\t// exception_table_length = %d\n", cf->methods[i].attributes[j].ca.exception_table_length);

                printf("\n");

                txt = dumpCodeAssembly(&cf->methods[i].attributes[j].ca);

                pchr = strtok(txt, "\n");
                while(pchr != NULL) {
                    printf("\t%s\n", pchr);
                    pchr = strtok(NULL, "\n");
                }
                free(txt);
            }
            //dumpAttributes(cf, cf->methods[i].attributes, cf->methods[i].attributes_count);
        }

        printf("}\n");


    }
}

void dumpAttribute(ClassFile *cf, attribute_info *ai) {
    int i;
    int length;
    char *txt;
    u1 tmpu1p[128];

    if(ai->attribute_length > 0) {
        length = cf->constant_pool[ai->attribute_name_index].utfi.length;

        memset(tmpu1p, 0, sizeof (tmpu1p));
        for(i = 0; i < length; i++)
            tmpu1p[i] = cf->constant_pool[ai->attribute_name_index].utfi.bytes[i];

        printf("\tAttribute: %s\n", tmpu1p);

        if(strncmp((const char *)tmpu1p, ATTR_CONSTANTVALUE, length) == 0) {
            printf("\t\tConstant pool index: %d\n", ai->cva.constantvalue_index);
        }

        if(strncmp((const char *)tmpu1p, ATTR_INNERCLASSES, length) == 0) {
            printf("\t\tNumber of classes: %d\n", ai->ica.number_of_classes);

            for(i = 0; i < ai->ica.number_of_classes; i++) {
                txt = accessFlagsToString(ai->ica.classes[i].inner_class_access_flags);
                printf("\t\tAccess flags: %s [%02X]\n", txt, ai->ica.classes[i].inner_class_access_flags);
                free(txt);

                txt = nameIndexToString(cf, ai->ica.classes[i].inner_name_index);
                printf("\t\tClass name: %s\n", txt);
                free(txt);

                printf("\t\tai->ica.classes[i].inner_class_info_index = %d\n", ai->ica.classes[i].inner_class_info_index);
                printf("\t\tai->ica.classes[i].outer_class_info_index = %d\n", ai->ica.classes[i].outer_class_info_index);


            }

        }
    }
}

void RC_DumpInterfaces(ClassFile *cf) {
    int i;
    char *txt;

    for(i = 0; i < cf->interfaces_count; i++) {

        txt = nameIndexToString(cf, cf->constant_pool[cf->interfaces[i]].ci.name_index);
        printf("Interface: %s\n", txt);
        free(txt);

    }
}
