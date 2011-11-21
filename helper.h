#ifndef HELPER_H_
#define HELPER_H

#define DBG_WARN  0x01
#define DBG_ERROR 0x02

void debug(int level, const char *fmt, ...);
long long swapendll(long long v);
unsigned int swapendi(unsigned int v);
unsigned short swapends(unsigned short v);
void printUtf8(char *bytes, int length);

#endif