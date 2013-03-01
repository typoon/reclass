.. highlight:: c

Example 1
=========

::

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

Example 2
=========

::

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "reclass.h"

	int main(int argc, char **argv)
	{
	    int MyMethodRef_index = 0;
	    int MyMethodStringIndex = 0;
	    u1 MyMethodOpc[1024 * 10];
	    u1 mainOpc[1024 * 10];
	    method_info *MyMethod;
	    method_info *mainMethod;

	    ClassFile cf;

	    if(argc < 2) {
	        printf("Usage: %s <File.class>\n", argv[0]);
	        return -1;
	    }

	    RC_ReadClassFile(argv[1], &cf);


	    // Create my method
	    MyMethodRef_index = RC_AddMethod(&cf, "MyMethod", "()V",
	            ACC_PUBLIC | ACC_STATIC, &MyMethod);

	    // Create the string
	    MyMethodStringIndex = (char)RC_CPAddString(&cf, "I am inside MyMethod :D");

	    // Code for main
	    memcpy(mainOpc, "\xB2\x00\x02", 3);     // getstatic 0x00 0x02
	    memcpy(&mainOpc[3], "\x12\x03", 2);     // ldc 0x03
	    memcpy(&mainOpc[5], "\xB6\x00\x04", 3); // invokevirtual 0x00 0x04
	    memcpy(&mainOpc[8], "\xB8\x00", 2);     // invokestatic MyMethodRef_index
	    mainOpc[10] = (char)MyMethodRef_index;  //
	    memcpy(&mainOpc[11], "\xB1", 1);        // return

	    // Code for myMethod
	    memcpy(MyMethodOpc, "\xB2\x00\x02", 3);     // getstatic 0x00 0x02
	    memcpy(&MyMethodOpc[3], "\x12", 1);         // ldc MyMethodString_index
	    MyMethodOpc[4] = (char)MyMethodStringIndex; //
	    memcpy(&MyMethodOpc[5], "\xB6\x00\x04", 3); // invokevirtual 0x00 0x04
	    memcpy(&MyMethodOpc[8], "\xB1", 1);         // return

	    // Change main code
	    mainMethod = RC_GetMethod(&cf, "main", "([Ljava/lang/String;)V");
	    // mainOpc is 12 bytes long
	    // Do not change the max_stack size
	    // Do not change the max_locals size
	    RC_ChangeMethodCodeAttribute(&cf, mainMethod, mainOpc, 12, 0, 0);

	    // Change code for MyMethod
	    // MyMethodOpc is 9 bytes long
	    // max_stack size is 2
	    // max_locals size is 0
	    RC_ChangeMethodCodeAttribute(&cf, MyMethod, MyMethodOpc, 9, 2, 0);

	    RC_BuildClassFile(&cf, "/tmp", "MyRebuiltClass");

	    return 0;

	}

Example 3
=========

::

	#include <stdio.h>
	#include <stdlib.h>
	#include "reclass.h"

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
	    //RC_DumpClassFile(&cf);

	    return 0;
	}
