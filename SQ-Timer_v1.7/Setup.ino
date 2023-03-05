void drawCalibration()
{ //h=140w=260
  fmSprite.fillSprite(c2);
 // fmSprite.loadFont(latin);
  //fmSprite.setTextColor(c1,c2);
 // fmSprite.fillSmoothRoundRect(flowBX-4,flowBY-4,flowWidth-(flowBX*2)+8,flowHeight-(flowBY*2)+8,8,c1,c2);
  //fmSprite.fillSmoothRoundRect(flowBX,flowBY,flowWidth-(flowBX*2), flowHeight-(flowBY*2),8,c2,c1);
  //fmSprite.drawString("CHANGE UNITS",flowWidth*0.5, flowHeight*0.5);
  //fmSprite.unloadFont();
  fmSprite.pushSprite(flowX,flowY);
}

void drawUnitSelection()
{
  ctSprite.fillSprite(c2);
  ctSprite.loadFont(latin);
  ctSprite.setTextColor(c1,c2);
  uint16_t mc = c1;
  uint16_t ic = c4;
  if (metric == true){
    mc = c4;
    ic = c1;
  }

  //Btn 1 METRIC
  int width = (counterWidth/2)-8;
  int btnOneX = 0;
  ctSprite.fillSmoothRoundRect(btnOneX,      counterBY-4,   width,   counterHeight-(counterBY*2)+8,8,mc,c2);
  ctSprite.fillSmoothRoundRect(btnOneX+4,    counterBY,     width-8,   counterHeight-(counterBY*2),8,c2,mc);
  ctSprite.drawString("m3/ha",counterWidth*0.25, 40);
  //Btn 2 IMP
  int btnTwoX = (counterWidth/2)+4;
  ctSprite.fillSmoothRoundRect(btnTwoX,     counterBY-4,   width,   counterHeight-(counterBY*2)+8,8,ic,c2);
  ctSprite.fillSmoothRoundRect(btnTwoX+4,   counterBY,     width-8,   counterHeight-(counterBY*2),8,c2,ic);
  ctSprite.drawString("gal/ac",counterWidth*0.75, 40);
  ctSprite.unloadFont(); 
  
  //Push to Screen
  ctSprite.pushSprite(counterX,counterY);
  }

void tkrBtn()
{
  uint16_t colour = c1;
  uint16_t textColour = GREY;
  char *label = "tkr size";
  trgtSprite.fillSprite(c2);
  trgtSprite.fillSmoothRoundRect(targetBX-4,targetBY-4,targetWidth-(targetBX*2)+8,targetHeight-(targetBY*2)+8,8,colour,c2);
  trgtSprite.fillSmoothRoundRect(targetBX,targetBY,targetWidth-(targetBX*2), targetHeight-(targetBY*2),8,c2,colour);
  
  //90 Angled Lines for bottom text
  trgtSprite.drawLine(targetBX+18,targetBY+36,targetBX+18,targetBY+42,textColour);
  trgtSprite.drawLine(targetBX+18,targetBY+42,targetBX+34,targetBY+42,textColour);
  trgtSprite.drawLine(targetBX+102+36,targetBY+42,targetBX+118+36,targetBY+42,textColour);
  trgtSprite.drawLine(targetBX+118+36,targetBY+42,targetBX+118+36,targetBY+36,textColour);
  //bottom text
  trgtSprite.loadFont(small);
  trgtSprite.setTextColor(textColour,c2);
  trgtSprite.drawString(label,targetBX+targetWidth/2,targetBY+44);
  trgtSprite.setTextColor(c4,c1);
  //sprite.drawString(String(fps),20,80);
 
//Digits
  char trgtBuffer[20]="";
  char trgttemp[5]="";
  float tempSize = tkrSize;
  if (metric == true){
    sprintf(trgttemp,"%.1f",tempSize);
    strcat(trgtBuffer,trgttemp);
    strcat(trgtBuffer," m3");
  }
  else{
    sprintf(trgttemp,"%04d",(tempSize*220));
    strcat(trgtBuffer,trgttemp);
    strcat(trgtBuffer," gals");
    } 
  char *fmtValue = trgtBuffer;
  trgtSprite.loadFont(medium30);
  trgtSprite.setTextColor(textColour,c2);
  trgtSprite.drawString(fmtValue,targetBX+(targetWidth/2),targetBY+22);
  trgtSprite.unloadFont(); 
  //Push to Screen
  trgtSprite.pushSprite(targetX,targetY);
  // Calculate and return right hand side x coordinate
}

