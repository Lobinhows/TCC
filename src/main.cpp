#include <Arduino.h>
#include <TFT_eSPI.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include <math.h>
#include <Wire.h>

#include <esp_now.h>
#include <WiFi.h>
#include <SD.h>

#include <Player.h>
#include "Screens.h"
#include "Navigation.h"

#define CNUMBER 42

uint8_t temp_mac[6];
uint8_t mac_rcv1[6];
uint8_t mac_rcv2[6];
uint8_t mac_rcv3[6];
uint8_t mac_rcv4[6];
uint8_t mac_rcv5[6];
char plr_counter = 0;
uint8_t *mac_pos[] = {mac_rcv1, mac_rcv2, mac_rcv3, mac_rcv4, mac_rcv5};

String names[5] = {"","","","",""}; 


TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft); // Sprite for characters
TFT_eSprite sprAtk = TFT_eSprite(&tft); // Sprite for attacks
TFT_eSprite bckgReset = TFT_eSprite(&tft);  //Sprite for cleaning background (used when moving players)
TFT_eSprite hp_spr = TFT_eSprite(&tft); //Sprite for players HP.

// MPUs IMU(MPU6050);
// SensorData medidas; 

uint16_t* atkIMG;
uint16_t* atkIMG_mirror; 
byte progState = 0; // Basically, the actual screen

//Timers
unsigned long cb_timer, cd_timer, enm_move_timer;

Player player1(70,142); 
Player enemy(175,142);


char bPressed = 0;
int selected = 1;

// FLAGS PARA LÓGICA
// Logic flags
  //If character need to be moved
bool move_flag = 0;
bool move_flag_enm = 0;
  // Flags for multiplayer connection
bool mp_flag = 0;
bool flag_rqst = 0;
bool flag_acpt = 0;
bool flag_refuse = 0;
  // True if an attack is happening
bool atkOn = false;
bool atkOn_enm = false;

// Atk coordinates
int atkX, atkY, atkX_enm, atkY_enm;

int x;
unsigned long atkMillis;
unsigned long atkMillis_e;
int32_t frame = 0;

// For ESP-Now connection
pvp_pairing recv_message;
pvp_pairing send_message;
pvp_battle send_battle;
pvp_battle recv_battle;

// const double th[] = {-3.0410e-01, 4.7736e-01,
//   -5.9493e-02, -2.9056e-01,
//   -5.4744e-02,  4.3099e+00,
//   -3.0281e+00,  3.1324e+00,
//    4.2319e+00, -1.0801e+00,
//    7.7565e-02, -1.6591e-01,
//    7.6882e-01,  2.4546e+00,
//    2.3832e+00, -1.2142e+00,
//   -6.1278e-01, -2.9312e-01,
//   -3.3524e+00,  3.0519e+00,
//    2.1551e+01,  4.4169e+00,
//   -1.1543e+01, -5.2365e+00,
//   -6.0551e+00, -6.5194e-01,
//   -2.0221e+00,  4.8653e+00,
//   -1.8788e+01, -2.7750e+00,
//   -7.8082e+00, -8.3105e-02,
//    4.4213e+00,  1.5983e-01,
//    2.3940e-01, -1.9570e-01,
//    1.3634e+00, -8.3124e+00,
//    9.3144e-01,  4.9333e+01,
//   -3.3784e+00, -3.5528e-01,
//   -6.1823e-01,  4.6177e-01,
//   -1.0592e+00, -1.2834e+01,
//    3.6623e+00,  1.2897e+01,
//   -1.2019e+00, -2.5974e-01,
//   -2.8650e+00,  7.2204e-02,
//    1.2487e-01,  7.7739e-01,
//    8.1421e-03, -2.5218e+00,
//   -9.6413e-01, -3.1803e-01,
//   -1.6394e+00,  7.3128e-01,
//   -2.3394e+00,  4.4139e+00,
//   -7.0910e+00, -1.9732e+00,
//    2.8623e+00, -2.5572e-01,
//    8.0096e-01, -5.7822e-01,
//   -1.4965e+00, -2.2784e+00,
//   -3.2676e+00,  2.0104e-01,
//    3.1002e+00, -1.7277e-01,
//    1.5510e+00, -6.8569e-01,
//   -1.0059e+01, -2.4300e+01,
//    2.8653e+01,  1.9673e+01,
//    1.8766e+00};

