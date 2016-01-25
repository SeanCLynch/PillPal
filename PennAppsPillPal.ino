/*
 PillPal Arduino Code
 by: Sean Lynch
 date: Jan 24th, 2016

This sketch 
 */
#include <SoftwareSerial.h>  

int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3
int led = 13; // Pin for the onboard LED "L"
int motor1 = 12; // Pins for motors.
int motor2 = 11;
int motor3 = 10;
int motor4 = 9;
int redled = 5; // Pins for indicator LEDs
int yellowled = 6;
int blueled = 7;
int motorTime = 620; // Time for running the motors/dispensing pills.

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);
  pinMode(redled, OUTPUT);
  pinMode(yellowled, OUTPUT);
  pinMode(blueled, OUTPUT);
  
//  pinMode(sensor1, INPUT);

  Serial.begin(9600);  // Begin the serial monitor at 9600bps

  bluetooth.begin(115200);  // The Bluetooth Mate defaults to 115200bps
  bluetooth.print("$");  // Print three times individually
  bluetooth.print("$");
  bluetooth.print("$");  // Enter command mode
  delay(100);  // Short delay, wait for the Mate to send back CMD
  bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
  // 115200 can be too fast at times for NewSoftSerial to relay the data reliably
  bluetooth.begin(9600);  // Start bluetooth serial at 9600
  digitalWrite(blueled, HIGH); // Turn power-on indicator on.
}

void loop()
{   
  if(bluetooth.available())  // If the bluetooth sent any characters
  {
    // Read and send any characters the bluetooth prints to the serial monitor
    char c = bluetooth.read();
    Serial.print(c);  

    // Blink onboard LED
    if (c == 'g') {
      digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1000);               // wait for a second
      digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    }

    // Run motor 1
    if ((c == 'a')) {
      digitalWrite(yellowled, HIGH);
      digitalWrite(motor1, HIGH);
      delay(motorTime);
      digitalWrite(motor1, LOW);
      delay(1000);
      digitalWrite(yellowled, LOW);
    }

    // Run motor 2
    if (c == 's') {
      digitalWrite(yellowled, HIGH);
      digitalWrite(motor2, HIGH);
      delay(motorTime);
      digitalWrite(motor2, LOW);
      delay(1000);
      digitalWrite(yellowled, LOW);
    }
    
    // Run motor 3
     if (c == 'd') {
      digitalWrite(yellowled, HIGH);
      digitalWrite(motor3, HIGH);
      delay(motorTime);
      digitalWrite(motor3, LOW);
      delay(1000);
      digitalWrite(yellowled, LOW);
    }

     // Run motor 4
     if (c == 'f') {
      digitalWrite(yellowled, HIGH);
      digitalWrite(motor4, HIGH);
      delay(motorTime);
      digitalWrite(motor4, LOW);
      delay(1000);
      digitalWrite(yellowled, LOW);
    }

    // Stop all motors, just in case.
    if (c == 'z') {
      digitalWrite(motor1, LOW);
      digitalWrite(motor2, LOW);
      digitalWrite(motor3, LOW);
      digitalWrite(motor4, LOW);
    }

    // Blink empty indicator. 
    if (c == 'e') {
      digitalWrite(redled, HIGH);
      delay(1000);
      digitalWrite(redled, LOW);
      delay(1000);
      digitalWrite(redled, HIGH);
      delay(1000);
      digitalWrite(redled, LOW);
      delay(1000);
      digitalWrite(redled, HIGH);
      delay(1000);
      digitalWrite(redled, LOW);
      delay(1000);
    }

  }
  if(Serial.available())  // If stuff was typed in the serial monitor
  {
    // Send any characters the Serial monitor prints to the bluetooth
    bluetooth.print((char)Serial.read());
  }
  
  // and loop forever and ever!
}

