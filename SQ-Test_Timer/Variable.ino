
void drawVariable(int value, int dp, char *label)
{ //h=140w=260
  uint16_t colour = c1;
  int d0;
  int d1;
  int d2;
  int d3;
  int d4;
  d0 = (value/1000)%10;
  d1 = (value/100)%10;
  d2 = (value/10)%10;
  d3 = value%10;
  tmSprite.fillSprite(c2);
  tmSprite.fillSmoothRoundRect(timerBX-4,timerBY-4,timerWidth-(timerBX*2)+8,timerHeight-(timerBY*2)+8,8,c1,c2);
  tmSprite.fillSmoothRoundRect(timerBX,timerBY,timerWidth-(timerBX*2), timerHeight-(timerBY*2),8,c2,c1);

  tmSprite.setTextColor(c1,c2);  // Text colour
  //Draws the 4 digit backgrounds
  for(int i=0;i<4;i++){
    tmSprite.fillRect(timerBX+(5)+(i*62), timerBY+6, 58, 95, TFT_BLACK);
   // tmSprite.fillRectHGradient(timerX+(5)+(i*50), timerY+12, 15, 44, grays[2],TFT_BLACK);
    }
    //90 Angled Lines for bottom text
  tmSprite.drawLine(timerBX+25,timerBY+110,timerBX+25,timerBY+116,c1); //Vert L
  tmSprite.drawLine(timerBX+25,timerBY+116,timerBX+65,timerBY+116,c1); //Hor L
  tmSprite.drawLine(timerWidth-timerBX-65,timerBY+116,timerWidth-timerBX-25,timerBY+116,c1); //Hor R
  tmSprite.drawLine(timerWidth-timerBX-25,timerBY+116,timerWidth-timerBX-25,timerBY+110,c1); //Vert R
  //bottom text
  tmSprite.loadFont(small);
  tmSprite.setTextColor(c1,c2);
  tmSprite.drawString(label,timerWidth/2,timerBY+116);
  tmSprite.setTextColor(c4,c1);
  //sprite.drawString(String(fps),20,80);
  tmSprite.setTextColor(c1,c2);
  tmSprite.unloadFont(); 
  //DP
  if (dp > 0){
    tmSprite.fillSmoothCircle(timerBX+250-(dp*62), (timerHeight)-62, 6, c1, c2);
  }
  //Digits
  tmSprite.loadFont(large70);
  tmSprite.setTextColor(c1,TFT_BLACK);
  tmSprite.drawString(String(d0),timerBX+30,timerBY+55);
  tmSprite.drawString(String(d1),timerBX+92,timerBY+55);
  tmSprite.drawString(String(d2),timerBX+154,timerBY+55);
  tmSprite.drawString(String(d3),timerBX+216,timerBY+55);
  tmSprite.unloadFont(); 
  //Push to Screen
  tmSprite.pushSprite(timerX,timerY);
}

void drawControls(const char* stepValues[])
{
  ctSprite.fillSprite(c2);
  ctSprite.fillSmoothRoundRect(counterBX-4,counterBY-4,counterWidth-(counterBX*2)+8,counterHeight-(counterBY*2)+8,8,c1,c2);
  ctSprite.fillSmoothRoundRect(counterBX,counterBY,counterWidth-(counterBX*2), counterHeight-(counterBY*2),8,c2,c1);
  
  ctSprite.loadFont(small);
  ctSprite.setTextColor(c1,c2);
  int xpos = 0;
  int ypos = 0;
  ctSprite.fillTriangle(xpos+23, 65, xpos+50, 40, xpos+50, 90, c3);
  ctSprite.drawString(stepValues[0],xpos+32, 100);
  xpos += 70;
  ctSprite.fillTriangle(xpos+23, 65, xpos+50, 40, xpos+50, 90, c3);
  ctSprite.drawString(stepValues[1],xpos+32, 100);
  xpos += 80;
  ctSprite.fillTriangle(xpos+50, 65, xpos+20, 40, xpos+20, 90, c4);
  ctSprite.drawString(stepValues[2],xpos+30, 100);
  xpos += 70;
  ctSprite.fillTriangle(xpos+50, 65, xpos+20, 40, xpos+20, 90, c4);
  ctSprite.drawString(stepValues[3],xpos+30, 100);
  ctSprite.unloadFont(); 
  
  //Push to Screen
  ctSprite.pushSprite(counterX,counterY);
  }

