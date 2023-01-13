void createFlowMeter()
{
  uint16_t colour = c1;
  char *label = "flow meter";
  float M_SIZE = 1.1;
  if(flowOn == true){
    colour = c1;
    label = "running";
    }
  fmSprite.fillSprite(c2);
  //sprite.fillSmoothRoundRect(0,0,(left*2)+width,(fromTop*2)+heigth,8,c1,c2);
 // sprite.fillSmoothRoundRect(left,fromTop,width,heigth,8,c2,c1);
  fmSprite.fillSmoothRoundRect(0, 0, flowWidth, flowHeight, 8, colour, c2); //White Rect
  fmSprite.fillSmoothRoundRect(flowBX, flowBY, flowWidth-(flowBX*2), flowHeight-(flowBY*2), 8, c2, colour);
  fmSprite.setTextColor(c1,c2);  // Text colour
  // Draw ticks every 5 degrees from -50 to +50 degrees (100 deg. FSD swing)
  for (int i = -50; i < 51; i += 5) {
        // Long scale tick length
        int tl = 15;
        // Coodinates of tick to draw
        float sx = cos((i - 90) * 0.0174532925);
        float sy = sin((i - 90) * 0.0174532925);
        uint16_t x0 = sx * (M_SIZE*100 + tl) + M_SIZE*120;
        uint16_t y0 = sy * (M_SIZE*100 + tl) + M_SIZE*140;
        uint16_t x1 = sx * M_SIZE*100 + M_SIZE*120;
        uint16_t y1 = sy * M_SIZE*100 + M_SIZE*140;

        // Coordinates of next tick for zone fill
        float sx2 = cos((i + 5 - 90) * 0.0174532925);
        float sy2 = sin((i + 5 - 90) * 0.0174532925);
        int x2 = sx2 * (M_SIZE*100 + tl) + M_SIZE*120;
        int y2 = sy2 * (M_SIZE*100 + tl) + M_SIZE*140;
        int x3 = sx2 * M_SIZE*100 + M_SIZE*120;
        int y3 = sy2 * M_SIZE*100 + M_SIZE*140;

        // ORANGE zone limits
        if (i >= -50 && i < 0) {
          fmSprite.fillTriangle(flowBX+x0, flowBY+y0, flowBX+x1, flowBY+y1, flowBX+x2, flowBY+y2, GREY);
          fmSprite.fillTriangle(flowBX+x1, flowBY+y1, flowBX+x2, flowBY+y2, flowBX+x3, flowBY+y3, GREY);
        }
        // Green zone limits
        if (i >= -25 && i < 25) {
          fmSprite.fillTriangle(flowBX+x0, flowBY+y0, flowBX+x1, flowBY+y1, flowBX+x2, flowBY+y2, GREEN);
          fmSprite.fillTriangle(flowBX+x1, flowBY+y1, flowBX+x2, flowBY+y2, flowBX+x3, flowBY+y3, GREEN);
        }
        // Orange zone limits
        if (i >= 25 && i < 50) {
          fmSprite.fillTriangle(flowBX+x0, flowBY+y0, flowBX+x1, flowBY+y1, flowBX+x2, flowBY+y2, ORANGE);
          fmSprite.fillTriangle(flowBX+x1, flowBY+y1, flowBX+x2, flowBY+y2, flowBX+x3, flowBY+y3, ORANGE);
        }
        // Short scale tick length
        if (i % 25 != 0) tl = 8;
        // Recalculate coords incase tick lenght changed
        x0 = sx * (M_SIZE*100 + tl) + M_SIZE*120;
        y0 = sy * (M_SIZE*100 + tl) + M_SIZE*140;
        x1 = sx * M_SIZE*100 + M_SIZE*120;
        y1 = sy * M_SIZE*100 + M_SIZE*140;
        // Draw tick
        fmSprite.drawLine(flowBX+x0, flowBY+y0, flowBX+x1, flowBY+y1, c1);
        // Check if labels should be drawn, with position tweaks
        fmSprite.loadFont(small);
        fmSprite.setTextColor(c1, c2);
        if (i % 25 == 0) {
          // Calculate label positions
          x0 = sx * (M_SIZE*100 + tl + 10) + M_SIZE*120;
          y0 = sy * (M_SIZE*100 + tl + 10) + M_SIZE*140;
          if(metric == true){
              switch (i / 25) {
                case -2: fmSprite.drawCentreString("0", flowBX+x0, flowBY+y0 - 12, 2); break;
                case -1: fmSprite.drawCentreString("60", flowBX+x0, flowBY+y0 - 9, 2); break;
                case 0: fmSprite.drawCentreString("120", flowBX+x0, flowBY+y0 - 7, 2); break;
                case 1: fmSprite.drawCentreString("180", flowBX+x0, flowBY+y0 - 9, 2); break;
                case 2: fmSprite.drawCentreString("240", flowBX+x0, flowBY+y0 - 12, 2); break;
              }
              }
          else{
            switch (i / 25) {
                case -2: fmSprite.drawCentreString("0", flowBX+x0, flowBY+y0 - 12, 2); break;
                case -1: fmSprite.drawCentreString("13k", flowBX+x0, flowBY+y0 - 9, 2); break;
                case 0: fmSprite.drawCentreString("16k", flowBX+x0, flowBY+y0 - 7, 2); break;
                case 1: fmSprite.drawCentreString("40k", flowBX+x0, flowBY+y0 - 9, 2); break;
                case 2: fmSprite.drawCentreString("52k", flowBX+x0, flowBY+y0 - 12, 2); break;
              }
            }
        }
        fmSprite.unloadFont();
        // Now draw the arc of the scale
        sx = cos((i + 5 - 90) * 0.0174532925);
        sy = sin((i + 5 - 90) * 0.0174532925);
        x0 = sx * M_SIZE*100 + M_SIZE*120;
        y0 = sy * M_SIZE*100 + M_SIZE*140;
        // Draw scale arc, don't draw the last part
        if (i < 50) fmSprite.drawLine(flowBX+x0, flowBY+y0, flowBX+x1, flowBY+y1, TFT_BLACK);
      }
  fmSprite.loadFont(small);
  if(metric == true){
    fmSprite.drawString("m3/hr", flowBX+225, flowBY+110); // Units at bottom right
    }
  else{
    fmSprite.drawString("gal/hr", flowBX+225, flowBY+110); // Units at bottom right
    }
  fmSprite.unloadFont(); 
  fmSprite.loadFont(small);
  fmSprite.drawString("flow", flowBX+30, flowBY+110); // Comment out to avoid font 4
  fmSprite.unloadFont(); 
 // tft.drawRect(fmleft+5, fmTop+3, M_SIZE*230, M_SIZE*119, c1); // Draw bezel line
  drawFlowMeter(1, 0); // Put meter needle at 0
}

