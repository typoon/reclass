%{
#include <stdio.h>
#include "reclass.h"
#include "helper.h"
#include "parser.h"

#define YYPARSE_PARAM cf

int yylex();
int yyparse();
FILE *yyin;
 
void yyerror(const char *s);

buffer *code;
int current_method;
int current_max_stack;
int current_max_locals;


%}

%union {
    int int_val;
    double double_val;
    char *str_val;
    char *identifier;
    char *param;
    int visibility;
}

%token <int_val>    INT
%token <double_val> DOUBLE
%token <str_val>    STRING


/* General asm identifiers */
%token VAR_INT
%token VAR_STRING
%token VAR_DOUBLE

%token <identifier> IDENTIFIER

%token METHOD_START
%token <param> PARAMS
%token METHOD_END
%token <visibility> VISIBILITY

/* Opcodes */
%token NOP
%token ACONST_NULL
%token ICONST_M1
%token ICONST_0
%token ICONST_1
%token ICONST_2
%token ICONST_3
%token ICONST_4
%token ICONST_5
%token LCONST_0
%token LCONST_1
%token FCONST_0
%token FCONST_1
%token FCONST_2
%token DCONST_0
%token DCONST_1
%token BIPUSH
%token SIPUSH
%token LDC
%token LDC_W
%token LDC2_W
%token ILOAD
%token LLOAD
%token FLOAD
%token DLOAD
%token ALOAD
%token ILOAD_0
%token ILOAD_1
%token ILOAD_2
%token ILOAD_3
%token LLOAD_0
%token LLOAD_1
%token LLOAD_2
%token LLOAD_3
%token FLOAD_0
%token FLOAD_1
%token FLOAD_2
%token FLOAD_3
%token DLOAD_0
%token DLOAD_1
%token DLOAD_2
%token DLOAD_3
%token ALOAD_0
%token ALOAD_1
%token ALOAD_2
%token ALOAD_3
%token IALOAD
%token LALOAD
%token FALOAD
%token DALOAD
%token AALOAD
%token BALOAD
%token CALOAD
%token SALOAD
%token ISTORE
%token LSTORE
%token FSTORE
%token DSTORE
%token ASTORE
%token ISTORE_0
%token ISTORE_1
%token ISTORE_2
%token ISTORE_3
%token LSTORE_0
%token LSTORE_1
%token LSTORE_2
%token LSTORE_3
%token FSTORE_0
%token FSTORE_1
%token FSTORE_2
%token FSTORE_3
%token DSTORE_0
%token DSTORE_1
%token DSTORE_2
%token DSTORE_3
%token ASTORE_0
%token ASTORE_1
%token ASTORE_2
%token ASTORE_3
%token IASTORE
%token LASTORE
%token FASTORE
%token DASTORE
%token AASTORE
%token BASTORE
%token CASTORE
%token SASTORE
%token POP
%token POP2
%token DUP
%token DUP_X1
%token DUP_X2
%token DUP2
%token DUP2_X1
%token DUP2_X2
%token SWAP
%token IADD
%token LADD
%token FADD
%token DADD
%token ISUB
%token LSUB
%token FSUB
%token DSUB
%token IMUL
%token LMUL
%token FMUL
%token DMUL
%token IDIV
%token LDIV
%token FDIV
%token DDIV
%token IREM
%token LREM
%token FREM
%token DREM
%token INEG
%token LNEG
%token FNEG
%token DNEG
%token ISHL
%token LSHL
%token ISHR
%token LSHR
%token IUSHR
%token LUSHR
%token IAND
%token LAND
%token IOR
%token LOR
%token IXOR
%token LXOR
%token IINC
%token I2L
%token I2F
%token I2D
%token L2I
%token L2F
%token L2D
%token F2I
%token F2L
%token F2D
%token D2I
%token D2L
%token D2F
%token I2B
%token I2C
%token I2S
%token LCMP
%token FCMPL
%token FCMPG
%token DCMPL
%token DCMPG
%token IFEQ
%token IFNE
%token IFLT
%token IFGE
%token IFGT
%token IFLE
%token IF_ICMPEQ
%token IF_ICMPNE
%token IF_ICMPLT
%token IF_ICMPGE
%token IF_ICMPGT
%token IF_ICMPLE
%token IF_ACMPEQ
%token IF_ACMPNE
%token GOTO
%token JSR
%token RET
%token TABLESWITCH
%token LOOKUPSWITCH
%token IRETURN
%token LRETURN
%token FRETURN
%token DRETURN
%token ARETURN
%token RETURN
%token GETSTATIC
%token PUTSTATIC
%token GETFIELD
%token PUTFIELD
%token INVOKEVIRTUAL
%token INVOKESPECIAL
%token INVOKESTATIC
%token INVOKEINTERFACE
%token NEW
%token NEWARRAY
%token ANEWARRAY
%token ARRAYLENGTH
%token ATHROW
%token CHECKCAST
%token INSTANCEOF
%token MONITORENTER
%token MONITOREXIT
%token WIDE
%token MULTIANEWARRAY
%token IFNULL
%token IFNONNULL
%token GOTO_W
%token JSR_W
%token BREAKPOINT
%token LDC_QUICK
%token LDC_W_QUICK
%token LDC2_W_QUICK
%token GETFIELD_QUICK
%token PUTFIELD_QUICK
%token GETFIELD2_QUICK
%token PUTFIELD2_QUICK
%token GETSTATIC_QUICK
%token PUTSTATIC_QUICK
%token GETSTATIC2_QUICK
%token PUTSTATIC2_QUICK
%token INVOKEVIRTUAL_QUICK
%token INVOKENONVIRTUAL_QUICK
%token INVOKESUPER_QUICK
%token INVOKESTATIC_QUICK
%token INVOKEINTERFACE_QUICK
%token INVOKEVIRTUALOBJECT_QUICK
%token INVOKEIGNORED_QUICK
%token NEW_QUICK
%token ANEWARRAY_QUICK
%token MULTIANEWARRAY_QUICK
%token CHECKCAST_QUICK
%token INSTANCEOF_QUICK
%token INVOKEVIRTUAL_QUICK_W
%token GETFIELD_QUICK_W
%token PUTFIELD_QUICK_W
%token NONNULL_QUICK
%token SOFTWARE
%token HARDWARE

