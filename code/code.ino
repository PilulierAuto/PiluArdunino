/*************************
 * Code.ino
 * Fichier principal
 * 
 * Création : 27/12/17
 * Dernière modification : 6/1/18
 */

#include <EEPROM.h>
#include <DS1302RTC.h>
#include <Time.h>
#include "def.h"

/* Moteurs (l298n) M1:Rotation plateau M2:Montée médicaments*/
const int M1HorPin = 7;   //IN1
const int M1TrigPin = 8;  //IN2
const int M1Pwm = 5;      //ENA

const int M2HorPin = 9;   //IN3
const int M2TrigPin = 10; //IN4
const int M2Pwm = 6;      //ENB

/*Diodes IR*/
const int IREmmPin = 12, IRRecPin = A0;

/*Capteur contact*/
const int CptCtcPin = A3; //provisoire

/*Boutons*/
const int BtnPin = A2; //provisoire

/*DS1302 RTC*/
const int CEPin = 4, IOPin = 3, SLCKPin = 2;
DS1302RTC RTC(CEPin, IOPin, SLCKPin);
tmElements_t tm;

int PosPlat = 0; //position du plateau (0->4)

struct Med Med[5];
//const int EEPromOct = 42; //vàd
int heure = 0;
int Id = 0;
//short NbMedAct=0, NbMedVol=0;
unsigned short MedSeq[5];

void initRTC(); //initialisation du RTC
void RotPlat(); //rotation du plateau (un cran)
void AddMed(int nbr); //chute d'un médicament
void RempTab();

void setup() {
  
  initRTC();
  pinMode(IREmmPin, OUTPUT);
  

}

void loop() {
  while(analogRead(BtnPin)!=0){ //ou bluetooth
    delay(1000);
  }
  Id = AqPers();
  EEPROM.get(0, Med);
  RempTab();
  while(PosPlat<=4){
   AddMed(MedSeq[PosPlat]);
   RotPlat();        
  }
}

void initRTC(){
  
}

void RotPlat(){
  int temp = 0;
  analogWrite(M1Pwm, 42); //valeur à déterminer
  digitalWrite(M1HorPin, LOW);
  digitalWrite(M1TrigPin, HIGH);
  delay(100);
  
  do{
    temp = analogRead(CptCtcPin); 
  }while(temp<42); //valeur à déterminer
  
  digitalWrite(M1HorPin, HIGH); //arrêt moteur (frein)
  delay(100);

  analogWrite(M1Pwm, 0);       //arrêt moteur  
  digitalWrite(M1HorPin, LOW);
  digitalWrite(M1TrigPin, LOW);
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

  analogWrite(M2Pwm, 0);       //arrêt moteur  
  digitalWrite(M2HorPin, LOW);
  digitalWrite(M2TrigPin, LOW);
  if(PosPlat!=4)
   PosPlat++;
  else
   PosPlat=0;
}

int AqPers(){
  //CSQG
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
  else{
   for(i=0;i<=4;i++){
      MedSeq[i]=Med[Id].soir[i];
    } 
  }   
}


