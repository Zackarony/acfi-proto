#include <MaxMatrix.h> //Adding the MaxMatrix Library
#include "Adafruit_VEML7700.h" //Adding VEML Library

/*
*   Protogen LED head program. Check the GitHub at https://github.com/Zackarony/acfi-proto to learn about it
*   Write your own LED face animation! The ones use in this program are all UPSIDE-DOWN due to how the hardware was mounted by the protogen it was designed for -_-
*/

Adafruit_VEML7700 veml = Adafruit_VEML7700(); //Dunno, without this the VEML7700 lux sensor is completely useless so...
int vbright; //Variable for VEML lux brightness

int blink = 3; //The row which the blink animation starts on the LED pannels. It changes as it moves down the panel
unsigned int blinkDelay = 5; // CHANGE THIS TO SWITCH STARTING DELAY FOR BLINK ANIMATION
unsigned int blinkRand = 0; 

int blinkRandSet = rand() % 20 + 10; //Second number is lower bound, first is the higher bound when added to the lower.
//There is a second one you have to change on line 181

bool mouthOpen = false; //This is so that the eyes don't blink when the mouth is open (Will remove for 2 core version)


//Bunch of stuff for getting samples of the voice detection. SHOUTOUT
const int SAMPLE_TIME = 125;
unsigned long millisCurrent;
unsigned long millisLast = 0;
unsigned long millisElapsed = 0;
int sampleBufferValue = 0;





char EyeBoot02[] = {8, 8, B11111111, B10000000, B10000000, B10000000, B10000000, B10000000, B10000000, B11111111};
char EyeBoot01[] = {8, 8, B11111110, B00000010, B00000011, B00000011, B00000011, B00000011, B00000010, B11111110};

char EyeBoot02A[] = {8, 8, B11111111, B11110000, B11110000, B11110000, B11110000, B11110000, B11110000, B11111111};
char EyeBoot02B[] = {8, 8, B11111111, B11111110, B11111110, B11111110, B11111110, B11111110, B11111110, B11111111};
char EyeBoot02C[] = {8, 8, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111};
char EyeBoot01C[] = {8, 8, B11111110, B11000010, B11000011, B11000011, B11000011, B11000011, B11000010, B11111110};
char EyeBoot01D[] = {8, 8, B11111110, B11110010, B11110011, B11110011, B11110011, B11110011, B11110010, B11111110};
char EyeBoot01E[] = {8, 8, B11111110, B11111110, B11111111, B11111111, B11111111, B11111111, B11111110, B11111110};


char EyeBootL02[] = {8, 8, B01111111, B01000000, B11000000, B11000000, B11000000, B11000000, B01000000, B01111111};
char EyeBootL01[] = {8, 8, B11111111, B00000001, B00000001, B00000001, B00000001, B00000001, B00000001, B11111111};

char EyeBootL01A[] = {8, 8, B11111111, B00001111, B00001111, B00001111, B00001111, B00001111, B00001111, B11111111};
char EyeBootL01B[] = {8, 8, B11111111, B01111111, B01111111, B01111111, B01111111, B01111111, B01111111, B11111111};
char EyeBootL01C[] = {8, 8, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111};
char EyeBootL02C[] = {8, 8, B01111111, B01000011, B11000011, B11000011, B11000011, B11000011, B01000011, B01111111};
char EyeBootL02D[] = {8, 8, B01111111, B01001111, B11001111, B11001111, B11001111, B11001111, B01001111, B01111111};
char EyeBootL02E[] = {8, 8, B01111111, B01111111, B11111111, B11111111, B11111111, B11111111, B01111111, B01111111};


char BootMouthL01[] = {8, 8, B00000000, B11110100, B10010110, B11010110, B00010101, B00010101, B11110100, B00000000};
char BootMouthL02[] = {8, 8, B00000000, B10100110, B10100110, B10100110, B10100110, B10100110, B10101111, B00000000};
char BootMouthL03[] = {8, 8, B00000000, B01111011, B01001010, B01001010, B01001010, B01001010, B01111011, B00000000};
char BootMouthL04[] = {8, 8, B00000000, B11011110, B01010010, B01001110, B01001110, B01010010, B11011110, B00000000};

char BootMouth01[] = {8, 8, B00000000, B11110100, B10010110, B11010110, B00010101, B00010101, B11110100, B00000000};
char BootMouth02[] = {8, 8, B00000000, B10100110, B10100110, B10100110, B10100110, B10100110, B10101111, B00000000};
char BootMouth03[] = {8, 8, B00000000, B01111011, B01001010, B01001010, B01001010, B01001010, B01111011, B00000000};
char BootMouth04[] = {8, 8, B00000000, B11011110, B01010010, B01001110, B01001110, B01010010, B11011110, B00000000};



char Eye02[] =      {8, 8, B00000000, B00000000, B00111100, B00011111, B00001111, B00000111, B00000011, B00000000};
char Eye01[] =      {8, 8, B00000000, B00000000, B00011000, B11111000, B11110000, B11100000, B11000000, B00000000};

