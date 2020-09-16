# Ardunio-Uno-Based-Macro-Keyboard - Created by Maciej Zajaczkowski

WARNING: THIS IS JUST A PROOF OF CONCEPT/TESTER - JUST TO PROVE THAT READING DATA FROM A SERIAL PORT CONNECTED AN ARDUNIO UNO VIA C++ IS INDEED POSSIBLE. THE RESULTING MACRO KEYBOARD BUILT IN THIS PROJECT IS INEFFICIENT AND REQUIRES THE .EXE FILE TO BE CONTINUOUSLY RUNNING. IF YOU WANT TO CREATE YOUR OWN MACROPAD, PLEASE US AN ARDUNIO PRO MICRO/LEONARDO.

This is a 10 button and Joystick based Macro Keyboard designed to execute basic computer shortcuts using Ardunio Uno.

Since Ardunio Uno is not directly capable of acting as a HID device/ emulating a keyboard, I wrote a secondary program in C++ to read data sent by the ardunio uno and then send the corresponding commands to windows using the "windows.h" library to emulate keystrokes and mouse events.

The program reads the serial port Github user's ZainUlMustafa's, program for reading data sent by ardunio to a serial port in a computer.
I credit him for his code and attach the following links as attibution and for reference.

https://www.youtube.com/watch?v=8BWjyZxGr5o
https://github.com/ZainUlMustafa/

I have modified the original code to only recieve data, deal with large amounts of transmitted data. Emulate mouse and keyboard via the "windows.h" library and automatically scan for COM ports.

How to run the program:

1- Upload the code under "arduinokeyboardjoystick" to an ardunio uno and connect 9 push switches with pull down resistors to 
digital pins 2-10. Then connect a joystick with its axes pins to analogue pins A1 and A2 and the built in button to analogue pin A0.

2 - Run the executable file in this repository, scan for COM port and use the device - it will probably not be very efficient and will have significant time delays.








