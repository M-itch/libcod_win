#include "main.h"
#include <stdio.h>
#include "include/gsc.h"
#include "include/functions.h"
#include "include/cracking.h"

DWORD WINAPI MyThread(LPVOID);
DWORD g_threadID;
HMODULE g_hModule;
static int isStarted = 0;

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
