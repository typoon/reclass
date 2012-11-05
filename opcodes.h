#ifndef OPCODE_H_
#define OPCODE_H_

#define INFINITY -1

short opcodes[][2] = {
    //{opcode, num_arguments}  
    {0, 0}, /* nop */
    {1, 0}, /* aconst_null */
    {2, 0}, /* iconst_m1 */
    {3, 0}, /* iconst_0 */
    {4, 0}, /* iconst_1 */
    {5, 0}, /* iconst_2 */
    {6, 0}, /* iconst_3 */
    {7, 0}, /* iconst_4 */
    {8, 0}, /* iconst_5 */
    {9, 0}, /* lconst_0 */
    {10, 0}, /* lconst_1 */
    {11, 0}, /* fconst_0 */
    {12, 0}, /* fconst_1 */
    {13, 0}, /* fconst_2 */
    {14, 0}, /* dconst_0 */
    {15, 0}, /* dconst_1 */
    {16, 1}, /* bipush */
    {17, 2}, /* sipush */
    {18, 1}, /* ldc */
    {19, 2}, /* ldc_w */
    {20, 2}, /* ldc2_w */
    {21, 1}, /* iload */
    {22, 1}, /* lload */
    {23, 1}, /* fload */
    {24, 1}, /* dload */
    {25, 1}, /* aload */
    {26, 0}, /* iload_0 */
    {27, 0}, /* iload_1 */
    {28, 0}, /* iload_2 */
    {29, 0}, /* iload_3 */
    {30, 0}, /* lload_0 */
    {31, 0}, /* lload_1 */
    {32, 0}, /* lload_2 */
    {33, 0}, /* lload_3 */
    {34, 0}, /* fload_0 */
    {35, 0}, /* fload_1 */
    {36, 0}, /* fload_2 */
    {37, 0}, /* fload_3 */
    {38, 0}, /* dload_0 */
    {39, 0}, /* dload_1 */
    {40, 0}, /* dload_2 */
    {41, 0}, /* dload_3 */
    {42, 0}, /* aload_0 */
    {43, 0}, /* aload_1 */
    {44, 0}, /* aload_2 */
    {45, 0}, /* aload_3 */
    {46, 0}, /* iaload */
    {47, 0}, /* laload */
    {48, 0}, /* faload */
    {49, 0}, /* daload */
    {50, 0}, /* aaload */
    {51, 0}, /* baload */
    {52, 0}, /* caload */
    {53, 0}, /* saload */
    {54, 1}, /* istore */
    {55, 1}, /* lstore */
    {56, 1}, /* fstore */
    {57, 1}, /* dstore */
    {58, 1}, /* astore */
    {59, 0}, /* istore_0 */
    {60, 0}, /* istore_1 */
    {61, 0}, /* istore_2 */
    {62, 0}, /* istore_3 */
    {63, 0}, /* lstore_0 */
    {64, 0}, /* lstore_1 */
    {65, 0}, /* lstore_2 */
    {66, 0}, /* lstore_3 */
    {67, 0}, /* fstore_0 */
    {68, 0}, /* fstore_1 */
    {69, 0}, /* fstore_2 */
    {70, 0}, /* fstore_3 */
    {71, 0}, /* dstore_0 */
    {72, 0}, /* dstore_1 */
    {73, 0}, /* dstore_2 */
    {74, 0}, /* dstore_3 */
    {75, 0}, /* astore_0 */
    {76, 0}, /* astore_1 */
    {77, 0}, /* astore_2 */
    {78, 0}, /* astore_3 */
    {79, 0}, /* iastore */
    {80, 0}, /* lastore */
    {81, 0}, /* fastore */
    {82, 0}, /* dastore */
    {83, 0}, /* aastore */
    {84, 0}, /* bastore */
    {85, 0}, /* castore */
    {86, 0}, /* sastore */
    {87, 0}, /* pop */
    {88, 0}, /* pop2 */
    {89, 0}, /* dup */
    {90, 0}, /* dup_x1 */
    {91, 0}, /* dup_x2 */
    {92, 0}, /* dup2 */
    {93, 0}, /* dup2_x1 */
    {94, 0}, /* dup2_x2 */
    {95, 0}, /* swap */
    {96, 0}, /* iadd */
    {97, 0}, /* ladd */
    {98, 0}, /* fadd */
    {99, 0}, /* dadd */
    {100, 0}, /* isub */
    {101, 0}, /* lsub */
    {102, 0}, /* fsub */
    {103, 0}, /* dsub */
    {104, 0}, /* imul */
    {105, 0}, /* lmul */
    {106, 0}, /* fmul */
    {107, 0}, /* dmul */
    {108, 0}, /* idiv */
    {109, 0}, /* ldiv */
    {110, 0}, /* fdiv */
    {111, 0}, /* ddiv */
    {112, 0}, /* irem */
    {113, 0}, /* lrem */
    {114, 0}, /* frem */
    {115, 0}, /* drem */
    {116, 0}, /* ineg */
    {117, 0}, /* lneg */
    {118, 0}, /* fneg */
    {119, 0}, /* dneg */
    {120, 0}, /* ishl */
    {121, 0}, /* lshl */
    {122, 0}, /* ishr */
    {123, 0}, /* lshr */
    {124, 0}, /* iushr */
    {125, 0}, /* lushr */
    {126, 0}, /* iand */
    {127, 0}, /* land */
    {128, 0}, /* ior */
    {129, 0}, /* lor */
    {130, 0}, /* ixor */
    {131, 0}, /* lxor */
    {132, 2}, /* iinc */
    {133, 0}, /* i2l */
    {134, 0}, /* i2f */
    {135, 0}, /* i2d */
    {136, 0}, /* l2i */
    {137, 0}, /* l2f */
    {138, 0}, /* l2d */
    {139, 0}, /* f2i */
    {140, 0}, /* f2l */
    {141, 0}, /* f2d */
    {142, 0}, /* d2i */
    {143, 0}, /* d2l */
    {144, 0}, /* d2f */
    {145, 0}, /* i2b */
    {146, 0}, /* i2c */
    {147, 0}, /* i2s */
    {148, 0}, /* lcmp */
    {149, 0}, /* fcmpl */
    {150, 0}, /* fcmpg */
    {151, 0}, /* dcmpl */
    {152, 0}, /* dcmpg */
    {153, 2}, /* ifeq */
    {154, 2}, /* ifne */
    {155, 2}, /* iflt */
    {156, 2}, /* ifge */
    {157, 2}, /* ifgt */
    {158, 2}, /* ifle */
    {159, 2}, /* if_icmpeq */
    {160, 2}, /* if_icmpne */
    {161, 2}, /* if_icmplt */
    {162, 2}, /* if_icmpge */
    {163, 2}, /* if_icmpgt */
    {164, 2}, /* if_icmple */
    {165, 2}, /* if_acmpeq */
    {166, 2}, /* if_acmpne */
    {167, 2}, /* goto */
    {168, 2}, /* jsr */
    {169, 1}, /* ret */
    {170, INFINITY}, /* tableswitch */
    {171, INFINITY}, /* lookupswitch */
    {172, 0}, /* ireturn */
    {173, 0}, /* lreturn */
    {174, 0}, /* freturn */
    {175, 0}, /* dreturn */
    {176, 0}, /* areturn */
    {177, 0}, /* return */
    {178, 2}, /* getstatic */
    {179, 2}, /* putstatic */
    {180, 2}, /* getfield */
    {181, 2}, /* putfield */
    {182, 2}, /* invokevirtual */
    {183, 2}, /* invokespecial */
    {184, 2}, /* invokestatic */
    {185, 5}, /* invokeinterface */
    {186, 0}, /* reserved */
    {187, 2}, /* new */
    {188, 1}, /* newarray */
    {189, 2}, /* anewarray */
    {190, 0}, /* arraylength */
    {191, 0}, /* athrow */
    {192, 2}, /* checkcast */
    {193, 2}, /* instanceof */
    {194, 0}, /* monitorenter */
    {195, 0}, /* monitorexit */
    {196, INFINITY}, /* wide */
    {197, 3}, /* multianewarray */
    {198, 2}, /* ifnull */
    {199, 2}, /* ifnonnull */
    {200, 4}, /* goto_w */
    {201, 4}, /* jsr_w */
    {202, 0}, /* breakpoint */
    {203, 1}, /* ldc_quick */
    {204, 2}, /* ldc_w_quick */
    {205, 2}, /* ldc2_w_quick */
    {206, 2}, /* getfield_quick */
    {207, 2}, /* putfield_quick */
    {208, 2}, /* getfield2_quick */
    {209, 2}, /* putfield2_quick */
    {210, 2}, /* getstatic_quick */
    {211, 2}, /* putstatic_quick */
    {212, 2}, /* getstatic2_quick */
    {213, 2}, /* putstatic2_quick */
    {214, 2}, /* invokevirtual_quick */
    {215, 2}, /* invokenonvirtual_quick */
    {216, 2}, /* invokesuper_quick */
    {217, 2}, /* invokestatic_quick */
    {218, 4}, /* invokeinterface_quick */
    {219, 2}, /* invokevirtualobject_quick */
    {220, 2}, /* invokeignored_quick */
    {221, 2}, /* new_quick */
    {222, 2}, /* anewarray_quick */
    {223, 3}, /* multianewarray_quick */
    {224, 2}, /* checkcast_quick */
    {225, 2}, /* instanceof_quick */
    {226, 2}, /* invokevirtual_quick_w */
    {227, 2}, /* getfield_quick_w */
    {228, 2}, /* putfield_quick_w */
    {229, 0}, /* nonnull_quick */
    {230, 0}, /* reserved */
    {231, 0}, /* reserved */
    {232, 0}, /* reserved */
    {233, 0}, /* reserved */
    {234, 0}, /* reserved */
    {235, 0}, /* reserved */
    {236, 0}, /* reserved */
    {237, 0}, /* reserved */
    {238, 0}, /* reserved */
    {239, 0}, /* reserved */
    {240, 0}, /* reserved */
    {241, 0}, /* reserved */
    {242, 0}, /* reserved */
    {243, 0}, /* reserved */
    {244, 0}, /* reserved */
    {245, 0}, /* reserved */
    {246, 0}, /* reserved */
    {247, 0}, /* reserved */
    {248, 0}, /* reserved */
    {249, 0}, /* reserved */
    {250, 0}, /* reserved */
    {251, 0}, /* reserved */
    {252, 0}, /* reserved */
    {253, 0}, /* reserved */
    {254, 0}, /* software */
    {255, 0}  /* hardware */
};

