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
    MessageBoxA( NULL, "[PLUGIN LOADED]", "libcod", MB_OK );
    Com_Printf("[PLUGIN LOADED]\n");

    cracking_hook_function(0x509290, (int)cdecl_injected_closer); // hook original closer function

    while(true)
    {

    }

    FreeLibraryAndExitThread(g_hModule, 0);
    return 0;
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        g_hModule = hinstDLL;
        DisableThreadLibraryCalls(hinstDLL);
        CreateThread(NULL, 0, &MyThread, NULL, 0, &g_threadID);
        break;

    case DLL_PROCESS_DETACH:
        Com_Printf("[PLUGIN UNLOADED]\n");
        break;

    case DLL_THREAD_ATTACH:
        // attach to thread
        break;

    case DLL_THREAD_DETACH:
        // detach from thread
        break;
    }
    return TRUE; // succesful
}
