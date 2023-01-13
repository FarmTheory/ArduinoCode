void setTimerOn(){
  updateTime = millis();
  unpauseTime = millis();
  timerPaused = false;
}

void setTimerPaused(){
 // float app = galsPerMin/(1000/(millis()-unpauseTime));
 // applied += app;
  loadTime += millis()-unpauseTime;
  pauseTime = millis();
  drawTimer(timerD0, timerD1, timerD2, sec);
  drawCounter(applied, "total applied");
}

void setTimerUnpaused(){
  updateTime = millis();
  unpauseTime = millis();
}

void setTimerOff(){
//  float app = galsPerMin/(1000/(millis()-unpauseTime));
 // applied += app;
  timerResetFlag = false;
  loadTime += millis()-unpauseTime;
  sec = 0;
  timerD0=0;
  timerD1=0;
  timerD2=0;
  drawTimer(timerD0, timerD1, timerD2, sec);
  drawCounter(applied, "total applied");
}



void drawTimer(int d0, int d1, int d2, int d3){ //h=140w=260
  uint16_t colour = c1;
  uint16_t textColour = c1;
  char *label = "timer";
  tmSprite.fillSprite(c2);
  if(timerOn == true && timerPaused == false){
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
  tmSprite.fillSmoothRoundRect(0, 0, timerWidth, timerHeight, 8, colour, c2); //White Rect
  tmSprite.fillSmoothRoundRect(timerBX, timerBY, timerWidth-(timerBX*2), timerHeight-(timerBY*2), 8, c2, colour);
  tmSprite.setTextColor(c1,c2);  // Text colour
  //Draws the 4 digit backgrounds
  for(int i=0;i<4;i++){
    tmSprite.fillRect(timerBX+(5)+(i*62), timerBY+6, 58, 95, TFT_BLACK);
   // tmSprite.fillRectHGradient(timerX+(5)+(i*50), timerY+12, 15, 44, grays[2],TFT_BLACK);
    }
    //90 Angled Lines for bottom text
  tmSprite.drawLine(timerBX+25,timerBY+110,timerBX+25,timerBY+116,c1); //Vert L
  tmSprite.drawLine(timerBX+25,timerBY+116,timerBX+45,timerBY+116,c1); //Hor L
  tmSprite.drawLine(timerWidth-timerBX-85,timerBY+116,timerWidth-timerBX-65,timerBY+116,c1); //Hor R
  tmSprite.drawLine(timerWidth-timerBX-65,timerBY+116,timerWidth-timerBX-65,timerBY+110,c1); //Vert R
  //bottom text
  tmSprite.loadFont(small);
  tmSprite.setTextColor(textColour,c2);
  tmSprite.drawString(label,(timerWidth/2)-20,timerBY+116);
  
  tmSprite.unloadFont(); 
  //Digits
  tmSprite.loadFont(large80);
  tmSprite.setTextColor(c1,TFT_BLACK);
  tmSprite.drawString(String(d0),timerBX+30,timerBY+55);
  tmSprite.drawString(String(d1),timerBX+92,timerBY+55);
  tmSprite.drawString(String(d2),timerBX+154,timerBY+55);
  tmSprite.drawString(String(d3),timerBX+216,timerBY+55);
  tmSprite.unloadFont(); 
  if (timerPaused == true){
    tmSprite.fillRect(timerWidth-timerBX-28, (timerHeight/2)-25, 15, 15, RED); //White Rect  
    tmSprite.loadFont(small);
    tmSprite.setTextColor(c1,c2);
    tmSprite.drawString("END",timerWidth-timerBX-22,(timerHeight/2)+10); 
    tmSprite.unloadFont();  
    }
  //Push to Screen
  tmSprite.pushSprite(timerX,timerY);
}
