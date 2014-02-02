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

int stackReturnInt(int ret) // obsolete
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

int stackReturnVector(float *ret) // obsolete
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
        *((int *)(&signature)) = 0x04838B0;
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
    /*aStackElement *scriptStack;
    scriptStack = *(aStackElement**)getStack();
    stackNew();
    scriptStack = *(aStackElement**)getStack();
    scriptStack->type = STACK_STRING;
    *(char *)&(scriptStack->offsetData) = *toPush;
    return 123;*/

    int (*signature)(char *, int, int);

    #if COD_VERSION == COD2_1_3
        *((int *)(&signature)) = 0x0477500;
    #else
        #warning int stackPushString(char *toPush) *((int *)(&signature)) = NULL;
        *((int *)(&signature)) = (int)NULL;
    #endif
    stackNew();
    return signature(toPush, 0, strlen(toPush)+1);
}

int stackPushEntity(int arg) // as in getent() // todo: find out how to represent an entity
{
    int (*signature)(int);

    #if COD_VERSION == COD2_1_3
        *((int *)(&signature)) = 0x04836C0;
    #else
        #warning int stackPushEntity(int arg) *((int *)(&signature)) = NULL;
        *((int *)(&signature)) = (int)NULL;
    #endif

    return signature(arg);
}

int cdecl_injected_closer()
{
    int function;

    float reference[3], point_a[3], point_b[3];
	if (
		stackGetNumberOfParams() == 3 &&
		stackGetParamVector(0, reference) &&
		stackGetParamVector(1, point_a) &&
		stackGetParamVector(2, point_b)
	) {
		// > Tests which of two points is the closest. Returns true if point a is closer to the reference than point b
		float delta_a[3] = {
			point_a[0] - reference[0],
			point_a[1] - reference[1],
			point_a[2] - reference[2]
		};
		float delta_b[3] = {
			point_b[0] - reference[0],
			point_b[1] - reference[1],
			point_b[2] - reference[2]
		};
		float distancesquared_a = delta_a[0]*delta_a[0] + delta_a[1]*delta_a[1] + delta_a[2]*delta_a[2];
		float distancesquared_b = delta_b[0]*delta_b[0] + delta_b[1]*delta_b[1] + delta_b[2]*delta_b[2];

		if (distancesquared_a < distancesquared_b)
			return stackPushInt(1);
		else
			return stackPushInt(0);
	}

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

        case 202:
        {
            return stackPushString((char *)"pushworks");
        }

        #if COMPILE_MYSQL == 1
        case 100: return gsc_mysql_init();
        case 101: return gsc_mysql_real_connect();
        case 102: return gsc_mysql_close();
        case 103: return gsc_mysql_query();
        case 104: return gsc_mysql_errno();
        case 105: return gsc_mysql_error();
        case 106: return gsc_mysql_affected_rows();
        case 107: return gsc_mysql_store_result();
        case 108: return gsc_mysql_num_rows();
        case 109: return gsc_mysql_num_fields();
        case 110: return gsc_mysql_field_seek();
        case 111: return gsc_mysql_fetch_field();
        case 112: return gsc_mysql_fetch_row();
        case 113: return gsc_mysql_free_result();
        case 114: return gsc_mysql_real_escape_string();

        case 150: return gsc_mysql_stmt_init();
        case 151: return gsc_mysql_stmt_close();
        case 152: return gsc_mysql_stmt_get_stmt_id();
        case 153: return gsc_mysql_stmt_get_prefetch_rows();
        case 154: return gsc_mysql_stmt_get_param_count();
        case 155: return gsc_mysql_stmt_get_field_count();
        case 156: return gsc_mysql_stmt_prepare();
        case 157: return gsc_mysql_stmt_bind_param();
        case 158: return gsc_mysql_stmt_bind_result();
        case 159: return gsc_mysql_stmt_execute();
        case 160: return gsc_mysql_stmt_store_result();
        case 161: return gsc_mysql_stmt_fetch();
        #endif

        #if COMPILE_PLAYER == 1
        case 400: return gsc_player_stance_get();
		case 410: return gsc_player_velocity_set(); // todo: stackGetParamVector
		case 411: return gsc_player_velocity_add(); // todo: stackGetParamVector
		case 412: return gsc_player_velocity_get();
		case 420: return gsc_player_button_ads();
		case 421: return gsc_player_button_left();
		case 422: return gsc_player_button_right();
		case 423: return gsc_player_button_forward();
		case 424: return gsc_player_button_back();
		case 425: return gsc_player_button_leanleft();
		case 426: return gsc_player_button_leanright();
		case 427: return gsc_player_button_jump();

		case 430: return gsc_player_getip();
		case 431: return gsc_player_getping();

		case 450: return gsc_player_spectatorclient_get();
		#endif
    }

    return stackReturnInt(0);
}
