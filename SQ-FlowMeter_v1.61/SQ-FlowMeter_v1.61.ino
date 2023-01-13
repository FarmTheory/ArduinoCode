#include "FS.h"
#include <TFT_eSPI.h> // Hardware-specific library
#include <TFT_eWidget.h> 
#include <EEPROM.h>
#include "Latin_Hiragana_24.h"
#include "NotoSansBold15.h"
#include "NotoSansBold30.h"
#include "NotoSansBold40.h"
#include "NotoSansBold50.h"
#include "NotoSansBold60.h"
#include "NotoSansBold70.h"
#include "NotoSansBold80.h"
#include "NotoSansMonoSCB20.h"
#include "RunningAverage.h"
#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2, 1); // RX | TX

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library
TFT_eSprite wwSprite = TFT_eSprite(&tft);
TFT_eSprite rateSprite = TFT_eSprite(&tft);
TFT_eSprite calSprite = TFT_eSprite(&tft);
TFT_eSprite fmSprite = TFT_eSprite(&tft);
TFT_eSprite ctSprite = TFT_eSprite(&tft);
TFT_eSprite trgtSprite = TFT_eSprite(&tft);
TFT_eSprite hydSprite = TFT_eSprite(&tft);
TFT_eSprite relaySprite = TFT_eSprite(&tft);

#define latin Latin_Hiragana_24
#define small NotoSansBold15
#define digits NotoSansMonoSCB20
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

//VARIABLES
int flip = 0;
int secs = 0;
int r=100;
int sx=110;
int sy=116;
bool onOff=0;
bool metric = true;
bool prev_metric = true;
//VARIABLES2
char bluetoothVal; 
float ww;// = 10;
float tempWW;// = ww;
int appRate;// = 2500;
int tempApp;// = appRate;
int hydTrigger;// = 300;
int hydValue;
int analog1;
int volume1;
int analog2;
int volume2;
int flowAnalog = 0;
float flowRate = 0;
float avgFlowRate[] = {};
int epromAddress[] = {0,10,20,30,40,50};
//ADDRESSES = ww, TargetRate, calibrate a0, calibrate a1, calibrate b0, calibrate b1
float targetSpeed = 0;
//PINS
//LED variables
int ledPin = 26; //OUT
int hydPin = 27; //IN
int flowPin = 28; //IN
//BTNS
int b1Pin = 14;//IN
int b2Pin = 7;//IN
//RELAYS
int r1Pin = 6;//OUT
int r2Pin = 4;//OUT
int r3Pin = 3;//OUT
int r4Pin = 2;//OUT
//COUNTER
float applied = 0;
float tempApplied = 0;
int longLine=4;
int animationTimer=0;
//HISTORY
int historyEprom[] = {100,110,120,130,140,150, 160, 170, 180, 190};
int appHistory[10]={20, 30, 40, 50, 60, 0, 0, 0, 0, 0};
int appIndex = 0;
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
bool modeChanged = true;
//FLOWMETER
//VARIABLES FOR FLOW RATE DIAL
float ltx = 0;    // Saved x coord of bottom of needle
uint16_t osx = 1.33*120, osy = 1.33*120; // Saved x & y coords
int old_analog =  -999; // Value last displayed
int value[6] = {0, 0, 0, 0, 0, 0};
int old_value[6] = { -1, -1, -1, -1, -1, -1};
int d = 0;

int flowWidth = 280;
int flowHeight = 140;
int flowX = (320-flowWidth)/2;
int flowY = 70;
int flowBX = 4;
int flowBY = 4;
bool flowOn = false;
static uint32_t updateTarget = millis();
//COUNTER
int counterWidth = 300;
int counterHeight = 80;
int counterX = (320-counterWidth)/2;
int counterY = flowY+flowHeight+10;
int counterBX = 14;
int counterBY = 4;
bool counterOn = false;
static uint32_t updateTime = millis();
static uint32_t btUpdateTime = millis();
//TARGET
int targetWidth = 180;
int targetHeight = 60;
int targetX = (320-targetWidth)/2;
int targetY = counterY+counterHeight+10;
int targetBX = 4;
int targetBY = 4;
bool targetOn = false;
//HYD (Relay 2)
int hydWidth = 120;
int hydHeight = 100;
int hydX = 10;
int hydY = 480 - hydHeight;
int hydBX = 4;
int hydBY = 4;
bool hydOn = false;

//RELAY (Relay 1)
int relayWidth = 172;
int relayHeight = 100;
int relayX = 144;
int relayY = 480 - relayHeight;
int relayBX = 4;
int relayBY = 4;
bool relayOn = false;
int debounce = 0;
int hardwareDebounce = 0;
static uint32_t relaySwitchTime = millis();
uint32_t relaySwitchUpdateTime = millis();
static uint32_t relayTimeout = 2*60; //Secs
uint32_t timeLeft = relayTimeout*1000;
//HARDWARE
int btnOneState = 0;
int btnTwoState = 0;
static uint32_t btnScanTime = millis();
static uint32_t finishWaitTime = 5*60*1000;
uint32_t finishCountDown =  finishWaitTime/1000;
uint32_t holdCounter = 0;
uint16_t grays[60]={0};
uint16_t lines[11]={0};
RunningAverage flowAvg(100);

