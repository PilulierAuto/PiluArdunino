/******************
 * Actu.ino
 * Fonctions d'actualisation de l'heure de la posologie
 * 
 * Dernière modification : 21/5/18
 */


void ActuPos(){
  serial=0;
  String NomTemp; //INIT
  String MedStr;
  char charTemp[16];
  byte f=0, e=0, d=25, i=0;
  EEPROM.get(0, Med);
  
  while (!Serial.available()){} //On attend que l'utilisateur entre son nom
    NomTemp=Serial.readString();

  NomTemp.toCharArray(charTemp, 16);
  
  for(e=0;e<5&&d==25;e++){            //On le compare à ceux déjà existants
    if(strcmp(charTemp, Med[e].Nom)) //et on détermine qui c'est (variable d)
      d=e;
  }

  if(d==25){                        //Le nom n'existe pas : envoi du signal d'erreur et fin
    Serial.write(ActuPos_Id_err);
  }
  else{                            //Le nom existe : envoi du signal OK
    Serial.write(ActuPos_Id_OK);
    while (!Serial.available()){}  //On attend  que l'utilisateur entre sa posologie
      if (Serial.read() == ActuPos_Debut){  //Signal de début de la réception
      while (!Serial.available()){}  //On attend  que l'utilisateur entre sa posologie
        MedStr=Serial.readString();

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
        EEPROM.put(0, Med);     //On rentre dans la mémoire EEProm
    }
  }
 serial = 1;    
}

void ActuRTC(){
  serial=0;
  int Hr_temp=0, Mn_temp=0;
  while(Hr_temp<=0)
    Hr_temp=Serial.parseInt();
  while(Mn_temp<=0)
    Mn_temp=Serial.parseInt();
  RTC.read(tm);
  if(tm.Hour!=Hr_temp || tm.Minute!=Mn_temp){
    setTime(Hr_temp, Mn_temp, tm.Second, tm.Day, tm.Month, tm.Year);
    RTC.set(now());
  }
  serial=1;
}
