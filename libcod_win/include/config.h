#ifndef _CONFIG_H_
#define _CONFIG_H_

/*
	DID MOST OF THIS TO HARDEN THE LIB FOR DECOMPILING
	countercheck:
		strings -a libcod2_ver_1_3.so | less
		strings libcod2_ver_1_3.so | less
		nm libcod2_ver_1_3.so | less
		nm -D libcod2_ver_1_3.so | less
*/

// that makes debugging easier after some months
#define DEBUG_MYSQL 1
#define DEBUG_GSC 0
#define DEBUG_MEMORY 0
#define DEBUG_CAR 0
#define DEBUG_TCC 0

// GSC MODULES
#define COMPILE_MYSQL 1
#define COMPILE_MYSQL_TESTS 0
#define COMPILE_PLAYER 1
#define COMPILE_ASTAR 0
#define COMPILE_MEMORY 0
#define COMPILE_CAR 0
#define COMPILE_TCC 0

// LIB FEATURES
#define COMPILE_DEBUG_SERVER 0

#define DEBUG_PRINTF 0

// GLOBAL MACROS
#define STR(s) #s // stringify used for __FUNCTION__

#endif
