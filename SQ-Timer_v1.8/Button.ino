
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
  char outBuffer[20]="";
  char temp[5]="";
  if (areaMetric == true){
      sprintf(temp,"%02d",appRate);
      strcat(outBuffer,temp);
      strcat(outBuffer,"m3/ha");}
  else {
    sprintf(temp,"%03d",(appRate*89/10));
    strcat(outBuffer,temp);
    strcat(outBuffer,"0gal/ac");}
  uint16_t colour = GREY;
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

void calBtn()
{
  uint16_t colour = GREY;
  char *label = "SETUP";
  if(calOn == true){
    colour = c4;
    }
  calSprite.fillSprite(c2);
  calSprite.fillSmoothRoundRect(0, 0, optWidth, optHeight, 8, colour, c2); //White Rect
  calSprite.fillSmoothRoundRect(optBX, optBY, optWidth-(optBX*2), optHeight-(optBY*2), 8, c2, colour);
  calSprite.loadFont(small);
  calSprite.setTextColor(GREY,c2);
  calSprite.drawString(label, optWidth/2, optHeight/2); // Value in middle
  calSprite.pushSprite(optX+(8*2)+(optWidth*2),optY);
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
    digitalWrite(r1Pin, LOW);
    }
  else{
    digitalWrite(r1Pin, HIGH);
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
           if ((y > flowY) && (y <= (flowY + flowHeight))) {
             if (optionOn == false){
                if ((x > flowX) && (x < (flowX + flowWidth-50))){
                      hydManualStart = true;
                      if (flowOn == false){
                        flowOn = true;
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
                  else if ((x >= (flowX + flowWidth-60)) && (x < 315)){
                        setTimerOff();
                        endLoad();
                      }
                  }
              else{
                  if ((x > flowX) && (x < (flowX + flowWidth/2))){
                      loadFinished(false);
                      }
                  else{
                      loadFinished(true);
                      }
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
          if ((y > 0) && (y <= (optY + optHeight + 40))) {
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
            //cal
              if ((x > (optBX + ((optWidth+4)*2) + 4)) && (x < 320)) {
                  modeChanged = true;
                  if (calOn == false){
                    calOn = true;
                    calBtn();
                    }
                  else{
                    calOn = false;
                    calBtn();
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

