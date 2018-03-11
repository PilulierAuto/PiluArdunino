int AqPers(){
  Lcd.print("Bonjour");
  while(!Serial.available() > 0){
    if (mouvement )  {      // on a détecté une rotation du bouton
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
  Lcd.write((unsigned char)Pos);// /!\ A VERIFIER /!\
  Serial.print(Pos);
}

void routineInterruption(){
  if (digitalRead(PinA))
    up = digitalRead(PinB);
  else
    up = !digitalRead(PinB);
  mouvement = true;
}

