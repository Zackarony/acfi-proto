#include <MaxMatrix.h> //Adding the MaxMatrix Library

char Eye02[] =      {8, 8, B00000000, B00000011, B00000111, B00001111, B00011111, B00111100, B00000000, B00000000};
char Eye01[] =      {8, 8, B00000000, B11000000, B11100000, B11110000, B11111000, B00011000, B00000000, B00000000};

char EyeL02[] =     {8, 8, B00000000, B00000011, B00000111, B00001111, B00011111, B00011000, B00000000, B00000000};
char EyeL01[] =     {8, 8, B00000000, B11000000, B11100000, B11110000, B11111000, B00111100, B00000000, B00000000};


char Mouth01[] =   {8, 8, B00000000, B00000000, B00000000, B01100000, B01111001, B00011111, B00000111, B00000000};
char Mouth02[] =   {8, 8, B00000000, B00000000, B00000000, B11100000, B11111100, B10011111, B00000011, B00000000};
char Mouth03[] =   {8, 8, B00000000, B00000000, B00000000, B00000000, B00110000, B01111110, B11100111, B11000001};
char Mouth04[] =   {8, 8, B00000000, B00000000, B00000000, B00000000, B00011000, B00111100, B11110111, B11000011};

char MouthL01[] =  {8, 8, B00000000, B00000000, B00000000, B00000000, B00011000, B00111100, B11101111, B11000011};
char MouthL02[] =  {8, 8, B00000000, B00000000, B00000000, B00000000, B00001100, B01111110, B11100111, B10000011};
char MouthL03[] =  {8, 8, B00000000, B00000000, B00000000, B00000111, B00111111, B11111001, B11000000, B00000000};
char MouthL04[] =  {8, 8, B00000000, B00000000, B00000000, B00000110, B10011110, B11111000, B11100000, B00000000};

char Nose01[] =    {8, 8, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000};
char NoseL01[] =   {8, 8, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000};


char DED01[] =      {8, 8, B11100000, B11111100, B00111111, B00000011, B00000011, B00111111, B11111100, B11100000};
char DED02[] =      {8, 8, B00000111, B00111111, B11111100, B11000000, B11000000, B11111100, B00111111, B00000111};


int DIN = 2;   // DIN pin of MAX7219 module
int CLK = 3;   // CLK pin of MAX7219 module
int CS = 4;    // CS pin of MAX7219 module
int maxInUse = 6; //Ammount of LED panels in series


//Blinking variables
int column1 = 40;
int column2 = 48;
int column3 = 31;
int column4 = 39;

//A counter for the DED animation
int counterDED = 0;


MaxMatrix m(DIN, CS, CLK, maxInUse);



void setup() {
Serial.begin(9600);
randomSeed(analogRead(0));
m.init();
m.setIntensity(1);   //LED intensity up to 15
m.clear();
}

void loop(){
m.writeSprite(32, 0, Eye02);
m.writeSprite(40, 0, Eye01);
m.writesprite(54, 0, EyeL02);
m.writesprite(62, 0, EyeL01);

m.writeSprite(0, 0, Mouth01);
m.writeSprite(8, 0, Mouth02);
m.writeSprite(16, 0, Mouth03);
m.writeSprite(24, 0, Mouth04);
m.writesprite(70, 0, MouthL01);
m.writesprite(78, 0, MouthL02);
m.writesprite(86, 0, MouthL03);
m.writesprite(94, 0, MouthL04);

m.writesprite(48, 0, Nose01);
m.writesprite(102, 0, Nose02);

delay(2500); //Delay between blinks

  if(1 == 1){ //Hpnestly useless lol
for (int i = 0; i < 8; i++) {

        //column1 = column1 - 1;
        //column2 = column2 - 1;

        column3 = column3 + 1;
        column4 = column4 + 1;
        //m.setColumn(column1, 00000000);
        //m.setColumn(column2, 00000000);
        m.setColumn(column3, 00000000);
        m.setColumn(column4, 00000000);
        delay(15); //Delay between eyelid opening and closing

      } 
      
      column1 = column1 - 1;
      column2 = column2 - 1;
      m.setColumn(column1, 00000000);
      m.setColumn(column2, 00000000);
      delay(40);
      column1 = column1 - 1;
      column2 = column2 - 1;
      m.setColumn(column1, B00000000);
      m.setColumn(column2, B00000000);
      delay(40);
      column1 = column1 - 1;
      column2 = column2 - 1;
      m.setColumn(column1, B00111100);
      m.setColumn(column2, B00011000);
      delay(30);
      column1 = column1 - 1;
      column2 = column2 - 1;
      m.setColumn(column1, B00011111);
      m.setColumn(column2, B11111000);
      delay(30);
      column1 = column1 - 1;
      column2 = column2 - 1;
      m.setColumn(column1, B00001111);
      m.setColumn(column2, B11110000);
      delay(15);
      column1 = column1 - 1;
      column2 = column2 - 1;
      m.setColumn(column1, B00000111);
      m.setColumn(column2, B11100000);
      delay(15);
      column1 = column1 - 1;
      column2 = column2 - 1;
      m.setColumn(column1, B00000011);
      m.setColumn(column2, B11000000);
      delay(10);
      column1 = column1 - 1;
      column2 = column2 - 1;
      m.setColumn(column1, B00000000);
      m.setColumn(column2, B00000000);
      delay(10);


      column1 = 40;
      column2 = 48;
      column3 = 31;
      column4 = 39;
    }
 
  counterDED++;

  if(counterDED >= 250){
    for (int i = 0; i < 6; i++){

      m.writeSprite(40, 0, DED02);
      m.writeSprite(32, 0, DED01);
      delay(500);
      m.clear();
      delay(500);
      
    }
    counterDED = 0;

  }
  
delay(1000);
}