#ifndef SYMBOL_H
#define SYMBOL_H

    unsigned char byte_val;
    int int_val;
    double double_val;
    char *str_val;

#define SYM_METHOD 0

#define SYM_BYTE   1
#define SYM_INT    2
#define SYM_DOUBLE 3
#define SYM_STR    4


typedef struct _symbol {
    char *name;
    char *signature; // used only when type = SYM_METHOD
    int   type;
    unsigned short cp_index;
    union {
        unsigned char byte_val;
        int int_val;
        double double_val;
        char *str_val;
    } value;
} symbol;


symbol* symbol_new(char *name);
void symbol_free(void *sym);
int symbol_cmp(void *s1, void *s2);


#endif /* SYMBOL_H */
