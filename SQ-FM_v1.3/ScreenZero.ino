void setMain(){
  Serial.println("MAIN CHANGE");
  tft.fillScreen(c2);
  initTopBtns();
  flowMeter(); 
  draw_counter(digit0, digit1, digit2, digit3, digit4, sec);
  initRelayBtns();
  screen = 0;
}


