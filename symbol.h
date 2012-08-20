#ifndef SYMBOL_H
#define SYMBOL_H

typedef struct _symbol {
    char *name;
    char *signature; // used only when type = SYM_METHOD
    int   type;
    int   cp_index;
} symbol;


symbol* symbol_new(char *name);
void symbol_free(void *sym);
int symbol_cmp(void *s1, void *s2);


#endif /* SYMBOL_H */
