
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
