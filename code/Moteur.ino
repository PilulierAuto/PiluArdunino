void RotPlat(){
  boolean fin=Fin();
  int temp = 0;
  if((MedSeq[(PosPlat+1)%5]!=0 && PosPlat+1<=4) || fin&&PosPlat==4){
    analogWrite(M1Pwm, 45);
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
    analogWrite(M1Pwm, 100);
    digitalWrite(M1HorPin, HIGH);
    digitalWrite(M1TrigPin, LOW);
    delay(100);
  
    do{
      temp = digitalRead(CptCtcPin); 
    }while(temp==0);
    delay(200);
    analogWrite(M1Pwm, 45);
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
    analogWrite(M1Pwm, 100);
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
    analogWrite(M1Pwm, 45);
    delay(200);
    do{
      temp = digitalRead(CptCtcPin); 
    }while(temp==0);
    
    digitalWrite(M1HorPin, HIGH); //arrêt moteur (frein)
    delay(100);

    analogWrite(M1Pwm, 0);       //arrêt moteur  
    digitalWrite(M1HorPin, LOW);
    digitalWrite(M1TrigPin, LOW);
    PosPlat+=3;
  }
  else if(MedSeq[(PosPlat+4)%5]!=0 && PosPlat+4<=4 || fin&&PosPlat==1){
    analogWrite(M1Pwm, 100);
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
    delay(200);
    do{
      temp = digitalRead(CptCtcPin); 
    }while(temp==0);
    analogWrite(M1Pwm, 100);
    delay(200);
    analogWrite(M1Pwm, 100);
    do{
      temp = digitalRead(CptCtcPin); 
    }while(temp==0);
    
    digitalWrite(M1HorPin, HIGH); //arrêt moteur (frein)
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

  analogWrite(M2Pwm, 255); 
  digitalWrite(M2HorPin, LOW);
  digitalWrite(M2TrigPin, HIGH);
  digitalWrite(IREmmPin, HIGH);
  ref = analogRead(IRRecPin) -50; 

  while(i<Nbr){
    do{
      j = analogRead(IRRecPin);
    }while(j>ref);
    i++;
    delay(100);
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




boolean Fin(){
  int i=0;
    for(i=0; i<5; i++)
    {
        if(MedSeq[i]!=0)
        return 0;
    }
    return 1; 
}

