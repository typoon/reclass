#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cfmodify.h"
#include "cfdump.h"
#include "helper.h"
#include "classfile.h"

/**
 * Adds a new CONSTANT_CLASS entry to the constant_pool and returns the index
 * in which it was added
 *
 * @para cf - The representation of the .class file
 * @param name - The name of the class
 */
int RC_CPAddClass(ClassFile *cf, char *name)
{
    int index;

    index = cf->constant_pool_count;
    cf->constant_pool_count += 1;


    cf->constant_pool = (cp_info *)realloc(cf->constant_pool, sizeof (cp_info) * (cf->constant_pool_count + 1));

    cf->constant_pool[index].tag = CONSTANT_CLASS;
    cf->constant_pool[index].ci.name_index = RC_CPAddUtf8(cf, name, strlen(name));

    return index;

}

/**
 * Adds a new CONSTANT_UTF8 entry to the constant pool and returns the index
 * in which it was added
 *
 * @param cf - The representation of the .class file
 * @param value - The UTF8 string
 * @param length - How many bytes in the 'value' parameter
 */
int RC_CPAddUtf8(ClassFile *cf, char *value, int length)
{
    int index;

    index = cf->constant_pool_count;
    cf->constant_pool_count += 1;

    cf->constant_pool = (cp_info *)realloc(cf->constant_pool, sizeof (cp_info) * (cf->constant_pool_count + 1));

    cf->constant_pool[index].tag = CONSTANT_UTF8;
    cf->constant_pool[index].utfi.length = length;
    cf->constant_pool[index].utfi.bytes = (u1 *)malloc(sizeof (u1) * length);
    memcpy(cf->constant_pool[index].utfi.bytes, value, length);

    return index;
}

/**
 * Adds a new CONSTANT_STRING entry to the constant pool and returns the index
 * in which it was added
 *
 * @param cf - The representation of the .class file
 * @param value - The contents of the string
 */
int RC_CPAddString(ClassFile *cf, char *value)
{
    int index;

    index = cf->constant_pool_count;
    cf->constant_pool_count += 1;


    cf->constant_pool = (cp_info *)realloc(cf->constant_pool, sizeof (cp_info) * (cf->constant_pool_count + 1));

    cf->constant_pool[index].tag = CONSTANT_STRING;
    cf->constant_pool[index].si.string_index =  RC_CPAddUtf8(cf, value, strlen(value));

    return index;
}

/**
 * Adds a new CONSTANT_INTEGER entry to the constant pool and returns the index
 * in which it was added
 *
 * @param cf - The representation of the .class file
 * @param value - The integer value
 */
int RC_CPAddInteger(ClassFile *cf, u4 value)
{
    int index;

    index = cf->constant_pool_count;
    cf->constant_pool_count += 1;


    cf->constant_pool = (cp_info *)realloc(cf->constant_pool, sizeof (cp_info) * (cf->constant_pool_count + 1));

    cf->constant_pool[index].tag = CONSTANT_INTEGER;
    cf->constant_pool[index].ii.bytes = swapendi(value);

    return index;
}

int RC_RenameClass(ClassFile *cf, char *name)
{
    int index;

    index = cf->constant_pool[cf->this_class].ci.name_index;

    cf->constant_pool[index].utfi.length = strlen(name);
    free(cf->constant_pool[index].utfi.bytes);

    cf->constant_pool[index].utfi.bytes = (u1 *)malloc(sizeof(u1) * strlen(name));
    memcpy(cf->constant_pool[index].utfi.bytes, name, strlen(name));

    return CF_OK;

}

/**
 * Changes the code attribute for a method and re-sets the attribute length
 * parameter accordingly.
 * If the method cannot be found, returns CF_NOTOK.
 *
 * @param cf - The representation of the .class file
 * @param method - The pointer to the method in the ClassFile method array,
 *                 retrieved by calling RC_GetMethod()
 * @param code - The new set of opcodes to replace the old one
 * @param code_length - How many bytes in the 'code' parameter
 * @param max_stack - The new maximum size of the operand stack. If this won't
 *                    change, set it to 0 to keep the old value
 * @param max_locals - The new maximum amount of local variables. If this won't
 *                     change, set it to 0 to keep the old value.
 */
