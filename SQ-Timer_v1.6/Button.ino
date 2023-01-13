
void wwBtn()
{
  uint16_t colour = GREY;
  char wwBuffer[20]="";
  char wwtemp[5]="";
  sprintf(wwtemp,"%.1f",ww);
  strcat(wwBuffer,wwtemp);
  strcat(wwBuffer,"m");
  char *label = wwBuffer;
  if(wwOn == true){
    colour = c4;
    label = "WIDTH";
    }
  wwSprite.fillSprite(c2);
  wwSprite.fillSmoothRoundRect(0, 0, optWidth, optHeight, 8, colour, c2); //White Rect
  wwSprite.fillSmoothRoundRect(optBX, optBY, optWidth-(optBX*2), optHeight-(optBY*2), 8, c2, colour);
  wwSprite.loadFont(small);
  wwSprite.setTextColor(GREY,c2);
  wwSprite.drawString(label, optWidth/2, optHeight/2); // Value in middle
  wwSprite.pushSprite(optX,optY);
  // Calculate and return right hand side x coordinate
}
void rateBtn()
{
  uint16_t colour = GREY;
  char outBuffer[20]="";
  char temp[5]="";
  sprintf(temp,"%04d",appRate);
  strcat(outBuffer,temp);
  strcat(outBuffer,"g/ac");
  char *label = outBuffer;
  if(rateOn == true){
    colour = c4;
    label = "APP RATE";
    }
  rateSprite.fillSprite(c2);
  rateSprite.fillSmoothRoundRect(0, 0, optWidth, optHeight, 8, colour, c2); //White Rect
  rateSprite.fillSmoothRoundRect(optBX, optBY, optWidth-(optBX*2), optHeight-(optBY*2), 8, c2, colour);
  rateSprite.loadFont(small);
  rateSprite.setTextColor(GREY,c2);
  rateSprite.drawString(label, optWidth/2, optHeight/2); // Value in middle
  rateSprite.pushSprite(optX+(8*1)+(optWidth*1),optY);
  // Calculate and return right hand side x coordinate
}
void tkrBtn()
{
  uint16_t colour = GREY;
  char outBuffer[20]="";
  char temp[5]="";
  sprintf(temp,"%04d",tkrSize);
  strcat(outBuffer,temp);
  strcat(outBuffer,"g");
  char *label = outBuffer;
  if(tkrOn == true){
    colour = c4;
    label = "TKR SIZE";
    }
  tkrSprite.fillSprite(c2);
  tkrSprite.fillSmoothRoundRect(0, 0, optWidth, optHeight, 8, colour, c2); //White Rect
  tkrSprite.fillSmoothRoundRect(optBX, optBY, optWidth-(optBX*2), optHeight-(optBY*2), 8, c2, colour);
  tkrSprite.loadFont(small);
  tkrSprite.setTextColor(GREY,c2);
  tkrSprite.drawString(label, optWidth/2, optHeight/2); // Value in middle
  tkrSprite.pushSprite(optX+(8*2)+(optWidth*2),optY);
  // Calculate and return right hand side x coordinate
}
void relayBtn(){
  uint16_t colour = c4;
  char *label = "MACERATE";
  char *labelTwo = "(FOLD)";
  if(relayOn == true){
    colour = c3;
    label = "FOLD";
    labelTwo = "(MACERATE)";
    relaySwitchTime = millis();
    relaySwitchUpdateTime = millis();
    timeLeft = relayTimeout*1000;
    digitalWrite(r1Pin, HIGH);
    }
  else{
    digitalWrite(r1Pin, LOW);
    }
  relaySprite.fillSprite(c2);
  relaySprite.fillSmoothRoundRect(0, 0, relayWidth, relayHeight, 8, colour, c2); //White Rect
  relaySprite.fillSmoothRoundRect(relayBX, relayBY, relayWidth-(relayBX*2), relayHeight-(relayBY*2), 8, c2, colour);
  relaySprite.loadFont(latin);
  relaySprite.setTextColor(c1,c2);
  relaySprite.drawString(label, relayWidth/2, (relayHeight/2)-10); // Value in middle
  relaySprite.setTextColor(GREY,c2);
  relaySprite.drawString(labelTwo, relayWidth/2, (relayHeight/2)+20); // Value in middle
  relaySprite.pushSprite(relayX,relayY);
  // Calculate and return right hand side x coordinate
}

