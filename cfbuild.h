#ifndef CFBUILD_H
#define CFBUILD_H

#include "reclass.h"

static int buildConstantPool(ClassFile *cf, FILE *f);
static int buildInterfaces(ClassFile *cf, FILE *f);
static int buildAttributes(ClassFile *cf, attribute_info *ai, FILE *f);
static int buildFields(ClassFile *cf, FILE *f);
static int buildMethods(ClassFile *cf, FILE *f);

#endif  /* CFBUILD_H */