void setup(void) {
  Serial.begin(9600);
  BTSerial.begin(9600); 
  EEPROM.begin(512);
  tft.init();
  tft.invertDisplay(true); 
  tft.setRotation(0);
  tft.fillScreen(c2);
  uint16_t calData[5] = { 485, 3150, 400, 3400, 6 };
  tft.setTouch(calData); 
  tft.setTextDatum(4);
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
  loadEEPROM();
  wwBtn();
  rateBtn();
  calBtn();
  relayBtn();
  hydBtn();
  createFlowMeter(); // Draw analogue meter
  drawCounter(0, "applied");
  drawTarget(targetSpeed);
  setAnimation();
 // hydMeter(hydValue, 0, 1000, 8, 8, 50, "HYD", 4, 240,2, 3);
 // draw_counter(digit0, digit1, digit2, digit3, digit4, sec);
  //LOGO
 // createTopLogo();
 // btSprite.createSprite(320,140);
 // btSprite.setTextDatum(4);
 // initRelayBtns();
  updateTime = millis(); // Next update time
}


void loop() {
  //MAIN SCREEN
  if (wwOn == false && rateOn == false && calOn == false && historyOn == false){
      flowRate = getFlow();//value[0];
      flowAvg.addValue(flowRate);
      if (millis() - updateTime >= 1000) {
        //Create a Sine wave for testing
        d += 4; if (d >= 360) d = 0;
        value[0] = 50 + 50 * sin((d + 0) * 0.0174532925);
        tempApplied += ((flowRate/3600)*((millis() - updateTime)/1000));
        drawCounter(applied+tempApplied, "applied");
        updateTime = millis();
        if (modeChanged == true){
           // Serial.println("MODE");
            fmSprite.fillSprite(c2);
            createFlowMeter();
            } // Draw analogue meter}
        float avgFR = flowAvg.getAverage();
        drawFlowMeter(avgFR, 5);
        //COUNTER
        setAnimation();
        relayCounter();
        if (modeChanged == true){
            wwBtn();
            rateBtn();
            calBtn();
            relayBtn();
            hydBtn();
            drawTarget(targetSpeed);
            modeChanged = false;
          }
        }
      if (millis() - btUpdateTime >= 4000){
        readBluetooth();
        sendBluetooth();
        btUpdateTime - millis();
        }
      if (millis() - updateTarget >= 10000){
        float avgFlowRate = flowAvg.getAverage();
        applied += ((avgFlowRate/3600)*((millis() - updateTarget)/1000));
        tempApplied = 0;
        drawCounter(applied, "applied");
        calcTarget();
        drawTarget(targetSpeed);
        updateTarget = millis();
        if (avgFlowRate > 0){
          targetOn = true;
          }
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
            drawVariable(appRate*220, 0, "app rate(gal/ac)");
            const char* stepList[] = {"-100", "-10", "+10", "+100"};
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
      //  drawVariable(tkrSize, 0, "tkr size(gals)");
        drawCalibration();
        drawUnitSelection();
        if (modeChanged == true){
           // saveBtn();
            backBtn();
            relaySprite.fillSprite(c2);
            relaySprite.pushSprite(relayX,relayY);
            trgtSprite.fillSprite(c2);
            trgtSprite.pushSprite(targetX,targetY);
            modeChanged = false;
            }
        }
    else if (historyOn == true){
      //  drawVariable(tkrSize, 0, "tkr size(gals)");
        if (appIndex < 0){
          appIndex = 9;
        }
        else if (appIndex > 9){
          appIndex = 0;
        }
        drawHistory();
        drawHistoryControls();
        if (modeChanged == true){
            //saveBtn();
            backBtn();
            relaySprite.fillSprite(c2);
            relaySprite.pushSprite(relayX,relayY);
            trgtSprite.fillSprite(c2);
            trgtSprite.pushSprite(targetX,targetY);
            modeChanged = false;
            }
        }
    //checkBtns();
    if (wwOn == false && rateOn == false && calOn == false && historyOn == false){
        checkTouch();
        }
    else {
        checkEditTouch();
    }
}

//PINS
void initPins(){
    int inPins[] = {hydPin, flowPin, b1Pin, b2Pin};
    int outPins[] = {ledPin, r1Pin, r2Pin, r3Pin, r4Pin};
    for (int i=0; i<4; i++){
      pinMode(inPins[i], INPUT);
      }
    for (int i=0; i<5; i++){
      pinMode(outPins[i], OUTPUT);
      }
    }

void loadEEPROM(){
  //ww, TargetRate, calibrate a0, calibrate a1, calibrate b0, calibrate b1
 //  writeIntIntoEEPROM(epromAddress[0], 10*10); //WW
 //  writeIntIntoEEPROM(epromAddress[1], 22); //APP rate m3/ha
  // writeIntIntoEEPROM(epromAddress[2], 220);  //A1
 //  writeIntIntoEEPROM(epromAddress[3], 0); //V1
 //  writeIntIntoEEPROM(epromAddress[4], 1024); //A2
 //  writeIntIntoEEPROM(epromAddress[5], 280); //V2
   ww = readIntFromEEPROM(epromAddress[0])/10;
   tempWW = ww;
   appRate = readIntFromEEPROM(epromAddress[1]);
   tempApp = appRate;
   analog1 = readIntFromEEPROM(epromAddress[2]);
   volume1 = readIntFromEEPROM(epromAddress[3]);
   analog2 = readIntFromEEPROM(epromAddress[4]);
   volume2 = readIntFromEEPROM(epromAddress[5]);
}
void writeIntIntoEEPROM(int address, int number)
{ 
  byte byte1 = number >> 8;
  byte byte2 = number & 0xFF;
  EEPROM.write(address, byte1);
  EEPROM.write(address + 1, byte2);
  if (EEPROM.commit()) {
    //  Serial.println("EEPROM successfully committed");
    } else {
     // Serial.println("ERROR! EEPROM commit failed");
    }
}
int readIntFromEEPROM(int address)
{
  byte byte1 = EEPROM.read(address);
  byte byte2 = EEPROM.read(address + 1);
  return (byte1 << 8) + byte2;
}

