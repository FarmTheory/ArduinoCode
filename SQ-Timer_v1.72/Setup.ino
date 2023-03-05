
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
  if (areaMetric == true){
    sprintf(trgttemp,"%.1f",tkrSize);
    strcat(trgtBuffer,trgttemp);
    strcat(trgtBuffer," m3");
  }
  else{
    int tempSize = tkrSize;
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

void drawDelaySelection()
{ 
  uint16_t textColour = GREY;
  fmSprite.fillSprite(c2);
  fmSprite.loadFont(latin);
  fmSprite.setTextColor(c1,c2);
  //BTN 1 - AREA
  uint16_t off_colour = c4;
  uint16_t on_colour = c3;
  char *label = "off";
  char *labelTwo = "10secs";
  if(endDelay == true){
    off_colour = c3;
    on_colour= c4;}
  //Btn 1 OFF
  int width = (counterWidth/2)-8;
  int btnOneX = 0;
  int y = flowBY+58;
  fmSprite.fillSmoothRoundRect(btnOneX,      y-4,   width,   counterHeight-(counterBY*2)+8,8,off_colour,c2);
  fmSprite.fillSmoothRoundRect(btnOneX+4,    y,     width-8,   counterHeight-(counterBY*2),8,c2,off_colour);
  fmSprite.drawString(label, counterWidth*0.25, y+25); // Value in middle
    //90 Angled Lines for bottom text
  //fmSprite.drawLine(btnOneX+18,y+46,btnOneX+18,y+52,textColour);
 // fmSprite.drawLine(btnOneX+18,y+52,btnOneX+34,y+52,textColour);
 // fmSprite.drawLine(btnOneX+102+4,y+52,btnOneX+118+4,y+52,textColour);
 // fmSprite.drawLine(btnOneX+118+4,y+52,btnOneX+118+4,y+46,textColour);
  //bottom text
  fmSprite.loadFont(small);
  fmSprite.setTextColor(textColour,c2);
  fmSprite.drawString("vent delay",btnOneX+(width/2),y+54);
  fmSprite.setTextColor(c4,c1);

  //BTN 2 10 SECS
  fmSprite.loadFont(latin);
  fmSprite.setTextColor(c1,c2);
  int btnTwoX = (counterWidth/2)+4;
  fmSprite.fillSmoothRoundRect(btnTwoX,     y-4,   width,   counterHeight-(counterBY*2)+8,8,on_colour,c2);
  fmSprite.fillSmoothRoundRect(btnTwoX+4,   y,     width-8,   counterHeight-(counterBY*2),8,c2,on_colour);
  fmSprite.drawString(labelTwo, counterWidth*0.75, y+25); // Value in middle
    //90 Angled Lines for bottom text
 // fmSprite.drawLine(btnTwoX+18,y+46,btnTwoX+18,y+52,textColour);
 // fmSprite.drawLine(btnTwoX+18,y+52,btnTwoX+34,y+52,textColour);
  //fmSprite.drawLine(btnTwoX+102+4,y+52,btnTwoX+118+4,y+52,textColour);
 // fmSprite.drawLine(btnTwoX+118+4,y+52,btnTwoX+118+4,y+46,textColour);
  //bottom text
  fmSprite.loadFont(small);
  fmSprite.setTextColor(textColour,c2);
  fmSprite.drawString("vent delay",btnTwoX+(width/2),y+54);
  fmSprite.setTextColor(c4,c1);
  fmSprite.unloadFont(); 
  //Push to Screen
  fmSprite.pushSprite(flowX,flowY);
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
//  relaySprite.fillSmoothRoundRect(0, 0, relayWidth, relayHeight, 8, colour, c2); //White Rect
  //relaySprite.fillSmoothRoundRect(relayBX, relayBY, relayWidth-(relayBX*2), relayHeight-(relayBY*2), 8, c2, colour);
  relaySprite.setTextColor(GREY,c2);
  relaySprite.drawString(label, relayWidth/2, (relayHeight/2)+30); // Value in middle
  relaySprite.pushSprite(relayX,relayY);
  // Calculate and return right hand side x coordinate
}