#include "main.h"
#include <stdio.h>
#include "include/gsc.h"
#include "include/functions.h"
#include "include/cracking.h"

DWORD WINAPI MyThread(LPVOID);
DWORD g_threadID;
HMODULE g_hModule;
static int isStarted = 0;
/*int codecallback_playercommand = 0;

typedef void (*gametype_scripts_t)();
#if COD_VERSION == COD2_1_3
	gametype_scripts_t gametype_scripts = (gametype_scripts_t)0x0503F90;
#else
	#warning gametype_scripts_t gametype_scripts = (gametype_scripts_t)NULL;
	gametype_scripts_t gametype_scripts = (gametype_scripts_t)NULL;
#endif

typedef int (*codscript_load_t)(char* file);
#if COD_VERSION == COD2_1_3
    codscript_load_t codscript_load = (codscript_load_t)0x0474D80;
#else
    codscript_load_t codscript_load = (codscript_load_t)NULL;
#endif

typedef int (*codscript_load_function_t)(char *function);
#if COD_VERSION == COD2_1_3
    codscript_load_function_t codscript_load_function = (codscript_load_function_t)0x0474950;
#else
    codscript_load_function_t codscript_load_function = (codscript_load_function_t)NULL;
#endif

void hook_codscript_gametype_scripts()
{
    //printf("codecallback_playercommand=%.8x\n", codecallback_playercommand);

	// unhook
	cracking_write_hex((int)gametype_scripts, (char *)"A1287E89018B"); //  todo: hook->unhook()

	// call original
	gametype_scripts();

    if(codscript_load((char *)"maps/mp/gametypes/_callbacksetup"))
        codecallback_playercommand = codscript_load_function((char *)"CodeCallback_PlayerCommand");

	// hook again
	cracking_hook_function((int)gametype_scripts, (int)hook_codscript_gametype_scripts);
}*/

//int hook_ClientCommand(int clientNum)
//{
	/*
	// perfect idea: dont call the original function here, so other players wont see chat
	// so ppl can do cracked servers with !login mulder trustno1
	// ooooops, need to call it always, when the callback was not found
	*/
/*	if ( ! codecallback_playercommand)
	{
		//printf("NOT USING hook_ClientCommand(), because codecallback_playercommand was not defined.\n");
		return ClientCommand(clientNum);
	}

	stackPushArray();
	int args = trap_Argc();
	//printf("args: %d\n", args);
	for (int i=0; i<args; i++)
	{
		char tmp[1024];

		trap_Argv(i, tmp, sizeof(tmp));
		stackPushString(tmp);
		//printf("pushing: %s\n", tmp);
		stackPushArrayLast();
	}*/

	// todo: G_ENTITY(clientNum)
	//#if COD_VERSION == COD2_1_3 // search '\\name\\badinfo'
	//	short ret = codscript_call_callback_entity(/*gentity*/0x01744380 + 560 * clientNum, codecallback_playercommand, 1);
	//#else
	//	#warning short ret = codscript_call_callback_entity(NULL, codecallback_playercommand, 1);
	//	short ret = codscript_call_callback_entity(NULL, codecallback_playercommand, 1);
	//#endif

	//printf("codecallback_playercommand=%.8x ret=%i\n", codecallback_playercommand, ret);

	/*codscript_callback_finish(ret);

	//printf("after codscript_callback_finish\n");

	return 0;
}*/

DWORD WINAPI MyThread(LPVOID)
{
    if (isStarted) {
        Com_Printf("Already started!\n");
        return (int)NULL;
    }
    isStarted = 1;
    Com_Printf("[PLUGIN LOADED]\n");

    #if COD_VERSION == COD2_1_0
        cracking_hook_call(0x46B83F, (int)Scr_GetCustomFunction);
        cracking_hook_call(0x46BA83, (int)Scr_GetCustomMethod);
    #elif COD_VERSION == COD2_1_3
        cracking_hook_call(0x46E7BF, (int)Scr_GetCustomFunction);
        cracking_hook_call(0x46EA03, (int)Scr_GetCustomMethod);
        //cracking_hook_function((int)gametype_scripts, (int)hook_codscript_gametype_scripts);
        //cracking_hook_call(hook_ClientCommand_call, (int)hook_ClientCommand);
    #endif

    return 0;
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            //MessageBoxA( NULL, "[PLUGIN LOADED]", "libcod", MB_OK );
            g_hModule = hinstDLL;
            DisableThreadLibraryCalls(hinstDLL);
            CloseHandle(CreateThread(NULL, 0, &MyThread, NULL, 0, &g_threadID));
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_PROCESS_DETACH:
            Com_Printf("[PLUGIN UNLOADED]\n");
            FreeLibraryAndExitThread(g_hModule, 0);
            break;

        case DLL_THREAD_DETACH:
            Com_Printf("[THREAD DETACH]\n");
            break;
    }
    return TRUE; // succesful
}
