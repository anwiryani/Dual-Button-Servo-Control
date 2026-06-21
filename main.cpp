#include <Arduino.h>
#include <ESP32Servo.h>

int buttonPINr[4] = {22, 32, 25, 27};
int buttonPINl[4] = {23, 33, 26, 14};
int servoPIN[4] = {16, 17, 18, 19}; 

Servo servo[4];
int pos[4] = {0, 0, 0, 0};

void setup()
{
  Serial.begin(115200);
  for(int i; i <4; i++){
    pinMode(buttonPINr[i], INPUT_PULLUP);
    pinMode(buttonPINl[i], INPUT_PULLUP);
    servo[i].attach(servoPIN[i], 500, 2400);
  }
}

void loop()
{
  for(int i = 0; i<4; i++){
    bool buttonSTATEr = digitalRead(buttonPINr[i]) == LOW;
    bool buttonSTATEl = digitalRead(buttonPINl[i]) == LOW;

    if(buttonSTATEr && pos[i] < 180){
      pos[i] ++;
      servo[i].write(pos[i]);
      delay(10);
      if(pos[i] == 180){
        Serial.println("mentok le");
      }
    } else if (buttonSTATEl && pos[i] > 0){
        pos[i] --;
        servo[i].write(pos[i]);
        delay(10);
        if(pos[i] == 0){
          Serial.println("mentok le");
        }
    } else if(buttonSTATEr && buttonSTATEl){
      Serial.println("gagal le");
    }
  }
}