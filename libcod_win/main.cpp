#include "main.h"
#include <stdio.h>
#include "include/functions.h"
#include "include/cracking.h"
#include "include/gsc.h"

DWORD WINAPI MyThread(LPVOID);
DWORD g_threadID;
HMODULE g_hModule;

DWORD WINAPI MyThread(LPVOID)
{
    Com_Printf("[PLUGIN LOADED]\n");

    #if COD_VERSION == COD2_1_3
        int closer = 0x509290;
    #else
        int closer = (int)NULL;
        #warning int closer = NULL;
    #endif

    cracking_hook_function(closer, (int)cdecl_injected_closer); // hook original closer function

    return 0;
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
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
