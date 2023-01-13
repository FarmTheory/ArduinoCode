
int hydMeter(int value, int vmin, int vmax, int x, int y, int r, char *units, byte scheme,int sp, int segm, int wid)
{
  uint16_t colour = c3;
  char *label = "OFF";
  if(hydOn == true){
    colour = c4;
    label = "ON";
    }

  hydSprite.fillSprite(c2);
  hydSprite.fillSmoothRoundRect(0, 0, hydWidth, hydHeight, 8, colour, c2); //White Rect
  hydSprite.fillSmoothRoundRect(hydBX, hydBY, hydWidth-(hydBX*2), hydHeight-(hydBY*2), 8, c2, colour);
  // Minimum value of r is about 52 before value text intrudes on ring
  // drawing the text first is an option
  
  x += r; y += r;   // Calculate coords of centre of ring
  int w = r / wid;    // Width of outer ring is 1/4 of radius
  sp = sp/2;
  int angle = sp;  // Half the sweep angle of meter (300 degrees)
  int text_colour = 0; // To hold the text colour
  int v = map(value, vmin, vmax, -angle, angle); // Map the value to an angle v

  byte seg = 5; // Segments are 5 degrees wide = 60 segments for 300 degrees
  byte inc = 5*segm; // Draw segments every 5 degrees, increase to 10 for segmented ring

  // Draw colour blocks every inc degrees
  for (int i = -angle; i < angle; i += inc) {

    // Choose colour from scheme
    int colour = 0;
    switch (scheme) {
      case 0: colour = c2; break; // Fixed colour
      case 1: colour = c3; break; // Fixed colour
      case 2: colour = c4; break; // Fixed colour
      case 3: colour = rainbow(map(i, -angle, angle, 0, 127)); break; // Full spectrum blue to red
      case 4: colour = rainbow(map(i, -angle, angle, 63, 127)); break; // Green to red (high temperature etc)
      case 5: colour = rainbow(map(i, -angle, angle, 127, 63)); break; // Red to green (low battery etc)
      default: colour = c5; break; // Fixed colour
    }

    // Calculate pair of coordinates for segment start
    float sx = cos((i - 90) * 0.0174532925);
    float sy = sin((i - 90) * 0.0174532925);
    uint16_t x0 = sx * (r - w) + x;
    uint16_t y0 = sy * (r - w) + y;
    uint16_t x1 = sx * r + x;
    uint16_t y1 = sy * r + y;

    // Calculate pair of coordinates for segment end
    float sx2 = cos((i + seg - 90) * 0.0174532925);
    float sy2 = sin((i + seg - 90) * 0.0174532925);
    int x2 = sx2 * (r - w) + x;
    int y2 = sy2 * (r - w) + y;
    int x3 = sx2 * r + x;
    int y3 = sy2 * r + y;

    if (i < v) { // Fill in coloured segments with 2 triangles
      hydSprite.fillTriangle(x0, y0, x1, y1, x2, y2, colour);
      hydSprite.fillTriangle(x1, y1, x2, y2, x3, y3, colour);
      text_colour = colour; // Save the last colour drawn
    }
    else // Fill in blank segments
    {
      hydSprite.fillTriangle(x0, y0, x1, y1, x2, y2, GREY);
      hydSprite.fillTriangle(x1, y1, x2, y2, x3, y3, GREY);
    }
  }

  // Convert value to a string
  char buf[10];
  byte len = 4; if (value > 999) len = 5;
  dtostrf(value, len, 0, buf);
  int xpos = x - 0;
  if (value > 99) {
    xpos = x - 3;
    }
  hydSprite.loadFont(small);
  hydSprite.setTextColor(c1,c2);
  hydSprite.drawCentreString(buf, xpos, y - 20, 4); // Value in middle

  hydSprite.drawCentreString("Hyd", x+1, y + 3, 2); // Units display
  hydSprite.drawCentreString(label, x+1, y + 20, 2); // Units display
  hydSprite.pushSprite(hydX,hydY);
  // Calculate and return right hand side x coordinate
  return x + r;
}

void getHyd(){
    static uint32_t waitTime = 5000;
    hydValue = analogRead(hydPin);
    }


unsigned int rainbow(byte value)
{
  // Value is expected to be in range 0-127
  // The value is converted to a spectrum colour from 0 = blue through to 127 = red

  byte red = 0; // Red is the top 5 bits of a 16 bit colour value
  byte green = 0;// Green is the middle 6 bits
  byte blue = 0; // Blue is the bottom 5 bits

  byte quadrant = value / 32;

  if (quadrant == 0) {
    blue = 31;
    green = 2 * (value % 32);
    red = 0;
  }
  if (quadrant == 1) {
    blue = 31 - (value % 32);
    green = 63;
    red = 0;
  }
  if (quadrant == 2) {
    blue = 0;
    green = 63;
    red = value % 32;
  }
  if (quadrant == 3) {
    blue = 0;
    green = 63 - 2 * (value % 32);
    red = 31;
  }
  return (red << 11) + (green << 5) + blue;
}
