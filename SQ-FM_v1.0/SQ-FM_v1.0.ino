
#define M_SIZE 1.3333
#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include "Latin_Hiragana_24.h"
#include "NotoSansBold15.h"
#include "NotoSansMonoSCB20.h"

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library
TFT_eSprite fmSprite= TFT_eSprite(&tft);
TFT_eSprite sprite= TFT_eSprite(&tft);

#define latin Latin_Hiragana_24
#define small NotoSansBold15
#define digits NotoSansMonoSCB20

#define TFT_GREY 0x5AEB
#define BACKROUND 0x94B2
#define ORANGE 0xEAA4
#define GREEN 0x0780
#define GREY 0x7BEF
#define BLUE 0x201F
#define WHITE 0xffff
#define BLACK 0x0000
#define YELLOW  0xFFE0  
#define RED 0xF800
//Total Counter Colours
#define c1 0xE73C //white
#define c2 0x18C3  //gray
#define c3 0x9986 //red
#define c4 0x2CAB  //green
#define c5 0xBDEF //gold

//POSITION VARAIBLES
//FLOWMETER DIAL
int fmTop=4;
int fmleft=2;
//COUNTER
int fromTop=4;
int left=4;
int width=250;
int heigth=80;

//VARIABLES FOR FLOW RATE DIAL
float ltx = 0;    // Saved x coord of bottom of needle
uint16_t osx = M_SIZE*120, osy = M_SIZE*120; // Saved x & y coords
uint32_t updateTime = 0;       // time for next update
int old_analog =  -999; // Value last displayed
int value[6] = {0, 0, 0, 0, 0, 0};
int old_value[6] = { -1, -1, -1, -1, -1, -1};
int d = 0;
//VARIABLES FOR COUNTER
uint16_t grays[60]={0};
uint16_t lines[11]={0};
int sec=0;
int pos=0;
int digit0=0;
int digit1=0;
int digit2=0;
int digit3=0;
int digit4=0;
long start=0;
long end=0;
int counter=0;
double fps=0;
int longLine=4;
int animationTimer=0;


void setup(void) {
  tft.init();
  tft.invertDisplay(true); 
  tft.setRotation(0);
  tft.fillScreen(c2);
  fmSprite.createSprite(320,120);
  fmSprite.setTextDatum(4);
  flowMeter(); // Draw analogue meter
  //COUNTER
  for(int i=0;i<50;i++)
      {
          grays[i]=tft.color565(i*5, i*5, i*5);
      }
  lines[0]=grays[5]; lines[1]=grays[10]; lines[2]=grays[20]; lines[3]=grays[30]; lines[4]=grays[40]; lines[5]=grays[49];
  lines[6]=grays[40]; lines[7]=grays[30]; lines[8]=grays[20]; lines[9]=grays[10]; lines[10]=grays[5];
  sprite.createSprite(258,88);
  sprite.setTextDatum(4);

  updateTime = millis(); // Next update time
}


void loop() {
  if (updateTime <= millis()) {
    updateTime = millis() + 2000; // Update emter every 35 milliseconds
     //Create a Sine wave for testing
    d += 4; if (d >= 360) d = 0;
    value[0] = 50 + 50 * sin((d + 0) * 0.0174532925);
    plotFlowMeter(value[0], 10);
    } // It takes between 2 and 12ms to replot the needle with zero delay
//COUNTER
if (sec%2 == 0){
  draw_counter(digit0, digit1, digit2, digit3, digit4, sec);
  }
sec++;
if(sec==10)
    {sec=0;
    digit4++;
    if(digit4==10){digit4=0; digit3++;}
    if(digit3==10){digit3=0; digit2++;}
    if(digit2==10){digit2=0; digit1++;}
    if(digit1==10){digit1=0; digit0++;}
    }
animationTimer++;
if(animationTimer==4)
    {
      animationTimer=0;
      longLine++;
      if( longLine==11)
      longLine=0;
    } 

  }



