#include <HID-Project.h>
#include <HID-Settings.h>

#define pinRVUP 16 //pinA
#define pinRVDW 10 //pinB
#define pinMuteButton 6
int lastPositionA = LOW;
int n = LOW;

//--------KEYMAP-------//
// using byte because it's need only one byte of memory instead of int which use two byte
const byte ROWS = 2; // two rows
const byte COLS = 3; // Three columns

char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'}
};

const byte rowPins[ROWS] = {14, 15};
const byte colPins[COLS] = {7, 8, 9}; 

//--------FUNCTION DECLARATIONS-------//
void checkMatrix();
void pressKey(char key);
void checkMuteButton();
void checkRotary();

//--------SETUP-------//
void setup() {
  Serial.begin(9600);
  for(int i=0; i<COLS;i++){
    pinMode(colPins[i], INPUT_PULLUP);
  }
  Consumer.begin(); //used for media keys (reference to HID-Project)
  pinMode(pinRVUP, INPUT_PULLUP);
  pinMode(pinRVDW, INPUT_PULLUP);
  pinMode(pinMuteButton, INPUT_PULLUP); 
}

//--------LOOP-------//
void loop() {
  checkMatrix();
  checkMuteButton();
  checkRotary();
}

//--------FUNCTION IMPLEMENTATIONS-------//
void pressKey(char key){
  switch(key){
    case '1':
      Keyboard.write(KEY_F19);
      delay(100);
      break;
    case '2':
      Keyboard.write(KEY_F20);
      delay(100);
      break;
    case '3':
      Keyboard.write(KEY_F21);
      delay(100);
      break;
    case '4':
      Keyboard.write(KEY_F22);
      delay(100);
      break;
    case '5':
      Keyboard.write(KEY_F23);
      delay(100);
      break;
    case '6':
      Keyboard.write(KEY_F24);
      delay(100);
      break;
    default:
      Serial.print(key);
  }
}

void checkMuteButton(){
  int mute = digitalRead(pinMuteButton);
  if(mute == LOW){
    Serial.println("Key pressed: Vol_Mute");
    Consumer.write(MEDIA_VOL_MUTE);
    delay(250);
  }
}

void checkRotary(){
  n = digitalRead(pinRVUP);
  if((lastPositionA == LOW) && (n == HIGH)){
    if(digitalRead(pinRVDW)== LOW){
      //anticlockwise rotation
      Consumer.write(MEDIA_VOL_DOWN);
      Serial.print("Volume Down!");
    }else{
      //clockwise rotation
      Consumer.write(MEDIA_VOL_UP);
      Serial.print("Volume UP!");
    }
    Serial.print ("\n");
  }
  lastPositionA = n;
}

void checkMatrix() {
    for(int j=0; j<COLS;j++){ 
      byte currentCol = colPins[j];
      for(int i=0; i<ROWS;i++){
        byte currentRow = rowPins[i];
        pinMode(currentRow, OUTPUT);
        digitalWrite(currentRow, LOW);
        if(digitalRead(currentRow)== LOW and digitalRead(currentCol)==LOW){
          char key = keys[i][j];
          pressKey(key);
          Serial.print("Hai premuto il tasto: ");
          Serial.println(key);
          delay(150);
        }
        pinMode(currentRow, INPUT);
      }
    pinMode(currentCol, INPUT_PULLUP);
  }
}
