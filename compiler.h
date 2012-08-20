#ifndef COMPILER_H_
#define COMPILER_H_

#include "reclass.h"

int yylex();
int yyparse();
void yyerror(const char *s);

#define SYM_METHOD 0
#define SYM_VAR    1

int compile(ClassFile *cf, char *file_path);

// Assembler functions
int method_start(ClassFile *cf, char *identifier, char *params);
int method_end(ClassFile *cf);

int create_int(ClassFile *cf, char *identifier, int value);

// Opcode functions
void jreturn();
void getstatic_int(ClassFile *cf, int index);
int getstatic_identifier(ClassFile *cf, char *identifier);
void pop();

#endif
