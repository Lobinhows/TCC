#ifndef SCREENS_H
#define SCREENS_H

#define DK_BLUE 0x08EB
#define MD_BLUE 0X3275
#define LG_BLUE 0x74BA
#define BG_COLOR 0xD71F
#define SEL_COLOR 0xCFEE
#define TXT_COLOR 0xF79D
#define DWIDTH 320 
#define DHEIGHT 240

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <background_arena.h>
#include "Typedefs.h"
#include "Player.h"

/// @brief Funções dedicadas à criação de telas e elementos de tela, como seletores e notificações;
extern pvp_pairing send_message;
extern pvp_pairing recv_message;
//  pvp_battle battle_send;
//  pvp_battle battle_recv;
extern String names[];

extern TFT_eSPI tft;
extern TFT_eSprite spr;
extern TFT_eSprite sprAtk;
extern TFT_eSprite bckgReset;
extern TFT_eSprite hp_spr;

extern Player player1;
extern Player enemy;
extern int plr_posit, enm_posit;

void mainScreen(TFT_eSPI tft);  // Tela inicial/Principal
void pvpScreen1(TFT_eSPI tft);  // Tela criar/procurar
void pvpScreen2(TFT_eSPI tft);  // Lobby de partida
void pvpScreen3(TFT_eSPI tft);  // Tela de procura de jogadores
void searchNames(TFT_eSPI tft);  // Atualizar os nomes na tela

void battleSetup();

void matchPrompt(TFT_eSPI tft);

void mainSelector(TFT_eSPI tft, int selected);
void pvp1Selector(TFT_eSPI tft, int selected);
void pvp3Selector(TFT_eSPI tft, int selected);


#endif