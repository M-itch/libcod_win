#include <stdio.h>
#include <Windows.h>
#include "../include/cracking.h"

#include "../include/gsc.h"

// a sample exported function
//void DLL_EXPORT SomeFunction(const LPCSTR sometext)
//{
//    MessageBoxA(0, sometext, "DLL Message", MB_OK | MB_ICONINFORMATION);
//}

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


FILE *logfile;
log_init() {
    logfile = fopen("libcod_log.txt", "w");
}
void log(char *msg, ...) {
    fwrite(msg, 1, strlen(msg),logfile);
    fflush(logfile);
}

cHook *chook_SetWindowLong;
LONG WINAPI hook_SetWindowLong(HWND hWnd, int  nIndex, LONG dwNewLong) {
    char buf[1024];
    sprintf(buf, "hook_SetWindowLong: hwnd=%p nIndex=%d dwNewLong=%p\n", hWnd, nIndex, dwNewLong);
    log(buf);
    chook_SetWindowLong->unhook();
    LONG WINAPI (*sig)(HWND hWnd, int nIndex, LONG dwNewLong);
    *(int *)&sig = (int)chook_SetWindowLong->from;
    LONG ret = sig(hWnd, nIndex, dwNewLong);
    chook_SetWindowLong->hook();
    return ret;
}


cHook *chook_CreateWindowExA;
HWND WINAPI hook_CreateWindowExA(DWORD dwExStyle, LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam) {
    chook_CreateWindowExA->unhook();
    char buf[1024];

    HWND WINAPI (*sig)( DWORD dwExStyle, LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);
    dwStyle |= WS_MAXIMIZEBOX;
    dwStyle |= WS_SIZEBOX;
    dwStyle |= WS_SYSMENU;

    dwStyle = WS_OVERLAPPEDWINDOW;


    //dwExStyle = WS_EX_TOPMOST;
    dwExStyle = 0;

    *(int *)&sig = (int)chook_CreateWindowExA->from;
    HWND ret = sig(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);

    sprintf(buf, "hook_CreateWindowExA: HWND=%p dwExStyle=%p classname=%s windowname=%s\n", ret, dwExStyle, lpClassName, lpWindowName);
    //MessageBoxA(NULL, buf, "hook_CreateWindowEx", 0);
    log(buf);

    chook_CreateWindowExA->hook();
    return ret;
}

cHook *chook_RegisterClassExA;
ATOM WINAPI hook_RegisterClassExA(WNDCLASSEX *lpwcx) {
    char buf[1024];
    sprintf(buf, "hook_RegisterClassExA: lpwcx=%p winproc=%p\n", lpwcx, lpwcx->lpfnWndProc);
    log(buf);
    chook_RegisterClassExA->unhook();
    LONG WINAPI (*sig)(WNDCLASSEX *lpwcx);
    *(int *)&sig = (int)chook_RegisterClassExA->from;
    ATOM ret = sig(lpwcx);
    chook_RegisterClassExA->hook();
    return ret;
}
void alert(char *msg) {
    MessageBoxA(NULL, msg, "void alert(char *msg);", 0);
}

