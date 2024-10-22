#include <MaxMatrix.h> //Adding the MaxMatrix Library

int blink = 3;
int blinkDelay = 5; // CHANGE THIS TO SWITCH STARTING DELAY FOR BLINK ANIMATION
int blinkRand = 0;
int blinkRandSet = rand() % 15 + 5; // time between blinks & chance of second blink


char Eye02[] =      {8, 8, B00000000, B00000000, B00111100, B00011111, B00001111, B00000111, B00000011, B00000000};
char Eye01[] =      {8, 8, B00000000, B00000000, B00011000, B11111000, B11110000, B11100000, B11000000, B00000000};


char EyeL02[] =      {8, 8, B00000000, B00000000, B00011000, B00011111, B00001111, B00000111, B00000011, B00000000};
char EyeL01[] =      {8, 8, B00000000, B00000000, B00111100, B11111000, B11110000, B11100000, B11000000, B00000000};


char Mouth01[] =   {8, 8, B00000000, B00000111, B00011111, B01111001, B01100000, B00000000, B00000000, B00000000};
char Mouth02[] =   {8, 8, B00000000, B00000011, B10011111, B11111100, B11100000, B00000000, B00000000, B00000000};
char Mouth03[] =   {8, 8, B11000001, B11100111, B01111110, B00110000, B00000000, B00000000, B00000000, B00000000};
char Mouth04[] =   {8, 8, B11000011, B11110111, B00111100, B00011000, B00000000, B00000000, B00000000, B00000000};

char MouthL01[] =  {8, 8, B11000011, B11101111, B00111100, B00011000, B00000000, B00000000, B00000000, B00000000};
char MouthL02[] =  {8, 8, B10000011, B11100111, B01111110, B00001100, B00000000, B00000000, B00000000, B00000000};
char MouthL03[] =  {8, 8, B00000000, B11000000, B11111001, B00111111, B00000111, B00000000, B00000000, B00000000};
char MouthL04[] =  {8, 8, B00000000, B11100000, B11111000, B10011110, B00000110, B00000000, B00000000, B00000000};

char Nose01[] =    {8, 8, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000};
char NoseL01[] =   {8, 8, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000};


char DED01[] =      {8, 8, B11100000, B11111100, B00111111, B00000011, B00000011, B00111111, B11111100, B11100000};
char DED02[] =      {8, 8, B00000111, B00111111, B11111100, B11000000, B11000000, B11111100, B00111111, B00000111};


int DIN = 2;   // DIN pin of MAX7219 module
int CLK = 4;   // CLK pin of MAX7219 module
int CS = 3;    // CS pin of MAX7219 module
int maxInUse = 12; //Ammount of LED panels in series


//Blinking variables
int column1 = 8;
int column2 = 16;
int column3 = 88;
int column4 = 96;

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
m.writeSprite(0, 0, Eye02);
delay(25);
m.writeSprite(8, 0, Eye01);
delay(25);
m.writeSprite(80, 0, EyeL02);
delay(25);
m.writeSprite(88, 0, EyeL01);
delay(25);

m.writeSprite(16, 0, Mouth01);
delay(25);
m.writeSprite(24, 0, Mouth02);
delay(25);
m.writeSprite(32, 0, Mouth03);
delay(25);
m.writeSprite(40, 0, Mouth04);
delay(25);
m.writeSprite(48, 0, MouthL01);
delay(25);
m.writeSprite(56, 0, MouthL02);
delay(25);
m.writeSprite(64, 0, MouthL03);
delay(25);
m.writeSprite(72, 0, MouthL04);
/*
m.writeSprite(48, 0, Nose01);
m.writeSprite(102, 0, NoseL01);
*/
//delay(5500); //Delay between blinks

/*
  if(1 == 1){ //Hpnestly useless lol

      
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
 */

if(blinkRand > blinkRandSet ){

  for (int i = 0; i < 8; i++) {

        column1 = column1 - 1;
        column2 = column2 - 1;

        column3 = column3 - 1;
        column4 = column4 - 1;
        m.setColumn(column1, B00000000);
        m.setColumn(column2, B00000000);
        m.setColumn(column3, B00000000);
        m.setColumn(column4, B00000000);
        delay(15); 

      } 
      delay(20); //Delay between eyelid opening and closing
  for (int i = 0; i <= 6; i++) {
      column1 = column1 + 1;
      column2 = column2 + 1;
      column3 = column3 + 1;
      column4 = column4 + 1;
      m.setColumn(column2, Eye01[blink]);
      m.setColumn(column1, Eye02[blink]);
      m.setColumn(column4, EyeL01[blink]);
      m.setColumn(column3, EyeL02[blink]);

      delay(blinkDelay);
      blink++;
      blinkDelay =  blinkDelay + 5; // Change number to change increase to speed of blink (negative for faster, remember to not let it get to a negative number)
  }
  column1 = 8;
  column2 = 16;
  column3 = 88;
  column4 = 96;
  blinkDelay = 5; //initial blink speed when the eye opens
  blink = 3;
blinkRandSet = rand() % 15 + 5;
blinkRand = 0;

}
blinkRand++;


  counterDED++;

  if(counterDED >= 750){
    for (int i = 0; i < 6; i++){

      m.writeSprite(8, 0, DED02);
      m.writeSprite(0, 0, DED01);

      m.writeSprite(88, 0, DED02);
      m.writeSprite(80, 0, DED01);
      delay(500);
      m.clear();
      delay(500);
      
    }
    counterDED = 0;

  }
  
}
