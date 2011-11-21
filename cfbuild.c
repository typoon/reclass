#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cfbuild.h"
#include "classfile.h"
#include "helper.h"
#include "cfmodify.h"

int buildConstantPool(ClassFile *cf, FILE *f)
{
    int i;
    u2 tmpu2;
    u4 tmpu4;

    tmpu2 = swapends(cf->constant_pool_count);
    fwrite(&tmpu2, 1, sizeof (cf->constant_pool_count), f);

    for(i = 1; i <= cf->constant_pool_count - 1; i++) {

        fwrite(&cf->constant_pool[i].tag, 1, sizeof (cf->constant_pool[i].tag), f);
        switch(cf->constant_pool[i].tag) {
        case CONSTANT_CLASS:
            tmpu2 = swapends(cf->constant_pool[i].ci.name_index);
            fwrite(&tmpu2, 1, sizeof (tmpu2), f);
            break;

        case CONSTANT_FIELDREF:
            tmpu2 = swapends(cf->constant_pool[i].fri.class_index);
            fwrite(&tmpu2, 1, sizeof (tmpu2), f);

            tmpu2 = swapends(cf->constant_pool[i].fri.name_and_type_index);
            fwrite(&tmpu2, 1, sizeof (tmpu2), f);
            break;

        case CONSTANT_METHODREF:
            tmpu2 = swapends(cf->constant_pool[i].mri.class_index);
            fwrite(&tmpu2, 1, sizeof (tmpu2), f);

            tmpu2 = swapends(cf->constant_pool[i].mri.name_and_type_index);
            fwrite(&tmpu2, 1, sizeof (tmpu2), f);
            break;

        case CONSTANT_INTERFACEMETHODREF:
            tmpu2 = swapends(cf->constant_pool[i].imri.class_index);
            fwrite(&tmpu2, 1, sizeof (tmpu2), f);

            tmpu2 = swapends(cf->constant_pool[i].imri.name_and_type_index);
            fwrite(&tmpu2, 1, sizeof (tmpu2), f);
            break;

        case CONSTANT_STRING:
            tmpu2 = swapends(cf->constant_pool[i].si.string_index);
            fwrite(&tmpu2, 1, sizeof (tmpu2), f);
            break;

        case CONSTANT_INTEGER:
            tmpu4 = swapendi(cf->constant_pool[i].ii.bytes);
            fwrite(&tmpu4, 1, sizeof (tmpu4), f);
            break;

        case CONSTANT_FLOAT:
            tmpu4 = swapendi(cf->constant_pool[i].fi.bytes);
            fwrite(&tmpu4, 1, sizeof (tmpu4), f);
            break;

        case CONSTANT_LONG:
            tmpu4 = swapendi(cf->constant_pool[i].li.high_bytes);
            fwrite(&tmpu4, 1, sizeof (tmpu4), f);

            tmpu4 = swapendi(cf->constant_pool[i].li.low_bytes);
            fwrite(&tmpu4, 1, sizeof (tmpu4), f);

            ++i;
            break;

        case CONSTANT_DOUBLE:
            tmpu4 = swapendi(cf->constant_pool[i].di.high_bytes);
            fwrite(&tmpu4, 1, sizeof (tmpu4), f);

            tmpu4 = swapendi(cf->constant_pool[i].di.low_bytes);
            fwrite(&tmpu4, 1, sizeof (tmpu4), f);

            ++i;
            break;

        case CONSTANT_NAMEANDTYPE:
            tmpu2 = swapends(cf->constant_pool[i].nti.name_index);
            fwrite(&tmpu2, 1, sizeof (tmpu2), f);

            tmpu2 = swapends(cf->constant_pool[i].nti.descriptor_index);
            fwrite(&tmpu2, 1, sizeof (tmpu2), f);
            break;

        case CONSTANT_UTF8:
            tmpu2 = swapends(cf->constant_pool[i].utfi.length);
            fwrite(&tmpu2, 1, sizeof (tmpu2), f);

            fwrite(cf->constant_pool[i].utfi.bytes, 1, cf->constant_pool[i].utfi.length, f);
            break;
        }
    }

    return CF_OK;
}