// #########################################################################
//  Draw the analogue meter on the screen
// #########################################################################
void flowMeter()
{

  fmSprite.fillSmoothRoundRect(fmleft+5, fmTop+3, M_SIZE*230, M_SIZE*119, 8, c2, c2);
  fmSprite.setTextColor(c1);  // Text colour
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
      tft.fillTriangle(fmleft+x0, fmTop+y0, fmleft+x1, fmTop+y1, fmleft+x2, fmTop+y2, c4);
      tft.fillTriangle(fmleft+x1, fmTop+y1, fmleft+x2, fmTop+y2, fmleft+x3, fmTop+y3, c4);
    }
    // Orange zone limits
    if (i >= 25 && i < 50) {
      tft.fillTriangle(fmleft+x0, fmTop+y0, fmleft+x1, fmTop+y1, fmleft+x2, fmTop+y2, ORANGE);
      tft.fillTriangle(fmleft+x1, fmTop+y1, fmleft+x2, fmTop+y2, fmleft+x3, fmTop+y3, ORANGE);
    }
    // Short scale tick length
    if (i % 25 != 0) tl = 8;
    // Recalculate coords incase tick lenght changed
    x0 = sx * (M_SIZE*100 + tl) + M_SIZE*120;
    y0 = sy * (M_SIZE*100 + tl) + M_SIZE*140;
    x1 = sx * M_SIZE*100 + M_SIZE*120;
    y1 = sy * M_SIZE*100 + M_SIZE*140;
    // Draw tick
    tft.drawLine(fmleft+x0, fmTop+y0, fmleft+x1, fmTop+y1, c1);
    // Check if labels should be drawn, with position tweaks
    if (i % 25 == 0) {
      // Calculate label positions
      x0 = sx * (M_SIZE*100 + tl + 10) + M_SIZE*120;
      y0 = sy * (M_SIZE*100 + tl + 10) + M_SIZE*140;
      switch (i / 25) {
        case -2: tft.drawCentreString("0", fmleft+x0, fmTop+y0 - 12, 2); break;
        case -1: tft.drawCentreString("50", fmleft+x0, fmTop+y0 - 9, 2); break;
        case 0: tft.drawCentreString("100", fmleft+x0, fmTop+y0 - 7, 2); break;
        case 1: tft.drawCentreString("150", fmleft+x0, fmTop+y0 - 9, 2); break;
        case 2: tft.drawCentreString("200", fmleft+x0, fmTop+y0 - 12, 2); break;
      }
    }
    // Now draw the arc of the scale
    sx = cos((i + 5 - 90) * 0.0174532925);
    sy = sin((i + 5 - 90) * 0.0174532925);
    x0 = sx * M_SIZE*100 + M_SIZE*120;
    y0 = sy * M_SIZE*100 + M_SIZE*140;
    // Draw scale arc, don't draw the last part
    if (i < 50) tft.drawLine(fmleft+x0, fmTop+y0, fmleft+x1, fmTop+y1, TFT_BLACK);
  }
  tft.loadFont(small);
  tft.drawString("m3/hr", fmleft+M_SIZE*(5 + 230 - 45), fmTop+M_SIZE*(119 - 20), 2); // Units at bottom right
  tft.drawCentreString("FlowRate", fmleft+M_SIZE*120, fmTop+M_SIZE*70, 4); // Comment out to avoid font 4
 // tft.drawRect(fmleft+5, fmTop+3, M_SIZE*230, M_SIZE*119, c1); // Draw bezel line
  plotFlowMeter(0, 0); // Put meter needle at 0
}
void plotFlowMeter(int value, byte ms_delay)
{
  tft.setTextColor(c1, c2);
  char buf[8]; dtostrf(value, 4, 0, buf);
  tft.loadFont(small);
  tft.drawRightString(buf,fmleft+M_SIZE*40, fmTop+M_SIZE*(119 - 20), 4);

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
    tft.drawLine(fmleft+M_SIZE*(120 + 20 * ltx - 1), fmTop+M_SIZE*(140 - 20), fmleft+osx - 1, fmTop+osy, c2);
    tft.drawLine(fmleft+M_SIZE*(120 + 20 * ltx), fmTop+M_SIZE*(140 - 20), fmleft+osx, fmTop+osy, c2);
    tft.drawLine(fmleft+M_SIZE*(120 + 20 * ltx + 1), fmTop+M_SIZE*(140 - 20), fmleft+osx + 1, fmTop+osy, c2);
    // Re-plot text under needle
    tft.setTextColor(TFT_WHITE);
    tft.loadFont(latin);
    tft.drawCentreString("FlowRate", fmleft+M_SIZE*120, fmTop+M_SIZE*70, 4); // // Comment out to avoid font 4

    // Store new needle end coords for next erase
    ltx = tx;
    osx = M_SIZE*(sx * 98 + 120);
    osy = M_SIZE*(sy * 98 + 140);

    // Draw the needle in the new postion, magenta makes needle a bit bolder
    // draws 3 lines to thicken needle
    tft.drawLine(fmleft+M_SIZE*(120 + 20 * ltx - 1), fmTop+M_SIZE*(140 - 20), fmleft+osx - 1, fmTop+osy, TFT_RED);
    tft.drawLine(fmleft+M_SIZE*(120 + 20 * ltx), fmTop+M_SIZE*(140 - 20), fmleft+osx, fmTop+osy, TFT_RED);
    tft.drawLine(fmleft+M_SIZE*(120 + 20 * ltx + 1), fmTop+M_SIZE*(140 - 20), fmleft+osx + 1, fmTop+osy, TFT_RED);
    // Slow needle down slightly as it approaches new postion
    if (abs(old_analog - value) < 10) ms_delay += ms_delay / 5;
    // Wait before next update
    delay(ms_delay);
  }
}