%%


start:
    identifiers methods
    | identifiers
    | methods
    ;

identifiers:
    identifiers VAR_INT IDENTIFIER INT
    | identifiers VAR_DOUBLE IDENTIFIER DOUBLE
    | identifiers VAR_STRING IDENTIFIER STRING
    | identifiers VAR_INT IDENTIFIER
    | identifiers VAR_DOUBLE IDENTIFIER
    | identifiers VAR_STRING IDENTIFIER
    | VAR_INT IDENTIFIER INT
    | VAR_DOUBLE IDENTIFIER DOUBLE
    | VAR_STRING IDENTIFIER STRING
    | VAR_INT IDENTIFIER
    | VAR_DOUBLE IDENTIFIER
    | VAR_STRING IDENTIFIER
    ;

methods:
    methods method_start method_body method_end
    | method_start method_body method_end
    ;

method_start:
    METHOD_START IDENTIFIER PARAMS { if(method_start((ClassFile *)cf, $2, $3) < 0) YYABORT; }
    ;
    
method_body:
    identifiers
    | mnemonics
    | identifiers mnemonics
    ;

method_end:
    METHOD_END { if(method_end((ClassFile *)cf) < 0) YYABORT; }
    ;

/*
 Why does this rule does not work?

method_body:
    identifiers mnemonics
    ;
*/


nop:
    NOP
    ;

mnemonics:
    mnemonics opcode
    | opcode
    ;

opcode:
    nop
