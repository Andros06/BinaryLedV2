#include <Arduino.h>


//Tildeler fysiske pinner til led og knapp
const int Led1 = 3;
const int Led2 = 4;
const int Led3 = 5;
const int Led4 = 6;
const int Button = 2;

//Lager counter til knapp
int ButtonCounter = 0;

//Lager en variabel for å kunne bruke i void loop
int UpdateCounterFlag = 0;

//Lager array for binær verdi, sørgar for at alle start verdiar er 0
int binaryArray[4] = {0, 0, 0, 0};


//Funksjon for å oppdatere binert array til counter verdi
void UpdateBinaryArray() {

  int tempCounter = ButtonCounter; //lager ein midlertidig variabel for å ikkje endre Buttoncounter

  /* 
  konvertere int til binært tall:
  1. for løkke kjøyrer so lenge "i" er under gitt verdi 4.  "int i = 0; i<4;" i får start verdi 0
  2. kvar gong løkka kjøyre blir "i" plussa på 1. "i++"
  3. "i" sei også kva posisjon i array, begynder på 0. i=0 vil sei binaryArray[0]
  4. "tempCounter & 1" leser av den minst signifikante binær verdien til tempCounter.
      dvs. den konverterer vanlig tall til binær tall og leser av den verdien som har minst innflytelse (tallet lengst til høgre). 
      I binært tall "11001" ville det bli 1 tallet heilt til høgre som er minst signifikant.
  5. binarArray[i] blir tildelt samme verdien som den minst signifikante til tempCounter, also 1 eller 0.
  6. tempCounter >>=1 flytter heile det binære tall rekka eit hakk til høgre og fjerner tallet som var lengst til høgre.
      "11001" ville blitt til "1100" dette gjer at neste gong løkka kjøyrer vil vi lese av det som hadde vore det neste tallet.
      pga dinna fjernar tall fra binær verdi er det lurt å ha den midlertidige variablen for å ikkje redigere ButtonCounter.
  7. repeterer so langt som for løkka bestemmer men 4 gonger er nok til arrayet.    
  */

  for (int i = 0; i < 4; i++) {
    binaryArray[i] = tempCounter & 1;
    tempCounter >>= 1;
  }
}



//Funksjon for å endere UpdateCounterFlag verdi

void counterchange() {
UpdateCounterFlag = 1; // setter kalle variabel til 1
}


void setup() {

  //Setter opp led som outputs
  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  pinMode(Led3, OUTPUT);
  pinMode(Led4, OUTPUT);

  //Forsikre seg om at led er satt til low
  digitalWrite(Led1, LOW);
  digitalWrite(Led2, LOW);
  digitalWrite(Led3, LOW);
  digitalWrite(Led4, LOW);


  //Setter opp knapp for pullup
  pinMode(Button, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Button), counterchange, FALLING);
  
  //Starter seriel kommunikasjon
  Serial.begin(9600);

}

void loop() {

//sjekker etter UpdateCounterFlag og counter verdi, utfører deretter

if (UpdateCounterFlag && ButtonCounter < 15){
  delay(200); //liten delay for å hindre feil verdier
  ButtonCounter += 1;
  UpdateCounterFlag = 0; //Reseter UpdateCounterFlag
  UpdateBinaryArray(); //utfører UpdateBinaryArray
}
else if (UpdateCounterFlag && ButtonCounter >= 15){
  delay(200); //liten delay for å hindre feil verdier
  ButtonCounter = 0;
  UpdateCounterFlag = 0; //Reseter UpdateCounterFlag
  UpdateBinaryArray(); //utfører UpdateBinaryArray
  }


//Skrur av og på led etter binary verdi forhold til array
digitalWrite(Led1, binaryArray[0]);
digitalWrite(Led2, binaryArray[1]);
digitalWrite(Led3, binaryArray[2]);
digitalWrite(Led4, binaryArray[3]);






}


