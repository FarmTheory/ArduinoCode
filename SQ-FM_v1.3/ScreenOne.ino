void setOne(){
  Serial.println("RATE CHANGE");
  tft.fillScreen(c1);
  screenOneSetup();
  screen = 1;
}

void screenOneSetup(){
    initBackBtn();
}

void screenOneMain(){
  uint16_t t_x = 0, t_y = 0;
  static uint32_t scanTime = millis();
  static uint32_t updateTime = millis();
  static uint32_t drawLinearTime = millis();
  // Scan keys every 50ms at most
   if (tft.getTouch(&t_x, &t_y)) {
     // static uint16_t color;
    //  bool pressed = tft.getTouch(&t_x, &t_y);
      scanTime = millis();
      // / Check if any key coordinate boxes contain the touch coordinates
      uint8_t btnCount = sizeof(screenOneBtn) / sizeof(screenOneBtn[0]);
      for (uint8_t b = 0; b < btnCount; b++) {
          if (screenOneBtn[b]->contains(t_x, t_y)) {
            screenOneBtn[b]->press(true);
            screenOneBtn[b]->pressAction();
          }
          else {
            screenOneBtn[b]->press(false);
            screenOneBtn[b]->releaseAction();
                }
          }
        }
}


void initBackBtn(){
  uint16_t x = 100;
  uint16_t y = 85;
  tft.loadFont(small);
  backBtn.initButtonUL(x, y, 150, 80, c1, c2, c1, "Back", 2);
  backBtn.drawSmoothButton(backBtn.getState(), 3, BACKROUND, "Back");
  tft.unloadFont(); 
  drawBackBtn();}

void drawBackBtn(){
  backBtn.setPressAction(back_pressAction);
  backBtn.setReleaseAction(back_releaseAction);
  backBtn.drawSmoothButton(false, 3, BACKROUND);
}
void back_pressAction(void){
  if (backBtn.justPressed()) {
    if (screen == 1){
        tft.loadFont(small);
        backBtn.drawSmoothButton(!backBtn.getState(), 3, BACKROUND, "Back");
        backBtn.setReleaseTime(millis());
        tft.unloadFont();
        }
   // setMain();
   // drawVariableName("Application Rate (g/ac)", 60);
  }}
void back_releaseAction(void){
    static uint32_t waitTime = 500;
    if (backBtn.getState() == 0){    
      if (millis() - backBtn.getReleaseTime() >= waitTime) {
        //tft.setFreeFont(FSB9);
         backBtn.drawSmoothButton(!backBtn.getState());
         setMain();
      }}

  }
