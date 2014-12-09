#ifndef _GSC_PLAYER_H_
#define _GSC_PLAYER_H_

void gsc_player_velocity_set(int id);
void gsc_player_velocity_add(int id);
void gsc_player_velocity_get(int id);

void gsc_player_button_ads(int id);
void gsc_player_button_left(int id);
void gsc_player_button_right(int id);
void gsc_player_button_forward(int id);
void gsc_player_button_back(int id);
void gsc_player_button_leanleft(int id);
void gsc_player_button_leanright(int id);
void gsc_player_button_jump(int id);

void gsc_player_stance_get(int id);

void gsc_player_spectatorclient_get(int id);

void gsc_player_getip(int id);
void gsc_player_getping(int id);

void gsc_player_ClientCommand(int id);

void gsc_player_getLastConnectTime(int id);
void gsc_player_getLastMSG(int id);

// entity functions
void gsc_entity_setalive(int id);
void gsc_entity_setbounds(int id);

void gsc_free_slot();

#endif
