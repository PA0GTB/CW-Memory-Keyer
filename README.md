# CW-Memory-Keyer
a CW Keyer with memory to store Macro's
a CW Keyer to genarate Morsecode via a PS/2 Keyboard
Original design bij Glen Popiel (KW5GP) and desbribed in the book Arduino Projects for Amateur Radio
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