char EyeL02[] =      {8, 8, B00000000, B00000000, B00011000, B00011111, B00001111, B00000111, B00000011, B00000000};
char EyeL01[] =      {8, 8, B00000000, B00000000, B00111100, B11111000, B11110000, B11100000, B11000000, B00000000};


char Mouth01[] =   {8, 8, B00000000, B00000001, B00000011, B00000110, B00001100, B00011000, B00110000, B01100000};
char Mouth02[] =   {8, 8, B00000000, B11000001, B11100111, B00111110, B00011000, B00000000, B00000000, B00000000};
char Mouth03[] =   {8, 8, B00000000, B10000011, B11101111, B01111100, B00011000, B00000000, B00000000, B00000000};
char Mouth04[] =   {8, 8, B00000000, B10000000, B11000111, B01111110, B00111000, B00000000, B00000000, B00000000};

char OpenMouth01[] =   {8, 8, B00000000, B00000001, B00000011, B00000111, B00001110, B00011100, B00111000, B01100000};
char OpenMouth02[] =   {8, 8, B00000000, B11000001, B11100111, B11111111, B01111111, B00111110, B00011000, B00000000};
char OpenMouth03[] =   {8, 8, B00000001, B10000011, B11101111, B11111111, B11111111, B01111111, B00011100, B00001000};
char OpenMouth04[] =   {8, 8, B10000000, B11100011, B11111111, B11111111, B11111111, B11111111, B01111110, B00111000};


char MouthL01[] =  {8, 8, B00000000, B00000001, B11100011, B01111110, B00011100, B00000000, B00000000, B00000000};
char MouthL02[] =  {8, 8, B00000000, B11000001, B11101111, B00111110, B00011000, B00000000, B00000000, B00000000};
char MouthL03[] =  {8, 8, B00000000, B10000011, B11100111, B01111100, B00011000, B00000000, B00000000, B00000000};
char MouthL04[] =  {8, 8, B00000000, B10000000, B11000000, B01100000, B00110000, B00011000, B00001100, B00000110};

char OpenMouthL01[] = {8, 8, B00000001, B11100011, B11111111, B11111111, B11111111, B11111111, B01111110, B00011100};
char OpenMouthL02[] = {8, 8, B10000000, B11000001, B11101111, B11111111, B11111111, B11111110, B00111000, B00010000};
char OpenMouthL03[] = {8, 8, B00000000, B10000011, B11100111, B11111111, B11111110, B01111100, B00011000, B00000000};
char OpenMouthL04[] = {8, 8, B00000000, B10000000, B11000000, B11100000, B01110000, B00111000, B00011100, B00000110};

char Nose01[] =    {8, 8, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000};
char NoseL01[] =   {8, 8, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000};


char DED01[] =      {8, 8, B11100000, B11111100, B00111111, B00000011, B00000011, B00111111, B11111100, B11100000};
char DED02[] =      {8, 8, B00000111, B00111111, B11111100, B11000000, B11000000, B11111100, B00111111, B00000111};



int DIN = 6;   // DIN pin of MAX7219 module
int CLK = 2;   // CLK pin of MAX7219 module
int CS = 4;    // CS pin of MAX7219 module
int maxInUse = 12; //Ammount of LED panels in series


//Blinking variables. They're just the starting column positions of the eye panels
int column1 = 8;
int column2 = 16;
int column3 = 88;
int column4 = 96;

int counterDED = 0;

MaxMatrix m(DIN, CS, CLK, maxInUse);

void setup() {
  
Serial.begin(115200);
veml.begin();
randomSeed(analogRead(0));
m.init();
m.setIntensity(0);   //LED intensity from 0-15
m.clear();
boot();
setBrightness();
face();
}

void loop(){
/* 
  You're going to see this "read()" command a LOT in this program. This is due to how the program grabs sound and uses it to run the mouth animation.
  I wasn't getting quick enough reads due to the speed of the code on a single core machine (In this case, an Arduino Nano),
  so I had to just litter the runtime with the "read()" command (which grabs microphone data and tells the microcontroler if the user is talking, so it can open the mouth on the LEDs).
  This is a quick fix to a problem I haven't figured out how to write better on a single core microcontroler. 
  It can easily be solved however via hardware by using something with a dual-core (Like an ESP32, as I do in future versions).
*/
read();

setBrightness();
mouth();
read();

if(blinkRand > blinkRandSet && mouthOpen == false){ 

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
    blinkDelay =  blinkDelay + 5; //Change number to change increase to speed of blink (subtract for faster, add for slower)
  }
  column1 = 8;
  column2 = 16;
  column3 = 88;
  column4 = 96;
  blinkDelay = 5; //initial blink speed when the eye opens
  blink = 3;
  blinkRandSet = rand() %  15 + 10; //Change this to whatever you have at the top
  blinkRand = 0;
}
read();
blinkRand++;
read();
counterDED++;
read();
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
    boot();
    counterDED = 0;
    face();
  }

