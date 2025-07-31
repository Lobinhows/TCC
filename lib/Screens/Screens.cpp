#include "Screens.h"

void mainScreen(TFT_eSPI tft){
  tft.fillScreen(0xD71F);
  // tft.fillRect(180,52,30,40,0xD77F);  //Em conversão direta, era 0xD71F
  tft.setTextColor(0xF79D,0x08EB);
  tft.setCursor(42,86);
  tft.fillSmoothRoundRect(32,76,131,29,6,0x08EB,0xD71F);  // Primeiro Bloco
  tft.print("Batalha");

  tft.fillSmoothRoundRect(32,113,131,29,6,0x3275,0xD71F); // Segundo Bloco
  tft.setCursor(42,123);
  tft.setTextColor(0xF79D,0x3275);
  tft.print("Multiplayer");
  
  tft.fillSmoothRoundRect(32,150,131,29,6,0x74BA,0xD71F); // Terceiro Bloco
  tft.setCursor(42,160);
  tft.setTextColor(0xF79D,0x74BA);
  tft.print("Placeholder");
}

void pvpScreen1(TFT_eSPI tft){
  tft.fillScreen(BG_COLOR);
  tft.setTextColor(0xF79D,DK_BLUE);
  tft.fillSmoothRoundRect(round(DWIDTH*.15),round(DHEIGHT*.3),150,40,8,DK_BLUE,BG_COLOR);
  tft.drawString("Criar",DWIDTH*.2,DHEIGHT*.35);

  tft.setTextColor(0xF79D,MD_BLUE);
  tft.fillSmoothRoundRect(round(DWIDTH*.15),round(DHEIGHT*.6),150,40,8,MD_BLUE,BG_COLOR);
  tft.drawString("Procurar",DWIDTH*.20,DHEIGHT*.65);
}

void pvpScreen2(TFT_eSPI tft){
  tft.fillScreen(BG_COLOR);
  tft.fillSmoothRoundRect(DWIDTH*.15,DHEIGHT*.30,120,40,8,DK_BLUE,BG_COLOR);
  tft.fillSmoothRoundRect(DWIDTH*.15,DHEIGHT*.55,120,40,8,MD_BLUE,BG_COLOR);
  // if (send_message.player_num == 0){
  //   tft.setTextColor(TXT_COLOR,DK_BLUE);
  //   tft.drawString(send_message.name,DWIDTH*.2,DHEIGHT*.30+10);
  //   tft.setTextColor(TXT_COLOR,MD_BLUE);
  //   tft.drawString(recv_message.name,DWIDTH*.2,DHEIGHT*.55+10);
  // }else {
  //   tft.setTextColor(TXT_COLOR,DK_BLUE);
  //   tft.drawString(recv_message.name,DWIDTH*.2,DHEIGHT*.30+10);
  //   tft.setTextColor(TXT_COLOR,MD_BLUE);
  //   tft.drawString(send_message.name,DWIDTH*.2,DHEIGHT*.55+10);
  // }
}

void pvpScreen3(TFT_eSPI tft){
  tft.fillScreen(BG_COLOR);
  tft.fillSmoothRoundRect(DWIDTH*.15,DHEIGHT*.15,120,30,7,MD_BLUE,BG_COLOR);
  tft.fillSmoothRoundRect(DWIDTH*.15,DHEIGHT*.3,120,30,7,MD_BLUE,BG_COLOR);
  tft.fillSmoothRoundRect(DWIDTH*.15,DHEIGHT*.45,120,30,7,MD_BLUE,BG_COLOR);
  tft.fillSmoothRoundRect(DWIDTH*.15,DHEIGHT*.6,120,30,7,MD_BLUE,BG_COLOR);
  tft.fillSmoothRoundRect(DWIDTH*.15,DHEIGHT*.75,120,30,7,MD_BLUE,BG_COLOR);
  searchNames(tft);
}

void searchNames(TFT_eSPI tft){
  tft.setTextColor(TXT_COLOR,MD_BLUE);
  tft.drawString(names[0],DWIDTH*.15+10,DHEIGHT*.15+5);
  tft.drawString(names[1],DWIDTH*.15+10,DHEIGHT*.3+5);
  tft.drawString(names[2],DWIDTH*.15+10,DHEIGHT*.45+5);
  tft.drawString(names[3],DWIDTH*.15+10,DHEIGHT*.6+5);
  tft.drawString(names[4],DWIDTH*.15+10,DHEIGHT*.75+5); 
}

