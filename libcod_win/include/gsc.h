#ifndef GSC_H
#define GSC_H

#define COD1_1_5 115
#define COD2_1_0 210
#define COD2_1_2 212
#define COD2_1_3 213
#define COD4_1_7 417

#if COD2_VERSION == COD2_VERSION_1_2 || COD2_VERSION == COD2_VERSION_1_3 || COD_VERSION == COD2_1_0
	#define STACK_UNDEFINED 0
	#define STACK_OBJECT 1
	#define STACK_STRING 2
	#define STACK_LOCALIZED_STRING 3
	#define STACK_VECTOR 4
	#define STACK_FLOAT 5
	#define STACK_INT 6
	#define STACK_CODEPOS 7
	#define STACK_PRECODEPOS 8
	#define STACK_FUNCTION 9
	#define STACK_STACK 10
	#define STACK_ANIMATION 11
	#define STACK_DEVELOPER_CODEPOS 12
	#define STACK_INCLUDE_CODEPOS 13
	#define STACK_THREAD_LIST 14
	#define STACK_THREAD_1 15
	#define STACK_THREAD_2 16
	#define STACK_THREAD_3 17
	#define STACK_THREAD_4 18
	#define STACK_STRUCT 19
	#define STACK_REMOVED_ENTITY 20
	#define STACK_ENTITY 21
	#define STACK_ARRAY 22
	#define STACK_REMOVED_THREAD 23

#elif COD_VERSION == COD1_1_5

	#define STACK_UNDEFINED 0
	#define STACK_STRING 1
	#define STACK_LOCALIZED_STRING 2
	#define STACK_VECTOR 3
	#define STACK_FLOAT 4
	#define STACK_INT 5
	#define STACK_CODEPOS 6
	#define STACK_OBJECT 7
	#define STACK_KEY_VALUE 8
	#define STACK_FUNCTION 9
	#define STACK_STACK 10
	#define STACK_ANIMATION 11
	#define STACK_THREAD 12
	#define STACK_ENTITY 13
	#define STACK_STRUCT 14
	#define STACK_ARRAY 15
	#define STACK_DEAD_THREAD 16
	#define STACK_DEAD_ENTITY 17
	#define STACK_DEAD_OBJECT 18

#elif COD_VERSION == COD4_1_7
	/*
	THOSE ARE CoD2 ones!

	WinHex: 1E3AE3

	*/
	#define STACK_UNDEFINED 0
	#define STACK_OBJECT 1
	#define STACK_STRING 2
	#define STACK_LOCALIZED_STRING 3
	#define STACK_VECTOR 4
	#define STACK_FLOAT 5
	#define STACK_INT 6
	#define STACK_CODEPOS 7
	#define STACK_PRECODEPOS 8
	#define STACK_FUNCTION 9
	#define STACK_STACK 10
	#define STACK_ANIMATION 11
	#define STACK_DEVELOPER_CODEPOS 12
	#define STACK_INCLUDE_CODEPOS 13
	#define STACK_THREAD_LIST 14
	#define STACK_THREAD_1 15
	#define STACK_THREAD_2 16
	#define STACK_THREAD_3 17
	#define STACK_THREAD_4 18
	#define STACK_STRUCT 19
	#define STACK_REMOVED_ENTITY 20
	#define STACK_ENTITY 21
	#define STACK_ARRAY 22
	#define STACK_REMOVED_THREAD 23
#else
	// NO ERROR, because those are only available if code is compiled version-dependent!
	//#warning NO STACK TYPES
#endif

typedef struct
{
	void *offsetData;
	int type;
} aStackElement;

int stackNew();
int stackPushUndefined();

int stackGetParamInt(int param, int *value);
int stackGetParamString(int param, char **value);
int stackGetParamVector(int param, float value[3]);
int stackGetParamFloat(int param, float *value);
int stackGetNumberOfParams();

int stackReturnInt(int ret); // obsolete
int stackPushInt(int ret);
int stackReturnVector(float *ret); // obsolete
int stackPushVector(float *ret);
int stackPushFloat(float ret);
int stackPushString(char *toPush);
int stackPushEntity(int arg);

int cdecl_injected_closer();

#endif // GSC_H
