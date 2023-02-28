#include <Arduino.h>
#include <ESP32Servo360.h>
#include <wire.h>

ESP32Servo360 servo;

#define I2C_SDA 23
#define I2C_SCL 22
#define angle 100     // angle de la boussole voulue (entre 0 et 255)


float angleVoulue = 250 ; // angle entre 0 et 360 deg 

uint8_t compass = 0;  // valeur de la boussole lu 

int vitesse = 0; // entre 0 et 255 
int attends = 0; // temps d'attente en ms
const int moteur = 4; // pin du moteur

float erreur = 0;   // erreur en degré entre la position voulue et la position actuelle


void vitesses(float erreur){
  
  float sortieTemps = ((erreur * 0.00111) + 1.5);

  digitalWrite(moteur, HIGH);
  delay(sortieTemps);

  float tempsBas = 20 - sortieTemps;
  digitalWrite(moteur, LOW);
  delay(tempsBas);
  
}

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


float positionEnDegre(int compass){
  float angleEnDegre = compass * 360.0 / 255.0;
 // Serial.println(angleEnDegre);
  return angleEnDegre;
}


float rotation = 1.5 ;
void setup() {
  pinMode(moteur, OUTPUT);
  Wire.begin(I2C_SDA, I2C_SCL);
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  compass = readCompass();
  erreur = angle - positionEnDegre(compass);
  Serial.print("erreur : ");
  Serial.println(erreur);

  vitesses(erreur);


  // for (int i = 0; i < 1000; i++)
  // {
  //   rotation = rotation - 0.01;
  //   Serial.println(rotation);
  //   servo.spin(rotation);
  //   delay(100);
  // }
  // servo.spin(vitesse);
    // compass = readCompass();
    // float erreur = angle - compass;
    // Serial.print("erreur : ");
    // Serial.println(erreur);

    // positionEnDegre(compass);

    // while(erreur > 3 || erreur < -3){

    //   servo.attach(4, 16);
    //   while (erreur < -3)
    //   {
    //     vitesse = 10;     // clockwise 
    //     servo.spin(vitesse); 
    //     compass = readCompass();
    //     erreur = compass - angle;
    //     //Serial.println(erreur);
    //   }
    //   while (erreur > 3)
    //   {
    //     vitesse = -1;     // conter clockwise
    //     servo.spin(vitesse); 
    //     compass = readCompass();
    //     erreur = compass - angle;
    //    // Serial.println(erreur);
    //   }
      
    //   //compass = readCompass();

    // }
    // servo.detach();  
    // //Serial.println(compass);
}




