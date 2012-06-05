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
    char *bytes;
} buffer;

buffer* buffer_new(unsigned int size);
void buffer_free(buffer* b);
void buffer_clear(buffer *b);
int buffer_append(buffer *b, char* data, unsigned int size);



// Map helpers!

/*
 * Simple map implemented as a linked list. There are better ways to do
 * this, but I am kinda in a hurry and lazy to do so :)
 * Feel free to reimplement!
 */
typedef struct _map {
    char *key;
    void *value;
    struct _map *next;
} map;

map* map_new();
int map_add(map *m, char *key, void *value);
void map_del(map *m, char *key);
void map_free(map *m);



#endif