/*
    | nop
    | aconst_null
    | iconst_m1
    | iconst_0
    | iconst_1
    | iconst_2
    | iconst_3
    | iconst_4
    | iconst_5
    | lconst_0
    | lconst_1
    | fconst_0
    | fconst_1
    | fconst_2
    | dconst_0
    | dconst_1
    | bipush
    | sipush
    | ldc
    | ldc_w
    | ldc2_w
    | iload
    | lload
    | fload
    | dload
    | aload
    | iload_0
    | iload_1
    | iload_2
    | iload_3
    | lload_0
    | lload_1
    | lload_2
    | lload_3
    | fload_0
    | fload_1
    | fload_2
    | fload_3
    | dload_0
    | dload_1
    | dload_2
    | dload_3
    | aload_0
    | aload_1
    | aload_2
    | aload_3
    | iaload
    | laload
    | faload
    | daload
    | aaload
    | baload
    | caload
    | saload
    | istore
    | lstore
    | fstore
    | dstore
    | astore
    | istore_0
    | istore_1
    | istore_2
    | istore_3
    | lstore_0
    | lstore_1
    | lstore_2
    | lstore_3
    | fstore_0
    | fstore_1
    | fstore_2
    | fstore_3
    | dstore_0
    | dstore_1
    | dstore_2
    | dstore_3
    | astore_0
    | astore_1
    | astore_2
    | astore_3
    | iastore
    | lastore
    | fastore
    | dastore
    | aastore
    | bastore
    | castore
    | sastore
    | pop
    | pop2
    | dup
    | dup_x1
    | dup_x2
    | dup2
    | dup2_x1
    | dup2_x2
    | swap
    | iadd
    | ladd
    | fadd
    | dadd
    | isub
    | lsub
    | fsub
    | dsub
    | imul
    | lmul
    | fmul
    | dmul
    | idiv
    | ldiv
    | fdiv
    | ddiv
    | irem
    | lrem
    | frem
    | drem
    | ineg
    | lneg
    | fneg
    | dneg
    | ishl
    | lshl
    | ishr
    | lshr
    | iushr
    | lushr
    | iand
    | land
    | ior
    | lor
    | ixor
    | lxor
    | iinc
    | i2l
    | i2f
    | i2d
    | l2i
    | l2f
    | l2d
    | f2i
    | f2l
    | f2d
    | d2i
    | d2l
    | d2f
    | i2b
    | i2c
    | i2s
    | lcmp
    | fcmpl
    | fcmpg
    | dcmpl
    | dcmpg
    | ifeq
    | ifne
    | iflt
    | ifge
    | ifgt
    | ifle
    | if_icmpeq
    | if_icmpne
    | if_icmplt
    | if_icmpge
    | if_icmpgt
    | if_icmple
    | if_acmpeq
    | if_acmpne
    | goto
    | jsr
    | ret
    | tableswitch
    | lookupswitch
    | ireturn
    | lreturn
    | freturn
    | dreturn
    | areturn
    | return
*/
    | getstatic
