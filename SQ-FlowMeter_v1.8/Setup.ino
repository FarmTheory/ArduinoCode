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
  //BTN 1 - AREA
  uint16_t colour = c4;
  char *label = "m3/ha";
  char *labelTwo = "(gal/ac)";
  if(areaMetric == false){
    colour = c3;
    label = "gal/ac";
    labelTwo = "(m3/ha)";}
  //Btn 1 AREA
  int width = (counterWidth/2)-8;
  int btnOneX = 0;
  ctSprite.fillSmoothRoundRect(btnOneX,      counterBY-4,   width,   counterHeight-(counterBY*2)+8,8,colour,c2);
  ctSprite.fillSmoothRoundRect(btnOneX+4,    counterBY,     width-8,   counterHeight-(counterBY*2),8,c2,colour);
  ctSprite.drawString(label, counterWidth*0.25, (counterHeight/2)-10); // Value in middle
  ctSprite.setTextColor(GREY,c2);
  ctSprite.drawString(labelTwo, counterWidth*0.25, (counterHeight/2)+20); // Value in middle
  //BTN 2 - SPEED
  char *spLabel = "kph";
  char *spLabelTwo = "(mph)";
  colour = c4;
  ctSprite.setTextColor(c1,c2);
  if(speedMetric == false){
    colour = c3;
    spLabel = "mph";
    spLabelTwo = "(kph)";}
  int btnTwoX = (counterWidth/2)+4;
  ctSprite.fillSmoothRoundRect(btnTwoX,     counterBY-4,   width,   counterHeight-(counterBY*2)+8,8,colour,c2);
  ctSprite.fillSmoothRoundRect(btnTwoX+4,   counterBY,     width-8,   counterHeight-(counterBY*2),8,c2,colour);
  ctSprite.drawString(spLabel, counterWidth*0.75, (counterHeight/2)-10); // Value in middle
  ctSprite.setTextColor(GREY,c2);
  ctSprite.drawString(spLabelTwo, counterWidth*0.75, (counterHeight/2)+20); // Value in middle
  ctSprite.unloadFont(); 
  
  //Push to Screen
  ctSprite.pushSprite(counterX,counterY);
  }

void drawVersion(){
  uint16_t colour = GREY;
  char verBuffer[20]="";
  char vertemp[5]="";
  strcat(verBuffer,"version: ");
  sprintf(vertemp,"%.2f",version);
  strcat(verBuffer,vertemp);
  char *label = verBuffer;
  relaySprite.fillSprite(c2);
  relaySprite.fillSmoothRoundRect(0, 0, relayWidth, relayHeight, 8, colour, c2); //White Rect
  relaySprite.fillSmoothRoundRect(relayBX, relayBY, relayWidth-(relayBX*2), relayHeight-(relayBY*2), 8, c2, colour);
  relaySprite.setTextColor(GREY,c2);
  relaySprite.drawString(label, relayWidth/2, (relayHeight/2)); // Value in middle
  relaySprite.pushSprite(relayX,relayY);
  // Calculate and return right hand side x coordinate
}
