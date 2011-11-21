#ifndef CFGET_H
#define	CFGET_H

#include "classfile.h"

extern method_info* RC_GetMethod(ClassFile *cf, char *name, char *signature);
extern int RC_GetMethodCode(ClassFile *cf, method_info *method, u1 *code, u4 length);
extern int RC_GetMethodCodeLength(ClassFile *cf, method_info *method);

#endif	/* CFGET_H */