int buildInterfaces(ClassFile *cf, FILE *f)
{
    int i;
    u2 tmpu2;

    tmpu2 = swapends(cf->interfaces_count);
    fwrite(&tmpu2, 1, sizeof (cf->interfaces_count), f);

    for(i = 0; i < cf->interfaces_count; i++) {
        tmpu2 = swapends(cf->interfaces[i]);
        fwrite(&tmpu2, 1, sizeof (u2), f);
    }

    return CF_OK;
}

int buildAttributes(ClassFile *cf, attribute_info *ai, FILE *f)
{
    int i;
    int length;
    u1 tmpu1p[1024];
    u2 tmpu2;
    u4 tmpu4;

    memset(tmpu1p, 0, sizeof (tmpu1p));

    tmpu2 = swapends(ai->attribute_name_index);
    fwrite(&tmpu2, 1, sizeof (ai->attribute_name_index), f);

    tmpu4 = swapendi(ai->attribute_length);
    fwrite(&tmpu4, 1, sizeof (ai->attribute_length), f);

    if(ai->attribute_length > 0) {
        length = cf->constant_pool[ai->attribute_name_index].utfi.length;

        memset(tmpu1p, 0, sizeof (tmpu1p));
        for(i = 0; i < length; i++) {
            tmpu1p[i] = cf->constant_pool[ai->attribute_name_index].utfi.bytes[i];
        }


        if(strncmp((const char *)tmpu1p, ATTR_CONSTANTVALUE, length) == 0) {
            if(ai->attribute_length != 2) {
                debug(DBG_ERROR, "Attribute length (%d) does not match expected (2)\n",
                        ai->attribute_length);

                return CF_NOTOK;
            }

            tmpu2 = swapends(ai->cva.constantvalue_index);
            fwrite(&tmpu2, 1, sizeof (ai->cva.constantvalue_index), f);
        }

        if(strncmp((const char *)tmpu1p, ATTR_CODE, length) == 0) {
            tmpu2 = swapends(ai->ca.max_stack);
            fwrite(&tmpu2, 1, sizeof (ai->ca.max_stack), f);

            tmpu2 = swapends(ai->ca.max_locals);
            fwrite(&tmpu2, 1, sizeof (ai->ca.max_locals), f);

            tmpu4 = swapendi(ai->ca.code_length);
            fwrite(&tmpu4, 1, sizeof (ai->ca.code_length), f);

            if(ai->ca.code_length < 0) {
                debug(DBG_ERROR, "Code length cannot be 0");
                return CF_NOTOK;
            }

            fwrite(ai->ca.code, 1, ai->ca.code_length, f);

            tmpu2 = swapends(ai->ca.exception_table_length);
            fwrite(&tmpu2, 1, sizeof (ai->ca.exception_table_length), f);

            for(i = 0; i < ai->ca.exception_table_length; i++) {
                tmpu2 = swapends(ai->ca.exception_table[i].start_pc);
                fwrite(&tmpu2, 1, sizeof (ai->ca.exception_table[i].start_pc), f);

                tmpu2 = swapends(ai->ca.exception_table[i].end_pc);
                fwrite(&tmpu2, 1, sizeof (ai->ca.exception_table[i].end_pc), f);

                tmpu2 = swapends(ai->ca.exception_table[i].handler_pc);
                fwrite(&tmpu2, 1, sizeof (ai->ca.exception_table[i].handler_pc), f);

                tmpu2 = swapends(ai->ca.exception_table[i].catch_type);
                fwrite(&tmpu2, 1, sizeof (ai->ca.exception_table[i].catch_type), f);
            }

            tmpu2 = swapends(ai->ca.attributes_count);
            fwrite(&tmpu2, 1, sizeof (ai->ca.attributes_count), f);

            for(i = 0; i < ai->ca.attributes_count; i++) {
                if(buildAttributes(cf, &ai->ca.attributes[i], f) == CF_NOTOK)
                    return CF_NOTOK;
            }
        }

        if(strncmp((const char *)tmpu1p, ATTR_EXCEPTIONS, length) == 0) {
            tmpu2 = swapends(ai->ea.number_of_exceptions);
            fwrite(&tmpu2, 1, sizeof (ai->ea.number_of_exceptions), f);

            for(i = 0; i < ai->ea.number_of_exceptions; i++) {
                tmpu2 = swapends(ai->ea.exception_index_table[i]);
                fwrite(&tmpu2, 1, sizeof (ai->ea.exception_index_table[i]), f);
            }
        }


        if(strncmp((const char *)tmpu1p, ATTR_INNERCLASSES, length) == 0) {

            tmpu2 = swapends(ai->ica.number_of_classes);
            fwrite(&tmpu2, 1, sizeof (ai->ica.number_of_classes), f);

            for(i = 0; i < ai->ica.number_of_classes; i++) {
                tmpu2 = swapends(ai->ica.classes[i].inner_class_info_index);
                fwrite(&tmpu2, 1, sizeof (ai->ica.classes[i].inner_class_info_index), f);

                tmpu2 = swapends(ai->ica.classes[i].outer_class_info_index);
                fwrite(&tmpu2, 1, sizeof (ai->ica.classes[i].outer_class_info_index), f);

                tmpu2 = swapends(ai->ica.classes[i].inner_name_index);
                fwrite(&tmpu2, 1, sizeof (ai->ica.classes[i].inner_name_index), f);

                tmpu2 = swapends(ai->ica.classes[i].inner_class_access_flags);
                fwrite(&tmpu2, 1, sizeof (ai->ica.classes[i].inner_class_access_flags), f);
            }
        }

        if(strncmp((const char *)tmpu1p, ATTR_SYNTHETIC, length) == 0) {
            // Nothing to do here
        }

        if(strncmp((const char *)tmpu1p, ATTR_SOURCEFILE, length) == 0) {
            tmpu2 = swapends(ai->sfa.sourcefile_index);
            fwrite(&tmpu2, 1, sizeof (ai->sfa.sourcefile_index), f);
        }

        if(strncmp((const char *)tmpu1p, ATTR_LINENUMBERTABLE, length) == 0) {
            tmpu2 = swapends(ai->lnta.line_number_table_length);
            fwrite(&tmpu2, 1, sizeof (ai->lnta.line_number_table_length), f);

            for(i = 0; i < ai->lnta.line_number_table_length; i++) {
                tmpu2 = swapends(ai->lnta.line_number_table[i].start_pc);
                fwrite(&tmpu2, 1, sizeof (ai->lnta.line_number_table[i].start_pc), f);

                tmpu2 = swapends(ai->lnta.line_number_table[i].line_number);
                fwrite(&tmpu2, 1, sizeof (ai->lnta.line_number_table[i].line_number), f);
            }

        }

        if(strncmp((const char *)tmpu1p, ATTR_LOCALVARIABLETABLE, length) == 0) {
            tmpu2 = swapends(ai->lvta.local_variable_table_length);
            fwrite(&tmpu2, 1, sizeof (ai->lvta.local_variable_table_length), f);

            for(i = 0; i < ai->lvta.local_variable_table_length; i++) {
                tmpu2 = swapends(ai->lvta.local_variable_table[i].start_pc);
                fwrite(&tmpu2, 1, sizeof (ai->lvta.local_variable_table[i].start_pc), f);

                tmpu2 = swapends(ai->lvta.local_variable_table[i].length);
                fwrite(&tmpu2, 1, sizeof (ai->lvta.local_variable_table[i].length), f);

                tmpu2 = swapends(ai->lvta.local_variable_table[i].name_index);
                fwrite(&tmpu2, 1, sizeof (ai->lvta.local_variable_table[i].name_index), f);

                tmpu2 = swapends(ai->lvta.local_variable_table[i].descriptor_index);
                fwrite(&tmpu2, 1, sizeof (ai->lvta.local_variable_table[i].descriptor_index), f);

                tmpu2 = swapends(ai->lvta.local_variable_table[i].index);
                fwrite(&tmpu2, 1, sizeof (ai->lvta.local_variable_table[i].index), f);

            }

        }

        if(strncmp((const char *)tmpu1p, ATTR_DEPRECATED, length) == 0) {
            // Nothing to do here
        }

    }

    return CF_OK;
}

