#ifndef RECLASS_H
#define RECLASS_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "classfile.h"
//#include "opcodes.h"


/* classfile.c */
extern int RC_ReadClassFile(char *path, ClassFile *cf);

/* cfbuild.c */
extern int RC_BuildClassFile(ClassFile *cf, char *path, char *name);

/* cfget.c */
extern int RC_CPGetMethodRefIndexCurrentClass(ClassFile *cf, char *name, char *signature);
extern int RC_CPGetMethodRefIndex(ClassFile *cf, char *name, char *signature, char *className);

extern int RC_GetMethodIndex(ClassFile *cf, char *name, char *signature);
extern method_info* RC_GetMethod(ClassFile *cf, char *name, char *signature);
extern int RC_GetMethodCode(ClassFile *cf, method_info *method, u1 *code, u4 length);
extern int RC_GetMethodCodeLength(ClassFile *cf, method_info *method);

/* cfmodify.c */

// Constant Pool Manipulation
extern int RC_CPAddClass(ClassFile *cf, char *name);
extern int RC_CPAddFieldRef(ClassFile *cf, char *className, char *fieldName, char *fieldType);
extern int RC_CPAddString(ClassFile *cf, char *value);
extern int RC_CPAddInteger(ClassFile *cf, u4 value);
extern int RC_CPAddFloat(ClassFile *cf, float value);
extern int RC_CPAddLong(ClassFile *cf, long value);
extern int RC_CPAddDouble(ClassFile *cf, double value);
extern int RC_CPAddUtf8(ClassFile *cf, char *value, int length);
extern int RC_CPAddNameAndType(ClassFile *cf, char *name, char *type);
extern int RC_CPAddMethodRef(ClassFile *cf, int class_index, int nameAndType_index);
//cpAddInterfaceMethodRef(ClassFile *cf,

// Class Methods Manipulation
extern int RC_ChangeCodeAttribute(ClassFile *cf, char *method, u1 *code, int code_length, int max_stack, int max_locals);
extern int RC_ChangeMethodCodeAttribute(ClassFile *cf, method_info *method, u1 *code, int code_length, int max_stack, int max_locals);
extern int RC_AddMethod(ClassFile *cf, char *name, char *descriptor, int access_flags, method_info **method);

// Class manipulation
extern int RC_RenameClass(ClassFile *cf, char *name);

// The ultimate stuff!
extern int RC_AddCodeFromAsm(ClassFile *cf, char *file_path);

/* cfdump.c */
extern void RC_DumpClassFile(ClassFile *cf);
extern void RC_DumpMethods(ClassFile *cf);
extern void RC_DumpInterfaces(ClassFile *cf);

#ifdef  __cplusplus
}
#endif

#endif  /* RECLASS_H */

