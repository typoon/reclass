#ifndef PARSER_H_
#define PARSER_H_

#include "reclass.h"

int parse(ClassFile *cf, char *file_path);
int method_start(ClassFile *cf, char *identifier, char *params);
int method_end(ClassFile *cf);

// Opcode functions
void getstatic_int(ClassFile *cf, int index);

#endif
