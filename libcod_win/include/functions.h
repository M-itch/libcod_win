#ifndef FUNCTIONS_H
#define FUNCTIONS_H
//#include <string.h>

typedef int (*Com_Printf_t)(const char*, ...);

#if COD_VERSION == COD2_1_0
    static Com_Printf_t Com_Printf = (Com_Printf_t)0x0430540;
#elif COD_VERSION == COD2_1_3
    static Com_Printf_t Com_Printf = (Com_Printf_t)0x0431EE0;
#else
    static Com_Printf_t Com_Printf = (Com_Printf_t)0;
    #warning Com_Printf_t Com_Printf = NULL;
#endif

typedef int (*Cmd_ExecuteString_t)(const char *text);

#if COD_VERSION == COD2_1_0
    static Cmd_ExecuteString_t Cmd_ExecuteString = (Cmd_ExecuteString_t)0x041FD10;
#elif COD_VERSION == COD2_1_3
    static Cmd_ExecuteString_t Cmd_ExecuteString = (Cmd_ExecuteString_t)0x04214C0;
#else
    static Cmd_ExecuteString_t Cmd_ExecuteString = (Cmd_ExecuteString_t)0;
    #warning Cmd_ExecuteString_t Cmd_ExecuteString = NULL;
#endif

/*static int trap_Argc()
{
	#if COD_VERSION == COD2_1_3
		return *(int *)0x0B1A480;
	#else
		#warning trap_Argc() return *(int *)NULL;
		return *(int *)NULL;
	#endif
}

static char * Cmd_Argv(int arg)
{
    #if COD_VERSION == COD2_1_3
        return (char*)(*(int*)0x0B17A80 + arg);
    #else
        #warning Cmd_Argv() return (char*)NULL;
        return (char*)NULL;
    #endif
}

static void trap_Argv(unsigned int param, char* buf, int bufLen)
{
    char* cmd = Cmd_Argv(param);
    strncpy(buf, cmd, bufLen);
}

typedef int (*ClientCommand_t)(int clientNum); // search 'say_team' and see code xref function
#if COD_VERSION == COD2_1_3
	static ClientCommand_t ClientCommand = (ClientCommand_t)0x0503AD0; // usercall
	static int hook_ClientCommand_call = 0x0455DD7;
#else
	#warning static ClientCommand_t ClientCommand = (ClientCommand_t)NULL;
	#warning static int hook_ClientCommand_call = NULL;
	static ClientCommand_t ClientCommand = (ClientCommand_t)NULL;
	static int hook_ClientCommand_call = (int)NULL;
#endif

typedef short (*codscript_call_callback_entity_t)(int self, int callback, int params);
#if COD_VERSION == COD2_1_3
	static codscript_call_callback_entity_t codscript_call_callback_entity = (codscript_call_callback_entity_t)0x0482190;
#else
	#warning static codscript_call_callback_entity_t codscript_call_callback_entity = (codscript_call_callback_entity_t)NULL;
	static codscript_call_callback_entity_t codscript_call_callback_entity = (codscript_call_callback_entity_t)NULL;
#endif

typedef int (*codscript_callback_finish_t)(short callback_handle);
#if COD_VERSION == COD2_1_3
	static codscript_callback_finish_t codscript_callback_finish = (codscript_callback_finish_t)0x0479660; // usercall
#else
	#warning static codscript_callback_finish_t codscript_callback_finish = (codscript_callback_finish_t)NULL;
	static codscript_callback_finish_t codscript_callback_finish = (codscript_callback_finish_t)NULL;
#endif*/

#endif // FUNCTIONS_H
