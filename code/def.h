


struct Med {
  char Nom[16];
  unsigned short mat[5];
  unsigned short midi[5];
  unsigned short soir[5];
  unsigned short nuit[5];
  unsigned short aco[5]; //au cas où
};

//enum{MATIN, MIDI, SOIR};

byte Cust1 [8] = {0x1B, 0x13, 0x1b, 0x1b, 0x1b, 0x1b, 0x11, 0x1f};

byte Cust2 [8] = {0b10001, 0b01110, 0b11110, 0b11101, 0b11011, 0b10111, 0b00000, 0b11111};

byte Cust3 [8] = {0b10001, 0b01110, 0b11110, 0b10001, 0b11110, 0b11110, 0b01110, 0b10001};

byte Cust4 [8] = {0b11101, 0b11001, 0b10101, 0b01101, 0b00000, 0b11101, 0b11101, 0b11101};

byte Cust5 [8] = {0b00000, 0b01111, 0b01111, 0b00001, 0b11110, 0b11110, 0b01110, 0b10001};

const byte Mes_Recu = 0xFF;
const byte Mes_Actu = 0x1;
const byte Mes_DemPos = 0x3;
const byte ActuPos_Id1 = 0x4;
const byte ActuPos_Id2 = 0x5;
const byte ActuPos_Id3 = 0x6;
const byte ActuPos_Id4 = 0x7;
const byte ActuPos_Id5 = 0x8;


