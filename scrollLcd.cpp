/*  additional Class for LiquidCrystal_I2C library
Designed bij Edwin Arts, PA7FRN, october, 10, 2017
This Class modifies the behavior of the 4 Lines 20x4 LCD display
It cures the scrolling order of this display
Standard this display scrolled lines 0,2,1,3. With this additional Class
scrolling is now 0,1,2,3
*/

#include "scrollLcd.h"

ScrollLcd::ScrollLcd(
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
	) {
  _lcd = new LiquidCrystal_I2C(
    lcd_Addr, 
	En, 
	Rw, 
	Rs, 
	d4, 
	d5, 
	d6, 
	d7, 
	backlighPin, 
	POSITIVE
  );
}
  
void ScrollLcd::begin(byte cols, byte rows) {
  _lcdCols = cols;
  _lcdRows = rows;
  _strRow = new String[_lcdRows];
  _lcd->begin(_lcdCols, _lcdRows);
  _lcd->backlight();
  _lcd->clear();
}

void ScrollLcd::clear() {
  for(uint8_t r=0; r<_lcdRows; r++) {
    _strRow[r] = " ";
    while (_strRow[r].length() < _lcdCols) {
      _strRow[r] = _strRow[r] + " ";
    }
    _lcd->setCursor(0, r);
    _lcd->print(_strRow[r]);
  }
  home();
}

void ScrollLcd::home() {
  _colCur = 0;
  _rowCur = 0;
  _scrollStart = false;
}

void ScrollLcd::setCursor(byte col, byte row) {
  _rowCur = row;
  while (_rowCur >= _lcdRows) {
    _rowCur -= 4;
  }
  _colCur = col;
  while (_colCur >= _lcdCols) {
    _colCur -= _lcdCols;
    _rowCur++;
    if (_rowCur >= _lcdRows) {
      _rowCur = 0;
    }
  }
  _scrollStart = false;
}

void ScrollLcd::print(String str) {
  if (_scrollStart) {
    scrollPrint(str);
  }
  else {
	  noScrollPrint(str);
  }
}

void ScrollLcd::write(uint8_t value) {
  String str = String(char(value));
  print(str);
}

void ScrollLcd::backlight() {
  _lcd->backlight();
}

void ScrollLcd::noBacklight() {
  _lcd->noBacklight();
}

void ScrollLcd::autoscroll() {
  _doScroll = true;
}

void ScrollLcd::noAutoscroll() {
  _doScroll = false;
  home();
}

void ScrollLcd::scrollPrint(String str) {
  byte stringLenght = str.length();
  while (stringLenght > _lcdCols) {
    String strPart = str.substring(0,_lcdCols);
    for (byte r=0; r<_lcdRows; r++) {
      if (r < _lcdRows-1) {
        _strRow[r] = _strRow[r+1];
      }
      else {
        _strRow[r] = strPart;
      }
    }
    str = str.substring(_lcdCols,stringLenght);
    stringLenght = str.length();
  }

  for (byte r=0; r<_lcdRows; r++) {
    _strRow[r] = _strRow[r].substring(stringLenght, _lcdCols);
    if (r<_lcdRows-1) {
      _strRow[r] = _strRow[r] + _strRow[r+1].substring(0, stringLenght);
    }
    else {
      _strRow[r] = _strRow[r] + str;
    }
    _lcd->setCursor(0, r);
    _lcd->print(_strRow[r]);
  }
}

void ScrollLcd::noScrollPrint(String str) {
  byte stringLenght = str.length();
  byte spaceLeft = _lcdCols - _colCur;

  while ((stringLenght > spaceLeft) && (!_scrollStart)) {
    String strPart = str.substring(0,spaceLeft);
    _strRow[_rowCur] = _strRow[_rowCur].substring(0,_colCur) + strPart;
    str = str.substring(spaceLeft,stringLenght);
    stringLenght = str.length();
    _colCur = 0;
    _rowCur++;
    if (_rowCur >= _lcdRows) {
      _rowCur = 0;
      _scrollStart = _doScroll;
    }
    spaceLeft = _lcdCols - _colCur;
  }
  if (_scrollStart) {
    scrollPrint(str);
  }
  else if ((stringLenght > 0)) {
    _strRow[_rowCur] = _strRow[_rowCur].substring(0,_colCur) + str + _strRow[_rowCur].substring(_colCur + stringLenght, _lcdCols);
    _colCur += stringLenght;
    if (_colCur >= _lcdCols) {
      _colCur = 0;
      _rowCur++;
      if (_rowCur >= _lcdRows) {
        _rowCur = 0;
        _scrollStart = _doScroll;
      }
    }
  }

  for(uint8_t r=0; r<_lcdRows; r++) {
    _lcd->setCursor(0, r);
    _lcd->print(_strRow[r]);
  } 
}
