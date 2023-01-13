#include <TFT_eSPI.h> 
#include <TFT_eWidget.h> 
#include "fonts.h"
#include <EEPROM.h>
#include "TimerBold70.h"
#include "Latin_Hiragana_24.h"
#include "NotoSansBold15.h"
#include "NotoSansBold50.h"
#include "NotoSansBold60.h"
#include "NotoSansBold70.h"
#include "NotoSansBold80.h"
#include "NotoSansMonoSCB20.h"
TFT_eSPI tft = TFT_eSPI(); 
TFT_eSprite wwSprite = TFT_eSprite(&tft);
TFT_eSprite rateSprite = TFT_eSprite(&tft);
TFT_eSprite tkrSprite = TFT_eSprite(&tft);
TFT_eSprite tmSprite = TFT_eSprite(&tft);
TFT_eSprite ctSprite = TFT_eSprite(&tft);
TFT_eSprite hydSprite = TFT_eSprite(&tft);
TFT_eSprite relaySprite = TFT_eSprite(&tft);
//img.setFreeFont(&DSEG7_Modern_Bold_20);
 //img.drawString(String(VALUE),sx,sy-22);

#define latin Latin_Hiragana_24
#define small NotoSansBold15
#define digits NotoSansMonoSCB20
#define largeDigits TimerBold70
#define large50 NotoSansBold50
#define large60 NotoSansBold60
#define large70 NotoSansBold70
#define large80 NotoSansBold70

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
#define c1 0xE73C //white
#define c2 0x18C3  //gray
//#define c3 0x9986 //red
//#define c4 0x2CAB  //green
#define c3 0xEAA4
#define c4 0x0780
#define c5 0xBDEF //gold

//VARIABLES
int secs = 0;
int r=100;
int sx=110;
int sy=116;
bool onOff=0;
//VARIABLES2
float ww;// = 10;
float tempWW;// = ww;
int appRate;// = 2500;
int tempApp;// = appRate;
int tkrSize;// = 1600;
int tempSize;// = tkrSize;
int hydTrigger;// = 300;
int epromAddress[] = {0,10,20,30,40};
//ADDRESSES = PREV LOAD TIME, ww, TargetRate, trkSize, HydTrigger
//Timing for Loads
int prevLoadTime;
float loadTime = 0;
uint32_t unpauseTime;
//PINS
//LED variables
int ledPin = 27;
int hydPin = 26;
int btnPin = 28;
//RELAYS
int relay1Pin = 6;
int relay2Pin = 7;
//COUNTER
int applied = 0;
int tankerSize = 1600;
int galsPerMin = 420;
int longLine=4;
int animationTimer=0;
//TIMER
int sec=0;
int timerD0=0;
int timerD1=0;
int timerD2=0;
//HYD
int hydValue = 0;
//BUTTONS
//ButtonWidget r1Btn = ButtonWidget(&tft);
//ButtonWidget* btn[] = {&r1Btn};
//uint8_t buttonCount = sizeof(btn) / sizeof(btn[0]);
//int prevBtnState = 0;
//POS
//OPTION BTNS
int optWidth = 100;
int optHeight = 40;
int optX = 4;
int optY = 4;
int optBX = 4;
int optBY = 4;
bool wwOn = false;
bool rateOn = false;
bool tkrOn = false;
bool modeChanged = true;
//TIMER
int timerWidth = 260;
int timerHeight = 140;
int timerX = (320-timerWidth)/2;
int timerY = 70;
int timerBX = 4;
int timerBY = 4;
bool timerOn = false;
bool timerPaused = false;
//COUNTER
int counterWidth = 300;
int counterHeight = 140;
int counterX = (320-counterWidth)/2;
int counterY = 220;
int counterBX = 14;
int counterBY = 34;
bool counterOn = false;
static uint32_t updateTime = millis();

//HYD
int hydWidth = 120;
int hydHeight = 100;
int hydX = 10;
int hydY = 480 - hydHeight;
int hydBX = 4;
int hydBY = 4;
bool hydOn = false;

//RELAY BTN
int relayWidth = 172;
int relayHeight = 100;
int relayX = 144;
int relayY = 480 - relayHeight;
int relayBX = 4;
int relayBY = 4;
bool relayOn = false;
int debounce = 0;

uint16_t grays[60]={0};
uint16_t lines[11]={0};

void setup() {
    EEPROM.begin(512);
    tft.init();
    tft.invertDisplay(true); 
    tft.setRotation(0);
    tft.fillScreen(c2);
    uint16_t calData[5] = { 485, 3150, 400, 3400, 6 };
    tft.setTouch(calData); 
    tft.setTextDatum(4);
    //drawOnOFF();
    for(int i=0;i<50;i++)
      {
          grays[i]=tft.color565(i*5, i*5, i*5);
      }
    lines[0]=grays[5]; lines[1]=grays[10]; lines[2]=grays[20]; lines[3]=grays[30]; lines[4]=grays[40]; lines[5]=grays[49];
    lines[6]=grays[40]; lines[7]=grays[30]; lines[8]=grays[20]; lines[9]=grays[10]; lines[10]=grays[5];
    wwSprite.createSprite(optWidth, optHeight);
    wwSprite.setTextDatum(4);
    rateSprite.createSprite(optWidth, optHeight);
    rateSprite.setTextDatum(4);
    tkrSprite.createSprite(optWidth, optHeight);
    tkrSprite.setTextDatum(4);
    tmSprite.createSprite(timerWidth, timerHeight);
    tmSprite.setTextDatum(4);
    ctSprite.createSprite(counterWidth,counterHeight);
    ctSprite.setTextDatum(4);
    hydSprite.createSprite(hydWidth,hydHeight);
    hydSprite.setTextDatum(4);
    relaySprite.createSprite(relayWidth,relayHeight);
    relaySprite.setTextDatum(4);
    loadEEPROM();
    wwBtn();
    rateBtn();
    tkrBtn();
    relayBtn();
    //initRelayBtns();
}