int buildFields(ClassFile *cf, FILE *f)
{
    int i;
    int j;
    u2 tmpu2;

    tmpu2 = swapends(cf->fields_count);
    fwrite(&tmpu2, 1, sizeof (cf->fields_count), f);

    for(i = 0; i < cf->fields_count; i++) {
        tmpu2 = swapends(cf->fields[i].access_flags);
        fwrite(&tmpu2, 1, sizeof (cf->fields[i].access_flags), f);

        tmpu2 = swapends(cf->fields[i].name_index);
        fwrite(&tmpu2, 1, sizeof (cf->fields[i].name_index), f);

        tmpu2 = swapends(cf->fields[i].descriptor_index);
        fwrite(&tmpu2, 1, sizeof (cf->fields[i].descriptor_index), f);

        tmpu2 = swapends(cf->fields[i].attributes_count);
        fwrite(&tmpu2, 1, sizeof (cf->fields[i].attributes_count), f);

        for(j = 0; j < cf->fields[i].attributes_count; j++) {
            if(buildAttributes(cf, &cf->fields[i].attributes[j], f) == CF_NOTOK)
                return CF_NOTOK;

        }

    }

    return CF_OK;
}

int buildMethods(ClassFile *cf, FILE *f)
{
    int i;
    int j;
    u2 tmpu2;

    tmpu2 = swapends(cf->methods_count);
    fwrite(&tmpu2, 1, sizeof (cf->methods_count), f);

    for(i = 0; i < cf->methods_count; i++) {
        tmpu2 = swapends(cf->methods[i].access_flags);
        fwrite(&tmpu2, 1, sizeof (cf->methods[i].access_flags), f);

        tmpu2 = swapends(cf->methods[i].name_index);
        fwrite(&tmpu2, 1, sizeof (cf->methods[i].name_index), f);

        tmpu2 = swapends(cf->methods[i].descriptor_index);
        fwrite(&tmpu2, 1, sizeof (cf->methods[i].descriptor_index), f);

        tmpu2 = swapends(cf->methods[i].attributes_count);
        fwrite(&tmpu2, 1, sizeof (cf->methods[i].attributes_count), f);

        for(j = 0; j < cf->methods[i].attributes_count; j++) {
            if(buildAttributes(cf, &cf->methods[i].attributes[j], f) == CF_NOTOK)
                return CF_NOTOK;
        }
    }

    return CF_OK;
}

