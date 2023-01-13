
void flowMeter()
{
  fmSprite.fillSprite(c2);
  //sprite.fillSmoothRoundRect(0,0,(left*2)+width,(fromTop*2)+heigth,8,c1,c2);
 // sprite.fillSmoothRoundRect(left,fromTop,width,heigth,8,c2,c1);
  fmSprite.fillSmoothRoundRect(0, 0, (fmleft*2)+fmwidth-6, (fmTop*2)+fmheight-8, 8, c1, c2);
  fmSprite.fillSmoothRoundRect(fmleft, fmTop, fmwidth-6, fmheight-8, 8, c2, c1);
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
          fmSprite.fillTriangle(fmleft+x0, fmTop+y0, fmleft+x1, fmTop+y1, fmleft+x2, fmTop+y2, GREY);
          fmSprite.fillTriangle(fmleft+x1, fmTop+y1, fmleft+x2, fmTop+y2, fmleft+x3, fmTop+y3, GREY);
        }
        // Green zone limits
        if (i >= -25 && i < 25) {
          fmSprite.fillTriangle(fmleft+x0, fmTop+y0, fmleft+x1, fmTop+y1, fmleft+x2, fmTop+y2, c4);
          fmSprite.fillTriangle(fmleft+x1, fmTop+y1, fmleft+x2, fmTop+y2, fmleft+x3, fmTop+y3, c4);
        }
        // Orange zone limits
        if (i >= 25 && i < 50) {
          fmSprite.fillTriangle(fmleft+x0, fmTop+y0, fmleft+x1, fmTop+y1, fmleft+x2, fmTop+y2, ORANGE);
          fmSprite.fillTriangle(fmleft+x1, fmTop+y1, fmleft+x2, fmTop+y2, fmleft+x3, fmTop+y3, ORANGE);
        }
        // Short scale tick length
        if (i % 25 != 0) tl = 8;
        // Recalculate coords incase tick lenght changed
        x0 = sx * (M_SIZE*100 + tl) + M_SIZE*120;
        y0 = sy * (M_SIZE*100 + tl) + M_SIZE*140;
        x1 = sx * M_SIZE*100 + M_SIZE*120;
        y1 = sy * M_SIZE*100 + M_SIZE*140;
        // Draw tick
        fmSprite.drawLine(fmleft+x0, fmTop+y0, fmleft+x1, fmTop+y1, c1);
        // Check if labels should be drawn, with position tweaks
        fmSprite.loadFont(small);
        fmSprite.setTextColor(c1, c2);
        if (i % 25 == 0) {
          // Calculate label positions
          x0 = sx * (M_SIZE*100 + tl + 10) + M_SIZE*120;
          y0 = sy * (M_SIZE*100 + tl + 10) + M_SIZE*140;
          switch (i / 25) {
            case -2: fmSprite.drawCentreString("0", fmleft+x0, fmTop+y0 - 12, 2); break;
            case -1: fmSprite.drawCentreString("50", fmleft+x0, fmTop+y0 - 9, 2); break;
            case 0: fmSprite.drawCentreString("100", fmleft+x0, fmTop+y0 - 7, 2); break;
            case 1: fmSprite.drawCentreString("150", fmleft+x0, fmTop+y0 - 9, 2); break;
            case 2: fmSprite.drawCentreString("200", fmleft+x0, fmTop+y0 - 12, 2); break;
          }
        }
        fmSprite.unloadFont();
        // Now draw the arc of the scale
        sx = cos((i + 5 - 90) * 0.0174532925);
        sy = sin((i + 5 - 90) * 0.0174532925);
        x0 = sx * M_SIZE*100 + M_SIZE*120;
        y0 = sy * M_SIZE*100 + M_SIZE*140;
        // Draw scale arc, don't draw the last part
        if (i < 50) fmSprite.drawLine(fmleft+x0, fmTop+y0, fmleft+x1, fmTop+y1, TFT_BLACK);
      }
  fmSprite.loadFont(small);
  fmSprite.drawString("m3/hr", fmleft+265, fmTop+120); // Units at bottom right
  fmSprite.unloadFont(); 
  fmSprite.loadFont(small);
  fmSprite.drawString("flowrate", fmleft+160, fmTop+70); // Comment out to avoid font 4
  fmSprite.unloadFont(); 
 // tft.drawRect(fmleft+5, fmTop+3, M_SIZE*230, M_SIZE*119, c1); // Draw bezel line
  plotFlowMeter(0, 0); // Put meter needle at 0
}
void initRelayBtns(){
  uint16_t x = 5;
  uint16_t y = 335;
  //Relay 1 BTN
  tft.loadFont(latin);
  r1Btn.initButtonUL(x, y, 150, 130, c1, c4, c3, "MACERATE", 1);
  //Relay 2 BTN
  x = x+150+10;
  tft.loadFont(latin);
  r2Btn.initButtonUL(x, y, 150, 130, c1, c4, c3, "SPREAD", 1);
  drawRelayBtns();
  //btSprite.pushSprite(0,bty);
  }
