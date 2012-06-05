#ifndef CLASSFILE_H_
#define CLASSFILE_H_

// Generic defines by me :)
#define CF_NOTOK   -1
#define CF_OK       0

// Types to make life easier
typedef unsigned char  u1;
typedef unsigned short u2;
typedef unsigned int   u4;

// JVM Constants
#define JAVA_MAGIC 0xCAFEBABE

// Constants for the 'tag' component in the cp_info structure
#define CONSTANT_CLASS                   7
#define CONSTANT_FIELDREF                9
#define CONSTANT_METHODREF              10
#define CONSTANT_INTERFACEMETHODREF     11
#define CONSTANT_STRING                  8
#define CONSTANT_INTEGER                 3
#define CONSTANT_FLOAT                   4
#define CONSTANT_LONG                    5
#define CONSTANT_DOUBLE                  6
#define CONSTANT_NAMEANDTYPE            12
#define CONSTANT_UTF8                    1

// Constants for the 'access_flags' field in both the field_info and
// method_info structures
#define ACC_PUBLIC      0x0001 //Declared public; may be accessed from outside its package.
#define ACC_PRIVATE     0x0002 //Declared private; usable only within the defining class.
#define ACC_PROTECTED   0x0004 //Declared protected; may be accessed within subclasses.
#define ACC_STATIC      0x0008 //Declared static.
#define ACC_FINAL       0x0010 //Declared final; no further assignment after initialization.

// Constants for the 'access_flags' field in the field_info structure
#define ACC_VOLATILE    0x0040 //Declared volatile; cannot be cached.
#define ACC_TRANSIENT   0x0080 //Declared transient; not written or read by a persistent object manager.

// Constants for the 'access_flags' field in the method_info structure
#define ACC_SYNCHRONIZED  0x0020 //Declared synchronized; invocation is wrapped in a monitor lock.
#define ACC_NATIVE        0x0100 //Declared native; implemented in a language other than Java.
#define ACC_ABSTRACT      0x0400 //Declared abstract; no implementation is provided.
#define ACC_STRICT        0x0800 //Declared strictfp; floating-point mode is FP-strict

// Constants for the 'access_flags' field in the ClassFile struct
//#define ACC_PUBLIC    0x0001
//#define ACC_FINAL     0x0010
#define ACC_SUPER       0x0020 //Treat superclass methods specially when invoked by the invokespecial instruction.
#define ACC_INTERFACE   0x0200 //Is an interface, not a class.
//#define ACC_ABSTRACT  0x0400 //Declared abstract; may not be instantiated.


// Constants for the Attribute Names
// In my opinion this is not very cool. Sun could/should have used tags for
// attribute types just as they did with the constant pool entries
#define ATTR_CONSTANTVALUE       "ConstantValue"
#define ATTR_CODE                "Code"
#define ATTR_EXCEPTIONS          "Exceptions"
#define ATTR_INNERCLASSES        "InnerClasses"
#define ATTR_SYNTHETIC           "Synthetic"
#define ATTR_SOURCEFILE          "SourceFile"
#define ATTR_LINENUMBERTABLE     "LineNumberTable"
#define ATTR_LOCALVARIABLETABLE  "LocalVariableTable"
#define ATTR_DEPRECATED          "Deprecated"
#define ATTR_STACKMAPTABLE       "StackMapTable"

// Below attributes are currently not being read. They should be.
// Not reading them will cause class files with these attributes set to be read
// incorrectly
#define ATTR_ENCLOSINGMETHOD     "EnclosingMethod"
#define ATTR_SIGNATURE           "Signature"
#define ATTR_SOURCEDEBUGEXTENSION "SourceDebugExtension"
#define ATTR_LOCALVARIABLETYPETABLE "LocalVariableTypeTable"
#define ATTR_RUNTIMEVISIBLEANNOTATIONS "RuntimeVisibleAnnotations"
#define ATTR_RUNTIMEINVISIBLEANNOTATIONS "RuntimeInvisibleAnnotations"
#define ATTR_RUNTIMEVISIBLEPARAMETERANNOTATIONS "RuntimeVisibleParameterAnnotations"
#define ATTR_RUNTIMEINVISIBLEPARAMETERANNOTATIONS "RuntimeInvisibleParameterAnnotations"
#define ATTR_ANNOTATIONDEFAULT "AnnotationDefault"


// Constant Pool Structures

typedef struct _Class_info {
    u2 name_index;
} Class_info;

typedef struct _Fieldref_info {
    u2 class_index;
    u2 name_and_type_index;
} Fieldref_info;

