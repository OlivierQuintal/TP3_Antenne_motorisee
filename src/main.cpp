#include <Arduino.h>
#include <ESP32Servo360.h>
#include <wire.h>

ESP32Servo360 servo;

#define I2C_SDA 23
#define I2C_SCL 22
#define angle 100
uint8_t compass = 0;

int vitesse = 0; // entre 0 et 255 



int readCompass(void) {
  Wire.beginTransmission(0x60);
  Wire.write(0x01);
  Wire.endTransmission();
  Wire.requestFrom(0x60, 1);
  while (Wire.available() < 1) {
    delay(1);
  }
  return Wire.read();
}


void setup() {
  Wire.begin(I2C_SDA, I2C_SCL);
  Serial.begin(115200);
  delay(500);
  servo.attach(4, 16); // Control pin (white), signal pin (yellow).
  delay(1000);
  //servo.setSpeed(140); // Set turns per minute (RPM), 140 max.
}

void loop() {




    compass = readCompass();

    while(compass > angle +3 || compass < angle -3){

      servo.attach(4, 16);
      while (compass < angle -3)
      {
        vitesse = 10;
        servo.spin(vitesse); // Turn at 40 RPM anticlockwise.
        compass = readCompass();
      }
      while (compass > angle +3)
      {
        vitesse = -10;
        servo.spin(vitesse); // Turn at 40 RPM anticlockwise.
        compass = readCompass();
      }
      
      compass = readCompass();



    }

    servo.detach();
    //delay(1000);
      

    // servo.spin(); // Turn at set speed clockwise.
    // delay(2000);
    
    
    Serial.println(compass);
    



}