void relayCounter(){
    uint16_t colour = c3;
    char *label = "FOLD";
    char *labelTwo = "(MACERATE)";
    if(relayOn == true){
        Serial.println((millis()-relaySwitchUpdateTime));
        if ((millis()-relaySwitchUpdateTime) > 1000){
            timeLeft -= (millis()-relaySwitchUpdateTime);
            relaySwitchUpdateTime = millis();
            relaySprite.fillSprite(c2);
            relaySprite.fillSmoothRoundRect(0, 0, relayWidth, relayHeight, 8, colour, c2); //White Rect
            relaySprite.fillSmoothRoundRect(relayBX, relayBY, relayWidth-(relayBX*2), relayHeight-(relayBY*2), 8, c2, colour);
            relaySprite.loadFont(latin);
            relaySprite.setTextColor(c1,c2);
            relaySprite.drawString(label, relayWidth/2, (relayHeight/2)-10); // Value in middle
            relaySprite.setTextColor(GREY,c2);
            relaySprite.drawString(labelTwo, relayWidth/2, (relayHeight/2)+20); // Value in middle
            //TIMEOUT
            char timeoutBuffer[20]="";
            char timeouttemp[5]="";
            strcat(timeoutBuffer,"reset (");
            sprintf(timeouttemp,"%03d",timeLeft/1000);
            strcat(timeoutBuffer,timeouttemp);
            strcat(timeoutBuffer,")");
            if (timeLeft < 10000){
              soundBuzzer();
              }
            if (timeLeft < 1500){
                relayOn = false;
                modeChanged = true;
                }
            relaySprite.loadFont(small);
            relaySprite.setTextColor(RED,c2);
            relaySprite.drawString(timeoutBuffer, relayWidth/2, (relayHeight/2)-33); // Value in middle
            relaySprite.pushSprite(relayX,relayY);
        }
      }  
  }

void soundBuzzer(){
  digitalWrite(buzzerPin, HIGH);
  buzzerState = true;
  buzzerOn = millis();
}


void checkTouch(){
  uint16_t x, y;
  // See if there's any touch data for us
  if (tft.getTouch(&x, &y))
    {
      // Draw a block spot to show where touch was calculated to be
      if (debounce == 0){
        soundBuzzer();
        //TIMER
           if ((y > timerY) && (y <= (timerY + timerHeight))) {
             if ((x > timerX) && (x < (timerX + timerWidth-50))){
                  hydManualStart = true;
                  if (timerOn == false){
                    timerOn = true;
                    setTimerOn();
                    }
                  else if (timerPaused == false){
                    timerPaused = true;
                    setTimerPaused();
                    }   
                  else if (timerPaused == true){
                    timerPaused = false;
                    setTimerUnpaused();
                    }     
                }
              else if ((x >= (timerX + timerWidth-60)) && (x < 315)){
                    setTimerOff();
                    loadFinished();
                  }
            }

        //COUNTER
          if ((y > counterY) && (y <= (counterY + counterHeight))) {
              // HISTORY
              if ((x > counterX) && (x < (counterX+(counterWidth/2)))) {
                  historyOn = true;
                  modeChanged = true;
                  }
              // RESET
              if ((x >= (counterX+(counterWidth/2))) && (x < (counterX + counterWidth))) {
                  if (counterOn == false){
                    counterOn = true;
                    resetCounter();
                    counterOn = false;
                    }    
                }
            }
         //RELAY
          if ((x > relayX) && (x < (relayX + relayWidth))) {
              if ((y > relayY) && (y <= (relayY + relayHeight))) {
                  if (relayOn == false){
                    relayOn = true;
                    relayBtn();
                    }
                  else{
                    relayOn = false;
                    relayBtn();
                    }
                
                }
            }
          //RELAY 2 (HYD)
          if ((x > hydX) && (x < (hydX + hydWidth))) {
              if ((y > hydY) && (y <= (hydY + hydHeight))) {
                  hydSettingsOn = true;
                  modeChanged = true;
                  }
                }
         //OPTIONS
          if ((y > optY) && (y <= (optY + optHeight + 40))) {
              //WW
              if ((x > optBX) && (x < (optBX + optWidth + 4))) {
                  modeChanged = true;
                  if (wwOn == false){
                    wwOn = true;
                    wwBtn();
                    }
                  else{
                    wwOn = false;
                    wwBtn();
                    }
                }
              //rate
              if ((x > optBX + optWidth + 4) && (x < (optBX + ((optWidth+4)*2) + 4))) {
                  modeChanged = true;
                  if (rateOn == false){
                    rateOn = true;
                    rateBtn();
                    }
                  else{
                    rateOn = false;
                    rateBtn();
                    }
              }
            //tkr
              if ((x > (optBX + ((optWidth+4)*2) + 4)) && (x < 320)) {
                  modeChanged = true;
                  if (tkrOn == false){
                    tkrOn = true;
                    tkrBtn();
                    }
                  else{
                    tkrOn = false;
                    tkrBtn();
                    }
                }
            }
          debounce = 1;
        }
      }
  else {
    debounce = 0;
    }
  }

