
void drawVariable(int value, int dp, char *label)
{ //h=140w=260
  uint16_t colour = c1;
  int d0;
  int d1;
  int d2;
  int d3;
  int d4;
  d0 = (value/1000)%10;
  d1 = (value/100)%10;
  d2 = (value/10)%10;
  if (metric == true || ww == true){
      d3 = value%10;}
  else{
      d3 = 0;}
  fmSprite.fillSprite(c2);
  fmSprite.fillSmoothRoundRect(flowBX-4,flowBY-4,flowWidth-(flowBX*2)+8,flowHeight-(flowBY*2)+8,8,c1,c2);
  fmSprite.fillSmoothRoundRect(flowBX,flowBY,flowWidth-(flowBX*2), flowHeight-(flowBY*2),8,c2,c1);

  fmSprite.setTextColor(c1,c2);  // Text colour
  //Draws the 4 digit backgrounds
  for(int i=0;i<4;i++){
    fmSprite.fillRect(flowBX+(5)+(i*62), flowBY+6, 58, 95, TFT_BLACK);
   // tmSprite.fillRectHGradient(timerX+(5)+(i*50), timerY+12, 15, 44, grays[2],TFT_BLACK);
    }
    //90 Angled Lines for bottom text
  fmSprite.drawLine(flowBX+25,flowBY+110,flowBX+25,flowBY+116,c1); //Vert L
  fmSprite.drawLine(flowBX+25,flowBY+116,flowBX+65,flowBY+116,c1); //Hor L
  fmSprite.drawLine(flowWidth-flowBX-65,flowBY+116,flowWidth-flowBX-25,flowBY+116,c1); //Hor R
  fmSprite.drawLine(flowWidth-flowBX-25,flowBY+116,flowWidth-flowBX-25,flowBY+110,c1); //Vert R
  //bottom text
  fmSprite.loadFont(small);
  fmSprite.setTextColor(c1,c2);
  fmSprite.drawString(label,flowWidth/2,flowBY+116);
  fmSprite.setTextColor(c4,c1);
  //sprite.drawString(String(fps),20,80);
  fmSprite.setTextColor(c1,c2);
  fmSprite.unloadFont(); 
  //DP
  if (dp > 0){
    fmSprite.fillSmoothCircle(flowBX+250-(dp*62), (flowHeight)-62, 6, c1, c2);
  }
  //Digits
  fmSprite.loadFont(large70);
  fmSprite.setTextColor(c1,TFT_BLACK);
  fmSprite.drawString(String(d0),flowBX+30,flowBY+55);
  fmSprite.drawString(String(d1),flowBX+92,flowBY+55);
  fmSprite.drawString(String(d2),flowBX+154,flowBY+55);
  fmSprite.drawString(String(d3),flowBX+216,flowBY+55);
  fmSprite.unloadFont(); 
  //Push to Screen
  fmSprite.pushSprite(flowX,flowY);
}

void drawControls(const char* stepValues[])
{
  ctSprite.fillSprite(c2);
  ctSprite.fillSmoothRoundRect(counterBX-4,counterBY-4,counterWidth-(counterBX*2)+8,counterHeight-(counterBY*2)+8,8,c1,c2);
  ctSprite.fillSmoothRoundRect(counterBX,counterBY,counterWidth-(counterBX*2), counterHeight-(counterBY*2),8,c2,c1);
  
  ctSprite.loadFont(small);
  ctSprite.setTextColor(BLACK,c2);
  int midPt = (counterWidth*0.5);
  int ypos = 40;
  ctSprite.fillTriangle(midPt-130, ypos, midPt-80, ypos-25, midPt-80, ypos+25, c3);
  ctSprite.drawString(stepValues[0],midPt-102, ypos+2);
  ctSprite.fillTriangle(midPt-65, ypos, midPt-15, ypos-25, midPt-15, ypos+25, c3);
  ctSprite.drawString(stepValues[1],midPt-30, ypos+2);
  ctSprite.fillTriangle(midPt+65, ypos, midPt+15, ypos-25, midPt+15, ypos+25, c4);
  ctSprite.drawString(stepValues[2],midPt+30, ypos+2);
  ctSprite.fillTriangle(midPt+130, ypos, midPt+80, ypos-25, midPt+80, ypos+25, c4);
  ctSprite.drawString(stepValues[3],midPt+102, ypos+2);
  ctSprite.unloadFont(); 
  
  //Push to Screen
  ctSprite.pushSprite(counterX,counterY);
  }

void saveBtn(){
  uint16_t colour = c4;
  char *label = "SAVE";
  relaySprite.fillSprite(c2);
  relaySprite.fillSmoothRoundRect(0, 0, relayWidth, relayHeight, 8, colour, c2); //White Rect
  relaySprite.fillSmoothRoundRect(relayBX, relayBY, relayWidth-(relayBX*2), relayHeight-(relayBY*2), 8, c2, colour);
  relaySprite.loadFont(latin);
  relaySprite.setTextColor(c1,c2);
  relaySprite.drawString(label, relayWidth/2, relayHeight/2); // Value in middle
  relaySprite.pushSprite(relayX,relayY);
  // Calculate and return right hand side x coordinate
}
void backBtn(){
  uint16_t colour = c3;
  char *label = "BACK";
  hydSprite.fillSprite(c2);
  hydSprite.fillSmoothRoundRect(0, 0, hydWidth, hydHeight, 8, colour, c2); //White Rect
  hydSprite.fillSmoothRoundRect(hydBX, hydBY, hydWidth-(hydBX*2), hydHeight-(hydBY*2), 8, c2, colour);
  hydSprite.loadFont(latin);
  hydSprite.setTextColor(c1,c2);
  hydSprite.drawString(label, hydWidth/2, hydHeight/2); // Value in middle
  hydSprite.pushSprite(hydX,hydY);
  // Calculate and return right hand side x coordinate
}

