#ifndef HELPER_H_
#define HELPER_H

#define DBG_WARN  0x01
#define DBG_ERROR 0x02

void debug(int level, const char *fmt, ...);
long long swapendll(long long v);
unsigned int swapendi(unsigned int v);
unsigned short swapends(unsigned short v);
void printUtf8(char *bytes, int length);


// Buffer helpers!
typedef struct _buffer {
    unsigned int size;
    unsigned char *bytes;
} buffer;

buffer* buffer_new(unsigned int size);
void buffer_free(buffer* b);
void buffer_clear(buffer *b);
int buffer_append(buffer *b, unsigned char* data, unsigned int size);

/**
 * This function should be able to free the data pointed by the 
 * 'data' member in the list_item struct
 */
typedef void (*t_dllist_free)(void*);

/**
 * This function will be used to compare the value of the 'data' member
 * of the list_item struct with another value of the same type.
 * This function should return 0 if both values are equal.
 * 
 */
typedef int  (*t_dllist_cmp) (void*, void*);

typedef struct _dllist_item {
    void *data;
    struct _dllist_item *next;
    struct _dllist_item *prev;
} dllist_item;

typedef struct _dllist {
    int tag;
    t_dllist_free free_fn;
    t_dllist_cmp  cmp_fn;
    dllist_item *items;   
} dllist;

dllist* dllist_new(int tag, t_dllist_free free_fn, t_dllist_cmp cmp_fn);
void    dllist_add(dllist *l, void *data);
void    dllist_del(dllist *l, void *data);
void    dllist_free(dllist *l);
void*   dllist_find(dllist *l, void *what);


#endif
