#include "Navigation.h"

bool lpress, rpress, upress, dpress, atkpress, bckpress = false;

char readPress(){
  if(digitalRead(leftButton)==HIGH){
    lpress = true;
  }
  if (digitalRead(leftButton)==LOW && lpress == true){
    lpress = false;
    return 1;
  }

  if(digitalRead(rightButton)==HIGH){
    rpress = true;
  }
  if (digitalRead(rightButton)==LOW && rpress == true){
    rpress = false;
    return 2;
  }

  if(digitalRead(upButton)==HIGH){
    upress = true;
  }
  if (digitalRead(upButton)==LOW && upress == true){
    upress = false;
    return 3;
  }



  if(digitalRead(downButton)==HIGH){
    dpress = true;
  } 
  if (digitalRead(downButton)==LOW && dpress == true){
    dpress = false;
    return 4;
  }


  if(digitalRead(atkButton)==HIGH){
    atkpress = true;
  }
  if (digitalRead(atkButton)==LOW && atkpress == true){
    atkpress = false;
    return 5;
  }
  if(digitalRead(bckButton)==HIGH){
    bckpress = true;
  }
  if(digitalRead(bckButton)==LOW && bckpress == true){
    bckpress = false;
    return 6;
  }else{
    return 0;
  }
}

void menuCommands(TFT_eSPI tft, char press){
  switch (progState){
    case 0:
      mainMenu(tft, press);
    break;
    case 1:

    break;
    case 2:
      menuPVP1(tft,press);
    break;
    case 3:
      menuPVP2(tft,press);
    break;

  default:
    break;
  }
}

void mainMenu(TFT_eSPI tft, char press){
  switch (press){
    case 1:
      selected -= 1;
      if (selected < 1){
        selected = 3;
      }
      mainSelector(tft,selected);
      bPressed = 0;
    break;
    case 2:
      selected += 1;
      if (selected > 3){
        selected = 1;
      }
      mainSelector(tft,selected);
      bPressed = 0;
    break;
    case 3:
      selected -= 1;
      if (selected < 1){
        selected = 3;
      }
      mainSelector(tft,selected);
      bPressed = 0;
    break;
    case 4:
      selected += 1;
      if (selected > 3){
        selected = 1;
      }
      mainSelector(tft,selected);
      bPressed = 0;
    break;
    case 5:
     
      if (selected == 1){
         progState = selected;
        mp_flag = 0;
        enm_move_timer = millis();
        battleSetup();
      }
      if (selected == 2){
        // tft.fillScreen(BG_COLOR);
         progState = 4;
        progState = 4;
        pvpScreen3(tft);
        delay(30);
        selected = 1;
        pvp3Selector(tft,1);
        configEspNow(broadcastAddress);
        esp_now_register_recv_cb(matchmakingCallback);
      }
      bPressed = 0;
    break;
    case 6:
      
    break;

    default:
    break;
  }
}
void menuPVP1(TFT_eSPI tft, char press){   // Commandos Criar/procurar sala
  switch(press){
    case 1:
      selected -= 1;
      if (selected < 1){
        selected = 2;
      }
      pvp1Selector(tft,selected);
      bPressed = 0;
    break;
    case 2:
      selected += 1;
      if (selected > 2){
        selected = 1;
      }
      pvp1Selector(tft,selected);
      bPressed = 0;
    break;
    case 3:
      selected -= 1;
      if (selected < 1){
        selected = 2;
      }
      pvp1Selector(tft,selected);
      bPressed = 0;
    break;
    case 4:
      selected += 1;
      if (selected > 2){
        selected = 1;
      }
      pvp1Selector(tft,selected);
      bPressed = 0;
    break;
    case 5: 
      if (selected == 1){
        // battleSetup();
        progState = 3;
        pvpScreen2(tft);   // Mostra a nova tela
        configEspNow(broadcastAddress);
        send_message.name = "Player 1 - Criando";
        // send_message.player_num = 0;
        esp_now_register_recv_cb(matchmakingCallback);
        cb_timer = millis();
      }
      
      if (selected == 2){   
        progState = 4;
        pvpScreen3(tft);
        delay(30);
        selected = 1;
        pvp3Selector(tft,1);
        configEspNow(broadcastAddress);
        esp_now_register_recv_cb(matchmakingCallback);
      }
      bPressed = 0;
    break;
    case 6:
      progState = 0;
      selected = 1;
      mainScreen(tft);
      mainSelector(tft,selected);
      bPressed = 0;
    break;
   }
  }


void menuPVP2(TFT_eSPI tft, char press){   // Sala do PVP
  // switch (press){
  //   case 5:
  //   if (send_message.player_num == 0){
  //     progState = 1;
  //     send_message.rqst_match = 1;
  //     // Criar forma de travar só o MAC do player 2
  //     // enviar msg de início
  //     esp_now_send(broadcastAddress,(uint8_t *) &send_message,sizeof(send_message));
  //     battleSetup();    
  //     bPressed = 0;
  //   }
  //   break;
  //   case 6:
  //     progState = 2;
  //     // tft.fillScreen(BG_COLOR);
  //     // delay(30);
  //     pvpScreen1(tft);
  //     pvp1Selector(tft,1);
  //     bPressed = 0;
  //   break;
    
  //   default:
  //   break;
  // }
}

void menuPVP3(TFT_eSPI tft, char press){
  switch(press){
    case 1:
      selected -= 1;
      if (selected < 1){
        selected = 5;
      }
      pvp3Selector(tft,selected);
      bPressed = 0;
    break;
    case 2:
      selected += 1;
      if (selected > 5){
        selected = 1;
      }
      pvp3Selector(tft,selected);
      bPressed = 0;
    break;
    case 3:
      selected -= 1;
      if (selected < 1){
        selected = 5;
      }
      pvp3Selector(tft,selected);
      bPressed = 0;
    break;
    case 4:
      selected += 1;
      if (selected > 5){
        selected = 1;
      }
      pvp3Selector(tft,selected);
      bPressed = 0;
    break;
    case 5: 
      // progState = 3;
      esp_now_peer_info_t peerInfo;
      Serial.println(selected);
      memcpy(peerInfo.peer_addr, mac_pos[selected-1], sizeof(uint8_t)*6);

      peerInfo.ifidx = WIFI_IF_STA;
      peerInfo.channel = 0;  
      peerInfo.encrypt = false;
      if(esp_now_is_peer_exist(peerInfo.peer_addr) == false){
        if (esp_now_add_peer(&peerInfo) != ESP_OK){
          Serial.println("Failed to add peer");
          // return;
        }
      }
      send_message.name = "Lobo ";
      send_message.rqst_match = 1;
      
      // Serial.println("Erro é o seguinte:");
      if (esp_now_send(mac_rcv1, (uint8_t *) &send_message,sizeof(send_message)) == ESP_OK){
        send_message.rqst_match = 0;
        unsigned long resp_timer = millis();
        bool resp_ok = 0;

        while(resp_ok == 0 && millis()-resp_timer <5000){  // "Travar" enquanto aguarda resposta
          if (flag_acpt == true || flag_refuse == true){
            resp_ok = true ;
          }
        }
      }
      // pvpScreen2(tft);   // Mostra a nova tela
      // esp_now_register_recv_cb(matchmakingCallback);
      // cb_timer = millis();
      bPressed = 0;
    break;
    case 6:
      progState = 0;
      selected = 1;
      esp_now_deinit();
      mainScreen(tft);
      mainSelector(tft,selected);
      bPressed = 0;
    break;
  }
}