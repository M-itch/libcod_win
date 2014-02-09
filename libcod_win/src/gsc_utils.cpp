#include "../include/gsc_utils.h"
#include "../include/functions.h"
#include "../include/gsc.h"
#include "../include/cracking.h"
#include <string.h> // strlen
#include <stdlib.h> // system
#include <windows.h>

//#if COMPILE_UTILS == 1

int gsc_utils_disableGlobalPlayerCollision()
{
	int ret;

	// well, i could also just write LEAVE,RETN C9,C3 at beginnung of function

	#if COD_VERSION == COD2_1_3
        cracking_write_hex(0x05009F0, (char *)"C3");
        cracking_write_hex(0x05011E5, (char *)"02");
        cracking_write_hex(0x041CB40, (char *)"C3");
	#endif

	return stackPushInt(ret);
}

int gsc_utils_ClientCommand()
{
	int clientNum;
	if ( ! stackGetParamInt(1, &clientNum))
		return stackPushUndefined();
	//int ret = ClientCommand(clientNum);
	return stackPushInt(0);
}

int gsc_utils_getAscii()
{
	char *str;
	if ( ! stackGetParamString(1, &str))
		return stackPushUndefined();
	if (strlen(str) == 0)
		return stackPushUndefined();
	return stackPushInt(str[0]);
}

int gsc_utils_system() // closer 903, "ls"
{
	char *cmd;
	if (stackGetNumberOfParams() < 2) // function, command
	{
		Com_Printf("scriptengine> ERROR: please specify atleast 2 arguments to gsc_system_command()\n");
		return stackPushUndefined();
	}
	if (!stackGetParamString(1, &cmd))
	{
		Com_Printf("scriptengine> ERROR: closer(): param \"cmd\"[1] has to be a string!\n");
		return stackPushUndefined();
	}
	//setenv("LD_PRELOAD", "", 1); // dont inherit lib of parent
	int ret = system(cmd);
	return stackPushInt(ret);
}
int gsc_utils_file_link()
{
	char *source;
	char *dest;
	if (stackGetNumberOfParams() < 3) // function, source, dest
	{
		Com_Printf("scriptengine> ERROR: please specify atleast 3 arguments to gsc_link_file()\n");
		return stackPushUndefined();
	}
	if (!stackGetParamString(1, &source))
	{
		Com_Printf("scriptengine> ERROR: closer(): param \"source\"[1] has to be a string!\n");
		return stackPushUndefined();
	}
	if (!stackGetParamString(2, &dest))
	{
		Com_Printf("scriptengine> ERROR: closer(): param \"dest\"[2] has to be a string!\n");
		return stackPushUndefined();
	}
	int ret = CreateHardLink(source, dest, NULL);
	return stackPushInt(ret); // 1 == success
}

int gsc_utils_file_unlink()
{
	char *file;
	if (stackGetNumberOfParams() < 2) // function, source, dest
	{
		Com_Printf("scriptengine> ERROR: please specify atleast 2 arguments to gsc_unlink_file()\n");
		return stackPushUndefined();
	}
	if (!stackGetParamString(1, &file))
	{
		Com_Printf("scriptengine> ERROR: closer(): param \"file\"[1] has to be a string!\n");
		return stackPushUndefined();
	}
	int ret = DeleteFile(file);
	return stackPushInt(ret); // 1 == success
}

//#endif