bool recv = false;


void enemyDraw(int posit){
  // Erases character from old position
  spr.pushImage(-enemy.getPositionPlayer().x,-enemy.getPositionPlayer().y,320,240,background_arena);
  spr.pushSprite(enemy.getPositionPlayer().x,enemy.getPositionPlayer().y);
  
  // Draws character in new position
  switch (posit)
    {
    case 1:
            spr.fillSprite(TFT_GREEN);
            spr.fillCircle(10,10,7,TFT_DARKGREEN);
            spr.pushSprite(175,142,TFT_GREEN);
            enemy.setPositionPlayer(175,142);
      break;
    case 2:
            spr.fillSprite(TFT_GREEN);
            spr.fillCircle(10,10,7,TFT_DARKGREEN);
            spr.pushSprite(229,142,TFT_GREEN);
            enemy.setPositionPlayer(229,142);
      break;
    case 3:
            spr.fillSprite(TFT_GREEN);
            spr.fillCircle(10,10,7,TFT_DARKGREEN);
            spr.pushSprite(282,142,TFT_GREEN);
            enemy.setPositionPlayer(282,142);
      break;
    case 4:
            spr.fillSprite(TFT_GREEN);
            spr.fillCircle(10,10,7,TFT_DARKGREEN);
            spr.pushSprite(175,168,TFT_GREEN);
            enemy.setPositionPlayer(175,168);
      break;
    case 5:
            spr.fillSprite(TFT_GREEN);
            spr.fillCircle(10,10,7,TFT_DARKGREEN);
            spr.pushSprite(229,168,TFT_GREEN);
            enemy.setPositionPlayer(229,168);
      break;
    case 6:
            spr.fillSprite(TFT_GREEN);
            spr.fillCircle(10,10,7,TFT_DARKGREEN);
            spr.pushSprite(282,168,TFT_GREEN);
            enemy.setPositionPlayer(282,168);
      break;
    case 7:
            spr.fillSprite(TFT_GREEN);
            spr.fillCircle(10,10,7,TFT_DARKGREEN);
            spr.pushSprite(175,195,TFT_GREEN);
            enemy.setPositionPlayer(175,195);
      break;
    case 8:
            spr.fillSprite(TFT_GREEN);
            spr.fillCircle(10,10,7,TFT_DARKGREEN);
            spr.pushSprite(229,195,TFT_GREEN);
            enemy.setPositionPlayer(229,195);
      break;
    case 9:
            spr.fillSprite(TFT_GREEN);
            spr.fillCircle(10,10,7,TFT_DARKGREEN);
            spr.pushSprite(282,195,TFT_GREEN);
            enemy.setPositionPlayer(282,195);
      break;
    }
}


int enm_posit = 1;
void enemyMove(int posit){
  // bool move_flag_enm = 0;
  if (mp_flag == 0){
    if(millis() - enm_move_timer > 1000){
      int helper;
      enm_move_timer = millis();
      srand(enm_move_timer);
      helper = rand() % 5 + 1;
      Serial.print("Valor :");
      Serial.println(helper);
      switch (helper)
      {
      case 1:
        if (posit != 3 && posit != 6 && posit != 9){
          enm_posit = posit + 1;
        }
        break;
      case 2:
        if (posit != 1 && posit != 4 && posit != 7){
          enm_posit = posit - 1;
        }
        break;
      case 3:
        if (posit < 7){
          enm_posit = posit + 3;
        }
        break;
      case 4:
        if (posit > 3){
          enm_posit = posit - 3;
        }
        break;
      case 5:
        // x = -20;
        if(atkOn_enm == false){
          atkMillis_e = millis();
          atkX_enm = enemy.getPositionPlayer().x-40;
          atkY_enm = enemy.getPositionPlayer().y;
          atkOn_enm = true;
          enm_posit = posit;
        }
        break;
      default:
        break;
      }
    Serial.print("Posição atual :");
    Serial.println(enm_posit);
    move_flag_enm = 1;
    }
  }
}

