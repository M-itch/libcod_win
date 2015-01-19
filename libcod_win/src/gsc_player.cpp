#include "../include/gsc_player.h"
#include "../include/functions.h"
#include "../include/gsc.h"
#include <stdio.h>

#if COMPILE_PLAYER == 1

// search ------- Game Initialization -------
#if COD_VERSION == COD2_1_0
	int playerStates = 0x01722E00;
	int sizeOfPlayer = 0x28A4;
#elif COD_VERSION == COD2_1_3
	int playerStates = 0x01897E80;
	int sizeOfPlayer = 0x28A4;
#else
	#warning int playerStates int sizeOfPlayer
	int playerStates = NULL;
	int sizeOfPlayer = NULL;
#endif

#if COD_VERSION == COD2_1_0
	int gentities = 0x015CF300;
	int gentities_size = 560;
#elif COD_VERSION == COD2_1_3
	int gentities = 0x01744380;
	int gentities_size = 560;
#else
	#warning int gentities int gentities_size
	int gentities = NULL;
	int gentities_size = NULL;
#endif

#define PLAYERSTATE(playerid) (playerStates + playerid * sizeOfPlayer)
#if COD_VERSION == COD2_1_0 || COD_VERSION == COD2_1_2 || COD_VERSION == COD2_1_3
	#define PLAYERSTATE_VELOCITY(playerid) (PLAYERSTATE(playerid) + 0x20)
#else
	#warning NO PLAYERSTATE_VELOCITY!
	#define PLAYERSTATE_VELOCITY(playerid) 0
#endif

#if COD_VERSION == COD2_1_0
	int playerinfo_base = 0x0C0990C;
	int playerinfo_size = 0x78F14;
#elif COD_VERSION == COD2_1_3
	int playerinfo_base = 0x0D3570C;
	int playerinfo_size = 0xB1064;
#else
	#warning PLAYERBASE() got no working addresses
	int playerinfo_base = 0x0;
	int playerinfo_size = 0x0;
#endif

#define PLAYERBASE(playerid) (*(int*)(playerinfo_base) + playerid * playerinfo_size)

void gsc_player_velocity_set(int id) {
	float velocity[3];

	if ( ! stackGetParams((char *)"v", &velocity)) {
		Com_Printf("scriptengine> wrongs args for gsc_player_velocity_add(vector velocity);\n");
		stackPushUndefined();
		return;
	}

	float *player_0_velocity_x = (float *)(PLAYERSTATE_VELOCITY(id) + 0);
	float *player_0_velocity_y = (float *)(PLAYERSTATE_VELOCITY(id) + 4);
	float *player_0_velocity_z = (float *)(PLAYERSTATE_VELOCITY(id) + 8);

	*player_0_velocity_x = velocity[0];
	*player_0_velocity_y = velocity[1];
	*player_0_velocity_z = velocity[2];

	stackReturnInt(1);
}

void gsc_player_velocity_add(int id) {
	float velocity[3];

	if ( ! stackGetParams((char *)"v", &velocity)) {
		Com_Printf("scriptengine> wrongs args for gsc_player_velocity_add(vector velocity);\n");
		stackPushUndefined();
		return;
	}

	float *player_0_velocity_x = (float *)(PLAYERSTATE_VELOCITY(id) + 0);
	float *player_0_velocity_y = (float *)(PLAYERSTATE_VELOCITY(id) + 4);
	float *player_0_velocity_z = (float *)(PLAYERSTATE_VELOCITY(id) + 8);

	*player_0_velocity_x += velocity[0];
	*player_0_velocity_y += velocity[1];
	*player_0_velocity_z += velocity[2];

	stackReturnInt(1);
}

void gsc_player_velocity_get(int id) {
	//int currentPlayer = playerStates + id * sizeOfPlayer;
	float *vectorVelocity = (float *)PLAYERSTATE_VELOCITY(id); // (currentPlayer + 0x20);
	stackReturnVector(vectorVelocity);
}

