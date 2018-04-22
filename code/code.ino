/*************************
 * Code.ino
 * Fichier principal
 * 
 * Création : 27/12/17
 * Dernière modification : 8/3/18
 */

#include <EEPROM.h>
#include <DS1302RTC.h>
#include <Time.h>
#include "def.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "rgb_lcd.h"

#define PinA 2    //  1ere sortie du codeur
#define PinB 3    //  2e sortie du codeur

volatile boolean mouvement;
volatile boolean up;

/* Moteurs (l298n) M1:Rotation plateau M2:Montée médicaments*/
const int M1HorPin = 7;   //IN1
const int M1TrigPin = 8;  //IN2
const int M1Pwm = 5;      //ENA

const int M2HorPin = 9;   //IN3
const int M2TrigPin = 10; //IN4
const int M2Pwm = 6;      //ENB

/*Diodes IR*/
const int IREmmPin = 13, IRRecPin = A0;

/*Capteur contact*/
const int CptCtcPin = A2; 

/*Boutons*/
const int BtnPin = A1; 
/*DS1302 RTC*/
const int CEPin = 4, IOPin = 12, SLCKPin = 11;
DS1302RTC RTC(CEPin, IOPin, SLCKPin);
tmElements_t tm;

int PosPlat = 0; //position du plateau (0->4)

struct Med Med[5];
//const int EEPromOct = 42; //vàd
int heure = 0;
int Id = 0;
//short NbMedAct=0, NbMedVol=0;
unsigned short MedSeq[5];
/*écran */
int Pos = 0;
byte Cust1 [8] = {0x1B, 0x13, 0x1b, 0x1b, 0x1b, 0x1b, 0x11, 0x1f};

byte Cust2 [8] = {0b10001, 0b01110, 0b11110, 0b11101, 0b11011, 0b10111, 0b00000, 0b11111};

byte Cust3 [8] = {0b10001, 0b01110, 0b11110, 0b10001, 0b11110, 0b11110, 0b01110, 0b10001};

byte Cust4 [8] = {0b11101, 0b11001, 0b10101, 0b01101, 0b00000, 0b11101, 0b11101, 0b11101};

byte Cust5 [8] = {0b00000, 0b01111, 0b01111, 0b00001, 0b11110, 0b11110, 0b01110, 0b10001};

rgb_lcd Lcd;

void RotPlat(); //rotation du plateau
void AddMed(int nbr); //chute des médicaments
void RempTab();
void ActuRTC(); //syncronisation temps avec bluetooth
void routineInterruption();
int AqPers();
boolean Fin(); //vérifie si les médicaments ont été distribués

void setup() {
  Serial.begin(9600);
  pinMode(IREmmPin, OUTPUT);
  Lcd.begin(16,2);
  digitalWrite (PinA, HIGH);
  digitalWrite (PinB, HIGH);
  attachInterrupt (0, routineInterruption, FALLING);
  
   //------------------------------*MENU*----------------------------
  Lcd.createChar(0, Cust1);
  Lcd.createChar(1, Cust2);
  Lcd.createChar(2, Cust3);
  Lcd.createChar(3, Cust4);
  Lcd.createChar(4, Cust5);
}

void loop() {
//  while(analogRead(BtnPin)!=0){ //ou bluetooth
//    delay(1000);
//  }
  Id = AqPers();
  EEPROM.get(0, Med);
  RempTab();
  boolean fin=0;
  while(fin==0){
   fin=Fin();
   AddMed(MedSeq[PosPlat]);
   RotPlat();        
  }

}


