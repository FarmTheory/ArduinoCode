void resetCounter(){
  //MOVE ALL ALONG 1
  int tempHistory[10] = {};
  memcpy(tempHistory, appHistory, 10);
  for (int i=1; i<10; i++){
      int tempValue = tempHistory[i-1];
      writeIntIntoEEPROM(historyEprom[i], tempValue);
      appHistory[i] = tempValue;} 
  writeIntIntoEEPROM(historyEprom[0], applied);
  appHistory[0] = applied;
  historicTotal += applied;
  writeIntIntoEEPROM(historyEprom[10], historicTotal);
  applied = 0;
  drawCounter(applied, "applied");
  drawHistoricTotal();
}

void setAnimation(){
  animationTimer++;
  if(animationTimer==4)
      {
        animationTimer=0;
        longLine++;
        if( longLine==11)
        longLine=0;
      } 
    }

void drawCounter(float value, char *label)
{
  char charBuffer[20]="";
  int fmtValue;
  if (areaMetric == true){
    fmtValue = value;
    strcat(charBuffer,label);
    strcat(charBuffer," (m3)");}
  else {
    fmtValue = (value*220);
    strcat(charBuffer,label);
    strcat(charBuffer," (gal)");}
  int d0;
  int d1;
  int d2;
  int d3;
  int d4;
  int d5;
  d0 = (fmtValue/100000)%10;
  d1 = (fmtValue/10000)%10;
  d2 = (fmtValue/1000)%10;
  d3 = (fmtValue/100)%10;
  d4 = (fmtValue/10)%10;
  d5 = fmtValue%10;
  
  ctSprite.fillSprite(c2);
  ctSprite.fillSmoothRoundRect(counterBX-4,counterBY-4,counterWidth-(counterBX*2)+8,counterHeight-(counterBY*2)+8,8,c1,c2);
  ctSprite.fillSmoothRoundRect(counterBX,counterBY,counterWidth-(counterBX*2), counterHeight-(counterBY*2),8,c2,c1);
  //Draws the 5 digits  +30
  for(int i=0;i<6;i++){
      ctSprite.fillRectHGradient(counterBX+(40)+(i*33), counterBY+6, 15, 42, TFT_BLACK,grays[2]);
      ctSprite.fillRectHGradient(counterBX+(55)+(i*33), counterBY+6, 15, 42, grays[2],TFT_BLACK);
      if (i < 5) { //Skip final digit ticks
        for(int j=0;j<11;j++)
        if(j==5)
        ctSprite.drawLine(counterBX+(60)+(i*33),counterBY+8+(j*4),counterBX+(67)+(i*33),counterBY+8+(j*4),lines[j]);
        else
        ctSprite.drawLine(counterBX+(63)+(i*33),counterBY+8+(j*4),counterBX+(67)+(i*33),counterBY+8+(j*4),lines[j]);
        }
      }
  // Final Digit ticks  +30
  for(int j=0;j<11;j++){
      if(j==longLine)
      ctSprite.drawLine(counterBX+(60)+(5*33),counterBY+8+(j*4),counterBX+(67)+(5*33),counterBY+8+(j*4),lines[j]);
      else
      ctSprite.drawLine(counterBX+(63)+(5*33),counterBY+8+(j*4),counterBX+(67)+(5*33),counterBY+8+(j*4),lines[j]);
      }
  //90 Angled Lines for bottom text +30
  ctSprite.drawLine(counterBX+48,counterBY+54,counterBX+48,counterBY+60,c1);
  ctSprite.drawLine(counterBX+48,counterBY+60,counterBX+74,counterBY+60,c1);
  ctSprite.drawLine(counterBX+152+36,counterBY+60,counterBX+178+36,counterBY+60,c1);
  ctSprite.drawLine(counterBX+178+36,counterBY+60,counterBX+178+36,counterBY+54,c1);
  //bottom text
  ctSprite.loadFont(small);
  ctSprite.setTextColor(c1,c2);
  ctSprite.drawString(charBuffer,counterBX+89+45,counterBY+62);
  ctSprite.setTextColor(c4,c1);
  //sprite.drawString(String(fps),20,80);
  //HISTORY
  ctSprite.fillSmoothCircle(counterBX+20, (counterHeight/2)-10, 10, GREY, c2);
  ctSprite.loadFont(small);
  ctSprite.setTextColor(c1,c2);
  ctSprite.drawString("HIST",counterBX+20,counterBY+58);
  ctSprite.unloadFont();
  //RESET +15
  ctSprite.fillSmoothCircle(counterBX+148+36+36+30, (counterHeight/2)-10, 10, c3, c2);
  ctSprite.loadFont(small);
  ctSprite.setTextColor(c1,c2);
  ctSprite.drawString("RESET",counterBX+148+36+36+30,counterBY+58);
  ctSprite.unloadFont(); 

  //Digits
  ctSprite.loadFont(digits);
  ctSprite.setTextColor(c1,TFT_BLACK);
  ctSprite.drawString(String(d0),counterBX+50,counterBY+29);
  ctSprite.drawString(String(d1),counterBX+83,counterBY+29);
  ctSprite.drawString(String(d2),counterBX+116,counterBY+29);
  ctSprite.drawString(String(d3),counterBX+149,counterBY+29);
  ctSprite.drawString(String(d4),counterBX+182,counterBY+29);
  ctSprite.drawString(String(d5),counterBX+215,counterBY+29);
  ctSprite.unloadFont(); 
  //Push to Screen
  ctSprite.pushSprite(counterX,counterY);
  }