#include <stdio.h>
#define _WIN32_WINNT 0x500
#include <windows.h>
#include <tlhelp32.h>

void EnableDebugPriv();
void CALLBACK WaitOrTimerCallback(PVOID lpParameter, BOOLEAN TimerOrWaitFired);
int GetProcessByName(char *name, HANDLE *outProcessHandle, int *outProcessID);
void InjectDLL(HANDLE hProcess, char *name, bool delay);
void WaitForProcessAndInjectDLL(char *name_process, char *name_dll);
void LoopInjecting();
bool nodelay = false;

BOOL FileExists(LPCTSTR szPath)
{
  DWORD dwAttrib = GetFileAttributes(szPath);

  return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
         !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

void EnableDebugPriv() {
    HANDLE hToken;
    LUID luid;
    TOKEN_PRIVILEGES tkp;
    OpenProcessToken( GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken );
    LookupPrivilegeValue( NULL, SE_DEBUG_NAME, &luid );
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Luid = luid;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    AdjustTokenPrivileges( hToken, false, &tkp, sizeof( tkp ), NULL, NULL );
    CloseHandle( hToken );
}

void CALLBACK WaitOrTimerCallback(PVOID lpParameter, BOOLEAN TimerOrWaitFired) {
    //MessageBox(0, "The process has exited.", "INFO", MB_OK);
    LoopInjecting();
}

int GetProcessByName(char *name, HANDLE *outProcessHandle, int *outProcessID) {
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof( PROCESSENTRY32 );
    HANDLE snapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, NULL );
    if ( Process32First( snapshot, &entry ) != TRUE )
        return 0;
    while (Process32Next( snapshot, &entry ) == TRUE) {
        if (stricmp( entry.szExeFile, name) != 0)
            continue;
        // printf("Found: %s\n", entry.szExeFile);
        // PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_WRITE
        *outProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
        *outProcessID = entry.th32ProcessID;
        return 1;
    }
    CloseHandle( snapshot );
    return 0;
}

void InjectDLL(HANDLE hProcess, char *name, bool delay) {
    char dirPath[MAX_PATH];
    char fullPath[MAX_PATH];
    GetCurrentDirectory( MAX_PATH, dirPath );
    snprintf ( fullPath, MAX_PATH, "%s\\%s", dirPath, name);

    if(FileExists(fullPath) == 1)
    {
        if(delay && !nodelay)
            Sleep(350); // delay injecting due to UAC popup

        printf("Injecting: %s\n", fullPath);
        LPVOID libAddr = (LPVOID)GetProcAddress( GetModuleHandle( "kernel32.dll" ), "LoadLibraryA" );
        LPVOID llParam = (LPVOID)VirtualAllocEx( hProcess, NULL, strlen( fullPath ) + 1, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE );
        printf("libAddr=%.8p llParam=%.8p\n", libAddr, llParam);
        bool written = WriteProcessMemory( hProcess, llParam, fullPath, strlen( fullPath ) + 1, NULL );
        HANDLE threadID = CreateRemoteThread( hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)libAddr, llParam, NULL, NULL );
        //CloseHandle( hProcess );
        printf("Finished injecting DLL success=%d thread #%d\n", written, threadID);
    }
    else
        printf("File '%s' does not exist.\n", fullPath);
}

void WaitForProcessAndInjectDLL(char *name_process, char *name_dll) {
    printf("WaitForProcessAndInjectDLL(process=%s, dll=%s);\n", name_process, name_dll);
    HANDLE hProcess;
    int processID;
    bool delay = false;
    while (1) {
        int ret = GetProcessByName(name_process, &hProcess, &processID);
        if (ret == 0) {
            printf(".");
            Sleep(1000);
            delay = true;
            continue;
        }
        printf("\nprocessID=%d\n", processID);
        InjectDLL(hProcess, name_dll, delay);
        HANDLE hNewHandle;
        RegisterWaitForSingleObject(&hNewHandle, hProcess, WaitOrTimerCallback, NULL, INFINITE, WT_EXECUTEONLYONCE);
        break;
    }
}

int argc;
char **argv;
void LoopInjecting() {
    // CoD2MP_s.exe
    WaitForProcessAndInjectDLL(argv[1], argv[2]); // process, dll
}
int main(int c, char **v) {
    argc = c;
    argv = v;
    if (argc < 2) {
        printf("Please provide process-name and dll-name!\nExample: InjectDLL SERVER.exe libcod2_1_3.dll");
        getchar();
        return 1;
    }

    if(argc == 4 && strcmp(argv[3], "1"))
        nodelay = true;

    EnableDebugPriv();
    LoopInjecting();
    getchar();
    return 0;
}
