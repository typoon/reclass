#include <string.h>
#include <stdlib.h>

#include "symbol.h"

symbol* symbol_new(char *name)
{
    symbol *s;
    s = (symbol *)malloc(sizeof(symbol));
    s->name = strdup(name);
    s->signature = NULL;

    return s;

}

void symbol_free(void *sym)
{
    symbol *s = (symbol *)sym;
    
    if(s->signature) {
        free(s->signature);
    }
    
    free(s->name);
    free(s);
}

int symbol_cmp(void *s1, void *s2)
{
    int ret = 0;
    
    if((strcmp(((symbol *)s1)->name, ((symbol *)s2)->name) == 0) &&
        ((symbol *)s1)->type == ((symbol *)s2)->type) {
        
        ret = 1;
    }
    
    return  ret;
}
