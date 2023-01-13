
//RELAY Buttons
void r1_pressAction(void){
  if (r1Btn.justPressed()) {
     // tft.setFreeFont(FSB9);
      tft.loadFont(latin);
      r1Btn.drawSmoothButton(!r1Btn.getState(), 5, c1, r1Btn.getState() ? "MACERATE" : "FOLD");
      tft.unloadFont(); 
  }}
void r1_releaseAction(void){
  if (r1Btn.justReleased() == 1){
      if (r1Btn.getState()==1){
        digitalWrite(relay1Pin, HIGH);
        }
      else if (r1Btn.getState()==0) {
        digitalWrite(relay1Pin, LOW);        
        }
      }
    }
void r2_pressAction(void){
  if (r2Btn.justPressed()) {
     // tft.setFreeFont(FSB9);
      tft.loadFont(latin);
      r2Btn.drawSmoothButton(!r2Btn.getState(), 5, c1, r2Btn.getState() ? "SPREAD" : "REEL");
      tft.unloadFont(); 
  }}
void r2_releaseAction(void){
  if (r2Btn.justReleased() == 1){
      if (r2Btn.getState()==1){
        digitalWrite(relay2Pin, HIGH);
        }
      else if (r2Btn.getState()==0) {
        digitalWrite(relay2Pin, LOW);        
        }
      }
    }

void rate_pressAction(void){
  if (rateBtn.justPressed()) {
    tft.loadFont(small);
    rateBtn.drawSmoothButton(!rateBtn.getState(), 3, BACKROUND, rateBtn.getState() ? "2000g/a" : "Rate");
    rateBtn.setReleaseTime(millis());
    tft.unloadFont();
   // drawVariableName("Application Rate (g/ac)", 60);
  }}
void rate_releaseAction(void){
    static uint32_t waitTime = 1000;
    if (rateBtn.getState() == 0){    
      if (millis() - rateBtn.getReleaseTime() >= waitTime) {
        //tft.setFreeFont(FSB9);
        rateBtn.drawSmoothButton(!rateBtn.getState());
        setOne();
      // drawVariableName("OFF", 60);
      }}

  }
void ww_pressAction(void){
  if (wwBtn.justPressed()) {
    tft.loadFont(small);
    wwBtn.drawSmoothButton(!wwBtn.getState(), 3, BACKROUND, wwBtn.getState() ? "10.0m" : "Width");
    wwBtn.setReleaseTime(millis());
    tft.unloadFont();
  }}
void ww_releaseAction(void){
    static uint32_t waitTime = 3000;
    if (wwBtn.getState() == 1){    
      if (millis() - wwBtn.getReleaseTime() >= waitTime) {
        //tft.loadFont(small);
       // wwBtn.drawSmoothButton(!wwBtn.getState());
       // tft.unloadFont();
      }}
  }