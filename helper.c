#include <stdarg.h>
#include <stdio.h>
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