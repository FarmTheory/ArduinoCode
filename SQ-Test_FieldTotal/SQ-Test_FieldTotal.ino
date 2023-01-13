#include <TFT_eSPI.h>
#include "Latin_Hiragana_24.h"
#include "NotoSansBold15.h"
#include "NotoSansMonoSCB20.h"
TFT_eSPI tft = TFT_eSPI();  
TFT_eSprite sprite= TFT_eSprite(&tft);


#define latin Latin_Hiragana_24
#define small NotoSansBold15
#define digits NotoSansMonoSCB20

#define c1 0xE73C //white
#define c2 0x18C3  //gray
#define c3 0x9986 //red
#define c4 0x2CAB  //green
#define c5 0xBDEF //gold

int fromTop=4;
int left=4;
int width=250;
int heigth=80;

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

void setup() {

  tft.init();
  tft.setRotation(0);
  tft.invertDisplay(true); 
  tft.fillScreen(TFT_BLACK);
 for(int i=0;i<50;i++)
  grays[i]=tft.color565(i*5, i*5, i*5);

lines[0]=grays[5]; lines[1]=grays[10]; lines[2]=grays[20]; lines[3]=grays[30]; lines[4]=grays[40]; lines[5]=grays[49];
lines[6]=grays[40]; lines[7]=grays[30]; lines[8]=grays[20]; lines[9]=grays[10]; lines[10]=grays[5];

 
sprite.createSprite(258,88);
sprite.setTextDatum(4);


}

void loop() {
  if (sec%3 == 0){
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
sprite.fillSprite(c1);
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
sprite.pushSprite(30,0);
}