/*
    | putstatic
    | getfield
    | putfield
    | invokevirtual
    | invokespecial
    | invokestatic
    | invokeinterface
    | new
    | newarray
    | anewarray
    | arraylength
    | athrow
    | checkcast
    | instanceof
    | monitorenter
    | monitorexit
    | wide
    | multianewarray
    | ifnull
    | ifnonnull
    | goto_w
    | jsr_w
    | breakpoint
    | ldc_quick
    | ldc_w_quick
    | ldc2_w_quick
    | getfield_quick
    | putfield_quick
    | getfield2_quick
    | putfield2_quick
    | getstatic_quick
    | putstatic_quick
    | getstatic2_quick
    | putstatic2_quick
    | invokevirtual_quick
    | invokenonvirtual_quick
    | invokesuper_quick
    | invokestatic_quick
    | invokeinterface_quick
    | invokevirtualobject_quick
    | invokeignored_quick
    | new_quick
    | anewarray_quick
    | multianewarray_quick
    | checkcast_quick
    | instanceof_quick
    | invokevirtual_quick_w
    | getfield_quick_w
    | putfield_quick_w
    | nonnull_quick
    | software
    | hardware
    | iand
    | land
    | ior
    | lor
    | ixor
    | lxor
    | iinc
    | i2l
    | i2f
    | i2d
    | l2i
    | l2f
    | l2d
    | f2i
    | f2l
    | f2d
    | d2i
    | d2l
    | d2f
    | i2b
    | i2c
    | i2s
    | lcmp
    | fcmpl
    | fcmpg
    | dcmpl
    | dcmpg
    | ifeq
    | ifne
    | iflt
    | ifge
    | ifgt
    | ifle
    | if_icmpeq
    | if_icmpne
    | if_icmplt
    | if_icmpge
    | if_icmpgt
    | if_icmple
    | if_acmpeq
    | if_acmpne
    | goto
    | jsr
    | ret
    | tableswitch
    | lookupswitch
    | ireturn
    | lreturn
    | freturn
    | dreturn
    | areturn
    | return
    | getstatic
    | putstatic
    | getfield
    | putfield
    | invokevirtual
    | invokespecial
    | invokestatic
    | invokeinterface
    | new
    | newarray
    | anewarray
    | arraylength
    | athrow
    | checkcast
    | instanceof
    | monitorenter
    | monitorexit
    | wide
    | multianewarray
    | ifnull
    | ifnonnull
    | goto_w
    | jsr_w
    | breakpoint
    | ldc_quick
    | ldc_w_quick
    | ldc2_w_quick
    | getfield_quick
    | putfield_quick
    | getfield2_quick
    | putfield2_quick
    | getstatic_quick
    | putstatic_quick
    | getstatic2_quick
    | putstatic2_quick
    | invokevirtual_quick
    | invokenonvirtual_quick
    | invokesuper_quick
    | invokestatic_quick
    | invokeinterface_quick
    | invokevirtualobject_quick
    | invokeignored_quick
    | new_quick
    | anewarray_quick
    | multianewarray_quick
    | checkcast_quick
    | instanceof_quick
    | invokevirtual_quick_w
    | getfield_quick_w
    | putfield_quick_w
    | nonnull_quick
    | software
    | hardware
    | fload_3
    | dload_0
    | dload_1
    | dload_2
    | dload_3
    | aload_0
    | aload_1
    | aload_2
    | aload_3
    | iaload
    | laload
    | faload
    | daload
    | aaload
    | baload
    | caload
    | saload
    | istore
    | lstore
    | fstore
    | dstore
    | astore
    | istore_0
    | istore_1
    | istore_2
    | istore_3
    | lstore_0
    | lstore_1
    | lstore_2
    | lstore_3
    | fstore_0
    | fstore_1
    | fstore_2
    | fstore_3
    | dstore_0
    | dstore_1
    | dstore_2
    | dstore_3
    | astore_0
    | astore_1
    | astore_2
    | astore_3
    | iastore
    | lastore
    | fastore
    | dastore
    | aastore
    | bastore
    | castore
    | sastore
    | pop
    | pop2
    | dup
    | dup_x1
    | dup_x2
    | dup2
    | dup2_x1
    | dup2_x2
    | swap
    | iadd
    | ladd
    | fadd
    | dadd
    | isub
    | lsub
    | fsub
    | dsub
    | imul
    | lmul
    | fmul
    | dmul
    | idiv
    | ldiv
    | fdiv
    | ddiv
    | irem
    | lrem
    | frem
    | drem
    | ineg
    | lneg
    | fneg
    | dneg
    | ishl
    | lshl
    | ishr
    | lshr
    | iushr
    | lushr
    | iand
    | land
    | ior
    | lor
    | ixor
    | lxor
    | iinc
    | i2l
    | i2f
    | i2d
    | l2i
    | l2f
    | l2d
    | f2i
    | f2l
    | f2d
    | d2i
    | d2l
    | d2f
    | i2b
    | i2c
    | i2s
    | lcmp
    | fcmpl
    | fcmpg
    | dcmpl
    | dcmpg
    | ifeq
    | ifne
    | iflt
    | ifge
    | ifgt
    | ifle
    | if_icmpeq
    | if_icmpne
    | if_icmplt
    | if_icmpge
    | if_icmpgt
    | if_icmple
    | if_acmpeq
    | if_acmpne
    | goto
    | jsr
    | ret
    | tableswitch
    | lookupswitch
    | ireturn
    | lreturn
    | freturn
    | dreturn
    | areturn
    | return
    | getstatic
    | putstatic
    | getfield
    | putfield
    | invokevirtual
    | invokespecial
    | invokestatic
    | invokeinterface
    | new
    | newarray
    | anewarray
    | arraylength
    | athrow
    | checkcast
    | instanceof
    | monitorenter
    | monitorexit
    | wide
    | multianewarray
    | ifnull
    | ifnonnull
    | goto_w
    | jsr_w
    | breakpoint
    | ldc_quick
    | ldc_w_quick
    | ldc2_w_quick
    | getfield_quick
    | putfield_quick
    | getfield2_quick
    | putfield2_quick
    | getstatic_quick
    | putstatic_quick
    | getstatic2_quick
    | putstatic2_quick
    | invokevirtual_quick
    | invokenonvirtual_quick
    | invokesuper_quick
    | invokestatic_quick
    | invokeinterface_quick
    | invokevirtualobject_quick
    | invokeignored_quick
    | new_quick
    | anewarray_quick
    | multianewarray_quick
    | checkcast_quick
    | instanceof_quick
    | invokevirtual_quick_w
    | getfield_quick_w
    | putfield_quick_w
    | nonnull_quick
    | software
    | hardware
    | if_icmplt
    | if_icmpge
    | if_icmpgt
    | if_icmple
    | if_acmpeq
    | if_acmpne
    | goto
    | jsr
    | ret
    | tableswitch
    | lookupswitch
    | ireturn
    | lreturn
    | freturn
    | dreturn
    | areturn
    | return
    | getstatic
    | putstatic
    | getfield
    | putfield
    | invokevirtual
    | invokespecial
    | invokestatic
    | invokeinterface
    | new
    | newarray
    | anewarray
    | arraylength
    | athrow
    | checkcast
    | instanceof
    | monitorenter
    | monitorexit
    | wide
    | multianewarray
    | ifnull
    | ifnonnull
    | goto_w
    | jsr_w
    | breakpoint
    | ldc_quick
    | ldc_w_quick
    | ldc2_w_quick
    | getfield_quick
    | putfield_quick
    | getfield2_quick
    | putfield2_quick
    | getstatic_quick
    | putstatic_quick
    | getstatic2_quick
    | putstatic2_quick
    | invokevirtual_quick
    | invokenonvirtual_quick
    | invokesuper_quick
    | invokestatic_quick
    | invokeinterface_quick
    | invokevirtualobject_quick
    | invokeignored_quick
    | new_quick
    | anewarray_quick
    | multianewarray_quick
    | checkcast_quick
    | instanceof_quick
    | invokevirtual_quick_w
    | getfield_quick_w
    | putfield_quick_w
    | nonnull_quick
    | software
    | hardware
*/
    ;

