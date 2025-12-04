/***************************************************
// web: http://www.buydisplay.com
EastRising Technology Co.,LTD
Examples for ER-TFTM024-3 graphics test
Display is Hardward or Software SPI SPI 4-Wire SPI Interface  
Works with Arduino 2.3.4 IDE  
NOTE: test OK:ESP32-WROOM-32 
****************************************************/
/*
  ==TFT to ESP32  ==
  *1,40. GND       ->    GND
  *2. VCC       ->     3.3V OR 5V is optional, depending on the voltage of the module purchased
  *21. RES       ->    16  
  *23. CS        ->     5 
  *24. SCK       ->    18   
  *25. DC       ->     17
  *27. SDI       ->    23  
  *29. BL        ->    3.3V


*/

#include "SPI.h"
#include "ERGFX.h"
#include "TFTM024-3.h"
#include "pic.c"


#define TFT_RST 16
#define TFT_DC 17
#define TFT_CS 5
// If using the Hardware SPI
LCD tft = LCD(TFT_CS, TFT_DC,TFT_RST);

// If using the Software SPI
/*
#define TFT_CLK  18 
#define TFT_MOSI 23   
LCD tft = LCD(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST);
*/
void setup() {
  Serial.begin(9600);
  Serial.println("LCD Test!"); 
 
  tft.begin();
}


void loop(void) {

  tft.bmp16(0, 0, pic,240, 320);
  delay(2000);


  Serial.print(F("Text                     "));
  Serial.println(testText());
  delay(2000);

  Serial.print(F("Screen fill              "));
  Serial.println(testFillScreen());
  delay(1000);


  Serial.print(F("Lines                    "));
  Serial.println(testLines(LCD_CYAN));
  delay(1000);

  Serial.print(F("Horiz/Vert Lines         "));
  Serial.println(testFastLines(LCD_RED, LCD_BLUE));
  delay(1000);

  Serial.print(F("Rectangles (outline)     "));
  Serial.println(testRects(LCD_GREEN));
  delay(1000);

  Serial.print(F("Rectangles (filled)      "));
  Serial.println(testFilledRects(LCD_YELLOW, LCD_MAGENTA));
  delay(1000);

  Serial.print(F("Circles (filled)         "));
  Serial.println(testFilledCircles(10, LCD_MAGENTA));

  Serial.print(F("Circles (outline)        "));
  Serial.println(testCircles(10, LCD_WHITE));
  delay(1000);

  Serial.print(F("Triangles (outline)      "));
  Serial.println(testTriangles());
  delay(1000);

  Serial.print(F("Triangles (filled)       "));
  Serial.println(testFilledTriangles());
  delay(1000);

  Serial.print(F("Rounded rects (outline)  "));
  Serial.println(testRoundRects());
  delay(1000);

  Serial.print(F("Rounded rects (filled)   "));
  Serial.println(testFilledRoundRects());
  delay(1000);
  Serial.println(F("Done!"));
}

unsigned long testFillScreen() {
  unsigned long start = micros();
  tft.fillScreen(LCD_BLACK);  delay(500);
  tft.fillScreen(LCD_RED);  delay(500);
  tft.fillScreen(LCD_GREEN);  delay(500);
  tft.fillScreen(LCD_BLUE);  delay(500);
  tft.fillScreen(LCD_WHITE);  delay(500);
  tft.fillScreen(LCD_CYAN);  delay(500);
  tft.fillScreen(LCD_YELLOW);  delay(500);
  tft.fillScreen(LCD_MAGENTA);
  return micros() - start;
}

unsigned long testText() {
  tft.fillScreen(LCD_BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 20);
  tft.setTextColor(LCD_WHITE);  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(LCD_YELLOW); tft.setTextSize(2);
  tft.println(123456.78);
  tft.setTextColor(LCD_RED);    tft.setTextSize(3);
  tft.println(0xDEADBEEF, HEX);
   tft.setTextColor(LCD_GREEN); tft.setTextSize(2);
  tft.println("www.buydisplay.com");
   tft.setTextColor(LCD_CYAN); tft.setTextSize(4);
  tft.println("EastRising");
    tft.setTextColor(LCD_BLUE); tft.setTextSize(5);
  tft.println("Groop");
  return micros() - start;
}

