//drawHistory("Field 1", 25);
      //  drawHistoryControls();
void loadHistory(){
  if (eepromWrite == 1){
      for (int i=0; i<10; i++){
          writeIntIntoEEPROM(historyEprom[i], appHistory[i]); //History = 0
        }
      writeIntIntoEEPROM(historyEprom[10], 0);
    }
  for (int i=0; i<10; i++){
      int value = readIntFromEEPROM(historyEprom[i]);
      appHistory[i] = value;}
  //Serial.println(appHistory);
  writeIntIntoEEPROM(historyEprom[10], 528200);
  historicTotal =  readIntFromEEPROM(historyEprom[10]);         
  }
void drawHistory()
{ //h=140w=260
  //Get Value
  int applied = appHistory[eepromIndex];
  fmSprite.fillSprite(c2);
  fmSprite.loadFont(large70);
  fmSprite.setTextColor(c1,c2);
  fmSprite.fillSmoothRoundRect(flowBX-4,flowBY-4,flowWidth-(flowBX*2)+8,flowHeight-(flowBY*2)+8,8,c1,c2);
  fmSprite.fillSmoothRoundRect(flowBX,flowBY,flowWidth-(flowBX*2), flowHeight-(flowBY*2),8,c2,c1);
  char histBuffer[20]="";
  char histtemp[5]="";
  char *units;
//  Serial.println(value);
  if (metric==true){
      units = "(m3)";
      sprintf(histtemp,"%03d",applied);
      strcat(histBuffer,histtemp);}
  else {
      units = "(gal))";
      sprintf(histtemp,"%05d",applied*220);
      strcat(histBuffer,histtemp);}
 // strcat(histBuffer,"m3");
  char *fmtValue = histBuffer;
  fmSprite.drawString(fmtValue,flowWidth*0.5, flowHeight*0.5);
  fmSprite.unloadFont();
  fmSprite.loadFont(medium30);
  if (metric == true)
  fmSprite.drawString(units,flowWidth*0.5, flowHeight*0.8);
  fmSprite.unloadFont();
  fmSprite.pushSprite(flowX,flowY);
}

void drawHistoryControls()
{
  int fieldNum = eepromIndex;
  char labelBuffer[20]="";
  char labeltemp[5]="";
//  Serial.println(value);
  sprintf(labeltemp,"%01d",fieldNum);
  strcat(labelBuffer,"Field ");
  strcat(labelBuffer,labeltemp);
  char *fmtValue = labelBuffer;
  ctSprite.fillSprite(c2);
  ctSprite.fillSmoothRoundRect(counterBX-4,counterBY-4,counterWidth-(counterBX*2)+8,counterHeight-(counterBY*2)+8,8,c1,c2);
  ctSprite.fillSmoothRoundRect(counterBX,counterBY,counterWidth-(counterBX*2), counterHeight-(counterBY*2),8,c2,c1);
  
  ctSprite.loadFont(small);
  ctSprite.setTextColor(c1,c2);
  int ypos = 40;
  ctSprite.fillTriangle((counterWidth*0.5)-90, ypos, (counterWidth*0.5)-60, ypos-25, (counterWidth*0.5)-60, ypos+25, c3);
  ctSprite.drawString("prev",(counterWidth*0.5)-114, ypos);
  ctSprite.unloadFont(); 
  ctSprite.loadFont(medium30);
  ctSprite.drawString(fmtValue,counterWidth*0.5, ypos);
  ctSprite.unloadFont();
  ctSprite.loadFont(small);
  ctSprite.fillTriangle((counterWidth*0.5)+90, ypos, (counterWidth*0.5)+60, ypos-25, (counterWidth*0.5)+60, ypos+25, c4);
  ctSprite.drawString("next",(counterWidth*0.5)+114, ypos);
  ctSprite.unloadFont(); 
  
  //Push to Screen
  ctSprite.pushSprite(counterX,counterY);
  }

void drawHistoricTotal()
{     
  char *label = "total";
  //historicTotal
  int value = historicTotal;
  char charBuffer[20]="";
  if (metric == true){
    strcat(charBuffer,label);
    strcat(charBuffer," (m3)");}
  else {
    value = value*220;
    strcat(charBuffer,label);
    strcat(charBuffer," (gal)");}
  int d0;
  int d1;
  int d2;
  int d3;
  int d4;
  int d5;
  int d6;
  d0 = (value/1000000)%10;
  d1 = (value/100000)%10;
  d2 = (value/10000)%10;
  d3 = (value/1000)%10;
  d4 = (value/100)%10;
  d5 = (value/10)%10;
  d6 = value%10;
  trgtSprite.fillSprite(c2);
  trgtSprite.fillSmoothRoundRect(0,counterBY-4,counterWidth-(4*2)+8,counterHeight-(counterBY*2)+8,8,c1,c2);
  trgtSprite.fillSmoothRoundRect(4,counterBY,counterWidth-(4*2), counterHeight-(counterBY*2),8,c2,c1);
  //Draws the 6 digits  +30
  for(int i=0;i<7;i++){
      trgtSprite.fillRectHGradient(4+(0)+(i*36), counterBY+6, 15, 44, TFT_BLACK,grays[2]);
      trgtSprite.fillRectHGradient(4+(15)+(i*36), counterBY+6, 15, 44, grays[2],TFT_BLACK);
      for(int j=0;j<11;j++)
        if(j==5)
        trgtSprite.drawLine(4+(70)+(i*36),counterBY+8+(j*4),4+(77)+(i*36),counterBY+8+(j*4),lines[j]);
        else
        trgtSprite.drawLine(4+(73)+(i*36),counterBY+8+(j*4),4+(77)+(i*36),counterBY+8+(j*4),lines[j]);
      }
    
 
  //90 Angled Lines for bottom text +30
  trgtSprite.drawLine(4+8,counterBY+54,4+8,counterBY+60,c1);
  trgtSprite.drawLine(4+8,counterBY+60,4+24,counterBY+60,c1);
  trgtSprite.drawLine(4+112+36,counterBY+60,4+128+36,counterBY+60,c1);
  trgtSprite.drawLine(4+128+36,counterBY+60,4+128+36,counterBY+54,c1);
  //bottom text
  trgtSprite.loadFont(small);
  trgtSprite.setTextColor(c1,c2);
  trgtSprite.drawString(charBuffer,4+39+48,counterBY+62);
  trgtSprite.setTextColor(c4,c1);
  //sprite.drawString(String(fps),20,80);

  //Digits
  trgtSprite.loadFont(digits);
  trgtSprite.setTextColor(c1,TFT_BLACK);
  trgtSprite.drawString(String(d0),4+10,counterBY+29);
  trgtSprite.drawString(String(d1),4+46,counterBY+29);
  trgtSprite.drawString(String(d2),4+82,counterBY+29);
  trgtSprite.drawString(String(d3),4+118,counterBY+29);
  trgtSprite.drawString(String(d4),4+164,counterBY+29);
  trgtSprite.drawString(String(d5),4+200,counterBY+29);
  trgtSprite.drawString(String(d6),4+236,counterBY+29);
  trgtSprite.unloadFont(); 
  //Push to Screen
  trgtSprite.pushSprite(targetX,targetY);
  }
     