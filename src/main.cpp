//******************************************************************************************************************
//  Nom du fichier : TP3 antenne motorisee
//  Description    : Ce programme permet de faire tourner une antenne motorisee en fonction de la valeur de la boussole
//  Auteur         : Albert State et Olivier Quintal
//  Date           : 1 mars 2023
//******************************************************************************************************************

#include <Arduino.h>
#include <wire.h>


#define I2C_SDA 23  // SDA pin pour la boussole
#define I2C_SCL 22  // SCL pin pour la boussole

float angleVoulue = 100 ; // angle entre 0 et 360 deg 

uint8_t compass = 0;  // valeur de la boussole lu (valeur entre 0 et 255)

int vitesse = 0;    // determine la vitesse du moteur
float tempsBas = 0; // temps bas de notre signal PWM pour le servo moteur 
const int moteur = 4; // pin du moteur

float erreur = 0;   // erreur en degré entre la position voulue et la position actuelle

//**********************************************************************************************************************
// fonction qui permet de calculer la vitesse du moteur en fonction de l'erreur
//**********************************************************************************************************************
void vitesses(float erreur){

  digitalWrite(moteur, HIGH);
  
  float sortieTemps = ((erreur * 0.0011111) + 1.5);

  
  delayMicroseconds(sortieTemps*1000);



  digitalWrite(moteur, LOW);
  tempsBas = 20 - sortieTemps;
  
  delayMicroseconds(tempsBas*1000);
  
}


//**********************************************************************************************************************
// fonction qui permet de lire la valeur de la boussole
//**********************************************************************************************************************
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

//**********************************************************************************************************************
// fonction qui permet de convertir la valeur de la boussole en degré
//**********************************************************************************************************************
float positionEnDegre(int compass){
  float angleEnDegre = compass * 360.0 / 255.0;
  // Serial.print("angle en degré : ");
  // Serial.println(angleEnDegre);
  return angleEnDegre;
}


void setup() {
  pinMode(moteur, OUTPUT);        // met la pni du moteur en sortie
  Wire.begin(I2C_SDA, I2C_SCL);
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  compass = readCompass();    // valeur entre 0 et 255
  erreur = positionEnDegre(compass) - angleVoulue;    // valeur de l'erreur en degré 
  //Serial.print("erreur : ");
  //Serial.println(erreur);

  vitesses(erreur);     // fait le pwm pour le moteur 
}




