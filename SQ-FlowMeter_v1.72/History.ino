//drawHistory("Field 1", 25);
      //  drawHistoryControls();
void loadHistory(){
  for (int i=0; i<10; i++){
      int value = readIntFromEEPROM(historyEprom[i]);
      appHistory[i] = value;}
  //Serial.println(appHistory);
  historicTotal = readIntFromEEPROM(historyEprom[10]);      
  }
void drawHistory()
{ //h=140w=260
  //Get Value
  int app = appHistory[eepromIndex];
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
      sprintf(histtemp,"%03d",app);
      strcat(histBuffer,histtemp);}
  else {
      units = "(gal))";
      sprintf(histtemp,"%05d",app*220);
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
  sprintf(labeltemp,"%01d",fieldNum+1);
  strcat(labelBuffer,labeltemp);
  strcat(labelBuffer,"/10");
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
  //historicTotal
 // uint32_t value = historicTotal;
  char *label = "all time";
  char charBuffer[20]="";
  if (metric == true){
    strcat(charBuffer,label);
    strcat(charBuffer," (m3)");}
  else {
    strcat(charBuffer,label);
    strcat(charBuffer," (gal)");}
  uint16_t colour = c1;
  uint16_t textColour = GREY;
  trgtSprite.fillSprite(c2);
  trgtSprite.fillSmoothRoundRect(targetBX-4,targetBY-4,targetWidth-(targetBX*2)+8,targetHeight-(targetBY*2)+8,8,colour,c2);
  trgtSprite.fillSmoothRoundRect(targetBX,targetBY,targetWidth-(targetBX*2), targetHeight-(targetBY*2),8,c2,colour);
  
  //90 Angled Lines for bottom text
  trgtSprite.drawLine(targetBX+12,targetBY+36,targetBX+12,targetBY+42,textColour);
  trgtSprite.drawLine(targetBX+12,targetBY+42,targetBX+28,targetBY+42,textColour);
  trgtSprite.drawLine(targetBX+108+36,targetBY+42,targetBX+124+36,targetBY+42,textColour);
  trgtSprite.drawLine(targetBX+124+36,targetBY+42,targetBX+124+36,targetBY+36,textColour);
  //bottom text
  trgtSprite.loadFont(small);
  trgtSprite.setTextColor(textColour,c2);
  trgtSprite.drawString(charBuffer,(targetWidth/2),targetBY+44);
  trgtSprite.setTextColor(c4,c1);
  //sprite.drawString(String(fps),20,80);
 
  //Digits
  char trgtBuffer[60]="";
  char trgttemp[35]="";
  if (metric == true){
      sprintf(trgttemp,"%08d",historicTotal);
      strcat(trgtBuffer,trgttemp);}
  else{
      sprintf(trgttemp,"%08d",historicTotal*220);
      strcat(trgtBuffer,trgttemp);}
  char *fmtValue = trgtBuffer;
  trgtSprite.loadFont(medium30);
  trgtSprite.setTextColor(textColour,c2);
  trgtSprite.drawString(fmtValue,(targetWidth/2),targetBY+22);
  trgtSprite.unloadFont(); 
  //Push to Screen
  trgtSprite.pushSprite(targetX,targetY);
  }
     