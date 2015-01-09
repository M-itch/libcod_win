#include "../include/gsc.h"
#include "../include/functions.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#if COD_VERSION == COD2_1_0
	Scr_GetFunction_t Scr_GetFunction = (Scr_GetFunction_t)0x506F30;
	Scr_GetMethod_t Scr_GetMethod = (Scr_GetMethod_t)0x506FC0;
#elif COD_VERSION == COD2_1_3
	Scr_GetFunction_t Scr_GetFunction = (Scr_GetFunction_t)0x50D280;
	Scr_GetMethod_t Scr_GetMethod = (Scr_GetMethod_t)0x50D310;
#else
	#warning Scr_GetFunction_t Scr_GetFunction = (Scr_GetFunction_t)NULL;
	#warning Scr_GetMethod_t Scr_GetMethod = (Scr_GetMethod_t)NULL;
	Scr_GetFunction_t Scr_GetFunction = (Scr_GetFunction_t)NULL;
	Scr_GetMethod_t Scr_GetMethod = (Scr_GetMethod_t)NULL;
#endif

char *stackGetParamTypeAsString(int param) {
	aStackElement *scriptStack = *(aStackElement**)getStack();
	aStackElement *arg = scriptStack - param;

	char *type = (char *)"UNKNOWN TYPE!";
	switch (arg->type) {
		case  0: type = (char *)"UNDEFINED"; break;
		case  1: type = (char *)"OBJECT"; break;
		case  2: type = (char *)"STRING"; break;
		case  3: type = (char *)"LOCALIZED_STRING"; break;
		case  4: type = (char *)"VECTOR"; break;
		case  5: type = (char *)"FLOAT"; break;
		case  6: type = (char *)"INT"; break;
		case  7: type = (char *)"CODEPOS"; break;
		case  8: type = (char *)"PRECODEPOS"; break;
		case  9: type = (char *)"FUNCTION"; break;
		case 10: type = (char *)"STACK"; break;
		case 11: type = (char *)"ANIMATION"; break;
		case 12: type = (char *)"DEVELOPER_CODEPOS"; break;
		case 13: type = (char *)"INCLUDE_CODEPOS"; break;
		case 14: type = (char *)"THREAD_LIST"; break;
		case 15: type = (char *)"THREAD_1"; break;
		case 16: type = (char *)"THREAD_2"; break;
		case 17: type = (char *)"THREAD_3"; break;
		case 18: type = (char *)"THREAD_4"; break;
		case 19: type = (char *)"STRUCT"; break;
		case 20: type = (char *)"REMOVED_ENTITY"; break;
		case 21: type = (char *)"ENTITY"; break;
		case 22: type = (char *)"ARRAY"; break;
		case 23: type = (char *)"REMOVED_THREAD"; break;
	}
	return type;
}

int stackPrintParam(int param) {
	if (param >= stackGetNumberOfParams())
		return 0;

	switch (stackGetParamType(param)) {
		case STACK_STRING:
			char *str;
			stackGetParamString(param, &str); // no error checking, since we know it's a string
			Com_Printf("%s", str);
			return 1;
		case STACK_VECTOR:
			float vec[3];
			stackGetParamVector(param, vec);
			Com_Printf("(%.2f, %.2f, %.2f)", vec[0], vec[1], vec[2]);
			return 1;
		case STACK_FLOAT:
			float tmp_float;
			stackGetParamFloat(param, &tmp_float);
			Com_Printf("%.3f", tmp_float); // need a way to define precision
			return 1;
		case STACK_INT:
			int tmp_int;
			stackGetParamInt(param, &tmp_int);
			Com_Printf("%d", tmp_int);
			return 1;
	}
	Com_Printf("(%s)", stackGetParamTypeAsString(param));
	return 0;
}

void gsc_utils_printf() {
	char *str;
	if ( ! stackGetParams((char *)"s", &str)) {
		Com_Printf("scriptengine> WARNING: printf undefined argument!\n");
		stackPushUndefined();
		return;
	}

	if(stackGetNumberOfParams() == 1 || strchr(str, '%') == NULL)
    {
        Com_Printf("%s", str);
        stackPushInt(1);
        return;
    }

	int param = 1; // maps to first %
	int len = strlen(str);

	for (int i=0; i<len; i++) {
		if (str[i] == '%')
		{
			if(str[i + 1] == '%') {
				Com_Printf("%c", '%');
				i++;
			} else
				stackPrintParam(param++);
		}
		else
			Com_Printf("%c", str[i]);
	}

	stackPushInt(1);
}
void gsc_utils_printfline() {
	gsc_utils_printf();
	Com_Printf("\n");
}

