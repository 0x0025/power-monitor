#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 20 chars and 4 line display

float v, a, w, wh;

bool power;

void setup(){
  v = 230.1;
  a = 0.8;
  w = 127.5;
  wh = 94.3;
  
  lcd.begin();
 
  lcd.backlight();
}

void loop(){
  updDisplay();
  
}

void updDisplay(){
  lcd.setCursor(0, 0);
  lcd.print(formatCell(v) + "V " + formatCell(a) + "A");
  
  lcd.setCursor(0, 1);
  lcd.print(formatCell(w) + "W " + formatCell(wh) + "Wh");
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
