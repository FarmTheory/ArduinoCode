
void resetCounter(){
  applied = 0;
  drawCounter(applied, "total applied");
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

void drawCounter(int value, char *label)
{
  int d0;
  int d1;
  int d2;
  int d3;
  int d4;
  d0 = (value/10000)%10;
  d1 = (value/1000)%10;
  d2 = (value/100)%10;
  d3 = (value/10)%10;
  d4 = value%10;
  ctSprite.fillSprite(c2);
  ctSprite.fillSmoothRoundRect(counterBX-4,counterBY-4,counterWidth-(counterBX*2)+8,counterHeight-(counterBY*2)+8,8,c1,c2);
  ctSprite.fillSmoothRoundRect(counterBX,counterBY,counterWidth-(counterBX*2), counterHeight-(counterBY*2),8,c2,c1);
  //Draws the 5 digits
  for(int i=0;i<5;i++){
    ctSprite.fillRectHGradient(counterBX+(20)+(i*36), counterBY+6, 15, 44, TFT_BLACK,grays[2]);
    ctSprite.fillRectHGradient(counterBX+(35)+(i*36), counterBY+6, 15, 44, grays[2],TFT_BLACK);
    if (i < 4) { //Skip final digit ticks
      for(int j=0;j<11;j++)
      if(j==5)
      ctSprite.drawLine(counterBX+(40)+(i*36),counterBY+8+(j*4),counterBX+(47)+(i*36),counterBY+8+(j*4),lines[j]);
      else
      ctSprite.drawLine(counterBX+(43)+(i*36),counterBY+8+(j*4),counterBX+(47)+(i*36),counterBY+8+(j*4),lines[j]);
      }
    }
  // Final Digit ticks
  for(int j=0;j<11;j++)
  if(j==longLine)
  ctSprite.drawLine(counterBX+(40)+(4*36),counterBY+8+(j*4),counterBX+(47)+(4*36),counterBY+8+(j*4),lines[j]);
  else
  ctSprite.drawLine(counterBX+(43)+(4*36),counterBY+8+(j*4),counterBX+(47)+(4*36),counterBY+8+(j*4),lines[j]);
  //90 Angled Lines for bottom text
  ctSprite.drawLine(counterBX+28,counterBY+54,counterBX+28,counterBY+60,c1);
  ctSprite.drawLine(counterBX+28,counterBY+60,counterBX+44,counterBY+60,c1);
  ctSprite.drawLine(counterBX+132+36,counterBY+60,counterBX+148+36,counterBY+60,c1);
  ctSprite.drawLine(counterBX+148+36,counterBY+60,counterBX+148+36,counterBY+54,c1);
  //bottom text
  ctSprite.loadFont(small);
  ctSprite.setTextColor(c1,c2);
  ctSprite.drawString(label,counterBX+89+18,counterBY+62);
  ctSprite.setTextColor(c4,c1);
  //sprite.drawString(String(fps),20,80);
  //RESET
  ctSprite.fillSmoothCircle(counterBX+148+36+36+10, (counterHeight/2)-10, 10, c3, c2);
  ctSprite.loadFont(small);
  ctSprite.setTextColor(c1,c2);
  ctSprite.drawString("RESET",counterBX+148+36+36+10,counterBY+58);
  ctSprite.unloadFont(); 
  //Digits
  ctSprite.loadFont(digits);
  ctSprite.setTextColor(c1,TFT_BLACK);
  ctSprite.drawString(String(d0),counterBX+30,counterBY+29);
  ctSprite.drawString(String(d1),counterBX+66,counterBY+29);
  ctSprite.drawString(String(d2),counterBX+102,counterBY+29);
  ctSprite.drawString(String(d3),counterBX+138,counterBY+29);
  ctSprite.drawString(String(d4),counterBX+174,counterBY+29);
  ctSprite.unloadFont(); 
  //Push to Screen
  ctSprite.pushSprite(counterX,counterY);
  }