Scr_Function scriptFunctions[] = {
	{"printf", gsc_utils_printf, 0},
	{"printfline", gsc_utils_printfline, 0}, // adds \n at end

	#if COMPILE_MYSQL == 1
	{"mysql_init"              , gsc_mysql_init              , 0},
	{"mysql_real_connect"      , gsc_mysql_real_connect      , 0},
	{"mysql_close"             , gsc_mysql_close             , 0},
	{"mysql_query"             , gsc_mysql_query             , 0},
	{"mysql_errno"             , gsc_mysql_errno             , 0},
	{"mysql_error"             , gsc_mysql_error             , 0},
	{"mysql_affected_rows"     , gsc_mysql_affected_rows     , 0},
	{"mysql_store_result"      , gsc_mysql_store_result      , 0},
	{"mysql_num_rows"          , gsc_mysql_num_rows          , 0},
	{"mysql_num_fields"        , gsc_mysql_num_fields        , 0},
	{"mysql_field_seek"        , gsc_mysql_field_seek        , 0},
	{"mysql_fetch_field"       , gsc_mysql_fetch_field       , 0},
	{"mysql_fetch_row"         , gsc_mysql_fetch_row         , 0},
	{"mysql_free_result"       , gsc_mysql_free_result       , 0},
	{"mysql_real_escape_string", gsc_mysql_real_escape_string, 0},
	#endif

	#if COMPILE_PLAYER == 1
	{"free_slot"                   , gsc_free_slot                         , 0},
	#endif

	#if COMPILE_UTILS == 1
	{"disableGlobalPlayerCollision", gsc_utils_disableGlobalPlayerCollision, 0},
	{"getAscii"                    , gsc_utils_getAscii                    , 0},
	{"system"                      , gsc_utils_system                      , 0},
	{"file_link"                   , gsc_utils_file_link                   , 0},
	{"file_unlink"                 , gsc_utils_file_unlink                 , 0},
	{"file_exists"                 , gsc_utils_file_exists                 , 0},
	{"getType"                     , gsc_utils_getType                     , 0},
	{"stringToFloat"               , gsc_utils_stringToFloat               , 0},
	{"Cmd_ExecuteString"           , gsc_utils_ExecuteString               , 0},
	#endif

	{NULL, NULL, 0}
};

Scr_FunctionCall Scr_GetCustomFunction(const char **fname, int *fdev) {
	//Com_Printf("Scr_GetCustomFunction: fdev=%d fname=%s\n", *fdev, *fname);
	Scr_FunctionCall m = Scr_GetFunction(fname, fdev);
	if (m)
		return m;

	for (int i=0; scriptFunctions[i].name; i++) {
		if (strcasecmp(*fname, scriptFunctions[i].name))
			continue;
		Scr_Function func = scriptFunctions[i];
		*fname = func.name;
		*fdev = func.developer;
		return func.call;
	}

	return NULL;
}

void gsc_player_printf(int id) {
	Com_Printf("id: %.8p\n", id);
}

Scr_Method scriptMethods[] = {
	{"printf", gsc_player_printf, 0}, // rather use sprintf() to re-use iprintlnbold() etc.?

	#if COMPILE_PLAYER == 1
	{"getStance"             , gsc_player_stance_get         , 0},
	{"setVelocity"           , gsc_player_velocity_set       , 0},
	{"addVelocity"           , gsc_player_velocity_add       , 0},
	{"getVelocity"           , gsc_player_velocity_get       , 0},
	{      "aimButtonPressed", gsc_player_button_ads         , 0},
	{     "leftButtonPressed", gsc_player_button_left        , 0},
	{    "rightButtonPressed", gsc_player_button_right       , 0},
	{  "forwardButtonPressed", gsc_player_button_forward     , 0},
	{     "backButtonPressed", gsc_player_button_back        , 0},
	{ "leanleftButtonPressed", gsc_player_button_leanleft    , 0},
	{"leanrightButtonPressed", gsc_player_button_leanright   , 0},
	{     "jumpButtonPressed", gsc_player_button_jump        , 0},
	{"getIP"                 , gsc_player_getip              , 0},
	{"getPing"               , gsc_player_getping            , 0},
	{"getSpectatorClient"    , gsc_player_spectatorclient_get, 0},
	{"ClientCommand"         , gsc_player_ClientCommand      , 0},
	{"getLastConnectTime"    , gsc_player_getLastConnectTime , 0},
	{"getLastMSG"            , gsc_player_getLastMSG         , 0},
	{"setAlive"              , gsc_entity_setalive           , 0},
	{"setBounds"             , gsc_entity_setbounds          , 0},
	#endif

	{NULL, NULL, 0}
};