void loop() {
    if (timerOn == true && timerPaused == false){
        if (millis() - updateTime >= 5000){
              int app = galsPerMin/12;
              applied += app;
              updateTime = millis();
            }
        sec++;
        if(sec==10)
            {sec=0;
            timerD2++;
            if(timerD2==10){timerD2=0; timerD1++;}
            if(timerD1==10){timerD1=0; timerD0++;}
            }
        }
    //MAIN SCREEN
    if (wwOn == false && rateOn == false && tkrOn == false){
        drawTimer(timerD0, timerD1, timerD2, sec);
        drawCounter(applied, "total applied");
        setAnimation();
        hydMeter(hydValue, 0, 1000, 8, 8, 50, "HYD", 4, 240,2, 3);
        if (modeChanged == true){
          wwBtn();
          rateBtn();
          tkrBtn();
          relayBtn();
        }
        }
    else if (wwOn == true){
        drawVariable(ww*10, 1, "width(m)");
        const char* stepList[] = {"-1", "-.1", "+.1", "+1"};
        drawControls(stepList);
        if (modeChanged == true){
            saveBtn();
            backBtn();
            modeChanged = false;
            }
        }
    else if (rateOn == true){
        drawVariable(appRate, 0, "app rate(gals)");
        const char* stepList[] = {"-100", "-10", "+10", "+100"};
        drawControls(stepList);
        if (modeChanged == true){
            saveBtn();
            backBtn();
            modeChanged = false;
            }
        }
    else if (tkrOn == true){
        drawVariable(tkrSize, 0, "tkr size(gals)");
        const char* stepList[] = {"-100", "-10", "+10", "+100"};
        drawControls(stepList);
        if (modeChanged == true){
            saveBtn();
            backBtn();
            modeChanged = false;
            }
        }
  // (int value, int vmin, int vmax, int x, int y, int r, char *units, byte scheme,int sp, int segm, int wid)
    hydValue += 12;
    if (hydValue > 1000){
      hydValue = 0;
    }
    if (hydValue > hydTrigger){
      hydOn = true;
    }
    else {
      hydOn = false;
    }
    //checkBtns();
    if (wwOn == false && rateOn == false && tkrOn == false){
        checkTouch();
        }
    else {
        checkEditTouch();
    }
     // }
//xpos = 60, ypos = 95, gap = 10, radius = 60, sweep = 240,segm =2, wid =3;

}

void loadEEPROM(){
  // writeIntIntoEEPROM(epromAddress[0], 120); //Write Default Load Time
   //writeIntIntoEEPROM(epromAddress[1], ww*10); 
   //writeIntIntoEEPROM(epromAddress[2], appRate); 
   //writeIntIntoEEPROM(epromAddress[3], tkrSize); 
   //writeIntIntoEEPROM(epromAddress[4], hydTrigger); 
   prevLoadTime = readIntFromEEPROM(epromAddress[0]);
   ww = readIntFromEEPROM(epromAddress[1])/10;
   tempWW = ww;
   appRate = readIntFromEEPROM(epromAddress[2]);
   tempApp = appRate;
   tkrSize = readIntFromEEPROM(epromAddress[3]);
   tempSize = tkrSize;
   hydTrigger = readIntFromEEPROM(epromAddress[4]);
}
void writeIntIntoEEPROM(int address, int number)
{ 
  byte byte1 = number >> 8;
  byte byte2 = number & 0xFF;
  EEPROM.write(address, byte1);
  EEPROM.write(address + 1, byte2);
  if (EEPROM.commit()) {
      Serial.println("EEPROM successfully committed");
    } else {
      Serial.println("ERROR! EEPROM commit failed");
    }
}
int readIntFromEEPROM(int address)
{
  byte byte1 = EEPROM.read(address);
  byte byte2 = EEPROM.read(address + 1);
  return (byte1 << 8) + byte2;
}

void drawOnOFF(){
    tft.fillRect(192,11,50,16,TFT_BLACK);
    tft.drawCircle(202,18,7,TFT_WHITE);
    tft.drawCircle(222,18,7,TFT_WHITE);
    tft.drawLine(202,11,222,11,TFT_WHITE);
    tft.drawLine(202,25,222,25,TFT_WHITE);
    tft.fillRect(203,12,18,13,TFT_BLACK);
    if(onOff==1)
    tft.fillCircle(222,18,4,TFT_ORANGE); 
    else
    tft.fillCircle(202,18,4,TFT_ORANGE);
}
