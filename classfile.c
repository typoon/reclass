/*
 * classfile.c
 *
 * Created by Henrique M.D.
 *
 * Copyright (c) 2011 Gilgamesh
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * Neither the name of the project's author nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "reclass.h"
#include "classfile.h"
#include "helper.h"



// Local functions prototypes
static int readConstantPool(ClassFile *cf, FILE *f);
static int readInterfaces(ClassFile *cf, FILE *f);
static int readFields(ClassFile *cf, FILE *f);
static int readMethods(ClassFile *cf, FILE *f);
static int readAttributeInfo(ClassFile *cf, attribute_info *af, FILE *f);

int RC_ReadClassFile(char *path, ClassFile *cf)
{
    int i;
    FILE *f;


    f = fopen(path, "r");
    if(f == NULL) {
        debug(DBG_ERROR, "Impossible to open file %s\n", path);
        return CF_NOTOK;
    }

    // Read the magic number
    fread(&cf->magic, 1, sizeof (cf->magic), f);
    cf->magic = swapendi(cf->magic);

    if(cf->magic != JAVA_MAGIC) {
        debug(DBG_ERROR, "This is not a JAVA class file (%s) (%08X)\n", path, cf->magic);
        fclose(f);
        return CF_NOTOK;
    }

    // Read the minor and major version
    fread(&cf->minor_version, 1, sizeof (cf->minor_version), f);
    fread(&cf->major_version, 1, sizeof (cf->major_version), f);

    cf->minor_version = swapends(cf->minor_version);
    cf->major_version = swapends(cf->major_version);

    if(readConstantPool(cf, f) == CF_NOTOK) {
        fclose(f);
        return CF_NOTOK;
    }

    // If the number of LONGs/DOUBLEs read is odd, then we
    // should stop swapping the endianess of the bytes
    // But I have NO IDEA WHY!

    fread(&cf->access_flags, 1, sizeof (cf->access_flags), f);
    fread(&cf->this_class, 1, sizeof (cf->this_class), f);
    fread(&cf->super_class, 1, sizeof (cf->super_class), f);

    cf->access_flags = swapends(cf->access_flags);
    cf->this_class = swapends(cf->this_class);
    cf->super_class = swapends(cf->super_class);


    if(readInterfaces(cf, f) == CF_NOTOK) {
        // TODO
        // Need to free the memory from the constant pool here

        fclose(f);
        return CF_NOTOK;
    }

    if(readFields(cf, f) == CF_NOTOK) {
        // TODO
        // Need to free the memory from the constant pool here

        fclose(f);
        return CF_NOTOK;
    }

    if(readMethods(cf, f) == CF_NOTOK) {
        // TODO
        // Need to free the memory from the constant pool here

        fclose(f);
        return CF_NOTOK;
    }

    fread(&cf->attributes_count, 1, sizeof (cf->attributes_count), f);
    cf->attributes_count = swapends(cf->attributes_count);

    if(cf->attributes_count > 0) {
        cf->attributes = (attribute_info *)calloc(cf->attributes_count, sizeof (attribute_info));
        debug(DBG_WARN, "readClassFile - Will read %d attributes\n", cf->attributes_count);

        for(i = 0; i < cf->attributes_count; i++) {
            readAttributeInfo(cf, &cf->attributes[i], f);
        }
    }

    return CF_OK;
}

static int readConstantPool(ClassFile *cf, FILE *f)
{
    int i;
    int index = 1;
    u1 tag;
    u2 cp_items;

    u2 tmpu2;
    u4 tmpu4;

    fread(&cf->constant_pool_count, 1, sizeof (cf->constant_pool_count), f);

    cf->constant_pool_count = swapends(cf->constant_pool_count);
    cp_items = cf->constant_pool_count;

    debug(DBG_WARN, "Items in the constant pool: %d\n", cp_items);

    if(cp_items > 0) {
        cf->constant_pool = (cp_info *)calloc(cp_items + 1, sizeof (cp_info));
    } else {
        debug(DBG_ERROR, "Constant pool is empty. This does not seem right\n");
        return CF_NOTOK;
    }

    // All references in the constant pool are made considering 1 as the
    // first index. So we ignore position [0] in the array, and start from
    // position 1 :)
    // from http://java.sun.com/docs/books/jvms/second_edition/html/ClassFile.doc.html#1348
    // The constant_pool table is indexed from 1 to constant_pool_count-1.
    for(i = 1; i <= cp_items - 1; i++) {
        fread(&tag, 1, 1, f);
        cf->constant_pool[index].tag = tag;

        switch(tag) {
        case CONSTANT_CLASS:
            fread(&tmpu2, 1, sizeof (tmpu2), f);
            cf->constant_pool[index].ci.name_index = swapends(tmpu2);
            break;

        case CONSTANT_FIELDREF:
            fread(&tmpu2, 1, sizeof (tmpu2), f);
            cf->constant_pool[index].fri.class_index = swapends(tmpu2);

            fread(&tmpu2, 1, sizeof (tmpu2), f);
            cf->constant_pool[index].fri.name_and_type_index = swapends(tmpu2);
            break;

        case CONSTANT_METHODREF:
            fread(&tmpu2, 1, sizeof (tmpu2), f);
            cf->constant_pool[index].mri.class_index = swapends(tmpu2);

            fread(&tmpu2, 1, sizeof (tmpu2), f);
            cf->constant_pool[index].mri.name_and_type_index = swapends(tmpu2);
            break;

        case CONSTANT_INTERFACEMETHODREF:
            fread(&tmpu2, 1, sizeof (tmpu2), f);
            cf->constant_pool[index].imri.class_index = swapends(tmpu2);

            fread(&tmpu2, 1, sizeof (tmpu2), f);
            cf->constant_pool[index].imri.name_and_type_index = swapends(tmpu2);
            break;

        case CONSTANT_STRING:
            fread(&tmpu2, 1, sizeof (tmpu2), f);
            cf->constant_pool[index].si.string_index = swapends(tmpu2);
            break;

        case CONSTANT_INTEGER:
            fread(&tmpu4, 1, sizeof (tmpu4), f);
            cf->constant_pool[index].ii.bytes = swapendi(tmpu4);
            break;

        case CONSTANT_FLOAT:
            fread(&tmpu4, 1, sizeof (tmpu4), f);
            cf->constant_pool[index].fi.bytes = swapendi(tmpu4);
            break;

        case CONSTANT_LONG:
            debug(DBG_WARN, "Found long at index %d\n", index);

            fread(&tmpu4, 1, sizeof (tmpu4), f);
            cf->constant_pool[index].li.high_bytes = swapendi(tmpu4);
            cf->constant_pool[index + 1].li.high_bytes = swapendi(tmpu4);

            fread(&tmpu4, 1, sizeof (tmpu4), f);
            cf->constant_pool[index].li.low_bytes = swapendi(tmpu4);
            cf->constant_pool[index + 1].li.low_bytes = swapendi(tmpu4);

            ++index;
            ++i;
            break;

        case CONSTANT_DOUBLE:
            debug(DBG_WARN, "Found long at index %d\n", index);

            fread(&tmpu4, 1, sizeof (tmpu4), f);
            cf->constant_pool[index].di.high_bytes = swapendi(tmpu4);
            cf->constant_pool[index + 1].di.high_bytes = swapendi(tmpu4);

            fread(&tmpu4, 1, sizeof (tmpu4), f);
            cf->constant_pool[index].di.low_bytes = swapendi(tmpu4);
            cf->constant_pool[index + 1].di.low_bytes = swapendi(tmpu4);

            ++index;
            ++i;
            break;

        case CONSTANT_NAMEANDTYPE:
            fread(&tmpu2, 1, sizeof (tmpu2), f);
            cf->constant_pool[index].nti.name_index = swapends(tmpu2);

            fread(&tmpu2, 1, sizeof (tmpu2), f);
            cf->constant_pool[index].nti.descriptor_index = swapends(tmpu2);
            break;

        case CONSTANT_UTF8:
            fread(&tmpu2, 1, sizeof (tmpu2), f);
            cf->constant_pool[index].utfi.length = swapends(tmpu2);

            cf->constant_pool[index].utfi.bytes = (u1 *)malloc(swapends(tmpu2) * sizeof (u1));

            fread(cf->constant_pool[index].utfi.bytes, 1, swapends(tmpu2), f);
            break;
        }

        ++index;

    }

    // TODO
    // Need to validate if this constant pool is valid
    // by applying the checks from the JVM documentation

    return CF_OK;
}

static int readInterfaces(ClassFile *cf, FILE *f)
{
    int i;
    u2 if_items;
    u2 tmpu2;

    fread(&cf->interfaces_count, 1, sizeof (cf->interfaces_count), f);

    cf->interfaces_count = swapends(cf->interfaces_count);
    if_items = cf->interfaces_count;

    debug(DBG_WARN, "Items in the interfaces array: %d\n", if_items);

    if(if_items > 0) {
        cf->interfaces = (u2 *)calloc(if_items, sizeof (u2));
    } else {
        cf->interfaces = NULL;
    }

    for(i = 0; i < if_items; i++) {
        fread(&tmpu2, 1, sizeof (tmpu2), f);
        cf->interfaces[i] = swapends(tmpu2);
    }

    // TODO
    // Validate and check if every interface listed here is present in the
    // constant pool, and if the corresponding contant_pool entry is of the
    // type CONSTANT_CLASS_INFO

    return CF_OK;
}

static int readFields(ClassFile *cf, FILE *f)
{
    int i;
    int j;
    u2 fld_items;
    u2 tmpu2;

    fread(&cf->fields_count, 1, sizeof (cf->fields_count), f);

    cf->fields_count = swapends(cf->fields_count);
    fld_items = cf->fields_count;

    debug(DBG_WARN, "Items in the fields array: %d\n", fld_items);

    if(fld_items > 0) {
        cf->fields = (field_info *)calloc(fld_items, sizeof (field_info));
    } else {
        cf->fields = NULL;
    }

    for(i = 0; i < fld_items; i++) {
        fread(&tmpu2, 1, sizeof (tmpu2), f);
        cf->fields[i].access_flags = swapends(tmpu2);

        fread(&tmpu2, 1, sizeof (tmpu2), f);
        cf->fields[i].name_index = swapends(tmpu2);

        fread(&tmpu2, 1, sizeof (tmpu2), f);
        cf->fields[i].descriptor_index = swapends(tmpu2);

        fread(&tmpu2, 1, sizeof (tmpu2), f);
        cf->fields[i].attributes_count = swapends(tmpu2);

        if(cf->fields[i].attributes_count > 0) {
            cf->fields[i].attributes = (attribute_info *)calloc(cf->fields[i].attributes_count, sizeof (attribute_info));
            debug(DBG_WARN, "readFields - Will read %d attributes\n", cf->fields[i].attributes_count);

            for(j = 0; j < cf->fields[i].attributes_count; j++) {
                if(readAttributeInfo(cf, &cf->fields[i].attributes[j], f) == CF_NOTOK)
                    return CF_NOTOK;
            }
        } else {
            cf->fields[i].attributes = NULL;
        }

        debug(DBG_WARN, "Field [%d] access_flags = %d\n", i, cf->fields[i].access_flags);
        debug(DBG_WARN, "Field [%d] name_index = %d\n", i, cf->fields[i].name_index);
        debug(DBG_WARN, "Field [%d] descriptor_index = %d\n", i, cf->fields[i].descriptor_index);
        debug(DBG_WARN, "Field [%d] attributes_count = %d\n", i, cf->fields[i].attributes_count);

    }

    // TODO
    // Validate that the fields are valid

    return CF_OK;
}

static int readMethods(ClassFile *cf, FILE *f)
{
    int i;
    int j;
    u2 mth_items;
    u2 tmpu2;

    fread(&cf->methods_count, 1, sizeof (cf->methods_count), f);

    cf->methods_count = swapends(cf->methods_count);
    mth_items = cf->methods_count;

    debug(DBG_WARN, "Items in the methods array: %d\n", mth_items);

    if(mth_items > 0) {
        cf->methods = (method_info *)calloc(mth_items, sizeof (method_info));
    } else {
        cf->methods = NULL;
    }

    for(i = 0; i < mth_items; i++) {
        fread(&tmpu2, 1, sizeof (tmpu2), f);
        cf->methods[i].access_flags = swapends(tmpu2);

        fread(&tmpu2, 1, sizeof (tmpu2), f);
        cf->methods[i].name_index = swapends(tmpu2);

        fread(&tmpu2, 1, sizeof (tmpu2), f);
        cf->methods[i].descriptor_index = swapends(tmpu2);

        fread(&tmpu2, 1, sizeof (tmpu2), f);
        cf->methods[i].attributes_count = swapends(tmpu2);

        debug(DBG_WARN, "Field [%d] access_flags = %d\n", i, cf->methods[i].access_flags);
        debug(DBG_WARN, "Field [%d] name_index = %d\n", i, cf->methods[i].name_index);
        debug(DBG_WARN, "Field [%d] descriptor_index = %d\n", i, cf->methods[i].descriptor_index);
        debug(DBG_WARN, "Field [%d] attributes_count = %d\n", i, cf->methods[i].attributes_count);

        if(cf->methods[i].attributes_count > 0) {
            cf->methods[i].attributes = (attribute_info *)calloc(cf->methods[i].attributes_count, sizeof (attribute_info));
            debug(DBG_WARN, "readMethods - Will read %d attributes\n", cf->methods[i].attributes_count);

            for(j = 0; j < cf->methods[i].attributes_count; j++) {
                if(readAttributeInfo(cf, &cf->methods[i].attributes[j], f) == CF_NOTOK)
                    return CF_NOTOK;
            }
        }

    }

    // TODO
    // Validate that the methods are valid

    return CF_OK;
}

static int readAttributeInfo(ClassFile *cf, attribute_info *ai, FILE *f)
{
    int i;
    int length;
    u1 tmpu1p[1024];
    u2 tmpu2;
    u4 tmpu4;

    fread(&tmpu2, 1, sizeof (tmpu2), f);
    ai->attribute_name_index = swapends(tmpu2);

    fread(&tmpu4, 1, sizeof (tmpu4), f);
    ai->attribute_length = swapendi(tmpu4);

    if(ai->attribute_length > 0) {
        length = cf->constant_pool[ai->attribute_name_index].utfi.length;

        memset(tmpu1p, 0, sizeof (tmpu1p));
        for(i = 0; i < length; i++)
            tmpu1p[i] = cf->constant_pool[ai->attribute_name_index].utfi.bytes[i];

        debug(DBG_WARN, "readAttributeInfo - Will read attribute %s (Length: %d)\n", tmpu1p, ai->attribute_length);

        if(strncmp((const char *)tmpu1p, ATTR_CONSTANTVALUE, length) == 0) {
            if(ai->attribute_length != 2) {
                debug(DBG_ERROR, "Attribute length (%d) does not match expected (2)\n",
                        ai->attribute_length);

                return CF_NOTOK;
            }

            fread(&ai->cva.constantvalue_index, 1, sizeof (ai->cva.constantvalue_index), f);
            ai->cva.constantvalue_index = swapends(ai->cva.constantvalue_index);

        }

        if(strncmp((const char *)tmpu1p, ATTR_CODE, length) == 0) {
            fread(&ai->ca.max_stack, 1, sizeof (ai->ca.max_stack), f);
            ai->ca.max_stack = swapends(ai->ca.max_stack);

            fread(&ai->ca.max_locals, 1, sizeof (ai->ca.max_locals), f);
            ai->ca.max_locals = swapends(ai->ca.max_locals);

            fread(&ai->ca.code_length, 1, sizeof (ai->ca.code_length), f);
            ai->ca.code_length = swapendi(ai->ca.code_length);

            if(ai->ca.code_length > 0) {
                ai->ca.code = (u1 *)calloc(ai->ca.code_length, sizeof (u1));
                fread(ai->ca.code, 1, ai->ca.code_length, f);
            } else {
                ai->ca.code = NULL;
            }

            debug(DBG_WARN, "\tai->ca.code_length = %d\n", ai->ca.code_length);

            fread(&ai->ca.exception_table_length, 1, sizeof (ai->ca.exception_table_length), f);
            ai->ca.exception_table_length = swapends(ai->ca.exception_table_length);

            debug(DBG_WARN, "\tai->ca.exception_table_length = %d\n", ai->ca.exception_table_length);

            if(ai->ca.exception_table_length > 0) {
                ai->ca.exception_table = (Exception_table *)calloc(ai->ca.exception_table_length, sizeof (Exception_table));

                for(i = 0; i < ai->ca.exception_table_length; i++) {
                    fread(&ai->ca.exception_table[i].start_pc, 1, sizeof (ai->ca.exception_table[i].start_pc), f);
                    ai->ca.exception_table[i].start_pc = swapends(ai->ca.exception_table[i].start_pc);

                    fread(&ai->ca.exception_table[i].end_pc, 1, sizeof (ai->ca.exception_table[i].end_pc), f);
                    ai->ca.exception_table[i].end_pc = swapends(ai->ca.exception_table[i].end_pc);

                    fread(&ai->ca.exception_table[i].handler_pc, 1, sizeof (ai->ca.exception_table[i].handler_pc), f);
                    ai->ca.exception_table[i].handler_pc = swapends(ai->ca.exception_table[i].handler_pc);

                    fread(&ai->ca.exception_table[i].catch_type, 1, sizeof (ai->ca.exception_table[i].catch_type), f);
                    ai->ca.exception_table[i].catch_type = swapends(ai->ca.exception_table[i].catch_type);

                }
            }

            fread(&ai->ca.attributes_count, 1, sizeof (ai->ca.attributes_count), f);
            ai->ca.attributes_count = swapends(ai->ca.attributes_count);

            if(ai->ca.attributes_count > 0) {
                ai->ca.attributes = (attribute_info *)calloc(ai->ca.attributes_count, sizeof (attribute_info));

                for(i = 0; i < ai->ca.attributes_count; i++) {
                    if(readAttributeInfo(cf, &ai->ca.attributes[i], f) == CF_NOTOK) {
                        return CF_NOTOK;
                    }
                }
            } else {
                ai->ca.attributes = NULL;
            }

        }


        if(strncmp((const char *)tmpu1p, ATTR_EXCEPTIONS, length) == 0) {

            fread(&ai->ea.number_of_exceptions, 1, sizeof (ai->ea.number_of_exceptions), f);
            ai->ea.number_of_exceptions = swapends(ai->ea.number_of_exceptions);

            if(ai->ea.number_of_exceptions > 0) {
                ai->ea.exception_index_table = (u2 *)calloc(ai->ea.number_of_exceptions, sizeof (u2));

                for(i = 0; i < ai->ea.number_of_exceptions; i++) {
                    fread(&tmpu2, 1, sizeof (u2), f);
                    ai->ea.exception_index_table[i] = swapends(tmpu2);
                }

            } else {
                ai->ea.exception_index_table = NULL;
            }

        }

        if(strncmp((const char *)tmpu1p, ATTR_INNERCLASSES, length) == 0) {
            fread(&ai->ica.number_of_classes, 1, sizeof (ai->ica.number_of_classes), f);
            ai->ica.number_of_classes = swapends(ai->ica.number_of_classes);

            if(ai->ica.number_of_classes > 0) {
                ai->ica.classes = (Classes_table *)calloc(ai->ica.number_of_classes, sizeof (Classes_table));

                for(i = 0; i < ai->ica.number_of_classes; i++) {
                    fread(&tmpu2, 1, sizeof (u2), f);
                    ai->ica.classes[i].inner_class_info_index = swapends(tmpu2);

                    fread(&tmpu2, 1, sizeof (u2), f);
                    ai->ica.classes[i].outer_class_info_index = swapends(tmpu2);

                    fread(&tmpu2, 1, sizeof (u2), f);
                    ai->ica.classes[i].inner_name_index = swapends(tmpu2);

                    fread(&tmpu2, 1, sizeof (u2), f);
                    ai->ica.classes[i].inner_class_access_flags = swapends(tmpu2);
                }

            } else {
                ai->ica.classes = NULL;
            }

        }

        if(strncmp((const char *)tmpu1p, ATTR_SYNTHETIC, length) == 0) {
            // Nothing to do here
        }

        if(strncmp((const char *)tmpu1p, ATTR_SOURCEFILE, length) == 0) {
            fread(&ai->sfa.sourcefile_index, 1, sizeof (ai->sfa.sourcefile_index), f);
            ai->sfa.sourcefile_index = swapends(ai->sfa.sourcefile_index);

        }

        if(strncmp((const char *)tmpu1p, ATTR_LINENUMBERTABLE, length) == 0) {
            fread(&ai->lnta.line_number_table_length, 1, sizeof (ai->lnta.line_number_table_length), f);
            ai->lnta.line_number_table_length = swapends(ai->lnta.line_number_table_length);

            debug(DBG_WARN, "\tai->lnta.line_number_table_length = %d\n", ai->lnta.line_number_table_length);

            if(ai->lnta.line_number_table_length > 0) {
                ai->lnta.line_number_table = (LineNumber_table *)calloc(ai->lnta.line_number_table_length, sizeof (LineNumber_table));

                for(i = 0; i < ai->lnta.line_number_table_length; i++) {
                    fread(&tmpu2, 1, sizeof (u2), f);
                    ai->lnta.line_number_table[i].start_pc = swapends(tmpu2);

                    fread(&tmpu2, 1, sizeof (u2), f);
                    ai->lnta.line_number_table[i].line_number = swapends(tmpu2);
                }
            }
        }

        if(strncmp((const char *)tmpu1p, ATTR_LOCALVARIABLETABLE, length) == 0) {

            fread(&ai->lvta.local_variable_table_length, 1, sizeof (ai->lvta.local_variable_table_length), f);
            ai->lvta.local_variable_table_length = swapends(ai->lvta.local_variable_table_length);

            if(ai->lvta.local_variable_table_length > 0) {
                ai->lvta.local_variable_table = (LocalVariable_table *)calloc(ai->lvta.local_variable_table_length, sizeof (LocalVariable_table));

                for(i = 0; i < ai->lvta.local_variable_table_length; i++) {
                    fread(&tmpu2, 1, sizeof (u2), f);
                    ai->lvta.local_variable_table[i].start_pc = swapends(tmpu2);

                    fread(&tmpu2, 1, sizeof (u2), f);
                    ai->lvta.local_variable_table[i].length = swapends(tmpu2);

                    fread(&tmpu2, 1, sizeof (u2), f);
                    ai->lvta.local_variable_table[i].name_index = swapends(tmpu2);

                    fread(&tmpu2, 1, sizeof (u2), f);
                    ai->lvta.local_variable_table[i].descriptor_index = swapends(tmpu2);

                    fread(&tmpu2, 1, sizeof (u2), f);
                    ai->lvta.local_variable_table[i].index = swapends(tmpu2);
                }

            }

        }

        if(strncmp((const char *)tmpu1p, ATTR_DEPRECATED, length) == 0) {
            // Nothing to do here
        }

        if(strncmp((const char *)tmpu1p, ATTR_STACKMAPTABLE, length) == 0) {
            // TODO: Learn about this. Read JSR202

            char buffer[2048];
            fread(buffer, 1, ai->attribute_length, f);
        }

        //af->info = (u1 *)calloc(af->attribute_length, sizeof(u1));
        //fread(&af->info[0], 1, af->attribute_length, f);
    }

    // TODO
    // Validate that attribute is valid

    return CF_OK;

}