// aimButtonPressed (toggleads or +speed/-speed)
void gsc_player_button_ads(int id) {
	int currentPlayer = playerStates + id * sizeOfPlayer;
	unsigned char *aim_address = (unsigned char *)(currentPlayer + 0x26CD);
	int aimButtonPressed = *aim_address & 0xF0; // just the first 4 bits tell the state
	stackReturnInt(aimButtonPressed);
}

void gsc_player_button_left(int id) {
	#if COD_VERSION == COD2_1_0 || COD_VERSION == COD2_1_2 || COD_VERSION == COD2_1_3
		unsigned char *aim_address = (unsigned char *)(PLAYERSTATE(id) + 0x26FD);
	#elif COD_VERSION == COD4_1_7
		unsigned char *aim_address = (unsigned char *)(PLAYERSTATE(id) + 0x2FA7);
	#else
		#warning unsigned char *aim_address = (unsigned char *)(NULL);
		unsigned char *aim_address = (unsigned char *)(NULL);
	#endif
	int leftButtonPressed = (*aim_address & 0x81)==0x81;
	stackReturnInt(leftButtonPressed);
}

void gsc_player_button_right(int id) {
	#if COD_VERSION == COD2_1_0 || COD_VERSION == COD2_1_2 || COD_VERSION == COD2_1_3
		unsigned char *aim_address = (unsigned char *)(PLAYERSTATE(id) + 0x26FD);
	#elif COD_VERSION == COD4_1_7
		unsigned char *aim_address = (unsigned char *)(PLAYERSTATE(id) + 0x2FA7);
	#else
		#warning unsigned char *aim_address = (unsigned char *)(NULL);
		unsigned char *aim_address = (unsigned char *)(NULL);
	#endif

	int rightButtonPressed = (*aim_address & 0x7F)==0x7F;
	stackReturnInt(rightButtonPressed);
}

void gsc_player_button_forward(int id) {
	#if COD_VERSION == COD2_1_0 || COD_VERSION == COD2_1_2 || COD_VERSION == COD2_1_3
		unsigned char *aim_address = (unsigned char *)(PLAYERSTATE(id) + 0x26FC);
	#elif COD_VERSION == COD4_1_7
		unsigned char *aim_address = (unsigned char *)(PLAYERSTATE(id) + 0x2FA6);
	#else
		#warning unsigned char *aim_address = (unsigned char *)(NULL);
		unsigned char *aim_address = (unsigned char *)(NULL);
	#endif

	int forwardButtonPressed = (*aim_address & 0x7F)==0x7F;
	stackReturnInt(forwardButtonPressed);
}

void gsc_player_button_back(int id) {
	#if COD_VERSION == COD2_1_0 || COD_VERSION == COD2_1_2 || COD_VERSION == COD2_1_3
		unsigned char *aim_address = (unsigned char *)(PLAYERSTATE(id) + 0x26FC);
	#elif COD_VERSION == COD4_1_7
		unsigned char *aim_address = (unsigned char *)(PLAYERSTATE(id) + 0x2FA6);
	#else
		#warning unsigned char *aim_address = (unsigned char *)(NULL);
		unsigned char *aim_address = (unsigned char *)(NULL);
	#endif

	int backButtonPressed = (*aim_address & 0x81)==0x81;
	stackReturnInt(backButtonPressed);
}

void gsc_player_button_leanleft(int id) {
	#if COD_VERSION == COD2_1_0 || COD_VERSION == COD2_1_2 || COD_VERSION == COD2_1_3
		unsigned char *aim_address = (unsigned char *)(PLAYERSTATE(id) + 0x26E8);
	#elif COD_VERSION == COD4_1_7
		unsigned char *aim_address = (unsigned char *)(PLAYERSTATE(id) + 0x2FB4);
	#else
		#warning unsigned char *aim_address = (unsigned char *)(NULL);
		unsigned char *aim_address = (unsigned char *)(NULL);
	#endif

	int leanleftButtonPressed = (*aim_address & 0x40)==0x40;
	stackReturnInt(leanleftButtonPressed);
}

