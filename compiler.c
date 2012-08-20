#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "reclass.h"
#include "compiler.h"
#include "helper.h"
#include "symbol.h"

FILE *yyin;
buffer *code;
dllist *symbols_list;
int current_method;
int current_max_stack;
int current_max_locals;

/* Opcode compilation */

void jreturn()
{
    unsigned char bytes[1];
    
    bytes[0] = 0xB1;
    buffer_append(code, bytes, 1);
    
}

/**
 * This function generates the opcode for the getstatic mnemonic
 * It will check if the index specified is valid into the constant_pool
 * according to the Classfile documentation and warn the user if 
 * it isn't. This check WILL NOT prevent the code from being compiled
 * as this value might have been intentional (looking for vulns for
 * example)
 */
void getstatic_int(ClassFile *cf, int index)
{
    unsigned char bytes[3];
    
    if(index > cf->constant_pool_count) {
        debug(DBG_WARN, "Index for getstatic %d is greater than the " 
                        "number of entries in the constant pool", index);
                         
    } else {
        if(cf->constant_pool[index].tag != CONSTANT_FIELDREF) {
            debug(DBG_WARN, "Index for getstatic %d does not point to "
                            "a CONSTANT_Fieldref into the constant_pool",
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

int getstatic_identifier(ClassFile *cf, char *identifier)
{
    
    symbol    *s;
    symbol    *tmp;
    
    tmp = symbol_new(identifier);
    
    s = dllist_find(symbols_list, tmp);
    
    symbol_free(tmp);
    
    if(s == NULL) {
        debug(DBG_ERROR, "getstatic: identifier %s not found", identifier);
        return -1;
    }
    
    getstatic_int(cf, ((symbol *)s)->cp_index);
    
    return 0;
    
}

void pop()
{
    unsigned char bytes[1];
    
    bytes[0] = 0x57;
    buffer_append(code, bytes, 1);
}

/* Assembler special directives */

int method_start(ClassFile *cf, char *identifier, char *params)
{
    method_info *MyMethod;
    symbol *s;
    
    s = symbol_new(identifier);
    s->type = SYM_METHOD;
    s->signature = strdup(params);
    
    current_method = RC_GetMethodIndex(cf, identifier, params);
    
    if(current_method == -1) {
        RC_AddMethod(cf, identifier, params, ACC_PUBLIC | ACC_STATIC, &MyMethod);
        
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
    
    
    current_method = 0;
    current_max_stack = 0;
    current_max_locals = 0;
    buffer_clear(code);
    
    return 0;
}

int create_int(ClassFile *cf, char *identifier, int value)
{
    
    int index;
    symbol *s;
    
    s = symbol_new(identifier);
    s->type = SYM_VAR;
    
    if(dllist_find(symbols_list, s)) {
        debug(DBG_ERROR, "Symbol %s already declared. Aborting...\n",
              identifier);
        
        symbol_free(s);
        
        return -1;
    }


    index = RC_CPAddInteger(cf, (u4)value);
    s->cp_index = index;
    
    dllist_add(symbols_list, (void *)s);
    
    return 0;
    
}


/* Entry point */
int compile(ClassFile *cf, char *file_path)
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
    symbols_list = dllist_new(0, symbol_free, symbol_cmp); 
    
    do {
        if(yyparse(cf) > 0) {
            ret = CF_NOTOK;
            break;
        }
    } while (!feof(yyin));


    buffer_free(code);
    dllist_free(symbols_list);
    fclose(f);

    return ret;
}

void yyerror(const char *s) {
    printf("Error on token: %s\n", s);
}
