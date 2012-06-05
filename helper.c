#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"

void debug(int level, const char *fmt, ...)
{
#ifdef DEBUG
    va_list arg;
    va_start(arg, fmt);

    vprintf(fmt, arg);

    va_end(arg);
#endif
}

long long swapendll(long long v)
{
    long long ret;

    ret = 0;

    ret = ((v >> 56)   & 0x00000000000000FF) |
            ((v >> 40) & 0x000000000000FF00) |
            ((v >> 24) & 0x0000000000FF0000) |
            ((v >> 8)  & 0x00000000FF000000) |
            ((v << 8)  & 0x000000FF00000000) |
            ((v << 24) & 0x0000FF0000000000) |
            ((v << 40) & 0x00FF000000000000) |
            ((v << 56) & 0xFF00000000000000);

    return ret;

}

/**
 * Converts big endian integer to little endian integer
 */
unsigned int swapendi(unsigned int v)
{
    unsigned int ret;

    ret = 0;

    ret = ((v >> 24) & 0x000000FF) |
            ((v >> 8) & 0x0000FF00) |
            ((v << 8) & 0x00FF0000) |
            ((v << 24) & 0xFF000000);

    return ret;

}

/**
 * Converts big endian short to little endia short
 */
unsigned short swapends(unsigned short v)
{
    unsigned short ret;

    ret = ((v >> 8) & 0x00FF) |
            ((v << 8) & 0xFF00);

    return ret;
}

/**
 *
 */
void printUtf8(char *bytes, int length)
{
}

/* Buffer related stuff */

/**
 * Returns a new buffer with "size" bytes
 */
buffer* buffer_new(unsigned int size)
{
    buffer *b;
    
    b = (buffer *)malloc(sizeof(buffer));
    
    if(b == NULL) {
        debug(DBG_ERROR, "Cannot allocate buffer structure");
        return NULL;
    }

    b->size = size;
    
    if(size > 0) {
        
        b->bytes = (char *)malloc(sizeof(char) * size);
        
        if(b->bytes == NULL) {
            debug(DBG_ERROR, "Cannot allocate %d bytes for buffer", size);
            free(b);
            return NULL;
        }
        
        buffer_clear(b);

    }
    
    return b;
    
}

/**
 * Frees the buffer
 **/
void buffer_free(buffer* b)
{
    if(b->bytes)
        free(b->bytes);
    
    if(b)
        free(b);
}

void buffer_clear(buffer *b)
{
    if(b) {
        if(b->bytes && (b->size > 0)) {
            memset(b->bytes, 0, b->size);
        }
    }
}

/**
 * Appends 'size' bytes from 'data' to 'b'
 * Reallocs buffer in case its size is not enough to handle all data
 * 
 * Returns the number of bytes appended or -1 in case of error
 */
int buffer_append(buffer *b, char* data, unsigned int size)
{
    if(!b)
        return -1;
    
    if(!data)
        return -1;
    
    if(size == 0)
        return 0;
        
    
    if(!realloc(b->bytes, b->size + size)) {
        return -1;
    }
    
    memcpy(&b->bytes[b->size], data, size);
    
    b->size += size;
    
    return size;
}
