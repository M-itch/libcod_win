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

/* THE BEGINNING of generalizing the push-value-functions! */
// pushing a new stack-element on stack
// available through getStack()
// 11.03.2013, Sido|Meine Jordans Instrumental, Generalisation is unstable!

/* search for "Internal script stack overflow", thats stackNew() */
/* can also be found in the next stackPush-functions */
int stackNew()
{
    int (*signature)();

	#if COD_VERSION == COD2_1_3
		*((int *)(&signature)) = 0x047D630;
	#else
		#warning int stackNew() *((int *)(&signature)) = NULL;
		*((int *)(&signature)) = (int)NULL;
	#endif

	return signature();
}

int stackPushUndefined()
{
    aStackElement *scriptStack;

	scriptStack = *(aStackElement**)getStack();
	stackNew();

	scriptStack = *(aStackElement**)getStack();

	//aStackElement *scriptStack = *(aStackElement**)getStack();
	//aStackElement *scriptStack = *(aStackElement**)ret;
	scriptStack->type = STACK_UNDEFINED;
	scriptStack->offsetData = NULL; // never tested anything else for UNDEFINED
	//return (int) *(aStackElement**) getStack(); // dunno...
	return 123; // dunno... works also lol. so no need to return some specific stackelement
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

/*
CoD2: just look in getent() e.g.
int __cdecl sub_8078DFC(int a1)
{
  return stringtable_8205E80 + 8 * a1;
}


kinda hard to find this for CoD1, because i cant trace the get-param-functions...
but search for: "parameter %d does not exist"
 - then make xrefs-to to it
 - all those functions shall have ONE parent-function
 - go into that parent-function and now just click through till it looks like str-function
*/
int stackGetParamString(int param, char **value)
{
    aStackElement *scriptStack = *(aStackElement**)getStack();
	aStackElement *arg = scriptStack - param;
	if (arg->type != STACK_STRING)
		return 0;

	#if COD_VERSION == COD2_1_3
		*value = (char *)(*(int *)0x0DF8D80 + 8*(int)arg->offsetData + 4);
	#else
		#warning stackGetParamString(int param, char **value) *value = (char *)(*(int *)NULL + 8*(int)arg->offsetData + 4);
		*value = (char *)(*(int *)NULL + 8*(int)arg->offsetData + 4);
	#endif

	return 1;
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
	#if COD_VERSION == COD2_1_3
		return 0x0F4B91C;
	#else
		#warning int getNumberOfParams() return NULL;
		return (int)NULL;
	#endif
}

int stackGetNumberOfParams()
{
    int numberOfParams = *(int *)getNumberOfParams();
	return numberOfParams;
}

int stackReturnInt(int ret)
{
    return stackPushInt(ret);
}

int stackPushInt(int ret)
{
    int (*signature)(int);

    #if COD_VERSION == COD2_1_3
        *((int *)(&signature)) = 0x0483580;
    #else
        #warning int stackPushInt(int ret)
        *((int *)(&signature)) = (int)NULL;
    #endif

    return signature(ret);
}

int stackReturnVector(float *ret)
{
    return stackPushVector(ret);
}

/*
	for CoD1:
		search MT_AllocIndex
		go 2 functions up or so and compare structure with CoD2
	for other CoD's:
		just go into getOrigin() or so and look
*/
int stackPushVector(float *ret) // as in vectornormalize
{
    int (*signature)(float *);

	#if COD_VERSION == COD2_1_3
		*((int *)(&signature)) = 0x08085306; // todo
	#else
		#warning int stackPushVector(float *ret) *((int *)(&signature)) = NULL;
		*((int *)(&signature)) = (int)NULL;
	#endif

	return signature(ret);
}

int stackPushFloat(float ret) // as in distance
{
    /* not working
    aStackElement *scriptStack;
    scriptStack = *(aStackElement**)getStack();
	stackNew();
	scriptStack = *(aStackElement**)getStack();
	scriptStack->type = STACK_FLOAT;
	*(float *)&(scriptStack->offsetData) = ret;
	return 123;*/

    int (*signature)(float);

	#if COD_VERSION == COD2_1_3
		*((int *)(&signature)) = 0x04835D0;
	#else
		#warning int stackPushFloat(float ret) *((int *)(&signature)) = NULL;
		*((int *)(&signature)) = (int)NULL;
	#endif

	return signature(ret);
}

int stackPushString(char *toPush) // as in getcvar()
{
    int (*signature)(char *);

	#if COD_VERSION == COD2_1_3
		*((int *)(&signature)) = 0x0483770;
	#else
		#warning int stackPushString(char *toPush) *((int *)(&signature)) = NULL;
		*((int *)(&signature)) = (int)NULL;
	#endif

	return signature(toPush);
}

int stackPushEntity(int arg) // as in getent() // todo: find out how to represent an entity
{
    int (*signature)(int);

	#if COD_VERSION == COD2_1_3
		*((int *)(&signature)) = 0x08117F50; // todo
	#else
		#warning int stackPushEntity(int arg) *((int *)(&signature)) = NULL;
		*((int *)(&signature)) = (int)NULL;
	#endif

	return signature(arg);
}

int cdecl_injected_closer()
{
    int function;
    Com_Printf("CLOSER\n");

    if (!stackGetParamInt(0, &function))
    {
        Com_Printf("scriptengine> ERROR: closer(): param \"function\"[0] has to be an integer!\n");
        return stackReturnInt(0);
    }

    Com_Printf("function: %d\n", function);
    Com_Printf("Number of parameters: %d\n", stackGetNumberOfParams());

    switch (function)
	{
		case 200:
		{
			char *msg;
			int helper = 0;
			helper += stackGetParamString(1, &msg); // todo: is string?
			if (helper < 1)
			{
				Com_Printf("scriptengine> wrongs args for: Com_Printf(msg): at least 1 arg\n");
				return stackReturnInt(0);
			}

			Com_Printf(msg);
			return stackReturnInt(1);
		}

		case 201:
        {
            return stackPushFloat(3.14);
        }
	}

    return stackReturnInt(0);
}