// Moves atk through the screen
void atkMoveSpr(int atkX_f, int atkY_f){
  if (atkOn == true && (millis()-atkMillis)>30){
    atkMillis = millis();
    // sprAtk.pushImage(-player1.getPositionPlayer().x-x,-player1.getPositionPlayer().y,320,240,background_arena);
    // sprAtk.pushSprite(player1.getPositionPlayer().x+x,player1.getPositionPlayer().y,TFT_GREEN);
    bckgReset.pushImage(-atkX_f,-atkY_f,320,240,background_arena);

    sprAtk.pushImage(0,-frame*20,30,80,atkIMG);
    sprAtk.pushToSprite(&bckgReset,10,0,0xE007);
    // sprAtk.pushSprite(player1.getPositionPlayer().x+x,player1.getPositionPlayer().y,TFT_GREEN);
    bckgReset.pushSprite(atkX_f,atkY_f);

    bool cond_1 = ((atkX_f+20)- enemy.getPositionPlayer().x) <10 && ((atkX_f+20) - enemy.getPositionPlayer().x) > -10;
    bool cond_2 = (atkY_f - enemy.getPositionPlayer().y) <5 && (atkY_f - enemy.getPositionPlayer().y) > -5;

    if (cond_1 && cond_2){
      enemy.hit_points -= 10;
      if (send_battle.player_num == 1 && mp_flag == 1){
        send_battle.hitpoints = enemy.hit_points;
        // esp_now_send(0,(uint8_t *) &send_battle,sizeof(send_battle));
      }
      Serial.println(enemy.hit_points);
      atkOn = false;
      bckgReset.pushImage(-atkX_f,-atkY_f,320,240,background_arena);
      bckgReset.pushSprite(atkX_f,atkY_f);
      spr.fillSprite(TFT_GREEN);
      spr.fillCircle(10,10,7,TFT_DARKGREEN);
      spr.pushSprite(enemy.getPositionPlayer().x,enemy.getPositionPlayer().y,TFT_GREEN);
      hp_spr.pushImage(-280,0,320,240,background_arena);
      hp_spr.drawNumber(enemy.hit_points,0,0);
      hp_spr.pushSprite(280,0);
    }

    atkX += 10;
    frame=frame+1;
    if (frame > 3){
      frame = 0;
    }
    if (atkX>330){
      atkOn = false;
    }
  }
}

void atkMoveSpr_enm(int atkX_f, int atkY_f){
  if (atkOn_enm == true && (millis()-atkMillis_e)>30){
    atkMillis_e = millis();
    // sprAtk.pushImage(-player1.getPositionPlayer().x-x,-player1.getPositionPlayer().y,320,240,background_arena);
    // sprAtk.pushSprite(player1.getPositionPlayer().x+x,player1.getPositionPlayer().y,TFT_GREEN);
    bckgReset.pushImage(-atkX_f,-atkY_f,320,240,background_arena);

    sprAtk.pushImage(0,-frame*20,30,80,atkIMG_mirror);
    sprAtk.pushToSprite(&bckgReset,0,0,0xE007);
    // sprAtk.pushSprite(player1.getPositionPlayer().x+x,player1.getPositionPlayer().y,TFT_GREEN);
    bckgReset.pushSprite(atkX_f,atkY_f);
    
    bool cond_1 = (atkX_f - player1.getPositionPlayer().x) <10 && (atkX_f - player1.getPositionPlayer().x) > -10;
    bool cond_2 = (atkY_f - player1.getPositionPlayer().y) <5 && (atkY_f - player1.getPositionPlayer().y) > -5;
    if (cond_1 && cond_2){
      player1.hit_points -= 10;
      if (send_battle.player_num == 0 && mp_flag == 1){
        send_battle.hitpoints = player1.hit_points;
        // esp_now_send(0,(uint8_t *) &send_battle,sizeof(send_battle));
      }
      Serial.println(player1.hit_points);
      atkOn_enm = false;
      bckgReset.pushImage(-atkX_f,-atkY_f,320,240,background_arena);
      bckgReset.pushSprite(atkX_f,atkY_f);
      spr.fillSprite(TFT_GREEN);
      spr.fillCircle(10,10,7,TFT_RED);
      spr.pushSprite(player1.getPositionPlayer().x,player1.getPositionPlayer().y,TFT_GREEN);
      hp_spr.pushImage(-10,0,320,240,background_arena);
      hp_spr.drawNumber(player1.hit_points,0,0);
      hp_spr.pushSprite(10,0,TFT_GREEN);
    }
    atkX_enm-=10;
    frame=frame+1;
    if (frame > 3){
      frame = 0;
    }
    if (atkX_enm<-50){
      atkOn_enm = false;
    }
    
  }
}


