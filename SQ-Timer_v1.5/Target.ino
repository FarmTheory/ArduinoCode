void calcTarget(){
float tkrSizeF = tkrSize*1.0;
float appRateF = appRate*1.0;
float acPerLoad = tkrSizeF/appRateF;
float haPerLoad = acPerLoad/2.48;
float mPerLoad = (haPerLoad*10000)/ww;
float kmPerLoad = mPerLoad/1000;
targetSpeed = kmPerLoad * (3600.0/prevLoadTime);
//Galspermin for counter
galsPerMin = tkrSizeF*(60.0/prevLoadTime);
Serial.print("Gals/Min");
Serial.println(galsPerMin);
//drawTS();
}

void drawTarget(float value)
{
  uint16_t colour = c1;
  uint16_t textColour = GREY;
  char *label = "estimate";
  if(targetOn == true){
    colour = c4;
    textColour = c1;
    label = "calibrated";
    }
  else if (targetOn == false){
    colour = GREY; 
  }
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
  sprintf(trgttemp,"%3.1f",value);
  strcat(trgtBuffer,trgttemp);
  strcat(trgtBuffer,"kph");
  char *fmtValue = trgtBuffer;
  trgtSprite.loadFont(medium30);
  trgtSprite.setTextColor(textColour,c2);
  trgtSprite.drawString(fmtValue,targetBX+targetWidth/2,targetBY+22);
  trgtSprite.unloadFont(); 
  //Push to Screen
  trgtSprite.pushSprite(targetX,targetY);
  }