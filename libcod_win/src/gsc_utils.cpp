#include "../include/gsc_utils.h"
#include "../include/functions.h"
#include "../include/gsc.h"
#include "../include/cracking.h"
#include <string.h> // strlen
#include <stdlib.h> // system
#include <windows.h>

#if COMPILE_UTILS == 1

void gsc_utils_disableGlobalPlayerCollision() {
	// well, i could also just write LEAVE,RETN C9,C3 at beginnung of function

    #if COD_VERSION == COD2_1_3
        cracking_write_hex(0x05009F0, (char *)"C3");
        cracking_write_hex(0x05011E5, (char *)"02");
        cracking_write_hex(0x041CB40, (char *)"C3");
	#endif

	stackPushUndefined();
}

void gsc_utils_getAscii() {
	char *str;
	if ( ! stackGetParams((char *)"s", &str) || strlen(str) == 0) {
		stackPushUndefined();
		return;
	}
	stackPushInt(str[0]);
}

void gsc_utils_system() { // closer 903, "ls"
	char *cmd;
	if ( ! stackGetParams((char *)"s",  &cmd)) {
		Com_Printf("scriptengine> ERROR: please specify the command as string to gsc_system_command()\n");
		stackPushUndefined();
		return;
	}
	//setenv("LD_PRELOAD", "", 1); // dont inherit lib of parent
	stackPushInt( system(cmd) );
}

void gsc_utils_file_link() {
	char *source, *dest;
	if ( ! stackGetParams((char *)"ss",  &source, &dest)) {
		Com_Printf("scriptengine> ERROR: please specify source and dest to gsc_link_file()\n");
		stackPushUndefined();
		return;
	}
	stackPushInt( CreateHardLink(source, dest, NULL) ); // 1 == success
}

void gsc_utils_file_unlink() {
	char *file;
	if ( ! stackGetParams((char *)"s",  &file)) {
		Com_Printf("scriptengine> ERROR: please specify file to gsc_unlink_file()\n");
		stackPushUndefined();
		return;
	}
	stackPushInt( DeleteFile(file) ); // 1 == success
}

void gsc_utils_file_exists() {
	char *filename;
	if ( ! stackGetParams((char *)"s", &filename)) {
		stackPushUndefined();
		return;
	}
	stackPushInt(1);
}

void gsc_utils_getType() {
	if (stackGetNumberOfParams() == 0) {
		stackPushUndefined();
		return;
	}
	stackPushString( stackGetParamTypeAsString(0) );
}

void gsc_utils_stringToFloat() {
	char *str;
	if ( ! stackGetParams((char *)"s", &str)) {
		stackPushUndefined();
		return;
	}
	stackPushFloat( atof(str) );
}

void gsc_utils_ExecuteString() {
    char *str;
	if ( ! stackGetParams((char *)"s", &str)) {
		stackPushUndefined();
		return;
	}

	Cmd_ExecuteString(str);
	stackPushInt(1);
}

#endif