void playerDraw(int posit){  
  // Erases character from old position
  spr.pushImage(-player1.getPositionPlayer().x,-player1.getPositionPlayer().y,320,240,background_arena);
  spr.pushSprite(player1.getPositionPlayer().x,player1.getPositionPlayer().y);
  
  // Draws character in new position
  switch (posit)
    {
    case 1:
            spr.fillSprite(TFT_GREEN);
            spr.fillCircle(10,10,7,TFT_RED);
            spr.pushSprite(COLUMN1,LINE1,TFT_GREEN);
            player1.setPositionPlayer(COLUMN1,LINE1);
      break;
    case 2:
            spr.fillSprite(TFT_GREEN);
            spr.fillCircle(10,10,7,TFT_RED);
            spr.pushSprite(COLUMN2,LINE1,TFT_GREEN);
            player1.setPositionPlayer(COLUMN2,LINE1);
      break;
    case 3:
            spr.fillSprite(TFT_GREEN);
            spr.fillCircle(10,10,7,TFT_RED);
            spr.pushSprite(COLUMN3,LINE1,TFT_GREEN);
            player1.setPositionPlayer(COLUMN3,LINE1);
      break;
    case 4:
            spr.fillSprite(TFT_GREEN);
            spr.fillCircle(10,10,7,TFT_RED);
            spr.pushSprite(COLUMN1,LINE2,TFT_GREEN);
            player1.setPositionPlayer(COLUMN1,LINE2);
      break;
    case 5:
            spr.fillSprite(TFT_GREEN);
            spr.fillCircle(10,10,7,TFT_RED);
            spr.pushSprite(COLUMN2,LINE2,TFT_GREEN);
            player1.setPositionPlayer(COLUMN2,LINE2);
      break;
    case 6:
            spr.fillSprite(TFT_GREEN);
            spr.fillCircle(10,10,7,TFT_RED);
            spr.pushSprite(COLUMN3,LINE2,TFT_GREEN);
            player1.setPositionPlayer(COLUMN3,LINE2);
      break;
    case 7:
            spr.fillSprite(TFT_GREEN);
            spr.fillCircle(10,10,7,TFT_RED);
            spr.pushSprite(COLUMN1,LINE3,TFT_GREEN);
            player1.setPositionPlayer(COLUMN1,LINE3);
      break;
    case 8:
            spr.fillSprite(TFT_GREEN);
            spr.fillCircle(10,10,7,TFT_RED);
            spr.pushSprite(COLUMN2,LINE3,TFT_GREEN);
            player1.setPositionPlayer(COLUMN2,LINE3);
      break;
    case 9:
            spr.fillSprite(TFT_GREEN);
            spr.fillCircle(10,10,7,TFT_RED);
            spr.pushSprite(COLUMN3,LINE3,TFT_GREEN);
            player1.setPositionPlayer(COLUMN3,LINE3);
      break;
  }
}

int plr_posit = 2;
void moveCommand(char command){
  int posit = plr_posit;  
  bool flag = 1;   //Button pressed flag
    switch (command){
      case 1:
        if (posit != 1 && posit != 4 && posit != 7){
          plr_posit = posit - 1;
          move_flag = 1;
        }
        break;
      case 2:
        if (posit != 3 && posit != 6 && posit != 9){
          plr_posit = posit + 1;
          move_flag = 1;
        }
        break;
      case 3:
        if (posit > 3){
          plr_posit = posit - 3;
          move_flag = 1;
        }
        break;
      case 4:
        if (posit < 7){
          plr_posit = posit + 3;
          move_flag = 1;
        }
        break;
      case 5:
        // x = -20;
        if (send_battle.player_num == 0){
          if(atkOn == false){
            atkMillis = millis();
            atkX = player1.getPositionPlayer().x+20;
            atkY = player1.getPositionPlayer().y;
            atkOn = true;
            frame = 0;
          }
        }else if(send_battle.player_num == 1){
          if(atkOn_enm == false){
            atkMillis_e = millis();
            atkX_enm = enemy.getPositionPlayer().x-40;
            atkY_enm = enemy.getPositionPlayer().y;
            atkOn_enm = true;
            enm_posit = posit;
          }
        }
        break;
      default:
       flag = 0;
        break;
    }
    
    //If button pressed while in multiplayer, it checks what player is before realizing its command
    if (flag == 1 && mp_flag == 1 && send_battle.player_num == 0){  
      send_battle.atkOn = atkOn;
      send_battle.pos = plr_posit;
      send_battle.atkX = atkX;
      send_battle.atkY = atkY;
      send_battle.move_ok = move_flag;
      esp_now_send(0,(uint8_t *) &send_battle,sizeof(send_battle));
    }else if(flag == 1 && mp_flag == 1 && send_battle.player_num == 1){
      send_battle.atkOn = atkOn_enm;
      send_battle.pos = plr_posit;
      send_battle.atkX = atkX_enm;
      send_battle.atkY = atkY_enm;
      send_battle.move_ok = move_flag;
      esp_now_send(0,(uint8_t *) &send_battle,sizeof(send_battle));
    }
    bPressed = 0;
}


