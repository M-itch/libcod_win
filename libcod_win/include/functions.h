#ifndef FUNCTIONS_H
#define FUNCTIONS_H

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

#if COD_VERSION == COD2_1_3
    static Cmd_ExecuteString_t Cmd_ExecuteString = (Cmd_ExecuteString_t)0x04214C0;
#else
    static Cmd_ExecuteString_t Cmd_ExecuteString = (Cmd_ExecuteString_t)0;
    #warning Cmd_ExecuteString_t Cmd_ExecuteString = NULL;
#endif

#endif // FUNCTIONS_H