void draw_counter(int d0, int d1, int d2, int d3, int d4, int d5)
{
  if(counter==0){
      start=millis();
    }
  counter++;
  if(counter==100)
  {
    end=millis();
    fps=100/((end-start)/1000.00)*3;
    counter=0;
  }
  sprite.fillSprite(c2);
  sprite.fillSmoothRoundRect(0,0,(left*2)+width,(fromTop*2)+heigth,8,c1,c2);
  sprite.fillSmoothRoundRect(left,fromTop,width,heigth,8,c2,c1);
  //Draws the 5 digits
  for(int i=0;i<6;i++){
    sprite.fillRectHGradient(left+(20)+(i*36), fromTop+12, 15, 44, TFT_BLACK,grays[2]);
    sprite.fillRectHGradient(left+(35)+(i*36), fromTop+12, 15, 44, grays[2],TFT_BLACK);
    if (i < 5) { //Skip final digit ticks
      for(int j=0;j<11;j++)
      if(j==5)
      sprite.drawLine(left+(40)+(i*36),fromTop+14+(j*4),left+(47)+(i*36),fromTop+14+(j*4),lines[j]);
      else
      sprite.drawLine(left+(43)+(i*36),fromTop+14+(j*4),left+(47)+(i*36),fromTop+14+(j*4),lines[j]);
      }
    }
  // Final Digit ticks
  for(int j=0;j<11;j++)
  if(j==longLine)
  sprite.drawLine(left+(40)+(5*36),fromTop+14+(j*4),left+(47)+(5*36),fromTop+14+(j*4),lines[j]);
  else
  sprite.drawLine(left+(43)+(5*36),fromTop+14+(j*4),left+(47)+(5*36),fromTop+14+(j*4),lines[j]);
  //90 Angled Lines for bottom text
  sprite.drawLine(left+28,fromTop+60,left+28,fromTop+66,c1);
  sprite.drawLine(left+28,fromTop+66,left+44,fromTop+66,c1);
  sprite.drawLine(left+132+36+36,fromTop+66,left+148+36+36,fromTop+66,c1);
  sprite.drawLine(left+148+36+36,fromTop+66,left+148+36+36,fromTop+60,c1);
  //bottom text
  sprite.loadFont(small);
  sprite.setTextColor(c1,c2);
  sprite.drawString("gals/field",left+125,fromTop+68);
  sprite.setTextColor(c4,c1);
  sprite.drawString(String(fps),20,80);
  sprite.setTextColor(c1,c2);
  sprite.unloadFont(); 
  //Digits
  sprite.loadFont(digits);
  sprite.setTextColor(c1,TFT_BLACK);
  sprite.drawString(String(digit0),left+30,fromTop+35);
  sprite.drawString(String(digit1),left+66,fromTop+35);
  sprite.drawString(String(digit2),left+102,fromTop+35);
  sprite.drawString(String(digit3),left+138,fromTop+35);
  sprite.drawString(String(digit4),left+174,fromTop+35);
  sprite.drawString(String(sec),left+210,fromTop+35);
  sprite.unloadFont(); 
  //Push to Screen
  sprite.pushSprite(30,175);
  }
