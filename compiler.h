#ifndef COMPILER_H_
#define COMPILER_H_

#include "reclass.h"

int yylex();
int yyparse();
void yyerror(const char *s);

int compile(ClassFile *cf, char *file_path);

// Assembler functions
int method_start(ClassFile *cf, char *identifier, char *params);
int method_end(ClassFile *cf);

int create_int(ClassFile *cf, char *identifier, int value);
int create_byte(ClassFile *cf, char *identifier, unsigned char value);

// Opcode functions
int nop();
int aconstnull();
int iconstm1();
int iconst0();
int iconst1();
int iconst2();
int iconst3();
int iconst4();
int iconst5();
int lconst0();
int lconst1();
int fconst0();
int fconst1();
int fconst2();
int dconst0();
int dconst1();

int bipush_byte(unsigned char byte);
int bipush_identifier(char *identifier);

int sipush_short(int s);
int sipush_identifier(char *identifier);

int ldc_byte(ClassFile *cf, unsigned char byte);
int ldc_identifier(ClassFile *cf, char *identifier);

int jreturn();
int getstatic_int(ClassFile *cf, int index);
int getstatic_identifier(ClassFile *cf, char *identifier);
int pop();

#endif
