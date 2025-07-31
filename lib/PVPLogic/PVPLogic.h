#ifndef PVP_LOGIC_H
#define PVP_LOGIC_H

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include "Screens.h"
#include "Navigation.h"

extern pvp_pairing recv_message;
extern pvp_battle recv_battle;

extern esp_now_peer_info_t peerInfo;
extern uint8_t broadcastAddress[];
extern TFT_eSPI tft; 

extern uint8_t temp_mac[6];
extern uint8_t mac_rcv1[6];
extern uint8_t mac_rcv2[6];
extern uint8_t mac_rcv3[6];
extern uint8_t mac_rcv4[6];
extern uint8_t mac_rcv5[6];
extern char  plr_counter;
extern uint8_t *mac_pos[];
extern int selected;
extern String names[5]; 
extern byte progState;
extern bool flag_rqst, flag_acpt, flag_refuse, atkOn, atkOn_enm, move_flag, move_flag_enm;

extern int atkX, atkY, atkX_enm, atkY_enm, enm_posit, plr_posit;

void configEspNow(const uint8_t * mac);
void matchmakingCallback(const uint8_t * mac, const uint8_t *incomingData, int len);
void battleCallback(const uint8_t * mac, const uint8_t *incomingData, int len);
void waitingMsg();

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status); 


#endif