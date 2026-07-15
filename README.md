Arduino Computer Lock

A hardware-based computer security lock built as a senior capstone project. The system requires a user to enter the correct passcode on a keypad before the Arduino can activate the PC's power switch, preventing unauthorized use of the computer.

Features:
1. Password-protected computer power button
2. LED status indicators
3. Communication between the Uno R4 and Nano Every using I2C
4. Randomly generated passcode every hour

Hardware:
1. Arduino Uno R4 
2. Arduino Nano Every
3. 3×4 Matrix Keypad (DIYables)
4. 16×2 I2C LCD
5. NOT Gate Schmitt Trigger (74HC14)
6. Logic Level Shifter (TCA9517D)
7. PNP Transistor
8. Red and Green LEDs
9. Resistors (1x 100 ohm, 2x 180 ohm, 2x 1k ohm, and 2x 4k ohm)
10. Breadboard and jumper wires

Installation
1. Download the Project

Clone or download this repository.

2. Install Arduino Cloud
Create an Arduino Cloud account if you do not already have one.
Download the Arduino Cloud app on your smartphone (available for Android and iOS).
Sign in to the app using the same Arduino account that will be used to configure the project.

4. Configure Arduino Cloud
Connect the Arduino Uno R4 to your computer.
Open Arduino Cloud and create a new device using the Arduino Uno R4.
Create a new Thing.
Add a Character String variable named random_passcode.

Configure the variable as:
Read Only
Update on Change

The generated passcode will automatically synchronize with your Arduino Cloud account and can be viewed from the Arduino Cloud mobile app after the project is running.

6. Upload the Code

Upload the following sketches:

CAPSTONE-UNOR4-Slave → Arduino Uno R4

CAPSTONE-NANO-Master → Arduino Nano Every

5. Assemble the Hardware

Build the circuit using the included WiringDiagram.pdf.

6. Operation
Power the circuit.
Open the Arduino Cloud mobile app on your phone.
View the current random_passcode displayed in the app.
Enter the passcode using the keypad.
If the passcode is correct, the Arduino will momentarily activate the computer's power switch, allowing the computer to power on.
