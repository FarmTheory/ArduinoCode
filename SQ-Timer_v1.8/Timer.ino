void setTimerOn(){
  updateTime = millis();
  unpauseTime = millis();
  timerPaused = false;
  sendBluetooth("TIMER:ON");
}

void setTimerPaused(){
 // float app = galsPerMin/(1000/(millis()-unpauseTime));
 // applied += app;
  loadTime += millis()-unpauseTime;
  pauseTime = millis();
  drawTimer(timerD0, timerD1, timerD2, sec);
  drawCounter(applied, "total applied");
  sendBluetooth("TIMER:PAUSE");
}

void setTimerUnpaused(){
  updateTime = millis();
  unpauseTime = millis();
  sendBluetooth("TIMER:UPPAUSE");
}

void setTimerOff(){
//  float app = galsPerMin/(1000/(millis()-unpauseTime));
 // applied += app;
  timerResetFlag = false;
  totalSec = 0;
  timerD0=0;
  timerD1=0;
  timerD2=0;
  timerD3=0;
  drawTimer(timerD0, timerD1, timerD2, timerD3);
  drawCounter(applied, "total applied");
  sendBluetooth("TIMER:OFF");
}

void drawOption(){
  fmSprite.fillSprite(c2);
  fmSprite.loadFont(latin);
  fmSprite.setTextColor(c1,c2);

  uint16_t calibrate = c4;
  uint16_t cancel = c1;
  //Btn 1 CANCEL
  int width = (flowWidth/2)-8;
  int btnOneX = 0;
  fmSprite.fillSmoothRoundRect(btnOneX,      flowBY-4,   width,   flowHeight-(flowBY*2)+8,8,cancel,c2);
  fmSprite.fillSmoothRoundRect(btnOneX+4,    flowBY,     width-8,   flowHeight-(flowBY*2),8,c2,cancel);
  fmSprite.drawString("CANCEL",counterWidth*0.25, flowHeight/2);
  //Btn 2 CALIBRATE
  int btnTwoX = (flowWidth/2)+4;
  fmSprite.fillSmoothRoundRect(btnTwoX,     flowBY-4,   width,   flowHeight-(flowBY*2)+8,8,calibrate,c2);
  fmSprite.fillSmoothRoundRect(btnTwoX+4,   flowBY,     width-8,   flowHeight-(flowBY*2),8,c2,calibrate);
  fmSprite.drawString("CALC",flowWidth*0.75, flowHeight/2);
  fmSprite.unloadFont(); 
  //TIMEOUT
  int secsRemaining = 5-((millis()-calcTime)/1000);
  char timeoutBuffer[20]="";
  char timeouttemp[5]="";
  strcat(timeoutBuffer,"timeout (");
  sprintf(timeouttemp,"%02d",secsRemaining);
  strcat(timeoutBuffer,timeouttemp);
  strcat(timeoutBuffer,")");
  char *label = timeoutBuffer;
  fmSprite.loadFont(small);
  fmSprite.setTextColor(RED,c2);
  fmSprite.drawString(label,(flowWidth*0.75),flowBY+116);
  
  //Push to Screen
  fmSprite.pushSprite(flowX,flowY);
  }