esp_now_peer_info_t peerInfo;
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};


void setup() {
  Serial.begin(115200);
  // Wire.begin();
  delay(100);
  // IMU.config_MPU6050();
  pinMode(leftButton,INPUT_PULLDOWN);
  pinMode(upButton,INPUT_PULLDOWN);
  pinMode(rightButton,INPUT_PULLDOWN);
  pinMode(downButton,INPUT_PULLDOWN);
  pinMode(atkButton,INPUT_PULLDOWN);
  pinMode(bckButton,INPUT_PULLDOWN);

  // ---- CONFIG ESPNow ------
  WiFi.mode(WIFI_STA);


  Serial.println(esp_get_free_heap_size());
  // ----- CONFIG SD -------
  if (!SD.begin(21)) {
    Serial.println("Falha ao iniciar o cartão SD");1
    return;
  }

  File file = SD.open("/atkIMG.data");
  if (!file) {
    Serial.println("Falha ao abrir o arquivo de imagem");
    return;
  }

  atkIMG = (uint16_t*)malloc(30*80*sizeof(uint16_t));
  if (!atkIMG) {
    Serial.println("Falha ao alocar memória para o buffer de imagem");
    return;
  } // Allocating ATK image 

  atkIMG_mirror = (uint16_t*)malloc(30*80*sizeof(uint16_t));
  if (!atkIMG_mirror) {
    Serial.println("Falha ao alocar memória para o buffer de imagem");
    return;
  } // Allocating ATK image mirrored (for the enemy)

  for (int y = 0; y < 2400; y++) {
      uint32_t pixelColor = file.read() << 24 | file.read() << 16 | file.read() << 8 | file.read(); // Leitura de um pixel da imagem
      
      // Converte para RGB565
      uint16_t tftColor = tft.color565((pixelColor >> 24) & 0xFF, (pixelColor >> 16) & 0xFF, (pixelColor>>8) & 0xFF);

      // Armazena no buffer de imagem
      atkIMG[y] = tftColor;

      int pix_pos = 30*(y/30) - (y % 30) + 29;
      atkIMG_mirror[pix_pos] = tftColor;
  }

  Serial.println(esp_get_free_heap_size());

  // ----- CONFIG TFT ------
  tft.init();
  tft.setRotation(1);
  tft.setSwapBytes(true);
  tft.setTextFont(2);
  mainScreen(tft);
  mainSelector(tft,selected);
  send_message.name = "Lobo";
} 


