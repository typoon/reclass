#ifndef CFDUMP_H_
#define CFDUMP_H_

#include "classfile.h"

extern void RC_DumpClassFile(ClassFile *cf);
extern void RC_DumpMethods(ClassFile *cf);
extern void RC_DumpInterfaces(ClassFile *cf);

char *nameIndexToString(ClassFile *cf, int index);
char *descriptorIndexToString(ClassFile *cf, int index);

#endif