int RC_ChangeMethodCodeAttribute(ClassFile *cf, method_info *method, u1 *code, int code_length, int max_stack, int max_locals)
{
    int j;
    int found = 0;
    char *attr_name;

    for(j = 0; j < method->attributes_count; j++) {

        attr_name = nameIndexToString(cf, method->attributes[j].attribute_name_index);

        if(strncmp(attr_name, ATTR_CODE, strlen(attr_name)) == 0) {
            found = 1;

            if(max_stack > 0) {
                method->attributes[j].ca.max_stack = max_stack;
            }

            if(max_locals > 0) {
                method->attributes[j].ca.max_locals = max_locals;
            }

            // Subtract the old code length and replace with the new one
            method->attributes[j].attribute_length -= method->attributes[j].ca.code_length;
            method->attributes[j].ca.code_length = code_length;
            method->attributes[j].attribute_length += code_length;

            // Reallocate the size of the code area
            method->attributes[j].ca.code = (u1 *)realloc(method->attributes[j].ca.code, code_length * sizeof(u1));
            memcpy(method->attributes[j].ca.code, code, code_length);
        }

        free(attr_name);
    }


    if(found)
        return CF_OK;

    return CF_NOTOK;

}

int RC_CPAddNameAndType(ClassFile *cf, char *name, char *type)
{

    int index;

    index = cf->constant_pool_count;
    cf->constant_pool_count += 1;

    cf->constant_pool = (cp_info *)realloc(cf->constant_pool, sizeof (cp_info) * (cf->constant_pool_count + 1));

    cf->constant_pool[index].tag = CONSTANT_NAMEANDTYPE;
    cf->constant_pool[index].nti.name_index = RC_CPAddUtf8(cf, name, strlen(name));
    cf->constant_pool[index].nti.descriptor_index = RC_CPAddUtf8(cf, type, strlen(type));

    return index;

}

int RC_CPAddMethodRef(ClassFile *cf, int class_index, int name_and_type_index)
{
    int index;

    index = cf->constant_pool_count;
    cf->constant_pool_count += 1;

    cf->constant_pool = (cp_info *)realloc(cf->constant_pool, sizeof (cp_info) * (cf->constant_pool_count + 1));

    cf->constant_pool[index].tag = CONSTANT_METHODREF;
    cf->constant_pool[index].mri.class_index = class_index;
    cf->constant_pool[index].mri.name_and_type_index = name_and_type_index;

    return index;
}

/**
 * This function adds a new method to the current class in the ClassFile
 * It returns the index into the constant_pool for the Methodref_info structure
 * and the method_info structure in the 'method' output parameter.
 * The method created has max_stack and max_locals set to 0, and a code
 * attribute of length 2, with a nop and a return instruction.
 * You should call RC_ChangeMethodCodeAttribute to change the code parameter
 * of this method with whatever you want.
 *
 * @param cf -
 * @param name - Name of the method
 * @param descriptor - Descriptor of the method in the format specified by the
 *                     Java .class Specification
 * @param access_flags - Access permissions to the method (ACC_*)
 * @param method - Variable where the method_info structure created for this
 *                 method will be returned
 */
int RC_AddMethod(ClassFile *cf, char *name, char *descriptor, int access_flags, method_info **method)
{
    int name_and_type_index;
    int attribute_name_index;
    int methodref_index;
    method_info *m;

    m = (method_info *)malloc(sizeof(method_info));

    name_and_type_index = RC_CPAddNameAndType(cf, name, descriptor);

    m->access_flags = access_flags;
    m->name_index = cf->constant_pool[name_and_type_index].nti.name_index;
    m->descriptor_index = cf->constant_pool[name_and_type_index].nti.descriptor_index;

    // Add the code attribute
    attribute_name_index = RC_CPAddUtf8(cf, ATTR_CODE, strlen(ATTR_CODE));

    m->attributes_count = 1; // Code attribute
    m->attributes = (attribute_info *)malloc(sizeof(attribute_info));
    m->attributes[0].attribute_name_index = attribute_name_index;
    m->attributes[0].attribute_length = 14;

    m->attributes[0].ca.max_stack  = 0;
    m->attributes[0].ca.max_locals = 0;
    m->attributes[0].ca.code_length = 2;
    m->attributes[0].ca.code = (u1 *)malloc(sizeof(u1) * m->attributes[0].ca.code_length);
    memcpy(m->attributes[0].ca.code, "\x00\xB1", 2); // nop and return

    m->attributes[0].ca.exception_table_length = 0;
    m->attributes[0].ca.exception_table = NULL;

    m->attributes[0].ca.attributes_count = 0;
    m->attributes[0].ca.attributes = NULL;

    // Add the method to the classfile
    cf->methods_count++;
    cf->methods = (method_info *)realloc(cf->methods, sizeof (method_info) * (cf->methods_count));
    memcpy(&cf->methods[cf->methods_count-1], m, sizeof(method_info));

    // Create reference to the method in the Constant Pool
    methodref_index = RC_CPAddMethodRef(cf, cf->this_class, name_and_type_index);

    free(m);
    *method = &cf->methods[cf->methods_count-1];
    return methodref_index;

}