void drawRelayBtns(){
  r1Btn.setPressAction(r1_pressAction);
  r1Btn.setReleaseAction(r1_releaseAction);
  r1Btn.drawSmoothButton(false, 5, BACKROUND);
  r2Btn.setPressAction(r2_pressAction);
  r2Btn.setReleaseAction(r2_releaseAction);
  r2Btn.drawSmoothButton(false, 5, BACKROUND);
  }

void initTopBtns(){
  uint16_t x = 3;
  uint16_t y = 3;
  //WW
  char wwBuffer[20]="";
  char wwtemp[5]="";
  sprintf(wwtemp,"%.1f",ww);
  strcat(wwBuffer,wwtemp);
  strcat(wwBuffer,"m");
  tft.loadFont(small);
  wwBtn.initButtonUL(x, y, 100, 38, c1, c2, c1, wwBuffer, 2); 
  wwBtn.drawSmoothButton(wwBtn.getState(), 3, BACKROUND, wwBtn.getState() ? wwBuffer : "Width");
  tft.unloadFont();
  //Rate Target
  x = 320 - 3 - 100;
  tft.loadFont(small);
  rateBtn.initButtonUL(x, y, 100, 38, c1, c2, c1, "2000g/a", 2);
  rateBtn.drawSmoothButton(rateBtn.getState(), 3, BACKROUND, rateBtn.getState() ? "2000g/a" : "Rate");
  tft.unloadFont(); 
  drawTopBtns();}

void drawTopBtns(){
  wwBtn.setPressAction(ww_pressAction);
  wwBtn.setReleaseAction(ww_releaseAction);
  wwBtn.drawSmoothButton(false, 3, BACKROUND);
  rateBtn.setPressAction(rate_pressAction);
  rateBtn.setReleaseAction(rate_releaseAction);
  rateBtn.drawSmoothButton(false, 3, BACKROUND);}

void createTopLogo(){
  //LOGO
  int16_t rc = png.openFLASH((uint8_t *)dark_ft, sizeof(dark_ft), pngDraw);
  if (rc == PNG_SUCCESS) {
    tft.startWrite();
    uint32_t dt = millis();
    rc = png.decode(NULL, 0);
    tft.endWrite();
  }
}

void createInitLogo(){
  int16_t rc = initpng.openFLASH((uint8_t *)slurryquip_logo, sizeof(slurryquip_logo), initpngDraw);
  if (rc == PNG_SUCCESS) {
    tft.startWrite();
    uint32_t dt = millis();
    rc = initpng.decode(NULL, 0);
    tft.endWrite();
    }
}

void pngDraw(PNGDRAW *pDraw) {
  uint16_t lineBuffer[MAX_IMAGE_WDITH];
  png.getLineAsRGB565(pDraw, lineBuffer, PNG_RGB565_BIG_ENDIAN, 0xffffffff);
  tft.pushImage(132, 2 + pDraw->y, pDraw->iWidth, 1, lineBuffer);
}

void initpngDraw(PNGDRAW *pDraw) {
  uint16_t lineBuffer[320];
  initpng.getLineAsRGB565(pDraw, lineBuffer, PNG_RGB565_BIG_ENDIAN, 0xffffffff);
  tft.pushImage(0, 100 + pDraw->y, pDraw->iWidth, 1, lineBuffer);
}


