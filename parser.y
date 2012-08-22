%{
#include <stdio.h>
#include <string.h>
#include "reclass.h"
#include "compiler.h"

#define YYPARSE_PARAM cf

%}

%union {
    unsigned char byte_val;
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
%token <byte_val>   BYTE


/* General asm identifiers */
%token VAR_INT
%token VAR_STRING
%token VAR_DOUBLE
%token VAR_BYTE

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
    identifiers var_int
    | identifiers var_double
    | identifiers var_string
    | identifiers var_byte
    | var_int
    | var_double
    | var_string
    | var_byte
    ;

var_int:
    VAR_INT IDENTIFIER INT      { if(create_int((ClassFile *)cf, $2, $3) < 0) YYABORT; }
    | VAR_INT IDENTIFIER        { if(create_int((ClassFile *)cf, $2, 0)  < 0) YYABORT; }
    ;

var_double:
    VAR_DOUBLE IDENTIFIER DOUBLE
    | VAR_DOUBLE IDENTIFIER
    ;

var_string:
    VAR_STRING IDENTIFIER STRING
    | VAR_STRING IDENTIFIER
    ;

var_byte:
    VAR_BYTE IDENTIFIER BYTE    { if(create_byte((ClassFile *)cf, $2, $3) < 0) YYABORT; }
    | VAR_BYTE IDENTIFIER       { if(create_byte((ClassFile *)cf, $2, 0)  < 0) YYABORT; }
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

mnemonics:
    mnemonics opcode
    | opcode
    ;

opcode:
    nop
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
/*
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
*/
    | return
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
*/
    | pop
/*
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

/** Opcodes start */
nop:
    NOP                      { if(nop() != CF_OK) YYABORT; }
    ;

aconst_null:
    ACONST_NULL              { if(aconstnull() != CF_OK) YYABORT; }
    ;

iconst_m1:
    ICONST_M1                { if(iconstm1() != CF_OK) YYABORT; }
    ;

iconst_0:
    ICONST_0                 { if(iconst0() != CF_OK) YYABORT; }
    ;

iconst_1:
    ICONST_1                 { if(iconst1() != CF_OK) YYABORT; }
    ;

iconst_2:
    ICONST_2                 { if(iconst2() != CF_OK) YYABORT; }
    ;

iconst_3:
    ICONST_3                 { if(iconst3() != CF_OK) YYABORT; }
    ;

iconst_4:
    ICONST_4                 { if(iconst4() != CF_OK) YYABORT; }
    ;

iconst_5:
    ICONST_5                 { if(iconst5() != CF_OK) YYABORT; }
    ;

lconst_0:
    LCONST_0                 { if(lconst0() != CF_OK) YYABORT; }
    ;

lconst_1:
    LCONST_1                 { if(lconst1() != CF_OK) YYABORT; }
    ;

fconst_0:
    FCONST_0                 { if(fconst0() != CF_OK) YYABORT; }
    ;

fconst_1:
    FCONST_1                 { if(fconst1() != CF_OK) YYABORT; }
    ;

fconst_2:
    FCONST_2                 { if(fconst2() != CF_OK) YYABORT; }
    ;

dconst_0:
    DCONST_0                 { if(dconst0() != CF_OK) YYABORT; }
    ;

dconst_1:
    DCONST_1                 { if(dconst1() != CF_OK) YYABORT; }
    ;

bipush:
    BIPUSH BYTE              { if(bipush_byte($2) != CF_OK) YYABORT; }
    | BIPUSH IDENTIFIER      { if(bipush_identifier($2) != CF_OK) { free($2); YYABORT; } free($2); }
    ;
    

return:
    RETURN                   { if(jreturn() != CF_OK) YYABORT; }
    ;

getstatic:
      GETSTATIC INT          { if(getstatic_int((ClassFile *)cf, $2) != CF_OK) YYABORT;        }
    | GETSTATIC BYTE         { if(getstatic_int((ClassFile *)cf, (int)$2) != CF_OK) YYABORT;   }
    | GETSTATIC IDENTIFIER   { if(getstatic_identifier((ClassFile *)cf, $2) != CF_OK) { free($2); YYABORT; } free($2); }
    ;

pop:
    POP                      { if(pop() != CF_OK) YYABORT; }

%%