void gsc_player_button_leanright(int id) {
	#if COD_VERSION == COD2_1_0 || COD_VERSION == COD2_1_2 || COD_VERSION == COD2_1_3
		unsigned char *aim_address = (unsigned char *)(PLAYERSTATE(id) + 0x26E8);
	#elif COD_VERSION == COD4_1_7
		unsigned char *aim_address = (unsigned char *)(PLAYERSTATE(id) + 0x2FB4);
	#else
		#warning unsigned char *aim_address = (unsigned char *)(NULL);
		unsigned char *aim_address = (unsigned char *)(NULL);
	#endif

	int leanrightButtonPressed = (*aim_address & 0x80)==0x80;
	stackReturnInt(leanrightButtonPressed);
}

void gsc_player_button_jump(int id) {
	#if COD_VERSION == COD2_1_0 || COD_VERSION == COD2_1_2 || COD_VERSION == COD2_1_3
		unsigned char *aim_address = (unsigned char *)(PLAYERSTATE(id) + 0x26E9);
	#elif COD_VERSION == COD4_1_7
		unsigned char *aim_address = (unsigned char *)(PLAYERSTATE(id) + 0x2FB5);
	#else
		#warning unsigned char *aim_address = (unsigned char *)(NULL);
		unsigned char *aim_address = (unsigned char *)(NULL);
	#endif

	int jumpButtonPressed = (*aim_address & 0x04)==0x04;
	stackReturnInt(jumpButtonPressed);
}

/*
CoD2 = 26E8 == leanleft:40 leanright:80
CoD4 = 26E9 == jump:04
CoD2 = 26FC == forward:7f backward:81
CoD2 = 26FD == left:81 right:7f

CoD4 = 2FA6 == forward:7f backward:81
CoD4 = 2FA7 == left:81 right:7f
CoD4 = 2FB4 == leanleft:40 leanright:80
CoD4 = 2FB5 == jump:04
*/

void gsc_player_stance_get(int id) {
	int entity = gentities + id * gentities_size;
	unsigned char *stance_address = (unsigned char *)(entity + 8);
	int code = *stance_address & 0x0F; // just the last 4 bits tell the state

	char *stance = (char *)"";
	switch (code) {
		case  0: stance = (char *)"stand"; break; // also in spec
		case  2: stance = (char *)"stand"; break;
		case  4: stance = (char *)"duck"; break;
		case  6: stance = (char *)"duck"; break;
		case  8: stance = (char *)"lie"; break;
		case 10: stance = (char *)"lie"; break;
		default: Com_Printf("unknown stance for player id=%d, code=%d\n", id, code);
	}

	stackPushString(stance);
}

void gsc_player_spectatorclient_get(int id) {
	int entity = PLAYERSTATE(id);
	int spectatorClient = *(unsigned char *)(entity + 0xCC);

	//Com_Printf("spectator client: %x=%d\n", entity, spectatorClient);

	// ups, its ALWAYS returning a real id
	// when i have 2 bots, then i got id 2, when i spec "myself" it will return 2, also when i play myself
	//if ( ! spectatorClient)
	//	return stackPushUndefined();

	stackPushEntity(gentities + spectatorClient * gentities_size);
}

void gsc_player_getip(int id) {
    #if COD_VERSION == COD2_1_0
        int info_ip_offset = 0x6E5C8;
	#elif COD_VERSION == COD2_1_3
		int info_ip_offset = 0x6E6D8;
	#else
		#warning gsc_player_getip() got no working addresses
		int info_ip_offset = 0x0;
	#endif

	int info_player = PLAYERBASE(id);

	int ip_a = *(unsigned char *)(info_player + info_ip_offset + 0);
	int ip_b = *(unsigned char *)(info_player + info_ip_offset + 1); // dafuq, its +1 but in IDA its +4 step :S
	int ip_c = *(unsigned char *)(info_player + info_ip_offset + 2);
	int ip_d = *(unsigned char *)(info_player + info_ip_offset + 3);
	//int port = *(unsigned char *)(info_player + info_ip_offset + 16);

	char tmp[64];
	snprintf(tmp, 64, "%d.%d.%d.%d", ip_a, ip_b, ip_c, ip_d);
	//snprintf(tmp, 64, "%d.%d.%d.%d:%d", ip_a, ip_b, ip_c, ip_d, port);

	stackPushString(tmp);
}

