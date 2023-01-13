//drawHistory("Field 1", 25);
      //  drawHistoryControls();

void drawHistory(char *label, int applied)
{ //h=140w=260
  fmSprite.fillSprite(c2);
  fmSprite.loadFont(medium40);
  fmSprite.setTextColor(c1,c2);
  fmSprite.fillSmoothRoundRect(flowBX-4,flowBY-4,flowWidth-(flowBX*2)+8,flowHeight-(flowBY*2)+8,8,c1,c2);
  fmSprite.fillSmoothRoundRect(flowBX,flowBY,flowWidth-(flowBX*2), flowHeight-(flowBY*2),8,c2,c1);
  fmSprite.drawString(label,flowWidth*0.5, flowHeight*0.2);
  char histBuffer[20]="";
  char histtemp[5]="";
//  Serial.println(value);
  sprintf(histtemp,"%03d",applied);
  strcat(histBuffer,histtemp);
  char *fmtValue = histBuffer;
  fmSprite.drawString(fmtValue,flowWidth*0.5, flowHeight*0.6);
  fmSprite.unloadFont();
  fmSprite.pushSprite(flowX,flowY);
}

void drawHistoryControls()
{
  ctSprite.fillSprite(c2);
  ctSprite.fillSmoothRoundRect(counterBX-4,counterBY-4,counterWidth-(counterBX*2)+8,counterHeight-(counterBY*2)+8,8,c1,c2);
  ctSprite.fillSmoothRoundRect(counterBX,counterBY,counterWidth-(counterBX*2), counterHeight-(counterBY*2),8,c2,c1);
  
  ctSprite.loadFont(small);
  ctSprite.setTextColor(c1,c2);
  int xpos = 50;
  int ypos = 40;
  ctSprite.fillTriangle(xpos+23, ypos, xpos+50, ypos-25, xpos+50, ypos+25, c3);
  ctSprite.drawString("prev",xpos+32, ypos);
  xpos += 100;
  ctSprite.fillTriangle(xpos+50, ypos, xpos+20, ypos-25, xpos+20, ypos+25, c4);
  ctSprite.drawString("next",xpos+30, ypos);
  ctSprite.unloadFont(); 
  
  //Push to Screen
  ctSprite.pushSprite(counterX,counterY);
  }

     