// MODE 1: hook the entry point (needs a custom .exe for each OS, because the address of LoadLibraryA differs)
// MODE 2: hook WinMain (tried hard, but it's just failing...) I thought I could end up using a platform independent LoadLibraryA, when more stuff is initialized (still could try Com_Init or something as entry hook)
#define MODE 1
// int a, int b, char *c, int d
void restore_start_function_and_jump_to_it() {
    alert("restore_start_function_and_jump_to_it()");


    #if MODE == 1
        // PE entry point

        #if COD_VERSION == COD2_1_0
            cracking_write_hex(0x005450D1, (char *)"6A60"); // PUSH 60
            cracking_write_hex(0x005450D3, (char *)"68F8965500"); // PUSH CoD2MP_s.005596F8
            cracking_write_hex(0x005450D8, (char *)"E847290000"); // CALL CoD2MP_s.00547A24
            cracking_write_hex(0x005450DD, (char *)"BF94000000"); // MOV EDI,94
            cracking_write_hex(0x005450E2, (char *)"8BC7"); // MOV EAX,EDI
            cracking_write_hex(0x005450E4, (char *)"E857740000"); // CALL CoD2MP_s.0054C540
            cracking_write_hex(0x005450E9, (char *)"8965E8"); // MOV DWORD PTR SS:[EBP-18],ESP
            cracking_write_hex(0x005450EC, (char *)"8BF4"); // MOV ESI,ESP
            cracking_write_hex(0x005450EE, (char *)"893E"); // MOV DWORD PTR DS:[ESI],EDI
            cracking_write_hex(0x005450F0, (char *)"56"); // PUSH ESI
            cracking_write_hex(0x005450F1, (char *)"FF157C915500"); // CALL DWORD PTR DS:[<&KERNEL32.GetVersion>; KERNEL32.GetVersionExA
            cracking_write_hex(0x005450F7, (char *)"8B4E10"); // MOV ECX,DWORD PTR DS:[ESI+10]
            asm("jmp *%0"::"r"(0x005450D1):);
        #elif COD_VERSION == COD2_1_0_1
            cracking_write_hex(0x005455D1, (char *)"6A60"); // PUSH 60
            cracking_write_hex(0x005455D3, (char *)"6828A75500"); // PUSH CoD2MP_s.005596F8
            cracking_write_hex(0x005455D8, (char *)"E847290000"); // CALL CoD2MP_s.00547A24
            cracking_write_hex(0x005455DD, (char *)"BF94000000"); // MOV EDI,94
            cracking_write_hex(0x005455E2, (char *)"8BC7"); // MOV EAX,EDI
            cracking_write_hex(0x005455E4, (char *)"E857740000"); // CALL CoD2MP_s.0054C540
            cracking_write_hex(0x005455E9, (char *)"8965E8"); // MOV DWORD PTR SS:[EBP-18],ESP
            cracking_write_hex(0x005455EC, (char *)"8BF4"); // MOV ESI,ESP
            cracking_write_hex(0x005455EE, (char *)"893E"); // MOV DWORD PTR DS:[ESI],EDI
            cracking_write_hex(0x005455F0, (char *)"56"); // PUSH ESI
            cracking_write_hex(0x005455F1, (char *)"FF1558A15500"); // CALL DWORD PTR DS:[<&KERNEL32.GetVersion>; KERNEL32.GetVersionExA
            cracking_write_hex(0x005455F7, (char *)"8B4E10"); // MOV ECX,DWORD PTR DS:[ESI+10]
            asm("jmp *%0"::"r"(0x005455D1):);
        #elif COD_VERSION == COD2_1_3
            cracking_write_hex(0x0057DB54, (char *)"6A60"); // PUSH 60
            cracking_write_hex(0x0057DB56, (char *)"68D8925900"); // PUSH original.005992D8
            cracking_write_hex(0x0057DB5B, (char *)"E8443F0000"); // CALL original.00581AA4
            cracking_write_hex(0x0057DB60, (char *)"BF94000000"); // MOV EDI,94
            cracking_write_hex(0x0057DB65, (char *)"8BC7"); // MOV EAX,EDI
            cracking_write_hex(0x0057DB67, (char *)"E8C4880000"); // CALL original.00586430
            cracking_write_hex(0x0057DB6C, (char *)"8965E8"); // MOV DWORD PTR SS:[EBP-18],ESP
            cracking_write_hex(0x0057DB6F, (char *)"8BF4"); // MOV ESI,ESP
            cracking_write_hex(0x0057DB71, (char *)"893E"); // MOV DWORD PTR DS:[ESI],EDI
            cracking_write_hex(0x0057DB73, (char *)"56"); // PUSH ESI                                 ; /pVersionInformation
            cracking_write_hex(0x0057DB74, (char *)"FF1560315900"); // CALL DWORD PTR DS:[<&KERNEL32.GetVersion>; \GetVersionExA
            cracking_write_hex(0x0057DB7A, (char *)"8B4E10"); // MOV ECX,DWORD PTR DS:[ESI+10]
            asm("jmp *%0"::"r"(0x0057DB54):);
        #endif

    #else
        // these are the WinAPI arguments
        // example from log: &a=0006FEA0 a=00400000 &b=0006FEA4 b=00000000 c=+dedicated 2 d=1
        char buf[1024];
        sprintf(buf, "&a=%08p a=%08x &b=%08p b=%08x c=%s d=%d\n", &a, a, &b, b, c, d);
        log(buf);

        // WinMain
        cracking_write_hex(0x00466460, (char *)"55"); // PUSH EBP
        cracking_write_hex(0x00466461, (char *)"8BEC"); // MOV EBP,ESP
        cracking_write_hex(0x00466463, (char *)"83E4F8"); // AND ESP,FFFFFFF8
        cracking_write_hex(0x00466466, (char *)"81EC04010000"); // SUB ESP,104
        cracking_write_hex(0x0046646C, (char *)"53"); // PUSH EBX
        cracking_write_hex(0x0046646D, (char *)"56"); // PUSH ESI
        cracking_write_hex(0x0046646E, (char *)"57"); // PUSH EDI
        cracking_write_hex(0x0046646F, (char *)"6800000300"); // PUSH 30000
        cracking_write_hex(0x00466474, (char *)"6800000200"); // PUSH 20000
        cracking_write_hex(0x00466479, (char *)"E850551100"); // CALL CoD2MP_s.0057B9CE
        cracking_write_hex(0x0046647E, (char *)"681F000800"); // PUSH 8001F
        cracking_write_hex(0x00466483, (char *)"681F000800"); // PUSH 8001F
        cracking_write_hex(0x00466488, (char *)"E841551100"); // CALL CoD2MP_s.0057B9CE

        sprintf(buf, "&a=%08p a=%08x &b=%08p b=%08x c=%s d=%d\n", &a, a, &b, b, c, d);
        log(buf);

        asm("int $3"); // visual studio debugging
        asm("jmp *%0"::"r"(0x00466460):);
    #endif

}

