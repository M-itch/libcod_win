#ifndef _GSC_PLAYER_H_
#define _GSC_PLAYER_H_

int gsc_player_velocity_set();
int gsc_player_velocity_add();
int gsc_player_velocity_get();

int gsc_player_button_ads();
int gsc_player_button_left();
int gsc_player_button_right();
int gsc_player_button_forward();
int gsc_player_button_back();
int gsc_player_button_leanleft();
int gsc_player_button_leanright();
int gsc_player_button_jump();

int gsc_player_state_alive_set();

int gsc_player_stance_get();

int gsc_player_spectatorclient_get();

int gsc_player_getip();
int gsc_player_getping();

#endif
