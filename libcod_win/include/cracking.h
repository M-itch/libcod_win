#ifndef _CRACKING_H_
#define _CRACKING_H_

#include <string.h>

int cracking_nop(int from, int to);
void cracking_hook_function(int from, int to);
void cracking_hook_call(int from, int to);
int cracking_write_hex(int address, char *hex);

int singleHexToNumber(char hexchar);
int hexToBuffer(char *hex, char *buffer, int bufferLen);

#endif
