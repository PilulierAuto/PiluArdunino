#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4)
void setup() {
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(13,INPUT_PULLUP);
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
}

void loop() {
  if(digitalRead(13)){
      lcd.println(analogRead(13));
    }
}
