#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cfdump.h"
#include "cfget.h"

/**
 * This function searches the Constant Pool for a method with name
 * 'name', signature 'signature' within the class loaded in the 'cf'.
 * If found, it returns the index from the Constant Pool where it has
 * been found. If not found, it returns -1
 */
int RC_CPGetMethodRefIndexCurrentClass(ClassFile *cf, char *name, char *signature)
{
    int ret = -1;
    char *classNameTmp;
    
    classNameTmp = nameIndexToString(cf, cf->constant_pool[cf->this_class].ci.name_index);
    ret = RC_CPGetMethodRefIndex(cf, name, signature, classNameTmp);
    
    free(classNameTmp);
    
    return ret;
}

/**
 * This function searches the Constant Pool for a method with name
 * 'name', signature 'signature' within class 'class'.
 * If found, it returns the index from the Constant Pool where it has
 * been found. If not found, it returns -1
 */
int RC_CPGetMethodRefIndex(ClassFile *cf, char *name, char *signature, char *className)
{

    int i;
    char *nameTmp;
    char *signatureTmp;
    char *classNameTmp;
    int ret = -1;
    
    for(i = 1; i < cf->constant_pool_count; i++) {
        if(cf->constant_pool[i].tag == CONSTANT_METHODREF) {
            nameTmp = nameIndexToString(cf, cf->constant_pool[cf->constant_pool[i].mri.name_and_type_index].nti.name_index);
            
            if(memcmp(name, nameTmp, strlen(name)) != 0) {
                free(nameTmp);
                continue;
            }
            
            free(nameTmp);
            
            signatureTmp = descriptorIndexToString(cf, cf->constant_pool[cf->constant_pool[i].mri.name_and_type_index].nti.descriptor_index);
            if(memcmp(signature, signatureTmp, strlen(signature)) != 0) {
                free(signatureTmp);
                continue;
            }
        
            free(signatureTmp);
            
            classNameTmp = nameIndexToString(cf, cf->constant_pool[cf->constant_pool[i].mri.class_index].ci.name_index);
            if(memcmp(className, classNameTmp, strlen(className)) != 0) {
                free(classNameTmp);
                continue;
            }
            
            free(classNameTmp);
            
            ret = i;
            break;
        }
    }

    return ret;
}


/**
 * This function searchs the ClassFile 'cf' methods for a method called
 * 'name' with params 'signature'.
 * If found, it returns the index into the 'methods' member from the
 * ClassFile 'cf' structure. If not, it returns -1.
 */
int RC_GetMethodIndex(ClassFile *cf, char *name, char *signature)
{

    int i;
    char *nameTmp;
    char *signatureTmp;
    int ret = -1;

    for(i = 0; i < cf->methods_count; i++) {
        nameTmp = nameIndexToString(cf, cf->methods[i].name_index);

        if(memcmp(name, nameTmp, strlen(name)) != 0) {
            free(nameTmp);
            continue;
        }

        free(nameTmp);

        signatureTmp = descriptorIndexToString(cf, cf->methods[i].descriptor_index);
        if(memcmp(signature, signatureTmp, strlen(signature)) == 0) {
            ret = i;
            free(signatureTmp);
            break;
        }
        
        free(signatureTmp);
    }

    return ret;
}

/**
 * This function searchs the ClassFile methods for a method called
 * 'name' with params 'signature'.
 * If found, it returns the reference to the method_info inside the
 * ClassFile cf structure. If not, it returns null.
 */
method_info* RC_GetMethod(ClassFile *cf, char *name, char *signature)
{

    int i;
    char *nameTmp;
    char *signatureTmp;
    method_info *ret = NULL;

    for(i = 0; i < cf->methods_count; i++) {
        nameTmp = nameIndexToString(cf, cf->methods[i].name_index);

        if(memcmp(name, nameTmp, strlen(name)) != 0) {
            free(nameTmp);
            continue;
        }

        free(nameTmp);

        signatureTmp = descriptorIndexToString(cf, cf->methods[i].descriptor_index);
        if(memcmp(signature, signatureTmp, strlen(signature)) == 0) {
            ret = &cf->methods[i];
            free(signatureTmp);
            break;
        }
        
        free(signatureTmp);
    }

    return ret;
}


/**
 * Reads the code array from the method and returns the number of bytes
 * in the code array. If this value is negative, it means that the buffer passed
 * in the 'code' parameter is not big enough. If the value is 0, this method
 * has no code attribute. If the value is greater than 0, then you have the
 * amount of bytes written to the 'codes' parameter
 *
 * @param cf - ClassFile representing the .class being changed
 * @param method - The method_info structure acquired from RC_GetMethod
 * @param code - Array where the code will be stored
 * @param length - Size of the code buffer
 *
 */
int RC_GetMethodCode(ClassFile *cf, method_info *method, u1 *code, u4 length)
{
    int j;
    int ret = 0; // No code attribute found
    char *attr_name;

    for(j = 0; j < method->attributes_count; j++) {

        attr_name = nameIndexToString(cf, method->attributes[j].attribute_name_index);

        if(strncmp(attr_name, ATTR_CODE, strlen(attr_name)) != 0) {
            free(attr_name);
            continue;
        }

        free(attr_name);

        if(length < method->attributes[j].ca.code_length) {
            return -1;
        }

        ret = method->attributes[j].ca.code_length;
        memcpy(code, method->attributes[j].ca.code, ret);

    }

    return ret;
}

/**
 * Returns the length of the code attribute of a method
 * If the value returned is 0, the code attribute could not be found.
 *
 * @param cf - ClassFile representing the .class being changed
 * @param method - The method_info structure acquired from RC_GetMethod
 */
int RC_GetMethodCodeLength(ClassFile *cf, method_info *method)
{

    int j;
    int ret = 0; // No code attribute found
    char *attr_name;

    for(j = 0; j < method->attributes_count; j++) {

        attr_name = nameIndexToString(cf, method->attributes[j].attribute_name_index);

        if(strncmp(attr_name, ATTR_CODE, strlen(attr_name)) != 0) {
            free(attr_name);
            continue;
        }

        free(attr_name);

        ret = method->attributes[j].ca.code_length;

    }

    return ret;
}