void RotPlat(){
  boolean fin=Fin();
  int temp = 0;
  analogWrite(M1Pwm, 42); //valeur à déterminer
  if((MedSeq[(PosPlat+1)%5]!=0 && PosPlat+1<=4) || fin&&PosPlat==4){
    digitalWrite(M1HorPin, HIGH);
    digitalWrite(M1TrigPin, LOW);
    delay(100);
  
    do{
      temp = digitalRead(CptCtcPin); 
    }while(temp==0);
  
    digitalWrite(M1HorPin, HIGH); //arrêt moteur (frein)
    delay(100);

    analogWrite(M1Pwm, 0);       //arrêt moteur  
    digitalWrite(M1HorPin, LOW);
    digitalWrite(M1TrigPin, LOW);
    if(PosPlat!=4)
      PosPlat++;
    else
      PosPlat=0;
  }
  else if(MedSeq[(PosPlat+2)%5]!=0 && PosPlat+2<=4 || fin&&PosPlat==3){
    digitalWrite(M1HorPin, HIGH);
    digitalWrite(M1TrigPin, LOW);
    delay(100);
  
    do{
      temp = digitalRead(CptCtcPin); 
    }while(temp==0);
    delay(200);
    do{
      temp = digitalRead(CptCtcPin); 
    }while(temp==0);
    
  
    digitalWrite(M1HorPin, HIGH); //arrêt moteur (frein)
    delay(100);

    analogWrite(M1Pwm, 0);       //arrêt moteur  
    digitalWrite(M1HorPin, LOW);
    digitalWrite(M1TrigPin, LOW);
    PosPlat+=2;
  }
    else if(MedSeq[(PosPlat+3)%5]!=0 && PosPlat+3<=4 || fin&&PosPlat==2){
    digitalWrite(M1TrigPin, HIGH);
    digitalWrite(M1HorPin, LOW);
    delay(100);
  
    do{
      temp = digitalRead(CptCtcPin); 
    }while(temp==0);
    
    digitalWrite(M1TrigPin, HIGH); //arrêt moteur (frein)
    delay(100);

    analogWrite(M1Pwm, 0);       //arrêt moteur  
    digitalWrite(M1HorPin, LOW);
    digitalWrite(M1TrigPin, LOW);
    PosPlat+=3;
  }
  else if(MedSeq[(PosPlat+4)%5]!=0 && PosPlat+4<=4 || fin&&PosPlat==1){
    digitalWrite(M1TrigPin, HIGH);
    digitalWrite(M1HorPin, LOW);
    delay(100);
  
    do{
      temp = digitalRead(CptCtcPin); 
    }while(temp==0);
    delay(200);
    do{
      temp = digitalRead(CptCtcPin); 
    }while(temp==0);
    
  
    digitalWrite(M1TrigPin, HIGH); //arrêt moteur (frein)
    delay(100);

    analogWrite(M1Pwm, 0);       //arrêt moteur  
    digitalWrite(M1HorPin, LOW);
    digitalWrite(M1TrigPin, LOW);
    PosPlat+=4;
  } 
  PosPlat=PosPlat%5;
}

void AddMed(int Nbr){
  int i = 0, j = 0, ref = 0;

  analogWrite(M2Pwm, 42);    //val à det
  digitalWrite(M2HorPin, LOW);
  digitalWrite(M2TrigPin, HIGH);
  digitalWrite(IREmmPin, HIGH);
  ref = analogRead(IRRecPin) +42; //val à det

  while(i<Nbr){
    do{
      j = analogRead(IRRecPin);
    }while(j>ref);
    Nbr++;
  }
  digitalWrite(M2HorPin, HIGH); //arrêt moteur (frein)
  delay(100);

  digitalWrite(M2TrigPin, LOW);
  delay(1000);

  digitalWrite(M2TrigPin, HIGH);
  delay(1000);
  
  analogWrite(M2Pwm, 0);       //arrêt moteur  
  digitalWrite(M2HorPin, LOW);
  digitalWrite(M2TrigPin, LOW);
  MedSeq[PosPlat]=0;
}

int AqPers(){
  Lcd.print("Bonjour");
  while(!Serial.available() > 0){
    if (mouvement)  {      // on a détecté une rotation du bouton
    if (up)
      Pos++;
    else
      Pos--;
    mouvement = false;
  }
    Affiche();
  delay(250);
    }
    Id = Serial.read()-48;
    struct Med temp;
    Serial.println(Id);
    EEPROM.get(sizeof(Med)*Id,temp);
    String Nom = temp.Nom;
    Lcd.setCursor(0,2);
    Lcd.print(temp.Nom);
  return Id;
}
void Affiche(void) {
  Lcd.clear();
  Lcd.print("Indentifiez vous ?");
  Lcd.setCursor(0, 1);
  Lcd.print("1  2  3  4  5");
  Lcd.setCursor((3 * Pos), 1);
  //Lcd.printByte(Pos); /!\ A VERIFIER /!\
  Serial.print(Pos);
}
void RempTab(){
  RTC.read(tm);
  int i=0;
  if(tm.Hour<10){
    for(i=0;i<=4;i++){
      MedSeq[i]=Med[Id].mat[i];
    }
  }
  else if(tm.Hour<15){
    for(i=0;i<=4;i++){
      MedSeq[i]=Med[Id].midi[i];
    }
  }
  else if(tm.Hour<21){
   for(i=0;i<=4;i++){
      MedSeq[i]=Med[Id].soir[i];
    } 
  }
  else{
   for(i=0;i<=4;i++){
      MedSeq[i]=Med[Id].nuit[i]; 
   }
  } 
}


void routineInterruption(){
  if (digitalRead(PinA))
    up = digitalRead(PinB);
  else
    up = !digitalRead(PinB);
  mouvement = true;
}

void ActuRTC(){
  int Hr_temp=0, Mn_temp=0;
  Serial.print("HrBlu"); //signal pour demander l'heure
  while(Hr_temp==0)
    Hr_temp=Serial.parseInt();
  while(Mn_temp==0)
    Mn_temp=Serial.parseInt();
  RTC.read(tm);
  if(tm.Hour!=Hr_temp || tm.Minute!=Mn_temp){
    setTime(Hr_temp, Mn_temp, tm.Second, tm.Day, tm.Month, tm.Year);
    RTC.set(now());
  }
}

boolean Fin(){
  int i=0;
    for(i=0; i<5; i++)
    {
        if(MedSeq[i]!=0)
        return 0;
    }
    return 1; 
}