read();
}


void read(){ //Reads the value of the microphone
  if (digitalRead(12) == HIGH){
    sampleBufferValue++;
  }
}

void mouth(){ //Runs mouth opening code

  read();
  millisCurrent = millis();
  read();
  millisElapsed = millisCurrent - millisLast;
  read();

  if (digitalRead(12) == HIGH){
    sampleBufferValue++;
  }
  read();
  if(sampleBufferValue > 0){
    open();
    if (digitalRead(12) == HIGH){
    sampleBufferValue++;
  }
  read();
  mouthOpen = true;
  read();
  blinkRand--;
  read();
  }else{
    close();
    mouthOpen = false;
  }
  read();
Serial.println(sampleBufferValue);
//Serial.println(digitalRead(12));
if (millisElapsed > SAMPLE_TIME){
    sampleBufferValue = 0;
    millisLast = millisCurrent;
  }
  read();
}

void boot(){ //Boot animation
m.clear();
m.writeSprite(0, 0, EyeBoot02);
delay(25);
m.writeSprite(88, 0, EyeBootL01);
delay(25);
m.writeSprite(8, 0, EyeBoot01);
delay(25);
m.writeSprite(80, 0, EyeBootL02);
delay(25);
m.writeSprite(72, 0, BootMouthL04);
delay(25);
m.writeSprite(40, 0, BootMouth04);
delay(25);
m.writeSprite(64, 0, BootMouthL03);
delay(25);
m.writeSprite(32, 0, BootMouth03);
delay(25);
m.writeSprite(56, 0, BootMouthL02);
delay(25);
m.writeSprite(24, 0, BootMouth02);
delay(25);
m.writeSprite(48, 0, BootMouthL01);
delay(25);
m.writeSprite(16, 0, BootMouth01);
delay(1000);
m.writeSprite(0, 0, EyeBoot02A);
m.writeSprite(88, 0, EyeBootL01A);
delay(1000);
m.writeSprite(0, 0, EyeBoot02B);
m.writeSprite(88, 0, EyeBootL01B);
delay(1000);
m.writeSprite(0, 0, EyeBoot02C);
m.writeSprite(88, 0, EyeBootL01C);
m.writeSprite(8, 0, EyeBoot01C);
m.writeSprite(80, 0, EyeBootL02C);
delay(1000);
m.writeSprite(8, 0, EyeBoot01D);
m.writeSprite(80, 0, EyeBootL02D);
delay(1000);
m.writeSprite(8, 0, EyeBoot01E);
m.writeSprite(80, 0, EyeBootL02E);
delay(1000);

m.clear();
delay(500);
}

void setBrightness(){ //Sets the brightness based on outside conditions
  vbright = veml.readLux();
  vbright = constrain(vbright, 0, 150);
  vbright = map(vbright, 0, 150, 0, 15);
  m.setIntensity(vbright); 
}

void open(){ //Opens mouth
  read();
  m.writeSprite(48, 0, OpenMouthL01);
  m.writeSprite(40, 0, OpenMouth04);
  m.writeSprite(56, 0, OpenMouthL02);
  m.writeSprite(32, 0, OpenMouth03);
  m.writeSprite(64, 0, OpenMouthL03);
  m.writeSprite(24, 0, OpenMouth02);
  m.writeSprite(72, 0, OpenMouthL04);
  m.writeSprite(16, 0, OpenMouth01);
  read();
}

void close(){ //Closes mouth
  read();
  m.writeSprite(16, 0, Mouth01);
  m.writeSprite(72, 0, MouthL04);
  m.writeSprite(24, 0, Mouth02);
  m.writeSprite(64, 0, MouthL03);
  m.writeSprite(32, 0, Mouth03);
  m.writeSprite(56, 0, MouthL02);
  m.writeSprite(40, 0, Mouth04);
  m.writeSprite(48, 0, MouthL01);
  read();
}

void face(){ //Resets the face to default
m.writeSprite(0, 0, Eye02);
m.writeSprite(88, 0, EyeL01);
delay(50);
m.writeSprite(8, 0, Eye01);
m.writeSprite(80, 0, EyeL02);
delay(50);
m.writeSprite(16, 0, Mouth01);
m.writeSprite(72, 0, MouthL04);
delay(50);
m.writeSprite(24, 0, Mouth02);
m.writeSprite(64, 0, MouthL03);
delay(50);
m.writeSprite(32, 0, Mouth03);
m.writeSprite(56, 0, MouthL02);
delay(50);
m.writeSprite(40, 0, Mouth04);
m.writeSprite(48, 0, MouthL01);
delay(500);
}

/*
*  This really was a lot of fun. I'm glad I got to work on it and I am hopeful it will be used and added onto for a very long time.
*  To one certain protogen: I'll see you at dinner, I made french toast.
*/ 