void gsc_player_getping(int id) {
    #if COD_VERSION == COD2_1_0
        int info_port_offset = 0x6E5A4;
	#elif COD_VERSION == COD2_1_3
		int info_port_offset = 0x6E6B4;
	#else
		#warning gsc_player_getip() got no working addresses
		int info_port_offset = 0x0;
	#endif

	int info_player = PLAYERBASE(id);
	int ping = *(unsigned int *)(info_player + info_port_offset);
	stackPushInt(ping);
}

void gsc_player_ClientCommand(int id) {
	stackPushInt(0); //ClientCommand(id));
}

void gsc_player_getLastConnectTime(int id) {
    #if COD_VERSION == COD2_1_0
		int info_start = *(int *)0x0C09904;
		int info_connecttime_offset = 0x20D14;
	#elif COD_VERSION == COD2_1_3
		int info_start = *(int *)0x0D35704;
		int info_connecttime_offset = 0x20E24;
	#else
		#warning gsc_player_getLastConnectTime() got no working addresses
		int info_start = *(int *)0x0;
		int info_connecttime_offset = 0x0;
	#endif

	int info_player = PLAYERBASE(id);
	int lastconnect = info_start - *(unsigned int *)(info_player + info_connecttime_offset);
	stackPushInt(lastconnect);
}

void gsc_player_getLastMSG(int id) {
	#if COD_VERSION == COD2_1_0
		int info_start = *(int *)0x0C09904;
		int info_lastmsg_offset = 0x20D10;
	#elif COD_VERSION == COD2_1_3
		int info_start = *(int *)0x0D35704;
		int info_lastmsg_offset = 0x20E20;
	#else
		#warning gsc_player_getlastmsg() got no working addresses
		int info_start = *(int *)0x0;
		int info_lastmsg_offset = 0x0;
	#endif

	int info_player = PLAYERBASE(id);
	int lastmsg = info_start - *(unsigned int *)(info_player + info_lastmsg_offset);
	stackPushInt(lastmsg);
}

// entity functions (could be in own file, but atm not many pure entity functions)

void gsc_entity_setalive(int id) { // as in isAlive?
	int isAlive;

	if ( ! stackGetParams((char *)"i", &isAlive)) {
		Com_Printf("scriptengine> ERROR: gsc_player_setalive(): param \"isAlive\"[1] has to be an integer!\n");
		stackPushUndefined();
		return;
	}

	*(char *)(gentities + gentities_size*id + 353) = isAlive;
	stackReturnInt(1);
}

void gsc_entity_setbounds(int id) {
	float width, height;

	if ( ! stackGetParams((char *)"ff", &width, &height)) {
		Com_Printf("scriptengine> ERROR: please specify width and height to gsc_entity_setbounds()\n");
		stackPushUndefined();
		return;
	}

	*(float*)(gentities + gentities_size*id + 280) = height;
	*(float*)(gentities + gentities_size*id + 276) = width;
	*(float*)(gentities + gentities_size*id + 272) = width;
	*(float*)(gentities + gentities_size*id + 264) = -width;
	*(float*)(gentities + gentities_size*id + 260) = -width;

	Com_Printf("id=%d height=%f width=%f\n", id, height, width);
	stackReturnInt(1);
}

void gsc_free_slot()
{
	int id = 0;
	if(!stackGetParamInt(0, &id))
	{
		printf("Param 0 needs to be an int for free_slot\n");
		stackPushUndefined();
		return;
	}

	int entity = PLAYERBASE(id);
	*(int*)entity = 0; //CS_FREE
	stackPushUndefined();
}

#endif
