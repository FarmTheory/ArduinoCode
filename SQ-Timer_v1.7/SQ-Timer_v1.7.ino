#include <TFT_eSPI.h> 
#include <TFT_eWidget.h> 
#include "fonts.h"
#include <EEPROM.h>
#include "TimerBold70.h"
#include "Latin_Hiragana_24.h"
#include "NotoSansBold15.h"
#include "NotoSansBold30.h"
#include "NotoSansBold40.h"
#include "NotoSansBold50.h"
#include "NotoSansBold60.h"
#include "NotoSansBold70.h"
#include "NotoSansBold80.h"
#include "NotoSansMonoSCB20.h"
TFT_eSPI tft = TFT_eSPI(); 
TFT_eSprite wwSprite = TFT_eSprite(&tft);
TFT_eSprite rateSprite = TFT_eSprite(&tft);
TFT_eSprite calSprite = TFT_eSprite(&tft);
TFT_eSprite fmSprite = TFT_eSprite(&tft);
TFT_eSprite ctSprite = TFT_eSprite(&tft);
TFT_eSprite trgtSprite = TFT_eSprite(&tft);
TFT_eSprite hydSprite = TFT_eSprite(&tft);
TFT_eSprite relaySprite = TFT_eSprite(&tft);
//img.setFreeFont(&DSEG7_Modern_Bold_20);
 //img.drawString(String(VALUE),sx,sy-22);

#define latin Latin_Hiragana_24
#define small NotoSansBold15
#define digits NotoSansMonoSCB20
#define largeDigits TimerBold70
#define medium30 NotoSansBold30
#define medium40 NotoSansBold40
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
//Meter Colour
#define GREEN2RED   4

//WRITE EEPROM!!
bool eepromWrite = 0;
//VARIABLES
int totalSec = 0;
int r=100;
int sx=110;
int sy=116;
bool onOff=0;
bool metric = false;
bool prev_metric = false;
//VARIABLES2
float ww;// = 10;
float tempWW;// = ww;
int appRate;// = 2500;
int tempApp;// = appRate;
float tkrSize;// = 1600;
float tempSize;// = tkrSize;
int hydTrigger;// = 300;
int tempHydTrigger;
int epromAddress[] = {0,16,32,48,64,70,76};
//ADDRESSES = PREV LOAD TIME, ww, TargetRate, trkSize, HydTrigger
//Timing for Loads
int prevLoadTime = 120;
float loadTime = 0;
uint32_t unpauseTime;
uint32_t pauseTime;
int resetTimeOut = 240; //TIMER RESET
float targetSpeed = 0;
//PINS
//LED variables
int buzzerPin = 26;
int hydPin = 27;
int flowPin = 28;
//BTNS
int b1Pin = 14;//IN
int b2Pin = 7;//IN
//RELAYS
int r1Pin = 4;// SWAPPED
int r2Pin = 6;// SWAPPED
int r3Pin = 3;//OUT
int r4Pin = 2;//OUT
//COUNTER
float applied = 0;
float tempApplied = 0;
float m3PerMin;
int longLine=4;
int animationTimer=0;
//HISTORY
int historyEprom[] = {100,116,132,148,164,180,196,212,228,244,260}; //200 is historic total
int appHistory[10]={5, 10, 15, 20, 25, 30, 35, 40, 45, 50};
int eepromIndex = 0;
static uint32_t historicTotal;
//TIMER
int sec=0;
int timerD0=0;
int timerD1=0;
int timerD2=0;
int timerD3=0;
bool timerResetFlag = false;
//HYD
int hydValue = 0;
bool hydManualStart = true;
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
bool calOn = false;
bool historyOn = false;
bool settingsOn = false;
bool hydSettingsOn = false;
bool tkrOn = false;
bool modeChanged = true;
//TIMER
int flowWidth = 300;
int flowHeight = 140;
int flowX = (320-flowWidth)/2;
int flowY = 70;
int flowBX = 4;
int flowBY = 4;
bool flowOn = false;
bool timerPaused = false;
static uint32_t updateTimer = millis();
//TARGET
int targetWidth = 180;
int targetHeight = 60;
int targetX = (320-targetWidth)/2;
int targetY = counterY+counterHeight+10;
int targetBX = 4;
int targetBY = 4;
bool targetOn = false;
//COUNTER
int counterWidth = 300;
int counterHeight = 80;
int counterX = (320-counterWidth)/2;
int counterY = flowY+flowHeight+10;
int counterBX = 14;
int counterBY = 4;
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
static uint32_t hydReadTime = millis();

