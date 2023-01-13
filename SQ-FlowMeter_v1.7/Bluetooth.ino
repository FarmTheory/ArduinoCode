void readBluetooth(){
  byte temp;
  char val;
  if (BTSerial.available()) {
      val = BTSerial.read();
      Serial.print(val);
      if (val=='A'){
        Serial.print("MASERATE");
        relayOn = false;
        relayBtn();
      }
      else if (val=='B'){
        Serial.println("FOLD");
        relayOn = true;
        relayBtn();
      }
      else if (val=='C'){
       Serial.println("SPREAD");
        hydOn = false;
        hydBtn();
      }
      else if (val=='D'){
        Serial.println("REEL");
        hydOn = true;
        hydBtn();
      }
    }
}

void sendBluetooth(){
    int sendVal = 800;
    char s[][10] = {"TxByte|", "0", "|AI1|", "800", "|AI2|", "20", "|"};
    char s2[][10] = {"TxByte|", "1", "|AI1|", "800", "|AI2|", "20", "|"};
    //Serial.println('**************');
    for (int i=0;i<7;i++){
      if (i==3){
        BTSerial.print(flowAnalog);
        Serial.print(flowAnalog);
        }
      else {
          if (flip==0){
              BTSerial.write(s[i]);
              Serial.write(s[i]);
              }
          else{
              BTSerial.write(s2[i]);
              Serial.write(s2[i]);
              }
          }
      BTSerial.write('\r\n');
      Serial.write('\r\n');
      }
    if(flip == 0){
      flip = 1;
    }
    else {flip = 0;}
    }