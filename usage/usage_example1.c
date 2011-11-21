#include <stdio.h>
#include "reclass.h"

u1 opc[] = {
    0x10, 0x63,       // bipush  0x63
    0x3C,             // istore_1
    0xB2, 0x00, 0x02, // getstatic  0x00 0x02
    0xBB, 0x00, 0x03, // new  0x00 0x03
    0x59,             // dup
    0xB7, 0x00, 0x04, // invokespecial  0x00 0x04
    0x12, 0x05,       // ldc  0x05
    0xB6, 0x00, 0x06, // invokevirtual  0x00 0x06
    0x1B,             // iload_1
    0xB6, 0x00, 0x07, // invokevirtual  0x00 0x07
    0xB6, 0x00, 0x08, // invokevirtual  0x00 0x08
    0xB6, 0x00, 0x09, // invokevirtual  0x00 0x09
    0xB2, 0x00, 0x02, // getstatic 00 02
    0x12, 0x2B,       // ldc 2B
    0xB6, 0x00, 0x09, // invokevirtual 00 09
    0xB1              // return
};

int main(int argc, char **argv)
{
    ClassFile cf;
    method_info *method;


    if(argc < 2) {
        printf("Usage: %s <File.class>\n", argv[0]);
        return -1;
    }

    RC_ReadClassFile(argv[1], &cf);

    RC_CPAddString(&cf, "Added code!");

    method = RC_GetMethod(&cf, "main", "([Ljava/lang/String;)V");
    if(method == NULL) {
        printf("Method not found. Aborting...\n");
        return -1;
    }

    RC_ChangeMethodCodeAttribute(&cf, method, opc, sizeof(opc), 0, 0);

    RC_BuildClassFile(&cf, "/tmp", "MyRebuiltClass");

    printf("this_class = %d\n", cf.this_class);
    RC_DumpClassFile(&cf);

    return 0;

}