Scr_MethodCall Scr_GetCustomMethod(const char **fname, int *fdev) {
	//printf("Scr_GetCustomMethod: fdev=%d fname=%s\n", *fdev, *fname);
	Scr_MethodCall m = Scr_GetMethod(fname, fdev);
	if (m)
		return m;

	for (int i=0; scriptMethods[i].name; i++) {
		if (strcasecmp(*fname, scriptMethods[i].name))
			continue;
		Scr_Method func = scriptMethods[i];
		*fname = func.name;
		*fdev = func.developer;
		return func.call;
	}

	return NULL;
}

int getStack()
{
#if COD_VERSION == COD2_1_0
    return 0x0DF2A10;
#elif COD_VERSION == COD2_1_3
    return 0x0F4B910;
#else
    #warning int getStack() return NULL;
    return (int)NULL;
#endif
}

int stackGetParamType(int param)
{
	aStackElement *scriptStack = *(aStackElement**)getStack();
	aStackElement *arg = scriptStack - param;
	return arg->type;
}

int stackGetParams(char *params, ...)
{
	va_list args;
	va_start(args, params);

	int errors = 0;

	int len = strlen(params);
	int i;
	for (i=0; i<len; i++)
	{
		switch (params[i])
		{
			case ' ': // ignore param (e.g. to ignore the function-id from closer()-wrapper)
				break;
			case 'i': {
				int *tmp = va_arg(args, int *);
				if ( ! stackGetParamInt(i, tmp)) {
					Com_Printf("Param %d needs to be an int, %s=%d given! NumParams=%d\n", i, ">make function for this<", stackGetParamType(i), stackGetNumberOfParams());
					errors++;
				}
				break;
			}
			case 'v': {
				float *tmp = va_arg(args, float *);
				if ( ! stackGetParamVector(i, tmp)) {
					Com_Printf("Param %d needs to be a vector, %s=%d given! NumParams=%d\n", i, ">make function for this<", stackGetParamType(i), stackGetNumberOfParams());
					errors++;
				}
				break;
			}
			case 'f': {
				float *tmp = va_arg(args, float *);
				if ( ! stackGetParamFloat(i, tmp)) {
					Com_Printf("Param %d needs to be a float, %s=%d given! NumParams=%d\n", i, ">make function for this<", stackGetParamType(i), stackGetNumberOfParams());
					errors++;
				}
				break;
			}
			case 's': {
				char **tmp = va_arg(args, char **);
				if ( ! stackGetParamString(i, tmp)) {
					Com_Printf("Param %d needs to be a string, %s=%d given! NumParams=%d\n", i, ">make function for this<", stackGetParamType(i), stackGetNumberOfParams());
					errors++;
				}
				break;
			}

			default:
				errors++;
				Com_Printf("[WARNING] stackGetParams: errors=%d Identifier '%c' is not implemented!\n", errors, params[i]);
		}
	}

	va_end(args);
	return errors == 0; // success if no errors
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

#if COD_VERSION == COD2_1_0
    *((int *)(&signature)) = 0x047A6A0;
#elif COD_VERSION == COD2_1_3
    *((int *)(&signature)) = 0x047D630;
#else
    #warning int stackNew() *((int *)(&signature)) = NULL;
    *((int *)(&signature)) = (int)NULL;
#endif

    return signature();
}

int getNumberOfReturnValues()
{
#if COD_VERSION == COD2_1_0
    return 0x0DF2A18;
#elif COD_VERSION == COD2_1_3
    return 0x0F4B918;
#else
    #warning int getNumberOfReturnValues() return NULL;
    return (int)NULL;
#endif
}

void stackCheck()
{
    void (*signature)(signed int, const char *, ...);

    #if COD_VERSION == COD2_1_0
        int stackend = 0x0DF2A04;
        int data = 0x056F7F8;
        *((int *)(&signature)) = 0x0430B20;
    #elif COD_VERSION == COD2_1_3
        int stackend = 0x0F4B904;
        int data = 0x05B01D0;
        *((int *)(&signature)) = 0x04324C0;
    #else
        int stackend = (int)NULL;
        int data = (int)NULL;
        *((int *)(&signature)) = (int)NULL;
    #endif


    if ( *(int*)getStack() == *(int *)stackend )
        signature(1, (char *)(int *)data);
}