void drawTimer(int d0, int d1, int d2, int d3){ //h=140w=260
  uint16_t colour = c1;
  uint16_t textColour = c1;
  char *label = "timer";
  fmSprite.fillSprite(c2);
  if (flowOn == true && timerPaused == false && optionOn == false){
    colour = c4;
    textColour = c1;
    label = "running";
    }
  else if (timerPaused == true){
    colour = c3;
    textColour = RED;
    int countDown = resetTimeOut-((millis()-pauseTime)/1000);
    char timeoutBuffer[20]="";
    char timeouttemp[5]="";
    strcat(timeoutBuffer,"paused (");
    sprintf(timeouttemp,"%03d",countDown);
    strcat(timeoutBuffer,timeouttemp);
    strcat(timeoutBuffer,")");
    label = timeoutBuffer;
    if (countDown < 0){
      timerResetFlag = true;
      }
  }
  //sprite.fillSmoothRoundRect(0,0,(left*2)+width,(fromTop*2)+heigth,8,c1,c2);
 // sprite.fillSmoothRoundRect(left,fromTop,width,heigth,8,c2,c1);
  fmSprite.fillSmoothRoundRect(0, 0, flowWidth, flowHeight, 8, colour, c2); //White Rect
  fmSprite.fillSmoothRoundRect(flowBX, flowBY, flowWidth-(flowBX*2), flowHeight-(flowBY*2), 8, c2, colour);
  fmSprite.setTextColor(c1,c2);  // Text colour
  //Draws the 4 digit backgrounds
  for(int i=0;i<4;i++){
    fmSprite.fillRect(flowBX+(5)+(i*62), flowBY+6, 58, 95, TFT_BLACK);
   // tmSprite.fillRectHGradient(timerX+(5)+(i*50), timerY+12, 15, 44, grays[2],TFT_BLACK);
    }
    //90 Angled Lines for bottom text
  fmSprite.drawLine(flowBX+25,flowBY+110,flowBX+25,flowBY+116,c1); //Vert L
  fmSprite.drawLine(flowBX+25,flowBY+116,flowBX+45,flowBY+116,c1); //Hor L
  fmSprite.drawLine(flowWidth-flowBX-85,flowBY+116,flowWidth-flowBX-65,flowBY+116,c1); //Hor R
  fmSprite.drawLine(flowWidth-flowBX-65,flowBY+116,flowWidth-flowBX-65,flowBY+110,c1); //Vert R
  //bottom text
  fmSprite.loadFont(small);
  fmSprite.setTextColor(textColour,c2);
  fmSprite.drawString(label,(flowWidth/2)-20,flowBY+116);
  
  fmSprite.unloadFont(); 
  //Digits
  fmSprite.loadFont(large80);
  fmSprite.setTextColor(c1,TFT_BLACK);
  fmSprite.drawString(String(d0),flowBX+32,flowBY+58);
  fmSprite.drawString(String(d1),flowBX+94,flowBY+58);
  fmSprite.drawString(String(d2),flowBX+153,flowBY+58);
  fmSprite.drawString(String(d3),flowBX+218,flowBY+58);
  fmSprite.unloadFont(); 
  if (timerPaused == true){
    fmSprite.fillRect(flowWidth-flowBX-28, (flowHeight/2)-25, 15, 15, RED); //White Rect  
    fmSprite.loadFont(small);
    fmSprite.setTextColor(c1,c2);
    fmSprite.drawString("END",flowWidth-flowBX-22,(flowHeight/2)+10); 
    fmSprite.unloadFont();  
    //VENT DELAY
    if (endDelay == true){
        fmSprite.loadFont(small);
        fmSprite.setTextColor(GREEN,c2);
        fmSprite.drawString("-10s",flowWidth-flowBX-26,flowBY+116); 
        fmSprite.unloadFont();  

    }
    }
  else if (flowOn == true){ //REMAINING %
      float tempSec = totalSec;
      float tempLoad = prevLoadTime;
      float prop = tempSec/tempLoad;      
      int remPerc = 100-(prop*100.0);
      if (remPerc < 0){
          remPerc = 0;
        }
      int p = prop*18;
      linearMeter(p, flowWidth-flowBX-30, flowBY+4, 18, 4, 1, 18, GREEN2RED);
      char timeoutBuffer[20]="";
      char timeouttemp[5]="";
      sprintf(timeouttemp,"%02d",remPerc);
      strcat(timeoutBuffer,timeouttemp);
      strcat(timeoutBuffer,"%");
      //fmSprite.fillRect(flowWidth-flowBX-28, (flowHeight/2)-25, 15, 15, RED); //White Rect  
      fmSprite.loadFont(small);
      fmSprite.setTextColor(c1,c2);
      fmSprite.drawString(timeoutBuffer,flowWidth-flowBX-22,flowBY+116); 
      fmSprite.unloadFont();
  }
  //Push to Screen
  fmSprite.pushSprite(flowX,flowY);
}

//LINEAR meter
void linearMeter(int val, int x, int y, int w, int h, int g, int n, byte s)
{
  // Variable to save "value" text colour from scheme and set default
  int colour = TFT_BLUE;
  // Draw n colour blocks
  for (int b = 1; b <= n; b++) {
    if (val > 0 && b <= val) { // Fill in coloured blocks
      fmSprite.fillRect(x, y + b*(h+g), w, h, TFT_DARKGREY);
    }
    else // Fill in blank segments
    {
      fmSprite.fillRect(x, y + b*(h+g), w, h, TFT_DARKGREY);
      switch (s) {
        case 0: colour = TFT_RED; break; // Fixed colour
        case 1: colour = TFT_GREEN; break; // Fixed colour
        case 2: colour = TFT_BLUE; break; // Fixed colour
        case 3: colour = rainbowColor(map(b, 0, n, 127,   0)); break; // Blue to red
        case 4: colour = rainbowColor(map(b, 0, n,  63,   0)); break; // Green to red
        case 5: colour = rainbowColor(map(b, 0, n,   0,  63)); break; // Red to green
        case 6: colour = rainbowColor(map(b, 0, n,   0, 159)); break; // Rainbow (red to violet)
      }
      fmSprite.fillRect(x, y + b*(h+g), w, h, colour);
    }
  }
}
uint16_t rainbowColor(uint8_t spectrum)
{
  spectrum = spectrum%192;
  
  uint8_t red   = 0; // Red is the top 5 bits of a 16 bit colour spectrum
  uint8_t green = 0; // Green is the middle 6 bits, but only top 5 bits used here
  uint8_t blue  = 0; // Blue is the bottom 5 bits

  uint8_t sector = spectrum >> 5;
  uint8_t amplit = spectrum & 0x1F;

  switch (sector)
  {
    case 0:
      red   = 0x1F;
      green = amplit; // Green ramps up
      blue  = 0;
      break;
    case 1:
      red   = 0x1F - amplit; // Red ramps down
      green = 0x1F;
      blue  = 0;
      break;
    case 2:
      red   = 0;
      green = 0x1F;
      blue  = amplit; // Blue ramps up
      break;
    case 3:
      red   = 0;
      green = 0x1F - amplit; // Green ramps down
      blue  = 0x1F;
      break;
    case 4:
      red   = amplit; // Red ramps up
      green = 0;
      blue  = 0x1F;
      break;
    case 5:
      red   = 0x1F;
      green = 0;
      blue  = 0x1F - amplit; // Blue ramps down
      break;
  }

  return red << 11 | green << 6 | blue;
}
