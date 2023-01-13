
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
  relaySprite.drawString(label, relayWidth/2, relayHeight/2); // Value in middle
  relaySprite.setTextColor(GREY,c2);
  relaySprite.drawString(labelTwo, relayWidth/2, (relayHeight/2)+30); // Value in middle
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
            relaySprite.drawString(label, relayWidth/2, relayHeight/2); // Value in middle
            relaySprite.setTextColor(GREY,c2);
            relaySprite.drawString(labelTwo, relayWidth/2, (relayHeight/2)+30); // Value in middle
            //TIMEOUT
            char timeoutBuffer[20]="";
            char timeouttemp[5]="";
            Serial.println(timeLeft);
            strcat(timeoutBuffer,"Timeout: ");
            sprintf(timeouttemp,"%03d",timeLeft/1000);
            strcat(timeoutBuffer,timeouttemp);
            if (timeLeft < 1500){
                relayOn = false;
                modeChanged = true;
                }
            relaySprite.loadFont(small);
            relaySprite.setTextColor(RED,c2);
            relaySprite.drawString(timeoutBuffer, relayWidth/2, (relayHeight/2)-30); // Value in middle
            relaySprite.pushSprite(relayX,relayY);
        }
      }  
  }

void checkTouch(){
  uint16_t x, y;
  // See if there's any touch data for us
  if (tft.getTouch(&x, &y))
    {
      // Draw a block spot to show where touch was calculated to be
      if (debounce == 0){
        //TIMER
           if ((x > timerX) && (x < (timerX + timerWidth))) {
              if ((y > timerY) && (y <= (timerY + timerHeight))) {
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
            }

        //COUNTER
          if ((x > counterX) && (x < (counterX + counterWidth))) {
              if ((y > counterY) && (y <= (counterY + counterHeight))) {
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
         //OPTIONS
          if ((y > optY) && (y <= (optY + optHeight + 40))) {
              //WW
              if ((x > 0) && (x < (optBX + optWidth + 4))) {
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

void checkHardwareBtn(){ 
    buttonState = digitalRead(btnPin);
    if (buttonState == HIGH){
        while (buttonState == HIGH){
            holdCounter = holdCounter+1;
            buttonState = digitalRead(btnPin);
            delay(50);
            }
        if (holdCounter > 40){
            setTimerOff();
            loadFinished();
            digitalWrite(ledPin, LOW);
            holdCounter = 0;
            }
        else{  
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
        digitalWrite(ledPin, HIGH);   
        }
    else {
      holdCounter = 0;
      }
    btnScanTime = millis();
      
  }

