#include <EEPROM.h>
#include "def.h"

struct Med Med[5];
struct Med Rec[5];

const char Nom0[16]="A";
const char Nom1[16]="B";
const char Nom2[16]="C";
const char Nom3[16]="D";
const char Nom4[16]="E";
String MedStr;
byte i,d;


void setup() {
  Serial.begin(9600);
  strcpy(Med[0].Nom, Nom0);
  strcpy(Med[1].Nom, Nom1);
  strcpy(Med[2].Nom, Nom2);
  strcpy(Med[3].Nom, Nom3);
  strcpy(Med[4].Nom, Nom4);
  d=0;
  MedStr="0110100011001012000032500";
          for(i=0;i<=4;i++){        //On copie les valeurs dans la structure provisoire
          Med[d].mat[i]=MedStr.charAt(i)-48;
          }         
        for(i=5;i<=9;i++){        //On copie les valeurs dans la structure provisoire
          Med[d].midi[i-5]=MedStr.charAt(i)-48;
          }
        for(i=10;i<=14;i++){        //On copie les valeurs dans la structure provisoire
          Med[d].soir[i-10]=MedStr.charAt(i)-48;
          }
        for(i=15;i<=19;i++){        //On copie les valeurs dans la structure provisoire
          Med[d].nuit[i-15]=MedStr.charAt(i)-48;
          } 
        for(i=20;i<=24;i++){        //On copie les valeurs dans la structure provisoire
          Med[d].aco[i-20]=MedStr.charAt(i)-48;
          }
  d=1;
  MedStr="1000120002300034000450005";
          for(i=0;i<=4;i++){        //On copie les valeurs dans la structure provisoire
          Med[d].mat[i]=MedStr.charAt(i)-48;
          }         
        for(i=5;i<=9;i++){        //On copie les valeurs dans la structure provisoire
          Med[d].midi[i-5]=MedStr.charAt(i)-48;
          }
        for(i=10;i<=14;i++){        //On copie les valeurs dans la structure provisoire
          Med[d].soir[i-10]=MedStr.charAt(i)-48;
          }
        for(i=15;i<=19;i++){        //On copie les valeurs dans la structure provisoire
          Med[d].nuit[i-15]=MedStr.charAt(i)-48;
          } 
        for(i=20;i<=24;i++){        //On copie les valeurs dans la structure provisoire
          Med[d].aco[i-20]=MedStr.charAt(i)-48;
          }
  d=2;
  MedStr="0111002220033300555001010";
          for(i=0;i<=4;i++){        //On copie les valeurs dans la structure provisoire
          Med[d].mat[i]=MedStr.charAt(i)-48;
          }         
        for(i=5;i<=9;i++){        //On copie les valeurs dans la structure provisoire
          Med[d].midi[i-5]=MedStr.charAt(i)-48;
          }
        for(i=10;i<=14;i++){        //On copie les valeurs dans la structure provisoire
          Med[d].soir[i-10]=MedStr.charAt(i)-48;
          }
        for(i=15;i<=19;i++){        //On copie les valeurs dans la structure provisoire
          Med[d].nuit[i-15]=MedStr.charAt(i)-48;
          } 
        for(i=20;i<=24;i++){        //On copie les valeurs dans la structure provisoire
          Med[d].aco[i-20]=MedStr.charAt(i)-48;
          }
  d=3;
  MedStr="0000011111000002222200000";
          for(i=0;i<=4;i++){        //On copie les valeurs dans la structure provisoire
          Med[d].mat[i]=MedStr.charAt(i)-48;
          }         
        for(i=5;i<=9;i++){        //On copie les valeurs dans la structure provisoire
          Med[d].midi[i-5]=MedStr.charAt(i)-48;
          }
        for(i=10;i<=14;i++){        //On copie les valeurs dans la structure provisoire
          Med[d].soir[i-10]=MedStr.charAt(i)-48;
          }
        for(i=15;i<=19;i++){        //On copie les valeurs dans la structure provisoire
          Med[d].nuit[i-15]=MedStr.charAt(i)-48;
          } 
        for(i=20;i<=24;i++){        //On copie les valeurs dans la structure provisoire
          Med[d].aco[i-20]=MedStr.charAt(i)-48;
          }
  d=4;
  MedStr="1888127772366634555454445";
          for(i=0;i<=4;i++){        //On copie les valeurs dans la structure provisoire
          Med[d].mat[i]=MedStr.charAt(i)-48;
          }         
        for(i=5;i<=9;i++){        //On copie les valeurs dans la structure provisoire
          Med[d].midi[i-5]=MedStr.charAt(i)-48;
          }
        for(i=10;i<=14;i++){        //On copie les valeurs dans la structure provisoire
          Med[d].soir[i-10]=MedStr.charAt(i)-48;
          }
        for(i=15;i<=19;i++){        //On copie les valeurs dans la structure provisoire
          Med[d].nuit[i-15]=MedStr.charAt(i)-48;
          } 
        for(i=20;i<=24;i++){        //On copie les valeurs dans la structure provisoire
          Med[d].aco[i-20]=MedStr.charAt(i)-48;
          }
   EEPROM.put(0, Med);
}

void loop() {
//  EEPROM.get(0, Rec);
//  for(i=0;i<=4;i++){
//    Serial.println(Rec[i].Nom); 
//    for(d=0;d<=4;d++){
//      Serial.print(Rec[i].mat[d]);     
//   }
//   Serial.print("\n");
//   for(d=0;d<=4;d++){
//      Serial.print(Rec[i].midi[d]);     
//   }
//    Serial.print("\n");
//   for(d=0;d<=4;d++){
//      Serial.print(Rec[i].soir[d]);     
//   }
//    Serial.print("\n");
//   for(d=0;d<=4;d++){
//      Serial.print(Rec[i].nuit[d]);     
//   }
//    Serial.print("\n");
//   for(d=0;d<=4;d++){
//      Serial.print(Rec[i].aco[d]);     
//   }
//   Serial.print("\n\n");
//  }
//  
//  delay(1000000);

}
