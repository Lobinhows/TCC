#ifndef MY_TYPES_H
#define MY_TYPES_H

// Estrutura para callback de pareamento
typedef struct pvp_pairing{
  byte safecode = 121;
  String name;
  uint8_t macAddress[6];
  bool rqst_match = 0;
  bool acpt_match = 0;
  bool refuse_match = 0;
} pvp_pairing;

// Estrutura para callback durante batalha
typedef struct pvp_battle{
    byte safecode = 122;
    bool player_num;  //Se 0 - Player 1 ; Se 1 - Player 2
    char hitpoints = 100;
    int pos;
    int atkX;
    int atkY;
    bool atkOn;
    bool move_ok;
} pvp_battle;

#endif