#include <Arduino.h>


//Tildeler fysiske pinner til led og knapp
const int Led1 = 3;
const int Led2 = 4;
const int Led3 = 5;
const int Led4 = 6;
const int Button = 2;

//Lager counter til knapp
int ButtonCounter = 0;


//Lager array for binary verdi
int binaryArray[4] = {0, 0, 0, 0};


//Updaterer binert array til counter verdi
void UpdateBinaryArray() {

  int tempCounter = ButtonCounter;
  for (int i = 0; i < 4; i++) {
    binaryArray[i] = tempCounter & 1;
    tempCounter >>= 1;
  }
}




//enderer counter verdi etter knappe trykk
void counterchange() {

if (ButtonCounter < 15){
  Serial.println("Button pressed");
  ButtonCounter += 1;
  Serial.println(ButtonCounter);
  delay(20);

}
else{
  ButtonCounter = 0;
}

UpdateBinaryArray();

}



void setup() {

  //Setter opp led som outputs
  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  pinMode(Led3, OUTPUT);
  pinMode(Led4, OUTPUT);

  digitalWrite(Led1, LOW);
  digitalWrite(Led2, LOW);
  digitalWrite(Led3, LOW);
  digitalWrite(Led4, LOW);


  //Setter opp knapp for pullup
  pinMode(Button, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), counterchange, FALLING);
  
  //Starter seriel kommunikasjon
  Serial.begin(9600);

}

void loop() {


//Skrur av og på led etter binary verdi
digitalWrite(Led1, binaryArray[0]);
digitalWrite(Led2, binaryArray[1]);
digitalWrite(Led3, binaryArray[2]);
digitalWrite(Led4, binaryArray[3]);


}