/**
 * This method rebuilds the class!
 * It will automatically rename the class to the same name as the file
 * so it can be executed.
 *
 * @param cf - The ClassFile you want to turn into a .class
 * @param path - The directory where the .class will be saved
 * @param name - The name of the class without the .class extension
 */
int RC_BuildClassFile(ClassFile* cf, char *path, char* name)
{
    int i;
    FILE *f;
    char fname[512];
    u2 tmpu2;
    u4 tmpu4;

    sprintf(fname, "%s/%s.class", path, name);

    f = fopen(fname, "w+");
    if(f == NULL) {
        debug(DBG_ERROR, "Impossible to open file %s\n", path);
        return CF_NOTOK;
    }

    // Change the class name here
    RC_RenameClass(cf, name);

    tmpu4 = swapendi(cf->magic);
    fwrite(&tmpu4, 1, sizeof (cf->magic), f);

    tmpu2 = swapends(cf->minor_version);
    fwrite(&tmpu2, 1, sizeof (cf->minor_version), f);

    tmpu2 = swapends(cf->major_version);
    fwrite(&tmpu2, 1, sizeof (cf->major_version), f);

    if(buildConstantPool(cf, f) == CF_NOTOK) {
        fclose(f);
        return CF_NOTOK;
    }

    tmpu2 = swapends(cf->access_flags);
    fwrite(&tmpu2, 1, sizeof (cf->access_flags), f);

    tmpu2 = swapends(cf->this_class);
    fwrite(&tmpu2, 1, sizeof (cf->this_class), f);

    tmpu2 = swapends(cf->super_class);
    fwrite(&tmpu2, 1, sizeof (cf->super_class), f);

    if(buildInterfaces(cf, f) == CF_NOTOK) {
        fclose(f);
        return CF_NOTOK;
    }

    if(buildFields(cf, f) == CF_NOTOK) {
        fclose(f);
        return CF_NOTOK;
    }

    if(buildMethods(cf, f) == CF_NOTOK) {
        fclose(f);
        return CF_NOTOK;
    }

    tmpu2 = swapends(cf->attributes_count);
    fwrite(&tmpu2, 1, sizeof (cf->attributes_count), f);

    for(i = 0; i < cf->attributes_count; i++) {
        if(buildAttributes(cf, &cf->attributes[i], f) == CF_NOTOK) {
            fclose(f);
            return CF_NOTOK;
        }
    }


    fclose(f);

    return CF_OK;
}