int getFlow(){
    flowAnalog = analogRead(flowPin);
    //Serial.print("Analog: ");
    //Serial.println(flowAnalog);
    int tempFlow = map(flowAnalog, analog1, analog2, volume1, volume2);
  //  Serial.print("Flow: ");
   // Serial.println(tempFlow);
    if (tempFlow < 0){
      tempFlow = 0;
      }
    return tempFlow;
    }

void drawFlowMeter(int value, byte ms_delay)
{
  float M_SIZE = 1.1;
  uint16_t colour = c4;
  uint16_t textColour = c1;
  char *label = "estimate";
  if(flowOn == true){
    textColour = c1;
    }
  else if (flowOn == false){
    colour = GREY; 
  }

  if (value < -10) value = -10; // Limit value to emulate needle end stops
  if (value > 210) value = 210;

  // Move the needle until new value reached
  while (!(value == old_analog)) {
    if (old_analog < value) old_analog++;
    else old_analog--;

    if (ms_delay == 0) old_analog = value; // Update immediately if delay is 0

    float sdeg = map(old_analog, -20, 220, -150, -30); // Map value to angle
    // Calcualte tip of needle coords
    float sx = cos(sdeg * 0.0174532925);
    float sy = sin(sdeg * 0.0174532925);

    // Calculate x delta of needle start (does not start at pivot point)
    float tx = tan((sdeg + 90) * 0.0174532925);

    // Erase old needle image
    fmSprite.drawLine(flowBX+M_SIZE*(120 + 20 * ltx - 1), flowBY+M_SIZE*(140 - 30), flowBX+osx - 1, flowBY+osy, c2);
    fmSprite.drawLine(flowBX+M_SIZE*(120 + 20 * ltx), flowBY+M_SIZE*(140 - 30), flowBX+osx, flowBY+osy, c2);
    fmSprite.drawLine(flowBX+M_SIZE*(120 + 20 * ltx + 1), flowBY+M_SIZE*(140 - 30), flowBX+osx + 1, flowBY+osy, c2);
    // Re-plot text under needle
    //fmSprite.setTextColor(c1, c2);
   // fmSprite.loadFont(small);
   // fmSprite.drawString("flowrate", flowBX+(flowWidth/2), flowBY+70); // // Comment out to avoid font 4
   // fmSprite.unloadFont(); 
    //Digits
    char flowBuffer[20]="";
    char flowtemp[5]="";
    char *fmtValue;
    //  Serial.println(value);
    if(metric == true){
        fmSprite.loadFont(large60);
        sprintf(flowtemp,"%03d",value);
        strcat(flowBuffer,flowtemp);
        fmtValue = flowBuffer;}
    else {
        fmSprite.loadFont(medium40);
        sprintf(flowtemp,"%05d",value*220);
        strcat(flowBuffer,flowtemp);
        fmtValue = flowBuffer;}
    fmSprite.setTextColor(textColour,c2);
    fmSprite.fillRect(flowBX-70+flowWidth/2, flowBY+70, 120, 50, c2);
    fmSprite.drawString(String(fmtValue),flowBX-10+flowWidth/2,flowBY+100);
    fmSprite.unloadFont(); 
    // Store new needle end coords for next erase
    ltx = tx;
    osx = M_SIZE*(sx * 98 + 120);
    osy = M_SIZE*(sy * 98 + 140);

    // Draw the needle in the new postion, magenta makes needle a bit bolder
    // draws 3 lines to thicken needle
    fmSprite.drawLine(flowBX+M_SIZE*(120 + 20 * ltx - 1), flowBY+M_SIZE*(140 - 30), flowBX+osx - 1, flowBY+osy, TFT_RED);
    fmSprite.drawLine(flowBX+M_SIZE*(120 + 20 * ltx), flowBY+M_SIZE*(140 - 30), flowBX+osx, flowBY+osy, TFT_RED);
    fmSprite.drawLine(flowBX+M_SIZE*(120 + 20 * ltx + 1), flowBY+M_SIZE*(140 - 30), flowBX+osx + 1, flowBY+osy, TFT_RED);
    // Slow needle down slightly as it approaches new postion
    if (abs(old_analog - value) < 10) ms_delay += ms_delay / 5;
    // Wait before next update
   // delay(ms_delay);
    fmSprite.pushSprite(flowX,flowY);
  }
}