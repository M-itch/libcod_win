#include "../include/gsc.h"
#include "../include/functions.h"
#include <string.h>

int getStack()
{
	#if COD_VERSION == COD2_1_3
		return 0x0F4B910;
	#else
		#warning int getStack() return NULL;
		return (int)NULL;
	#endif
}

int stackNew()
{
    return 0;
}

int stackPushUndefined()
{
    return 0;
}

int stackGetParamInt(int param, int *value)
{
    aStackElement *scriptStack = *(aStackElement**)getStack();
	aStackElement *arg = scriptStack - param;
	if (arg->type != STACK_INT)
		return 0;
	*value = (int)arg->offsetData;
	return 1;
}

int stackGetParamString(int param, char **value)
{
    return 0;
}

int stackGetParamVector(int param, float value[3])
{
    aStackElement *scriptStack = *(aStackElement**)getStack();
	aStackElement *arg = scriptStack - param;
	if (arg->type != STACK_VECTOR)
		return 0;
	value[0] = *(float *)((int)(arg->offsetData) + 0);
	value[1] = *(float *)((int)(arg->offsetData) + 4);
	value[2] = *(float *)((int)(arg->offsetData) + 8);
	return 1;
}

int stackGetParamFloat(int param, float *value)
{
    aStackElement *scriptStack = *(aStackElement**)getStack();
	aStackElement *arg = scriptStack - param;

	if (arg->type == STACK_INT)
	{
		int asInteger;
		int ret = stackGetParamInt(param, &asInteger);
		if (!ret)
			return 0;
		*value = (float) asInteger;
		return 1;
	}

	float tmp;
	if (arg->type != STACK_FLOAT)
		return 0;
	memcpy(&tmp, &arg->offsetData, 4); // cast to float xD
	*value = tmp;
	return 1;
}

int getNumberOfParams()
{
	return 0;
}

int stackGetNumberOfParams()
{
    int numberOfParams = *(int *)getNumberOfParams();
	return numberOfParams;
}

int stackReturnInt(int ret)
{
    return 0;
}

int stackPushInt(int ret)
{
    return 0;
}

int stackReturnVector(float *ret)
{
    return 0;
}

int stackPushVector(float *ret)
{
    return 0;
}

int stackPushFloat(float ret)
{
    return 0;
}

int stackPushString(char *toPush)
{
    return 0;
}

int stackPushEntity(int arg)
{
    return 0;
}

int cdecl_injected_closer()
{
    int function;
    Com_Printf("CLOSER\n");

    if (!stackGetParamInt(0, &function))
    {
        Com_Printf("scriptengine> ERROR: closer(): param \"function\"[0] has to be an integer!\n");
        return 0;
    }

    return 0;
}
