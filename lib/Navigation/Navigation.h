#ifndef NAVIGATION_H
#define NAVIGATION_H

#define leftButton 33
#define upButton 27
#define rightButton 25
#define downButton 14
#define atkButton 32
#define bckButton 26

#include <Arduino.h>
// #include "Screens.h"
#include "PVPLogic.h"
// #include "Typedefs.h"

/// @brief Funções que cuidam da parte lógica, dedicadas à navegação pelas telas

extern bool mp_flag;
extern char bPressed;
extern int selected;
extern byte progState;
extern unsigned long cb_timer;
extern unsigned long enm_move_timer;

extern pvp_pairing send_message;
extern pvp_pairing recv_message;
extern pvp_battle battle_send;
extern pvp_battle battle_recv;

extern uint8_t mac_rcv1[6];
extern uint8_t mac_rcv2[6];
extern uint8_t mac_rcv3[6];
extern uint8_t mac_rcv4[6];
extern uint8_t mac_rcv5[6];
extern char  plr_counter;
extern uint8_t *mac_pos[];

// extern bool lpress, rpress, upress, dpress, atkpress;
// bool lpress, rpress, upress, dpress, atkpress = false;
char readPress();


void menuCommands(TFT_eSPI tft, char press);  //Switch com estados do programa --- PROVAVELMENTE VAI SAIR DAQUI

void mainMenu(TFT_eSPI tft, char press);
void menuPVP1(TFT_eSPI tft, char press); // Criar/procurar sala
void menuPVP2(TFT_eSPI tft, char press); // Sala o PVP
void menuPVP3(TFT_eSPI tft, char press); // Procura de jogadores




#endif