
void initRelayBtns(){
  uint16_t x = 10;
  uint16_t y = 295;
  //Relay 1 BTN
  tft.loadFont(latin);
  r1Btn.initButtonUL(x, y, 150, 120, c1, c4, c3, "MACERATE", 1);
  //Relay 2 BTN
  x = x+150+10;
  tft.loadFont(latin);
  r2Btn.initButtonUL(x, y, 150, 120, c1, c4, c3, "SPREAD", 1);
  drawRelayBtns();
  }
void drawRelayBtns(){
  r1Btn.setPressAction(r1_pressAction);
  r1Btn.setReleaseAction(r1_releaseAction);
  r1Btn.drawSmoothButton(false, 5, BACKROUND);
  r2Btn.setPressAction(r2_pressAction);
  r2Btn.setReleaseAction(r2_releaseAction);
  r2Btn.drawSmoothButton(false, 5, BACKROUND);
  }