aStackElement* stackPush(int type)
{
    stackNew();
    stackCheck();
    *(int *)getStack() += 8;
    ++*(int *)getNumberOfReturnValues();
    aStackElement* scriptStack = *(aStackElement**)getStack();
    scriptStack->type = type;
    return scriptStack;
}

int stackPushUndefined()
{
    stackPush(STACK_UNDEFINED);
    return 123;
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

#if COD_VERSION == COD2_1_0
    *value = (char *)(*(int *)0x0C9FE80 + 8*(int)arg->offsetData + 4);
#elif COD_VERSION == COD2_1_3
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
#if COD_VERSION == COD2_1_0
    return 0x0DF2A1C;
#elif COD_VERSION == COD2_1_3
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

#if COD_VERSION == COD2_1_0
    *((int *)(&signature)) = 0x04804D0;
#elif COD_VERSION == COD2_1_3
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
    aStackElement * scriptStack = stackPush(STACK_VECTOR);

    int tmp[3];
    tmp[0] = (int)&ret[0];
    tmp[1] = (int)&ret[1];
    tmp[2] = (int)&ret[2];

    scriptStack->offsetData = (void *)tmp;

    return 123;
    /*int (*signature)(float *);

    #if COD_VERSION == COD2_1_3
        *((int *)(&signature)) = 0x04838B0; // = usercall (doesn't work)
    #else
    #warning int stackPushVector(float *ret) *((int *)(&signature)) = NULL;
        *((int *)(&signature)) = (int)NULL;
    #endif

    return signature(ret);*/
}

int stackPushFloat(float ret) // as in distance
{
    int (*signature)(float);

#if COD_VERSION == COD2_1_0
    *((int *)(&signature)) = 0x0480520;
#elif COD_VERSION == COD2_1_3
    *((int *)(&signature)) = 0x04835D0;
#else
    #warning int stackPushFloat(float ret) *((int *)(&signature)) = NULL;
    *((int *)(&signature)) = (int)NULL;
#endif

    return signature(ret);
}

int stackPushString(char *toPush) // as in getcvar()
{
    aStackElement* scriptStack = stackPush(STACK_STRING);

    int (*signature)(const void *, unsigned int8_t, unsigned int);

#if COD_VERSION == COD2_1_0
    *((int *)(&signature)) = 0x0474560;
#elif COD_VERSION == COD2_1_3
    *((int *)(&signature)) = 0x0477500;
#else
    #warning int stackPushString(char *toPush) *((int *)(&signature)) = NULL;
    *((int *)(&signature)) = (int)NULL;
#endif

    unsigned short int result = signature(toPush, 0, strlen(toPush)+1);
    scriptStack->offsetData = (void *)result;
    return result;
}

int stackPushEntity(int arg) // as in getent() // todo: find out how to represent an entity
{
    aStackElement* scriptStack = stackPush(STACK_OBJECT);
    scriptStack->offsetData = (void *)arg;

    #if COD_VERSION == COD2_1_0
        int address = 0x0CB0004; // 0x0480610
    #elif COD_VERSION == COD2_1_3
        int address = 0x0E08F04; // 0x04836C0
    #else
        int address = (int)NULL;
    #endif

    int v4 = 16 * arg;
    ++*(int *)(int *)((char *)(int *)address + v4);
    return (int)(((int *)address) + v4);
}

// as in bullettrace
int alloc_object_and_push_to_array() // use stackPushArray() now
{
    int (*signature)();

#if COD_VERSION == COD2_1_0
    *((int *)(&signature)) = 0x0480880;
#elif COD_VERSION == COD2_1_3
    *((int *)(&signature)) = 0x0483930;
#else
    #warning int alloc_object_and_push_to_array() *((int *)(&signature)) = NULL;
    *((int *)(&signature)) = (int)NULL;
#endif

    return signature();
}

int stackPushArray()
{
    return alloc_object_and_push_to_array();
}

int push_previous_var_in_array_sub() // stackPushArrayLast()
{
    int (*signature)();

#if COD_VERSION == COD2_1_0
    *((int *)(&signature)) = 0x04808F0;
#elif COD_VERSION == COD2_1_3
    *((int *)(&signature)) = 0x04839A0;
#else
    #warning int push_previous_var_in_array_sub() *((int *)(&signature)) = NULL;
    *((int *)(&signature)) = (int)NULL;
#endif

    return signature();
}

int stackPushArrayLast()
{
    return push_previous_var_in_array_sub();
}