getstatic:
    GETSTATIC INT          { getstatic_int((ClassFile *)cf, $2); }
    | GETSTATIC IDENTIFIER { printf("I will getstatic from string %s\n", $2); }
    ;

%%

/**
 * This function generates the opcode for the getstatic opcode
 * It will check if the index specified is valid into the constant_pool
 * according to the Classfile documentation and warn the user if 
 * it isn't. This check WILL NOT prevent the code of being compiled
 * as this value might have been intentional (looking for vulns for
 * example)
 */
void getstatic_int(ClassFile *cf, int index)
{
    unsigned char bytes[3];
    
    if(index > cf->constant_pool_count) {
        debug(DBG_WARN, "Index for getstatic %d is greater than the \
                         number of entries in the constant pool", index);
                         
    } else {
        if(cf->constant_pool[index].tag != CONSTANT_FIELDREF) {
            debug(DBG_WARN, "Index for getstatic %d does not point to \
                             a CONSTANT_Fieldref into the constant_pool",
                             index);
        }
    }
    
    bytes[0] = 0xB2;
    bytes[1] = (index & 0x0000FF00) >> 8;
    bytes[2] = (index & 0x000000FF);
    
    if(buffer_append(code, bytes, 3) != 3) {
        debug(DBG_ERROR, "Cannot append code to buffer... Aborting");
    }
    
    current_max_stack += 1;
    
}

int method_start(ClassFile *cf, char *identifier, char *params)
{
    method_info *MyMethod;
    
    current_method = RC_GetMethodIndex(cf, identifier, params);
    
    if(current_method == -1) {
        RC_AddMethod(cf, identifier, "()V", ACC_PUBLIC | ACC_STATIC, &MyMethod);
        
        current_method = RC_GetMethodIndex(cf, identifier, params);
        if(current_method == -1) {
            debug(DBG_ERROR, "Impossible to create method %s [%s]", identifier, params);
            return -1;
        }
    }


    return 0;
}

int method_end(ClassFile *cf)
{
    
    RC_ChangeMethodCodeAttribute(cf, &cf->methods[current_method] , 
                                 code->bytes, code->size, 
                                 current_max_stack, 
                                 current_max_locals);
    
    return 0;
}

int parse(ClassFile *cf, char *file_path)
{
    int ret = CF_OK;
    FILE *f;

    if((f = fopen(file_path, "r")) == NULL) {
        printf("Error opening file: %s\n", file_path);
        return CF_NOTOK;
    }
    
    yyin = f;
    current_method = 0;
    current_max_stack = 0;
    current_max_locals = 0;
    code = buffer_new(0);
    
    do {
        if(yyparse(cf) > 0) {
            ret = CF_NOTOK;
            break;
        }
    } while (!feof(yyin));


    buffer_free(code);

    return ret;
}

void yyerror(const char *s) {
    printf("Error on token: %s\n", s);
}