char *opcodes_str[] = {
    "nop",
    "aconst_null",
    "iconst_m1",
    "iconst_0",
    "iconst_1",
    "iconst_2",
    "iconst_3",
    "iconst_4",
    "iconst_5",
    "lconst_0",
    "lconst_1",
    "fconst_0",
    "fconst_1",
    "fconst_2",
    "dconst_0",
    "dconst_1",
    "bipush",
    "sipush",
    "ldc",
    "ldc_w",
    "ldc2_w",
    "iload",
    "lload",
    "fload",
    "dload",
    "aload",
    "iload_0",
    "iload_1",
    "iload_2",
    "iload_3",
    "lload_0",
    "lload_1",
    "lload_2",
    "lload_3",
    "fload_0",
    "fload_1",
    "fload_2",
    "fload_3",
    "dload_0",
    "dload_1",
    "dload_2",
    "dload_3",
    "aload_0",
    "aload_1",
    "aload_2",
    "aload_3",
    "iaload",
    "laload",
    "faload",
    "daload",
    "aaload",
    "baload",
    "caload",
    "saload",
    "istore",
    "lstore",
    "fstore",
    "dstore",
    "astore",
    "istore_0",
    "istore_1",
    "istore_2",
    "istore_3",
    "lstore_0",
    "lstore_1",
    "lstore_2",
    "lstore_3",
    "fstore_0",
    "fstore_1",
    "fstore_2",
    "fstore_3",
    "dstore_0",
    "dstore_1",
    "dstore_2",
    "dstore_3",
    "astore_0",
    "astore_1",
    "astore_2",
    "astore_3",
    "iastore",
    "lastore",
    "fastore",
    "dastore",
    "aastore",
    "bastore",
    "castore",
    "sastore",
    "pop",
    "pop2",
    "dup",
    "dup_x1",
    "dup_x2",
    "dup2",
    "dup2_x1",
    "dup2_x2",
    "swap",
    "iadd",
    "ladd",
    "fadd",
    "dadd",
    "isub",
    "lsub",
    "fsub",
    "dsub",
    "imul",
    "lmul",
    "fmul",
    "dmul",
    "idiv",
    "ldiv",
    "fdiv",
    "ddiv",
    "irem",
    "lrem",
    "frem",
    "drem",
    "ineg",
    "lneg",
    "fneg",
    "dneg",
    "ishl",
    "lshl",
    "ishr",
    "lshr",
    "iushr",
    "lushr",
    "iand",
    "land",
    "ior",
    "lor",
    "ixor",
    "lxor",
    "iinc",
    "i2l",
    "i2f",
    "i2d",
    "l2i",
    "l2f",
    "l2d",
    "f2i",
    "f2l",
    "f2d",
    "d2i",
    "d2l",
    "d2f",
    "i2b",
    "i2c",
    "i2s",
    "lcmp",
    "fcmpl",
    "fcmpg",
    "dcmpl",
    "dcmpg",
    "ifeq",
    "ifne",
    "iflt",
    "ifge",
    "ifgt",
    "ifle",
    "if_icmpeq",
    "if_icmpne",
    "if_icmplt",
    "if_icmpge",
    "if_icmpgt",
    "if_icmple",
    "if_acmpeq",
    "if_acmpne",
    "goto",
    "jsr",
    "ret",
    "tableswitch",
    "lookupswitch",
    "ireturn",
    "lreturn",
    "freturn",
    "dreturn",
    "areturn",
    "return",
    "getstatic",
    "putstatic",
    "getfield",
    "putfield",
    "invokevirtual",
    "invokespecial",
    "invokestatic",
    "invokeinterface",
    "reserved_invalid",
    "new",
    "newarray",
    "anewarray",
    "arraylength",
    "athrow",
    "checkcast",
    "instanceof",
    "monitorenter",
    "monitorexit",
    "wide",
    "multianewarray",
    "ifnull",
    "ifnonnull",
    "goto_w",
    "jsr_w",
    "breakpoint",
    "ldc_quick",
    "ldc_w_quick",
    "ldc2_w_quick",
    "getfield_quick",
    "putfield_quick",
    "getfield2_quick",
    "putfield2_quick",
    "getstatic_quick",
    "putstatic_quick",
    "getstatic2_quick",
    "putstatic2_quick",
    "invokevirtual_quick",
    "invokenonvirtual_quick",
    "invokesuper_quick",
    "invokestatic_quick",
    "invokeinterface_quick",
    "invokevirtualobject_quick",
    "invokeignored_quick",
    "new_quick",
    "anewarray_quick",
    "multianewarray_quick",
    "checkcast_quick",
    "instanceof_quick",
    "invokevirtual_quick_w",
    "getfield_quick_w",
    "putfield_quick_w",
    "nonnull_quick",
    "reserved_invalid",
    "reserved_invalid",
    "reserved_invalid",
    "reserved_invalid",
    "reserved_invalid",
    "reserved_invalid",
    "reserved_invalid",
    "reserved_invalid",
    "reserved_invalid",
    "reserved_invalid",
    "reserved_invalid",
    "reserved_invalid",
    "reserved_invalid",
    "reserved_invalid",
    "reserved_invalid",
    "reserved_invalid",
    "reserved_invalid",
    "reserved_invalid",
    "reserved_invalid",
    "reserved_invalid",
    "reserved_invalid",
    "reserved_invalid",
    "reserved_invalid",
    "reserved_invalid",
    "software",
    "hardware"
};

#endif