void loop() {

  // Lógica para movimentação dos personagens
  bPressed = readPress();
  delay(2);
  switch(progState){
    case 0:   // Main screen
      mainMenu(tft,bPressed);
      // medidas = IMU.getSensorData();
      // Serial.println((medidas.AccelX/4096.0*9.80665));
    break;
    case 1:  // Battle Screen
      if (send_battle.player_num == 0){
        moveCommand(bPressed);    
        if (move_flag == 1){
          playerDraw(plr_posit);
          move_flag = 0;
        }
        // enemyMove(MacSend.position);
        if (mp_flag == 0){
          enemyMove(enm_posit);
        }
        if (move_flag_enm == 1){
          enemyDraw(enm_posit);
          move_flag_enm = 0;
        }
        atkMoveSpr(atkX,atkY);
        atkMoveSpr_enm(atkX_enm,atkY_enm);
      }else{
        moveCommand(bPressed);    
        if (move_flag == 1){
          enemyDraw(plr_posit);
          move_flag = 0;
        }
        if (move_flag_enm == 1){
          playerDraw(enm_posit);
          move_flag_enm = 0;
        }
        atkMoveSpr(atkX,atkY);
        atkMoveSpr_enm(atkX_enm,atkY_enm);
      }
      if (enemy.hit_points == 0 || player1.hit_points == 0){
        tft.fillRect(64,48,192,144,DK_BLUE);
        
        if (enemy.hit_points == 0){
          tft.drawString("Jogador 1 ganhou",84,68);
        }else if(player1.hit_points == 0){
          tft.drawString("Jogador 2 ganhou",84,68);
        }
        progState = 2;
        enemy.hit_points = 100;
        player1.hit_points = 100;

        if (mp_flag == 1){
          esp_wifi_set_channel(0,wifi_second_chan_t{WIFI_SECOND_CHAN_NONE});
          esp_now_deinit();
          // memset(names,(char){' '},sizeof(String)*5);
          memset(mac_pos[0],0,sizeof(uint8_t)*6);
          memset(mac_pos[1],0,sizeof(uint8_t)*6);
          memset(mac_pos[2],0,sizeof(uint8_t)*6);
          memset(mac_pos[3],0,sizeof(uint8_t)*6);
          memset(mac_pos[4],0,sizeof(uint8_t)*6);
          plr_counter = 0;
        }
        
      }
    break;
    case 2:  // Create/Find PVP match screen
      if (bPressed == 6){
        progState = 0;
        selected = 1;
        mainScreen(tft);
        mainSelector(tft,selected);
        bPressed = 0;
      }
    break;
    case 3:  // PVP ROOM
      //Carregar as funções de callback antes de chegar aqui
      menuPVP2(tft,bPressed);
      if (millis() - cb_timer > 15000){
        Serial.println("Enviei msg");
        cb_timer = millis();
        esp_now_send(broadcastAddress,(uint8_t *) &send_message,sizeof(send_message));
      }
    break; 
    case 4: // Searching players nearby
      menuPVP3(tft,bPressed);
      if (millis() - cb_timer > 5000){
        Serial.println("Enviei msg");
        cb_timer = millis();
        esp_now_send(broadcastAddress,(uint8_t *) &send_message,sizeof(send_message));
      }
      if (flag_rqst == 1){
         matchPrompt(tft);
            unsigned long resp_timer = millis();
            bool resp = 0;
            while (resp == 0 && millis()-resp_timer < 5000){
                delay(1); //Only here to feed ESP watchdog
                int button = readPress();
                if (button == 5){   // Aceita a partida 
                    esp_now_peer_info_t peerInfo;                               // Add player who invites to peer list
                    memcpy(peerInfo.peer_addr, recv_message.macAddress, 6);
                    peerInfo.channel = 0;  
                    peerInfo.encrypt = false;
                    if (esp_now_is_peer_exist(peerInfo.peer_addr) == false){
                        if (esp_now_add_peer(&peerInfo) != ESP_OK){
                            Serial.println("Failed to add peer");
                        return;
                        }
                    }

                    send_message.acpt_match = 1;
                    esp_now_send(temp_mac,(uint8_t *) &send_message,sizeof(send_message));  // Sends accept message
                    resp = 1;
                    send_battle.player_num = 1;
                    mp_flag = 1;
                    peerInfo.channel = 2;  // Change espnow channel to battle channel
                    esp_now_mod_peer(&peerInfo);
                    esp_wifi_set_channel(2,wifi_second_chan_t{WIFI_SECOND_CHAN_NONE});
                    esp_now_unregister_recv_cb();
                    esp_now_register_recv_cb(battleCallback);

                    battleSetup();
                    // !!!!!!!!!!!!!!!!!!!!!!!
                    // Organizar as flags necessárias para a batalha aqui
                    // !!!!!!!!!!!!!!!!!!!!!!!
                    progState = 1;
                
                }else if(button == 6){  // Refuse match
                    send_message.refuse_match = 1;
                    esp_now_send(recv_message.macAddress,(uint8_t *) &send_message,sizeof(send_message));
                    resp = 1;
                    pvpScreen3(tft);
                }
            }
            flag_rqst = 0;
      }
    break;    
  }  
  // Serial.println(ESP.getMaxAllocHeap());
}
