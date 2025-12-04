/***************************************************
// web: http://www.buydisplay.com
EastRising Technology Co.,LTD
Examples for ER-TFTM024-3  Capacitive touch screen test
Display is Hardward SPI 4-Wire SPI Interface    Capacitive touch screen is Hardward I2C Interface 
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

  *30. CTPSCL    ->    22
  *31. CTPSDA    ->    21


*/


#include <SPI.h>       // this is needed for display
#include "ERGFX.h"
#include "TFTM024-3.h"
#include <Wire.h>      // this is needed for FT6206
#include "FT6206.h"

// The FT6206 uses hardware I2C (SCL/SDA)
FT6206 ctp = FT6206();

// The display also uses hardware SPI
#define TFT_RST 16
#define TFT_DC 17
#define TFT_CS 5
LCD tft = LCD(TFT_CS, TFT_DC,TFT_RST);

// Size of the color selection boxes and the paintbrush size
#define BOXSIZE LCD_TFTWIDTH/8
#define PENRADIUS 3
int oldcolor, currentcolor;

void setup(void) {
  
 
  Serial.begin(115200);
  Serial.println(F("Cap Touch Paint!"));
  
  tft.begin();

  if (! ctp.begin(40)) {  // pass in 'sensitivity' coefficient
    Serial.println("Couldn't start FT6206 touchscreen controller");
    while (1);
  }

  Serial.println("Capacitive touchscreen started");
  
  tft.fillScreen(LCD_BLACK);
  
  // make the color selection boxes
  tft.fillRect(0, 0, BOXSIZE, BOXSIZE, LCD_RED);
  tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, LCD_YELLOW);
  tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, LCD_GREEN);
  tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, LCD_CYAN);
  tft.fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, LCD_BLUE);
  tft.fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, LCD_MAGENTA);
  tft.fillRect(BOXSIZE*6, 0, BOXSIZE, BOXSIZE, LCD_WHITE);
   tft.fillRect(BOXSIZE*7, 0, BOXSIZE, BOXSIZE, LCD_BLACK);
  // select the current color 'red'
  tft.drawRect(0, 0, BOXSIZE, BOXSIZE, LCD_WHITE);
  currentcolor = LCD_RED;
}

void loop() {
  // Wait for a touch
  if (! ctp.touched()) {
    return;
  }

  // Retrieve a point  
  TS_Point p = ctp.getPoint();
  
 /*
  // Print out raw data from screen touch controller
  Serial.print("X = "); Serial.print(p.x);
  Serial.print("\tY = "); Serial.print(p.y);
  Serial.print(" -> ");
 */

  // flip it around to match the screen.
  p.x = map(p.x, 0, 240, 240, 0);
  p.y = map(p.y, 0, 320, 320, 0);
  p.x = 240-p.x; 
  p.y = 320-p.y; 

  // Print out the remapped (rotated) coordinates
  Serial.print("("); Serial.print(p.x);
  Serial.print(", "); Serial.print(p.y);
  Serial.println(")");
  

  if (p.y < BOXSIZE) {
     oldcolor = currentcolor;

     if (p.x < BOXSIZE) { 
       currentcolor = LCD_RED; 
       tft.drawRect(0, 0, BOXSIZE, BOXSIZE, LCD_WHITE);
     } else if (p.x < BOXSIZE*2) {
       currentcolor = LCD_YELLOW;
       tft.drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, LCD_WHITE);
     } else if (p.x < BOXSIZE*3) {
       currentcolor = LCD_GREEN;
       tft.drawRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, LCD_WHITE);
     } else if (p.x < BOXSIZE*4) {
       currentcolor = LCD_CYAN;
       tft.drawRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, LCD_WHITE);
     } else if (p.x < BOXSIZE*5) {
       currentcolor = LCD_BLUE;
       tft.drawRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, LCD_WHITE);
     } else if (p.x <= BOXSIZE*6) {
       currentcolor = LCD_MAGENTA;
       tft.drawRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, LCD_WHITE);
     }else if (p.x <= BOXSIZE*7) {
       currentcolor = LCD_WHITE;
       tft.drawRect(BOXSIZE*6, 0, BOXSIZE, BOXSIZE, LCD_WHITE);
      }else if (p.x <= BOXSIZE*8) {
          tft.fillScreen(LCD_BLACK);
  
        // make the color selection boxes
        tft.fillRect(0, 0, BOXSIZE, BOXSIZE, LCD_RED);
        tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, LCD_YELLOW);
        tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, LCD_GREEN);
        tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, LCD_CYAN);
        tft.fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, LCD_BLUE);
        tft.fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, LCD_MAGENTA);
        tft.fillRect(BOXSIZE*6, 0, BOXSIZE, BOXSIZE, LCD_WHITE);
        tft.fillRect(BOXSIZE*7, 0, BOXSIZE, BOXSIZE, LCD_BLACK);
        // select the current color 'red'
        tft.drawRect(0, 0, BOXSIZE, BOXSIZE, LCD_WHITE);
        currentcolor = LCD_RED;
    
     }


     if (oldcolor != currentcolor) {
        if (oldcolor == LCD_RED) 
          tft.fillRect(0, 0, BOXSIZE, BOXSIZE, LCD_RED);
        if (oldcolor == LCD_YELLOW) 
          tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, LCD_YELLOW);
        if (oldcolor == LCD_GREEN) 
          tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, LCD_GREEN);
        if (oldcolor == LCD_CYAN) 
          tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, LCD_CYAN);
        if (oldcolor == LCD_BLUE) 
          tft.fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, LCD_BLUE);
        if (oldcolor == LCD_MAGENTA) 
          tft.fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, LCD_MAGENTA);
           if (oldcolor == LCD_WHITE) 
          tft.fillRect(BOXSIZE*6, 0, BOXSIZE, BOXSIZE, LCD_WHITE);
   
     }



  }
  if (((p.y-PENRADIUS) > BOXSIZE) && ((p.y+PENRADIUS) < tft.height())) {
    tft.fillCircle(p.x, p.y, PENRADIUS, currentcolor);
  }
}