//RELAY BTN
int relayWidth = 172;
int relayHeight = 100;
int relayX = 144;
int relayY = 480 - relayHeight;
int relayBX = 4;
int relayBY = 4;
bool relayOn = false;
int debounce = 0;
static uint32_t relaySwitchTime = millis();
uint32_t relaySwitchUpdateTime = millis();
static uint32_t relayTimeout = 2*60; //Secs
uint32_t timeLeft = relayTimeout*1000;
//HARDWARE
int buttonState = 0;
static uint32_t btnScanTime = millis();
static uint32_t finishWaitTime = 4*60*1000; //4*60&1000
uint32_t finishCountDown =  finishWaitTime/1000;
uint32_t holdCounter = 0;
uint16_t grays[60]={0};
uint16_t lines[11]={0};
//BUZZER
static uint32_t buzzerOn = millis();
bool buzzerState = true;
static uint32_t buzzerLength = 100;

void setup() {
    Serial.begin(9600);
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
    calSprite.createSprite(optWidth, optHeight);
    calSprite.setTextDatum(4);
    fmSprite.createSprite(flowWidth, flowHeight);
    fmSprite.setTextDatum(4);
    ctSprite.createSprite(counterWidth,counterHeight);
    ctSprite.setTextDatum(4);
    trgtSprite.createSprite(targetWidth,targetHeight);
    trgtSprite.setTextDatum(4);
    hydSprite.createSprite(hydWidth,hydHeight);
    hydSprite.setTextDatum(4);
    relaySprite.createSprite(relayWidth,relayHeight);
    relaySprite.setTextDatum(4);
    initPins();
    Serial.println("EEPROM");
    loadEEPROM();
    wwBtn();
    rateBtn();
    calBtn();
    relayBtn();
    calcTarget();
    drawCounter(0, "applied");
    drawTarget(targetSpeed);
    updateTime = millis();
}

void loop() {
    if (flowOn == true && timerPaused == false){
        if (millis() - updateTime >= 2000){
              float multiply = ((millis() - updateTime)/60000.0);
              float app = m3PerMin*multiply;
              tempApplied += app;
              updateTime = millis();
            }
        if (millis() - updateTimer >= 900){
            int tempSec = (millis()-unpauseTime)/1000;
            totalSec = (loadTime/1000)+tempSec;
            timerD0 = (totalSec/1000)%10;
            timerD1 = (totalSec/100)%10;
            timerD2 = (totalSec/10)%10;
            timerD3 = totalSec%10;
            updateTimer = millis();
                }
          }
    //MAIN SCREEN
    if (wwOn == false && rateOn == false && calOn == false && historyOn == false && settingsOn == false && hydSettingsOn == false && tkrOn == false){
        drawTimer(timerD0, timerD1, timerD2, timerD3);
        //Serial.print("Gals Added");
        //Serial.println(tempGals);
        drawCounter(applied+tempApplied, "applied");
        drawTarget(targetSpeed);
        setAnimation();
        hydMeter(hydValue, 0, 1000, 8, 8, 50, "HYD", 4, 240,2, 3);
        relayCounter();
        if (modeChanged == true){
          wwBtn();
          rateBtn();
          calBtn();
          relayBtn();
          modeChanged = false;
        }
        }
    else if (wwOn == true){
        drawVariable(ww*10, 1, "width(m)");
        const char* stepList[] = {"-1", "-.1", "+.1", "+1"};
        drawControls(stepList);
        if (modeChanged == true){
            saveBtn();
            backBtn();
            trgtSprite.fillSprite(c2);
            trgtSprite.pushSprite(targetX,targetY);
            modeChanged = false;
            }
        }
    else if (rateOn == true){
        if (metric == true){
            drawVariable(appRate, 0, "app rate(m3/ha)");
            const char* stepList[] = {"-10", "-1", "+1", "+10"};
            drawControls(stepList);}
        else{
            drawVariable(appRate*89, 0, "app rate(gal/ac)");
            const char* stepList[] = {"-900", "-90", "+90", "+900"};
            drawControls(stepList);}
        if (modeChanged == true){
            saveBtn();
            backBtn();
            trgtSprite.fillSprite(c2);
            trgtSprite.pushSprite(targetX,targetY);
            modeChanged = false;
            }
        }
    else if (calOn == true){
        drawCalibration();
        drawUnitSelection();
        if (modeChanged == true){
           // saveBtn();
            backBtn();
            relaySprite.fillSprite(c2);
            relaySprite.pushSprite(relayX,relayY);
           // trgtSprite.fillSprite(c2);
           // trgtSprite.pushSprite(targetX,targetY);
            tkrBtn();
            modeChanged = false;
            }
        }
    else if (historyOn == true){
      //  drawVariable(tkrSize, 0, "tkr size(gals)");
        if (eepromIndex < 0){
          eepromIndex = 9;
        }
        else if (eepromIndex > 9){
          eepromIndex = 0;
        }
        drawHistory();
        drawHistoryControls();
        if (modeChanged == true){
            //saveBtn();
            drawHistoricTotal();
            backBtn();
            relaySprite.fillSprite(c2);
            relaySprite.pushSprite(relayX,relayY);
            modeChanged = false;
            }
        }
    else if (hydSettingsOn == true){
        drawHydSetting();
        const char* stepList[] = {"-100", "-10", "+10", "+100"};
        drawControls(stepList);
        if (modeChanged == true){
            saveBtn();
            backBtn();
            trgtSprite.fillSprite(c2);
            trgtSprite.pushSprite(targetX,targetY);
            modeChanged = false;
            }
        }
    else if (tkrOn == true){
        if (metric == true){
            drawVariable(tkrSize*10, 1, "tkr size(gals)");
            const char* stepList[] = {"-1", "-.1", "+.1", "+1"};
            drawControls(stepList);
            }
        else{
            drawVariable(tkrSize*220, 0 , "tkr size(gals)");
            const char* stepList[] = {"-220", "-22", "+22", "+220"};
            drawControls(stepList);
            }
        if (modeChanged == true){
            saveBtn();
            backBtn();
            trgtSprite.fillSprite(c2);
            trgtSprite.pushSprite(targetX,targetY);
            modeChanged = false;
            }
        }
  // (int value, int vmin, int vmax, int x, int y, int r, char *units, byte scheme,int sp, int segm, int wid)
   // hydValue += 12;
    if (millis()-hydReadTime > 3000){
        hydValue = analogRead(hydPin);
        if (hydValue > 1000){
          hydValue = 0;
        }
        if (hydValue > hydTrigger){
          hydOn = true;
          hydManualStart = false;
          if (flowOn == false){
              flowOn = true;
              setTimerOn();
              }
          else if (timerPaused == true){
              timerPaused = false;
              setTimerUnpaused();
              } 
        }
        else {
          hydOn = false;
          if (flowOn == true && timerPaused == false && hydManualStart == false){
              timerPaused = true;
              setTimerPaused();
              }  
        }
        hydReadTime = millis();
      }
    //CHECK HARDWARE BTNS
   // if (millis()-btnScanTime > 50){
    //  checkHardwareBtn();
   // }
    //checkBtns();
    if (wwOn == false && rateOn == false && calOn == false && historyOn == false && settingsOn == false && hydSettingsOn == false && tkrOn == false){
        checkTouch();
        }
    else {
        checkEditTouch();
    }
    if (timerResetFlag == true){
          setTimerOff();
          loadFinished();
          }
    if (buzzerState == true){
        if ((millis()-buzzerLength) > buzzerOn){
          digitalWrite(buzzerPin, LOW);
          buzzerState = false;
        }}

}