void checkEditTouch(){
  uint16_t x, y;
  // See if there's any touch data for us
  if (tft.getTouch(&x, &y))
    {
      if (debounce == 0){
         soundBuzzer();
        //ADD OR MINUS  x = [70, 150, 170, 250]
           if ((y > counterY-20) && (y <= 400)) {
                if ((x < 70)){
                    if (wwOn == true){
                        ww-=1;}
                    else if (rateOn == true){
                      if(metric==true){
                        appRate-=10;}
                      else{
                        appRate-=10;} 
                        }
                    else if (calOn == true){
                        metric = true;
                        writeIntIntoEEPROM(epromAddress[6], 1);
                        }
                    else if (historyOn == true){
                        eepromIndex -= 1;
                        }
                        }
                else if ((x > 70) && (x < 150)){
                    if (wwOn == true){
                        ww-=0.1;}
                    else if (rateOn == true){
                        if(metric==true){
                          appRate-=1;}
                        else{
                          appRate-=1;} 
                          }
                    else if (calOn == true){
                        metric = true;
                        writeIntIntoEEPROM(epromAddress[6], 1);
                        }
                    else if (historyOn == true){
                        eepromIndex -= 1;
                        }
                        }
                else if ((x > 170) && (x < 250)){
                    if (wwOn == true){
                        ww+=0.1;}
                    else if (rateOn == true){
                        if(metric==true){
                          appRate+=1;}
                        else{
                          appRate+=1;} 
                        }
                    else if (calOn == true){
                        metric = false;
                        writeIntIntoEEPROM(epromAddress[6], 0);
                        }
                    else if (historyOn == true){
                        eepromIndex += 1;
                        }}
                else if ((x > 250)){
                    if (wwOn == true){
                        ww+=1;}
                    else if (rateOn == true){
                        if(metric==true){
                          appRate+=10;}
                        else{
                          appRate+=10;} 
                          }
                    else if (calOn == true){
                        metric = false;
                        writeIntIntoEEPROM(epromAddress[6], 0);
                        }
                    else if (historyOn == true){
                        eepromIndex += 1;
                        }}
              }
        //BACK OR SAVE
           if ((y > 400)){
             if ((x < (hydWidth+hydX))){
                  if (wwOn == true){
                      ww = tempWW;}
                  else if (rateOn == true){
                      appRate = tempApp;}
                  else if (calOn == true){
                      calibrateCount=0;
                      calibrateValue=0;
                      calibrate=false;
                      rateBtn();
                      }
                  else if (historyOn == true){
                      eepromIndex =0;
                      }
                  wwOn = false;
                  rateOn = false;
                  calOn = false;
                  historyOn = false;
                  modeChanged = true;
                  }
              else if (x > (hydWidth+hydX+20)){
                  if (wwOn == true){
                      tempWW = ww;
                      writeIntIntoEEPROM(epromAddress[0], ww*10);
                      calcTarget();}
                  else if (rateOn == true){
                      tempApp = appRate;
                      writeIntIntoEEPROM(epromAddress[1], appRate);
                      calcTarget();}
                  else if (calOn == true){
                      if(calibrate==false){ //TURN ON CALIBRATE
                              if(calibrateCount == 0){
                                  calibrateTime = millis();                        
                                  }
                              calibrateCount+=1;
                              if(calibrateCount>=3){
                                calibrate=true;
                                calibrateCount=0;
                              }
                              if(millis()-calibrateTime > 4000){
                                calibrateCount=0;
                                }
                              modeChanged = true;
                              }
                      else if (calibrate==true && calibrateValue == 0){ //NEXT ANALOG VALUE
                              analog1 = flowAnalog;
                              writeIntIntoEEPROM(epromAddress[2], analog1);
                              calibrateValue+= 1;
                              }
                      else{                                             //END CALIBRATION
                              analog2 = flowAnalog;
                              writeIntIntoEEPROM(epromAddress[4], analog2);
                              calibrateValue = 0;
                              rateBtn();
                              calibrate= false;
                              }
                      }
                      
                  else if (historyOn == true){
                      }
                    
                  //EXIT TO MAIN UNLESS MOVING TO ANALOG 2
                  if(calibrate==false && calibrateCount==0 && calibrateValue != 1){
                      wwOn = false;
                      rateOn = false;
                      calOn = false;
                      historyOn = false;
                      modeChanged = true;
                      }
                }
              }
          //DIGIT
          debounce = 1;
        }
      }
  else {
    debounce = 0;
    }
  }