/*
    This must be called in DLL_PROCESS_ATTACH, when libcod_win is used without the DLL injector.
    Instead the .exe has changed opcodes at the Program Entry Point, which need to be fixed
    basically just two opcodes:
        PUSH "libcod2_1_3.dll"
        CALL LoadLibraryA
    Because the LoadLibraryA address differs on WinXP/7/8/10, the .exe is system dependent. But the .dll is portable (compiled on XP worked in 10)

*/
int restore_entry_function() {

            //MessageBoxA(NULL, "Hello KILLTUBE!", "blub Starting libcod.dll from libcod_1_3.exe!", MB_ICONINFORMATION);

            log_init();

            #if 0
            //cracking_hook_function(0x0059324C, (int)hook_CreateWindowEx);
            //cracking_hook_function(0x00547E88, (int)hook_CreateWindowEx);
            {
            DWORD createwindowexa = (DWORD) GetProcAddress(LoadLibraryA("user32.dll"), "CreateWindowExA");
            chook_CreateWindowExA = new cHook(createwindowexa, (int)hook_CreateWindowExA);
            chook_CreateWindowExA->hook();


            DWORD setwindowlong = (DWORD) GetProcAddress(LoadLibraryA("user32.dll"), "SetWindowLongA");
            chook_SetWindowLong = new cHook(setwindowlong, (int)hook_SetWindowLong);
            chook_SetWindowLong->hook();

            DWORD registerclassexa = (DWORD) GetProcAddress(LoadLibraryA("user32.dll"), "RegisterClassExA");
            chook_RegisterClassExA = new cHook(registerclassexa, (int)hook_RegisterClassExA);
            chook_RegisterClassExA->hook();




            //cracking_hook_function(createwindow, (int)hook_CreateWindowEx);
            char buf[1024];
            sprintf(buf, "DllMain: 0x0059324C = %.8p createwindow=%.8p\n", *(unsigned int *)0x0059324C, createwindowexa);
            log(buf);
            }
            #endif


            // the cleanup will now be executed when LoadLibraryA returned, before we just jumped from inside LoadLibraryA to start(), but that crashed without +set developer 2
            #if MODE == 1
                #if COD_VERSION == COD2_1_0
                    cracking_hook_function(0x005450DB, (int)restore_start_function_and_jump_to_it);
                #elif COD_VERSION == COD2_1_0_1
                    cracking_hook_function(0x005455DB, (int)restore_start_function_and_jump_to_it);
                #elif COD_VERSION == COD2_1_3
                    cracking_hook_function(0x0057db5e, (int)restore_start_function_and_jump_to_it);
                #endif


            #else
                cracking_hook_function(0x46646a, (int)restore_start_function_and_jump_to_it);
            #endif
}

