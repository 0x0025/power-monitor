#include <Wire.h>
#include <PZEM004Tv30.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x3f, 20, 4); //Если дисплей не работает, то заменить на 0x27

float w1, w2, w3, v1, v2, v3, a1, a2, a3, wh1, wh2, wh3;

bool power1, power2, power3 ;

PZEM004Tv30 pzem1(2, 16);  // (RX,TX) connect to TX,RX of PZEM
PZEM004Tv30 pzem2(12, 14); 
PZEM004Tv30 pzem3(D3, D7); 

void setup() {
  Serial.begin(115200);

  pinMode(A0, OUTPUT); 
  
  lcd.begin();
  lcd.backlight();
  
  pzem1.setAddress(0x42);
  pzem2.setAddress(0x42);
  pzem3.setAddress(0x42);

}

void loop() {
  updatePzem();
  Serial.println("pzem1: " + String(v1) + " v " + String(w1) + " w " + "pzem2: " + String(v2) + " v " + String(w2) + " w " + "pzem3: " + String(v3) + " v " + String(w3) + " w");
  updateDisplay();
}

void updateDisplay(){
  String displayStr = "";
  if (power1){
    displayStr += (formatCell(v1) + " ");
  }else{
    displayStr += "       ";
  }

  if (power2){
    displayStr += (formatCell(v2) + " ");
  }else{
    displayStr += "       ";
  }

  if (power3){
    displayStr += (formatCell(v3));
  }else{
    displayStr += "      ";
  }

  lcd.setCursor(0,0);
  lcd.print(displayStr);
  displayStr = "";

  if (power1){
    displayStr += (formatCell(a1) + " ");
  }else{
    displayStr += "  NO   ";
  }

  if (power2){
    displayStr += (formatCell(a2) + " ");
  }else{
    displayStr += "  NO   ";
  }

  if (power3){
    displayStr += (formatCell(a3));
  }else{
    displayStr += "  NO  ";
  }

  lcd.setCursor(0,1);
  lcd.print(displayStr);
  displayStr = "";
  
  if (power1){
    displayStr += (formatCell(w1) + " ");
  }else{
    displayStr += " POWER ";
  }

  if (power2){
    displayStr += (formatCell(w2) + " ");
  }else{
    displayStr += " POWER ";
  }

  if (power3){
    displayStr += (formatCell(w3));
  }else{
    displayStr += " POWER";
  }

  lcd.setCursor(0,2);
  lcd.print(displayStr);
  displayStr = "";

  if (power1){
    displayStr += (formatCell(wh1) + " ");
  }else{
    displayStr += "       ";
  }

  if (power2){
    displayStr += (formatCell(wh2) + " ");
  }else{
    displayStr += "       ";
  }

  if (power3){
    displayStr += (formatCell(wh3));
  }else{
    displayStr += "      ";
  }

  lcd.setCursor(0,3);
  lcd.print(displayStr);
  displayStr = "";
}

String formatCell(float val) {
  if (isnan(val)){
    return "   0.0";
  } 
  else if (val <= 0){
    return "   0.0";
  }
  else if (val < 10){
    return "   " + String(val).substring(0, 3);
  } 
  else if (val < 100){
    return "  " + String(val).substring(0, 4);
  }
  else if (val < 1000){
    return " " + String(val).substring(0, 5);
  }
  else if (val < 10000){
    return String(val).substring(0, 6);
  }
  else if (val < 100000){
    return " " + String(val).substring(0, 5);
  }
  return String(val);
}

void updatePzem(){
  v1 = pzem1.voltage();
  v2 = pzem2.voltage();
  v3 = pzem3.voltage();

  if(isnan(v1)){
    power1 = false;
  } else {
    power1 = true;
  }

  if(isnan(v2)){
    power2 = false;
  } else {
    power2 = true;
  }

  if(isnan(v3)){
    power3 = false;
  } else {
    power3 = true;
  }

  a1 = pzem1.current();
  a2 = pzem2.current();
  a3 = pzem3.current();

  w1 = pzem1.power();
  w2 = pzem2.power();
  w3 = pzem3.power();

  wh1 = pzem1.energy();
  wh2 = pzem2.energy();
  wh3 = pzem3.energy();
}
