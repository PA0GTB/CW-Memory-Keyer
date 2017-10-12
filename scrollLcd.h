/*  additional Class for LiquidCrystal_I2C library
Designed bij Edwin Arts, PA7FRN, october, 10, 2017
This Class modifies the behavior of the 4 Lines 20x4 LCD display
It cures the scrolling order of this display
Standard this display scrolled lines 0,2,1,3. With this additional Class
scrolling is now 0,1,2,3
*/

#ifndef SCROLL_LCD_H
#define SCROLL_LCD_H

#include <LiquidCrystal_I2C.h>

class ScrollLcd {
  public:
	  ScrollLcd(
	    uint8_t lcd_Addr, 
	    uint8_t En, 
	    uint8_t Rw, 
	    uint8_t Rs, 
      uint8_t d4, 
	    uint8_t d5, 
	    uint8_t d6, 
	    uint8_t d7,
      uint8_t backlighPin, 
	    t_backlighPol pol
	  );
    void begin(byte cols, byte rows);
    void clear();
    void home();
	  void setCursor(byte col, byte row);
	  void print(String str);
    void write(uint8_t value);
  	void backlight();
	  void noBacklight();
	  void autoscroll();
	  void noAutoscroll();
  private:
    void scrollPrint(String str);
    void noScrollPrint(String str);
    LiquidCrystal_I2C* _lcd;
    byte _lcdCols = 20;    // Number of character in a row
    byte _lcdRows = 4;     // Number of lines
	  byte _colCur = 0;
	  byte _rowCur = 0;
    String *_strRow;
	  bool _doScroll = false;
    bool _scrollStart = false;
};

#endif
