//#define USE_V3

#define PZEM_RX_PIN 12
#define PZEM_TX_PIN 11


#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

#ifdef USE_V3
#include <PZEM004Tv30.h>
PZEM004Tv30 pzem(PZEM_RX_PIN, PZEM_TX_PIN);
#endif

#ifndef USE_V3
#include <PZEM004T.h>         //Использовать старую версию библиотеки
IPAddress ip(192,168,1,1);
PZEM004T pzem(PZEM_RX_PIN,PZEM_TX_PIN);
#endif

LiquidCrystal_I2C lcd(0x27,16,2);

float v, a, w, wh;
bool power;

void setup(){
  
  Serial.begin(115200);
  lcd.begin();
  lcd.backlight();

  #ifndef USE_V3
  pzem.setAddress(ip);
  #endif
}

void loop(){
  #ifdef USE_V3
  v = pzem.voltage();
  a = pzem.current();
  w = pzem.power();
  wh = pzem.energy();
  #endif

  #ifndef USE_V3
  v = pzem.voltage(ip);
  a = pzem.current(ip);
  w = pzem.power(ip);
  wh = pzem.energy(ip);
  #endif
  
  Serial.println(String(v));
  updDisplay();
  
}

void updDisplay(){
  if ( (v <= 0) || (isnan(v)) ){
    lcd.setCursor(0, 0);
    lcd.print("       NO       ");
    lcd.setCursor(0, 1);
    lcd.print("      POWER     ");
  } else {
    lcd.setCursor(0, 0);
    lcd.print(formatVal(v) + "V " + formatVal(a) + "A");
    
    lcd.setCursor(0, 1);
    lcd.print(formatVal(w) + "W " + formatVal(wh) + "Wh");
  }
}

String formatVal(float val) {
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
