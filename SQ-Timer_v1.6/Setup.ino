void drawCalibration()
{ //h=140w=260
  tmSprite.fillSprite(c2);
 // fmSprite.loadFont(latin);
  //fmSprite.setTextColor(c1,c2);
 // fmSprite.fillSmoothRoundRect(flowBX-4,flowBY-4,flowWidth-(flowBX*2)+8,flowHeight-(flowBY*2)+8,8,c1,c2);
  //fmSprite.fillSmoothRoundRect(flowBX,flowBY,flowWidth-(flowBX*2), flowHeight-(flowBY*2),8,c2,c1);
  //fmSprite.drawString("CHANGE UNITS",flowWidth*0.5, flowHeight*0.5);
  //fmSprite.unloadFont();
  tmSprite.pushSprite(timerX,timerY);
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
  ctSprite.drawString("METRIC",counterWidth*0.25, 40);
  //Btn 2 IMP
  int btnTwoX = (counterWidth/2)+4;
  ctSprite.fillSmoothRoundRect(btnTwoX,     counterBY-4,   width,   counterHeight-(counterBY*2)+8,8,ic,c2);
  ctSprite.fillSmoothRoundRect(btnTwoX+4,   counterBY,     width-8,   counterHeight-(counterBY*2),8,c2,ic);
  ctSprite.drawString("IMPERIAL",counterWidth*0.75, 40);
  ctSprite.unloadFont(); 
  
  //Push to Screen
  ctSprite.pushSprite(counterX,counterY);
  }