void loadFinished(){
//Spreading Finished
  timerPaused = false;
  Serial.print("Saving Load Time: ");
  Serial.println(loadTime/1000);
  int loadSecs = loadTime/1000;
  writeIntIntoEEPROM(epromAddress[0], loadSecs);
  flowOn = false;
  prevLoadTime = loadSecs;
  targetOn = true;
  tempApplied = 0; //This is based on the timer
  applied += tkrSize; //Load count total
  calcTarget();
  loadTime = 0;  
}

void loadEEPROM(){
  if (eepromWrite == 1){
      writeIntIntoEEPROM(epromAddress[0], 240); //Load Time
      writeIntIntoEEPROM(epromAddress[1], 100); //WW * 10
      writeIntIntoEEPROM(epromAddress[2], 22); //APP RATE
      writeIntIntoEEPROM(epromAddress[3], 91); //Tkr Size m3*10
      writeIntIntoEEPROM(epromAddress[4], 100); //Hyd Trigger
      writeIntIntoEEPROM(epromAddress[5], 1); //metric 
       //HISTORY
      for (int i=0; i<10; i++){
          writeIntIntoEEPROM(historyEprom[i], appHistory[i]); //History = 0
        }
      writeIntIntoEEPROM(historyEprom[10], 0);
      
    }
   prevLoadTime = readIntFromEEPROM(epromAddress[0]);
   ww = readIntFromEEPROM(epromAddress[1])/10.0;
   tempWW = ww;
   appRate = readIntFromEEPROM(epromAddress[2]);
   tempApp = appRate;
   tkrSize = readIntFromEEPROM(epromAddress[3])/10.0;
   tempSize = tkrSize;
   hydTrigger = readIntFromEEPROM(epromAddress[4]);
   tempHydTrigger = hydTrigger;
   int metricInt = readIntFromEEPROM(epromAddress[5]);
   if (metricInt == 0){
      metric = false;
    }
   loadHistory();
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
 delay(100);
}
int readIntFromEEPROM(int address)
{
  byte byte1 = EEPROM.read(address);
  byte byte2 = EEPROM.read(address + 1);
  return (byte1 << 8) + byte2;
}

//PINS
void initPins(){
    int inPins[] = {hydPin, flowPin, b1Pin, b2Pin};
    int outPins[] = {buzzerPin, r1Pin, r2Pin, r3Pin, r4Pin};
    for (int i=0; i<4; i++){
      pinMode(inPins[i], INPUT);
      }
    for (int i=0; i<5; i++){
      pinMode(outPins[i], OUTPUT);
      }
    }
