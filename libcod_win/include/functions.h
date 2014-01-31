#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef int (*Com_Printf_t)(const char*, ...);

#if COD_VERSION == COD2_1_3
    static Com_Printf_t Com_Printf = (Com_Printf_t)0x0431EE0;
#else
    static Com_Printf_t Com_Printf = (Com_Printf_t)NULL;
    #warning Com_Printf_t Com_Printf = NULL;
#endif

#endif // FUNCTIONS_H