unsigned long testLines(uint16_t color) {
  unsigned long start, t;
  int           x1, y1, x2, y2,
                w = tft.width(),
                h = tft.height();

  tft.fillScreen(LCD_BLACK);

  x1 = y1 = 0;
  y2    = h - 1;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t     = micros() - start; // fillScreen doesn't count against timing

  tft.fillScreen(LCD_BLACK);

  x1    = w - 1;
  y1    = 0;
  y2    = h - 1;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  tft.fillScreen(LCD_BLACK);

  x1    = 0;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  tft.fillScreen(LCD_BLACK);

  x1    = w - 1;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);

  return micros() - start;
}

unsigned long testFastLines(uint16_t color1, uint16_t color2) {
  unsigned long start;
  int           x, y, w = tft.width(), h = tft.height();

  tft.fillScreen(LCD_BLACK);
  start = micros();
  for(y=0; y<h; y+=5) tft.drawFastHLine(0, y, w, color1);
  for(x=0; x<w; x+=5) tft.drawFastVLine(x, 0, h, color2);

  return micros() - start;
}

unsigned long testRects(uint16_t color) {
  unsigned long start;
  int           n, i, i2,
                cx = tft.width()  / 2,
                cy = tft.height() / 2;

  tft.fillScreen(LCD_BLACK);
  n     = min(tft.width(), tft.height());
  start = micros();
  for(i=2; i<n; i+=6) {
    i2 = i / 2;
    tft.drawRect(cx-i2, cy-i2, i, i, color);
  }

  return micros() - start;
}

unsigned long testFilledRects(uint16_t color1, uint16_t color2) {
  unsigned long start, t = 0;
  int           n, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(LCD_BLACK);
  n = min(tft.width(), tft.height());
  for(i=n-1; i>0; i-=6) {
    i2    = i / 2;
    start = micros();
    tft.fillRect(cx-i2, cy-i2, i, i, color1);
    t    += micros() - start;
    // Outlines are not included in timing results
    tft.drawRect(cx-i2, cy-i2, i, i, color2);
  }

  return t;
}

unsigned long testFilledCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int x, y, w = tft.width(), h = tft.height(), r2 = radius * 2;

  tft.fillScreen(LCD_BLACK);
  start = micros();
  for(x=radius; x<w; x+=r2) {
    for(y=radius; y<h; y+=r2) {
      tft.fillCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int           x, y, r2 = radius * 2,
                w = tft.width()  + radius,
                h = tft.height() + radius;

  // Screen is not cleared for this one -- this is
  // intentional and does not affect the reported time.
  start = micros();
  for(x=0; x<w; x+=r2) {
    for(y=0; y<h; y+=r2) {
      tft.drawCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testTriangles() {
  unsigned long start;
  int           n, i, cx = tft.width()  / 2 - 1,
                      cy = tft.height() / 2 - 1;

  tft.fillScreen(LCD_BLACK);
  n     = min(cx, cy);
  start = micros();
  for(i=0; i<n; i+=5) {
    tft.drawTriangle(
      cx    , cy - i, // peak
      cx - i, cy + i, // bottom left
      cx + i, cy + i, // bottom right
      tft.color565(0, 0, i));
  }

  return micros() - start;
}

unsigned long testFilledTriangles() {
  unsigned long start, t = 0;
  int           i, cx = tft.width()  / 2 - 1,
                   cy = tft.height() / 2 - 1;

  tft.fillScreen(LCD_BLACK);
  start = micros();
  for(i=min(cx,cy); i>10; i-=5) {
    start = micros();
    tft.fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      tft.color565(0, i, i));
    t += micros() - start;
    tft.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      tft.color565(i, i, 0));
  }

  return t;
}

unsigned long testRoundRects() {
  unsigned long start;
  int           w, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(LCD_BLACK);
  w     = min(tft.width(), tft.height());
  start = micros();
  for(i=0; i<w; i+=6) {
    i2 = i / 2;
    tft.drawRoundRect(cx-i2, cy-i2, i, i, i/8, tft.color565(i, 0, 0));
  }

  return micros() - start;
}

unsigned long testFilledRoundRects() {
  unsigned long start;
  int           i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(LCD_BLACK);
  start = micros();
  for(i=min(tft.width(), tft.height()); i>20; i-=6) {
    i2 = i / 2;
    tft.fillRoundRect(cx-i2, cy-i2, i, i, i/8, tft.color565(0, i, 0));
  }

  return micros() - start;
}
