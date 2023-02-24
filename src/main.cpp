#include <Arduino.h>
#include <ESP32Servo360.h>
#include <wire.h>

ESP32Servo360 servo;

#define I2C_SDA 23
#define I2C_SCL 22
uint8_t compass = 0;

int vitesse = 1; // entre 0 et 255 



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
 
  servo.attach(4, 16); // Control pin (white), signal pin (yellow).
  //servo.setSpeed(140); // Set turns per minute (RPM), 140 max.
}

void loop() {

  /*
    while (1) {
      for (int i = 0; i < 20; i++) {
        float duty = 140 * sin (i/20 * 2 * PI);
        servo.spin(duty);
        delay(1000);
        Serial.println(duty);
       }
    }
  */   

    // servo.spin(); // Turn at set speed clockwise.
    // delay(2000);
    if (vitesse != 0 )
    {
      //servo.attach(4, 16);
      servo.spin(vitesse); // Turn at 40 RPM anticlockwise.
    }else{
      //servo.detach();

    }
    
    
    compass = readCompass();
    Serial.println(compass);
    delay(1000);
 


}



