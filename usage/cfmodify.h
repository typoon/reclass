#ifndef CFMODIFY_H_
#define CFMODIFY_H_

#include "classfile.h"

// Internal helpers


// Exported stuff

// Constant Pool Manipulation
extern int RC_CPAddClass(ClassFile *cf, char *name);
extern int RC_CPAddFieldRef(ClassFile *cf, char *className, char *fieldName, char *fieldType);
//cpAddInterfaceMethodRef(ClassFile *cf,
extern int RC_CPAddString(ClassFile *cf, char *value);
extern int RC_CPAddInteger(ClassFile *cf, u4 value);
extern int RC_CPAddFloat(ClassFile *cf, float value);
extern int RC_CPAddLong(ClassFile *cf, long value);
extern int RC_CPAddDouble(ClassFile *cf, double value);
extern int RC_CPAddUtf8(ClassFile *cf, char *value, int length);

extern int RC_CPAddNameAndType(ClassFile *cf, char *name, char *type);
extern int RC_CPAddMethodRef(ClassFile *cf, int class_index, int nameAndType_index);

// Class Methods Manipulation
extern int RC_ChangeCodeAttribute(ClassFile *cf, char *method, u1 *code, int code_length, int max_stack, int max_locals);
extern int RC_ChangeMethodCodeAttribute(ClassFile *cf, method_info *method, u1 *code, int code_length, int max_stack, int max_locals);
extern int RC_AddMethod(ClassFile *cf, char *name, char *descriptor, int access_flags, method_info **method);

// Class manipulation
extern int RC_RenameClass(ClassFile *cf, char *name);

// The ultimate stuff!
int RC_AddCodeFromAsm(ClassFile *cf, char *file_path);

#endif