void saveBtn(){
  uint16_t colour = c4;
  char *label = "SAVE";
  relaySprite.fillSprite(c2);
  relaySprite.fillSmoothRoundRect(0, 0, relayWidth, relayHeight, 8, colour, c2); //White Rect
  relaySprite.fillSmoothRoundRect(relayBX, relayBY, relayWidth-(relayBX*2), relayHeight-(relayBY*2), 8, c2, colour);

  relaySprite.loadFont(latin);
  relaySprite.setTextColor(c1,c2);
  relaySprite.drawString(label, relayWidth/2, relayHeight/2); // Value in middle

  relaySprite.pushSprite(relayX,relayY);
  // Calculate and return right hand side x coordinate
}
void backBtn(){
  uint16_t colour = c3;
  char *label = "BACK";
  hydSprite.fillSprite(c2);
  hydSprite.fillSmoothRoundRect(0, 0, hydWidth, hydHeight, 8, colour, c2); //White Rect
  hydSprite.fillSmoothRoundRect(hydBX, hydBY, hydWidth-(hydBX*2), hydHeight-(hydBY*2), 8, c2, colour);

  hydSprite.loadFont(latin);
  hydSprite.setTextColor(c1,c2);
  hydSprite.drawString(label, hydWidth/2, hydHeight/2); // Value in middle

  hydSprite.pushSprite(hydX,hydY);
  // Calculate and return right hand side x coordinate
}

void checkEditTouch(){
  uint16_t x, y;
  // See if there's any touch data for us
  if (tft.getTouch(&x, &y))
    {
      if (debounce == 0){
        //ADD OR MINUS  x = [70, 150, 170, 250]
           if ((y > counterY-20) && (y <= 400)) {
                if ((x < 70)){
                    if (wwOn == true){
                        ww-=1;}
                    else if (rateOn == true){
                        appRate-=100;}
                    else if (tkrOn == true){
                        tkrSize-=100;}}
                else if ((x > 70) && (x < 150)){
                    if (wwOn == true){
                        ww-=0.1;}
                    else if (rateOn == true){
                        appRate-=10;}
                    else if (tkrOn == true){
                        tkrSize-=10;}}
                else if ((x > 170) && (x < 250)){
                    if (wwOn == true){
                        ww+=0.1;}
                    else if (rateOn == true){
                        appRate+=10;}
                    else if (tkrOn == true){
                        tkrSize+=10;}}
                else if ((x > 250)){
                    if (wwOn == true){
                        ww+=1;}
                    else if (rateOn == true){
                        appRate+=100;}
                    else if (tkrOn == true){
                        tkrSize+=100;}}
              }
        //BACK OR SAVE
           if ((y > 400)){
             if ((x < (hydWidth+hydX))){ //BACK WW
                  if (wwOn == true){
                      ww = tempWW;}
                  else if (rateOn == true){
                      appRate = tempApp;}
                  else if (tkrOn == true){
                      tkrSize = tempSize;}
                  wwOn = false;
                  rateOn = false;
                  tkrOn = false;
                  modeChanged = true;
                  }
              else if (x > (hydWidth+hydX+20)){ //CONFIRM WW
                  if (wwOn == true){
                      tempWW = ww;}
                  else if (rateOn == true){
                      tempApp = appRate;}
                  else if (tkrOn == true){
                      tempSize = tkrSize;}
                  wwOn = false;
                  rateOn = false;
                  tkrOn = false;
                  modeChanged = true;
                }
              }
          //DIGIT
          debounce = 1;
        }
      }
  else {
    debounce = 0;
    }
  }
