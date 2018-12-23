s

a CW Keyer with memory to store Macro's - 
a CW Keyer to generate Morsecode via a PS/2 Keyboard - 
Original design bij Glen Popiel (KW5GP) and desbribed in the book Arduino Projects for Amateur Radio - 
added several modifications bij Cor Struyk, PA0GTB :
-  Using a Arduino Mega2560 for more memory and Macro-key space
-  Using 20x4 display 4 lines 20 characters
-  Enlarged Buffer length to 120 characters
-  Added additional Macro keys F6-F8
-  Added Clear LCD via ESC key
-  Added Clear LCD and start on new line for Macro's F1 to F8
-  Added Display Macro input while typing
-  Changing the code for initialisation of the LCD display
-  Changed the code for increasing and decreasing Keying speed
-  Changed initial CW speed to 18 wpm
-  Changed the "error CW code"to standard, min 8 dits, Key DEL of BS
-------------------------------------------------------------------------
Additional modification by Cor Struyk, PA0GTB and Edwin Arts, PA7FRN, october 2017
   Changing the behavior of the 20x4 LCD Display
   
   Added additional "Class" ScrolLCD.cpp
   This class changes the sequence of scrolling the lines on the 20x4 LCD display
   from 0-2-1-3 to 0-1-2-3. Both files, ScrolLCD.cpp and ScrolLCD.h must be placed at the same position where the sketch can be found
   --
   Cleaning up the code and removed not used constants and declarations
   Renamed the Booleans status behavior, added LCD Adress constant
   --
   Added modified ps2keyboard library due to enlarged keyboard buffer for this project
   and the necessary Morse library
