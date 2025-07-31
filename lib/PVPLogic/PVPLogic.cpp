#include "PVPLogic.h"

void configEspNow(const uint8_t * mac){
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    esp_now_register_send_cb(OnDataSent);

    // memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    memcpy(peerInfo.peer_addr, mac, 6);

    peerInfo.channel = 0;  
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK){
        Serial.println("Failed to add peer");
        return;
    }

    esp_read_mac(send_message.macAddress, ESP_MAC_WIFI_STA);
}

void matchmakingCallback(const uint8_t * mac, const uint8_t *incomingData, int len){
    Serial.print("Bytes = ");
    Serial.println(len);
    memcpy(&recv_message, incomingData, sizeof(recv_message));
    if (recv_message.safecode == 121){
        if (recv_message.rqst_match == 0 && recv_message.acpt_match == 0 && recv_message.refuse_match == 0){
            if (plr_counter < 5){
                bool flag = false;
                for (int i=0;i<plr_counter;i++){
                    if (memcmp(mac_pos[i],recv_message.macAddress,sizeof(uint8_t)*6) == 0){
                        flag = true;   
                    }
                }
                if (flag == false){
                    memcpy(mac_pos[plr_counter], recv_message.macAddress, sizeof(uint8_t)*6);

                    names[plr_counter] = recv_message.name;
                    pvpScreen3(tft);
                    pvp3Selector(tft,selected);
                    plr_counter += 1;
                }
            }
        }   /// ATÉ AQUI EU SEI QUE TÁ CERTO 

        if (recv_message.rqst_match == 1){
            memcpy(temp_mac,recv_message.macAddress,sizeof(uint8_t)*6);
            flag_rqst = 1;
        }

        if (recv_message.acpt_match == 1){  //Código para iniciar a batalha
            flag_acpt = 1;
            mp_flag = 1;
            esp_now_peer_info_t peerInfo;
            esp_now_get_peer(recv_message.macAddress,&peerInfo);
            peerInfo.channel = 2;
            esp_now_mod_peer(&peerInfo);
            esp_wifi_set_channel(2,wifi_second_chan_t{WIFI_SECOND_CHAN_NONE});
            esp_now_unregister_recv_cb();
            esp_now_register_recv_cb(battleCallback);
            battleSetup();
            progState = 1;
        }
        if (recv_message.refuse_match == 1){
            flag_refuse = 1;
        }
    }
}

void battleCallback(const uint8_t * mac, const uint8_t *incomingData, int len){
    memcpy(&recv_battle, incomingData, sizeof(recv_battle));
    if (recv_battle.safecode == 122){
        Serial.println("Recebi msg batalha");
        if (recv_battle.player_num == 1){
            atkX_enm = recv_battle.atkX;
            atkY_enm = recv_battle.atkY;
            enemy.hit_points = recv_battle.hitpoints;
            enm_posit = recv_battle.pos;            
            atkOn_enm = recv_battle.atkOn;
            move_flag_enm = recv_battle.move_ok;
        }else{
            atkX = recv_battle.atkX;
            atkY = recv_battle.atkY;
            player1.hit_points = recv_battle.hitpoints;
            enm_posit = recv_battle.pos;            
            atkOn = recv_battle.atkOn;
            move_flag_enm = recv_battle.move_ok;
        }

    }    
}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  Serial.print("Packet to: ");
  // Copies the sender mac address to a string
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print(" send status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}