typedef struct _Methodref_info {
    u2 class_index;
    u2 name_and_type_index;
} Methodref_info;

typedef struct _InterfaceMethodref_info {
    u2 class_index;
    u2 name_and_type_index;
} InterfaceMethodref_info;

typedef struct _String_info {
    u2 string_index;
} String_info;

typedef struct _Integer_info {
    u4 bytes;
} Integer_info;

typedef struct _Float_info {
    u4 bytes;
} Float_info;

typedef struct _Long_info {
    u4 high_bytes;
    u4 low_bytes;
} Long_info;

typedef struct _Double_info {
    u4 high_bytes;
    u4 low_bytes;
} Double_info;

typedef struct _NameAndType_info {
    u2 name_index;
    u2 descriptor_index;
} NameAndType_info;

typedef struct _Utf8_info {
    u2 length;
    u1 *bytes; //[length]
} Utf8_info;

typedef struct _cp_info {
    u1 tag;

    union {
        Class_info ci;
        Fieldref_info fri;
        Methodref_info mri;
        InterfaceMethodref_info imri;
        String_info si;
        Integer_info ii;
        Float_info fi;
        Long_info li;
        Double_info di;
        NameAndType_info nti;
        Utf8_info utfi;
    };
} cp_info;


// Attributes Structures

typedef struct _ConstantValue_attribute {
    u2 constantvalue_index;
} ConstantValue_attribute;

typedef struct _Exception_table {
    u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_type;
} Exception_table;

struct _attribute_info;

typedef struct _Code_attribute {
    u2 max_stack;
    u2 max_locals;
    u4 code_length;
    u1 *code; //[code_length];
    u2 exception_table_length;
    Exception_table *exception_table; //[exception_table_length];
    u2 attributes_count;
    struct _attribute_info *attributes; //[attributes_count];
} Code_attribute;

typedef struct _Exceptions_attribute {
    u2 number_of_exceptions;
    u2 *exception_index_table; //[number_of_exceptions];
} Exceptions_attribute;

typedef struct _Classes_table {
    u2 inner_class_info_index;
    u2 outer_class_info_index;
    u2 inner_name_index;
    u2 inner_class_access_flags;
} Classes_table;

typedef struct _InnerClasses_attribute {
    u2 number_of_classes;
    Classes_table *classes; //[number_of_classes];
} InnerClasses_attribute;

typedef struct _Synthetic_attribute {
} Synthetic_attribute;

typedef struct _SourceFile_attribute {
    u2 sourcefile_index;
} SourceFile_attribute;

typedef struct _LineNumber_table {
    u2 start_pc;
    u2 line_number;
} LineNumber_table;

typedef struct _LineNumberTable_attribute {
    u2 line_number_table_length;
    LineNumber_table *line_number_table; //[line_number_table_length];
} LineNumberTable_attribute;

typedef struct _LocalVariable_table {
    u2 start_pc;
    u2 length;
    u2 name_index;
    u2 descriptor_index;
    u2 index;
} LocalVariable_table;

typedef struct _LocalVariableTable_attribute {
    u2 local_variable_table_length;
    LocalVariable_table *local_variable_table; //[local_variable_table_length];
} LocalVariableTable_attribute;

typedef struct _Deprecated_attribute {
} Deprecated_attribute;

typedef struct _attribute_info {
    u2 attribute_name_index;
    u4 attribute_length;
    //u1 *info; //[attribute_length]; Replaced by the union

    union {
        ConstantValue_attribute cva;
        Code_attribute ca;
        Exceptions_attribute ea;
        InnerClasses_attribute ica;
        Synthetic_attribute sa;
        SourceFile_attribute sfa;
        LineNumberTable_attribute lnta;
        LocalVariableTable_attribute lvta;
        Deprecated_attribute da;
    };
} attribute_info;

typedef struct _field_info {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info *attributes; //[attributes_count];
} field_info;

typedef struct _method_info {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info *attributes; //[attributes_count];
} method_info;

typedef struct _ClassFile {
    u4 magic;
    u2 minor_version;
    u2 major_version;
    u2 constant_pool_count;
    cp_info *constant_pool; //[constant_pool_count-1];
    u2 access_flags;
    u2 this_class;
    u2 super_class;
    u2 interfaces_count;
    u2 *interfaces; //[interfaces_count];
    u2 fields_count;
    field_info *fields; //[fields_count];
    u2 methods_count;
    method_info *methods; //[methods_count];
    u2 attributes_count;
    attribute_info *attributes; //[attributes_count];
} ClassFile;

// Functions go here
extern int RC_ReadClassFile(char *path, ClassFile *cf);

#endif