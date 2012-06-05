/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     DOUBLE = 259,
     STRING = 260,
     VAR_INT = 261,
     VAR_STRING = 262,
     VAR_DOUBLE = 263,
     IDENTIFIER = 264,
     METHOD_START = 265,
     PARAMS = 266,
     METHOD_END = 267,
     NOP = 268,
     ACONST_NULL = 269,
     ICONST_M1 = 270,
     ICONST_0 = 271,
     ICONST_1 = 272,
     ICONST_2 = 273,
     ICONST_3 = 274,
     ICONST_4 = 275,
     ICONST_5 = 276,
     LCONST_0 = 277,
     LCONST_1 = 278,
     FCONST_0 = 279,
     FCONST_1 = 280,
     FCONST_2 = 281,
     DCONST_0 = 282,
     DCONST_1 = 283,
     BIPUSH = 284,
     SIPUSH = 285,
     LDC = 286,
     LDC_W = 287,
     LDC2_W = 288,
     ILOAD = 289,
     LLOAD = 290,
     FLOAD = 291,
     DLOAD = 292,
     ALOAD = 293,
     ILOAD_0 = 294,
     ILOAD_1 = 295,
     ILOAD_2 = 296,
     ILOAD_3 = 297,
     LLOAD_0 = 298,
     LLOAD_1 = 299,
     LLOAD_2 = 300,
     LLOAD_3 = 301,
     FLOAD_0 = 302,
     FLOAD_1 = 303,
     FLOAD_2 = 304,
     FLOAD_3 = 305,
     DLOAD_0 = 306,
     DLOAD_1 = 307,
     DLOAD_2 = 308,
     DLOAD_3 = 309,
     ALOAD_0 = 310,
     ALOAD_1 = 311,
     ALOAD_2 = 312,
     ALOAD_3 = 313,
     IALOAD = 314,
     LALOAD = 315,
     FALOAD = 316,
     DALOAD = 317,
     AALOAD = 318,
     BALOAD = 319,
     CALOAD = 320,
     SALOAD = 321,
     ISTORE = 322,
     LSTORE = 323,
     FSTORE = 324,
     DSTORE = 325,
     ASTORE = 326,
     ISTORE_0 = 327,
     ISTORE_1 = 328,
     ISTORE_2 = 329,
     ISTORE_3 = 330,
     LSTORE_0 = 331,
     LSTORE_1 = 332,
     LSTORE_2 = 333,
     LSTORE_3 = 334,
     FSTORE_0 = 335,
     FSTORE_1 = 336,
     FSTORE_2 = 337,
     FSTORE_3 = 338,
     DSTORE_0 = 339,
     DSTORE_1 = 340,
     DSTORE_2 = 341,
     DSTORE_3 = 342,
     ASTORE_0 = 343,
     ASTORE_1 = 344,
     ASTORE_2 = 345,
     ASTORE_3 = 346,
     IASTORE = 347,
     LASTORE = 348,
     FASTORE = 349,
     DASTORE = 350,
     AASTORE = 351,
     BASTORE = 352,
     CASTORE = 353,
     SASTORE = 354,
     POP = 355,
     POP2 = 356,
     DUP = 357,
     DUP_X1 = 358,
     DUP_X2 = 359,
     DUP2 = 360,
     DUP2_X1 = 361,
     DUP2_X2 = 362,
     SWAP = 363,
     IADD = 364,
     LADD = 365,
     FADD = 366,
     DADD = 367,
     ISUB = 368,
     LSUB = 369,
     FSUB = 370,
     DSUB = 371,
     IMUL = 372,
     LMUL = 373,
     FMUL = 374,
     DMUL = 375,
     IDIV = 376,
     LDIV = 377,
     FDIV = 378,
     DDIV = 379,
     IREM = 380,
     LREM = 381,
     FREM = 382,
     DREM = 383,
     INEG = 384,
     LNEG = 385,
     FNEG = 386,
     DNEG = 387,
     ISHL = 388,
     LSHL = 389,
     ISHR = 390,
     LSHR = 391,
     IUSHR = 392,
     LUSHR = 393,
     IAND = 394,
     LAND = 395,
     IOR = 396,
     LOR = 397,
     IXOR = 398,
     LXOR = 399,
     IINC = 400,
     I2L = 401,
     I2F = 402,
     I2D = 403,
     L2I = 404,
     L2F = 405,
     L2D = 406,
     F2I = 407,
     F2L = 408,
     F2D = 409,
     D2I = 410,
     D2L = 411,
     D2F = 412,
     I2B = 413,
     I2C = 414,
     I2S = 415,
     LCMP = 416,
     FCMPL = 417,
     FCMPG = 418,
     DCMPL = 419,
     DCMPG = 420,
     IFEQ = 421,
     IFNE = 422,
     IFLT = 423,
     IFGE = 424,
     IFGT = 425,
     IFLE = 426,
     IF_ICMPEQ = 427,
     IF_ICMPNE = 428,
     IF_ICMPLT = 429,
     IF_ICMPGE = 430,
     IF_ICMPGT = 431,
     IF_ICMPLE = 432,
     IF_ACMPEQ = 433,
     IF_ACMPNE = 434,
     GOTO = 435,
     JSR = 436,
     RET = 437,
     TABLESWITCH = 438,
     LOOKUPSWITCH = 439,
     IRETURN = 440,
     LRETURN = 441,
     FRETURN = 442,
     DRETURN = 443,
     ARETURN = 444,
     RETURN = 445,
     GETSTATIC = 446,
     PUTSTATIC = 447,
     GETFIELD = 448,
     PUTFIELD = 449,
     INVOKEVIRTUAL = 450,
     INVOKESPECIAL = 451,
     INVOKESTATIC = 452,
     INVOKEINTERFACE = 453,
     NEW = 454,
     NEWARRAY = 455,
     ANEWARRAY = 456,
     ARRAYLENGTH = 457,
     ATHROW = 458,
     CHECKCAST = 459,
     INSTANCEOF = 460,
     MONITORENTER = 461,
     MONITOREXIT = 462,
     WIDE = 463,
     MULTIANEWARRAY = 464,
     IFNULL = 465,
     IFNONNULL = 466,
     GOTO_W = 467,
     JSR_W = 468,
     BREAKPOINT = 469,
     LDC_QUICK = 470,
     LDC_W_QUICK = 471,
     LDC2_W_QUICK = 472,
     GETFIELD_QUICK = 473,
     PUTFIELD_QUICK = 474,
     GETFIELD2_QUICK = 475,
     PUTFIELD2_QUICK = 476,
     GETSTATIC_QUICK = 477,
     PUTSTATIC_QUICK = 478,
     GETSTATIC2_QUICK = 479,
     PUTSTATIC2_QUICK = 480,
     INVOKEVIRTUAL_QUICK = 481,
     INVOKENONVIRTUAL_QUICK = 482,
     INVOKESUPER_QUICK = 483,
     INVOKESTATIC_QUICK = 484,
     INVOKEINTERFACE_QUICK = 485,
     INVOKEVIRTUALOBJECT_QUICK = 486,
     INVOKEIGNORED_QUICK = 487,
     NEW_QUICK = 488,
     ANEWARRAY_QUICK = 489,
     MULTIANEWARRAY_QUICK = 490,
     CHECKCAST_QUICK = 491,
     INSTANCEOF_QUICK = 492,
     INVOKEVIRTUAL_QUICK_W = 493,
     GETFIELD_QUICK_W = 494,
     PUTFIELD_QUICK_W = 495,
     NONNULL_QUICK = 496,
     SOFTWARE = 497,
     HARDWARE = 498
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 16 "parser.y"

    int int_val;
    double double_val;
    char* str_val;



/* Line 2068 of yacc.c  */
#line 301 "parser.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


