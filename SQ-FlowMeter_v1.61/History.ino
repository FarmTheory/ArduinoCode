//drawHistory("Field 1", 25);
      //  drawHistoryControls();

void drawHistory()
{ //h=140w=260
  //Get Value
  int applied = appHistory[appIndex];
  fmSprite.fillSprite(c2);
  fmSprite.loadFont(large70);
  fmSprite.setTextColor(c1,c2);
  fmSprite.fillSmoothRoundRect(flowBX-4,flowBY-4,flowWidth-(flowBX*2)+8,flowHeight-(flowBY*2)+8,8,c1,c2);
  fmSprite.fillSmoothRoundRect(flowBX,flowBY,flowWidth-(flowBX*2), flowHeight-(flowBY*2),8,c2,c1);
  char histBuffer[20]="";
  char histtemp[5]="";
//  Serial.println(value);
  sprintf(histtemp,"%03d",applied);
  strcat(histBuffer,histtemp);
 // strcat(histBuffer,"m3");
  char *fmtValue = histBuffer;
  fmSprite.drawString(fmtValue,flowWidth*0.5, flowHeight*0.5);
  fmSprite.unloadFont();
  fmSprite.loadFont(medium30);
  fmSprite.drawString("(m3)",flowWidth*0.5, flowHeight*0.8);
  fmSprite.unloadFont();
  fmSprite.pushSprite(flowX,flowY);
}

void drawHistoryControls()
{
  int fieldNum = appIndex+1;
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

     