void battleSetup(){
  tft.pushImage(0,0,320,240,background_arena);
  plr_posit = 2;
  enm_posit = 2;
  spr.createSprite(20,20);
  spr.setSwapBytes(true);
  spr.fillSprite(TFT_GREEN);
  spr.fillCircle(10,10,7,TFT_RED);
  spr.pushSprite(70,142);

  sprAtk.createSprite(30,20);
  // sprAtk.setSwapBytes(true);

  bckgReset.createSprite(40,20);
  bckgReset.setSwapBytes(true);

  spr.fillSprite(TFT_GREEN);
  spr.fillCircle(10,10,7,TFT_DARKCYAN);
  spr.pushSprite(229,142);

  hp_spr.createSprite(30,20);
  hp_spr.setSwapBytes(true);

  hp_spr.fillSprite(TFT_GREEN);
  hp_spr.drawNumber(player1.hit_points,0,0);
  hp_spr.pushSprite(10,0,TFT_GREEN);
  
  hp_spr.fillSprite(TFT_GREEN);
  hp_spr.drawNumber(enemy.hit_points,0,0);
  hp_spr.pushSprite(280,0,TFT_GREEN);

}

void mainSelector(TFT_eSPI tft, int selected){
  switch(selected){
    case 1:
      tft.fillSmoothCircle(138,90,7,0xCFEE,0x08EB);
      tft.fillSmoothCircle(138,126,7,0x3275,0x3275);
      tft.fillSmoothCircle(138,162,7,0x74BA,0x74BA);
    break;
    case 2:
      tft.fillSmoothCircle(138,90,7,0x08EB,0x08EB);
      tft.fillSmoothCircle(138,126,7,0xCFEE,0x3275);
      tft.fillSmoothCircle(138,162,7,0x74BA,0x74BA);
    break;
    case 3:
      tft.fillSmoothCircle(138,90,7,0x08EB,0x08EB);
      tft.fillSmoothCircle(138,126,7,0x3275,0x3275);
      tft.fillSmoothCircle(138,162,7,0xCFEE,0x74BA);
    break;
  }
}

void pvp1Selector(TFT_eSPI tft, int selected){
  switch (selected){
    case 1:
      tft.fillSmoothCircle(DWIDTH*.5,DHEIGHT*.38,8,SEL_COLOR,DK_BLUE);
      tft.fillSmoothCircle(DWIDTH*.5,DHEIGHT*.68,8,MD_BLUE,MD_BLUE);
      break;
    case 2:
      tft.fillSmoothCircle(DWIDTH*.5,DHEIGHT*.38,8,DK_BLUE,DK_BLUE);
      tft.fillSmoothCircle(DWIDTH*.5,DHEIGHT*.68,8,SEL_COLOR,MD_BLUE);
      break;
    default:
      break;
  }
}

void pvp3Selector(TFT_eSPI tft, int selected){
  switch (selected){
    case 1:
      tft.fillSmoothCircle(DWIDTH*.48,DHEIGHT*.2,8,SEL_COLOR,MD_BLUE);
      tft.fillSmoothCircle(DWIDTH*.48,DHEIGHT*.8,8,MD_BLUE,MD_BLUE);
      tft.fillSmoothCircle(DWIDTH*.48,DHEIGHT*.35,8,MD_BLUE,MD_BLUE);
    break;
    case 2:
      tft.fillSmoothCircle(DWIDTH*.48,DHEIGHT*.35,8,SEL_COLOR,MD_BLUE);
      tft.fillSmoothCircle(DWIDTH*.48,DHEIGHT*.2,8,MD_BLUE,MD_BLUE);
      tft.fillSmoothCircle(DWIDTH*.48,DHEIGHT*.5,8,MD_BLUE,MD_BLUE);
    break;
    case 3:
      tft.fillSmoothCircle(DWIDTH*.48,DHEIGHT*.5,8,SEL_COLOR,MD_BLUE);
      tft.fillSmoothCircle(DWIDTH*.48,DHEIGHT*.35,8,MD_BLUE,MD_BLUE);
      tft.fillSmoothCircle(DWIDTH*.48,DHEIGHT*.65,8,MD_BLUE,MD_BLUE);
    break;
    case 4:
      tft.fillSmoothCircle(DWIDTH*.48,DHEIGHT*.65,8,SEL_COLOR,MD_BLUE);
      tft.fillSmoothCircle(DWIDTH*.48,DHEIGHT*.5,8,MD_BLUE,MD_BLUE);
      tft.fillSmoothCircle(DWIDTH*.48,DHEIGHT*.8,8,MD_BLUE,MD_BLUE);
    break;
    case 5:
      tft.fillSmoothCircle(DWIDTH*.48,DHEIGHT*.8,8,SEL_COLOR,MD_BLUE);
      tft.fillSmoothCircle(DWIDTH*.48,DHEIGHT*.65,8,MD_BLUE,MD_BLUE);
      tft.fillSmoothCircle(DWIDTH*.48,DHEIGHT*.2,8,MD_BLUE,MD_BLUE);
    break;
  }
}

void matchPrompt(TFT_eSPI tft){
  tft.fillRect(64,48,192,144,MD_BLUE);
  tft.setTextColor(TXT_COLOR,MD_BLUE);
  tft.drawString(recv_message.name + "Deseja jogar com você",74,58);
}