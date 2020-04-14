//A0-Аналоговая клавиатура
//LCD 16x4 1604A  RS - 2, E - 3, DB4 - 4, DB5 - 5, DB6 - 6, DB7 - 7
//D8, D9, D10-Реле инкубаторов (D8-Первий D9-Второй D10-Третий)

#include <LiquidCrystal.h>

#include <EEPROM.h>


LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

int  line = 1;
int  stemp1 = 350;
int  stemp2 = 350;
int  stemp3 = 350;
int  rtemp1 = 378;
int  rtemp2 = 378;
int  rtemp3 = 378;
int  analog;
int  days = 0;
int  hours = 0;
int  mins = 0;
int  secs = 0;
int  prog = 0;

byte symbols[4][8] = {
  0b11111, 0b00100, 0b01000, 0b10000, 0b00001, 0b00010, 0b00100, 0b11111, //logo
  0b11100, 0b10100, 0b11100, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, //cels
  0b10001, 0b10011, 0b10011, 0b10101, 0b10101, 0b11001, 0b11001, 0b10001, //ink
  0b00000, 0b00000, 0b00000, 0b11111, 0b11111, 0b00000, 0b00000, 0b00000  //line
};

void syminit() {
  lcd.createChar(1, symbols[0]);
  lcd.createChar(2, symbols[1]);
  lcd.createChar(3, symbols[2]);
  lcd.createChar(4, symbols[3]);
}

void load() {
  stemp1 = EEPROM.get(5, stemp1);
  stemp2 = EEPROM.get(10, stemp2);
  stemp3 = EEPROM.get(15, stemp3);
}

void logo() {
  for (int prog = 0; prog <= 15; prog = prog + 1) {
    lcd.setCursor(1, 0);
    lcd.print("Inkubator v2.2");
    lcd.setCursor(prog, 1);
    lcd.print("\1");
    lcd.leftToRight();
    delay(250);
  }
  lcd.clear();
}

void time() {
  secs = millis() / 1000;
  mins = millis() / 1000 / 60;
  hours = mins / 60;
  days = hours / 24;
}

void time_convert() {
  secs = secs - mins * 60;
  mins = mins - hours * 60;
  hours = hours - days * 24;
}

void choose_menu_lcd() {
  if (analog < 35 && analog > 30) {
    if (line == 1) return;
    else
      line--;
    delay(50);

  } else if (analog < 95 && analog > 75) {
    if (line == 3) return;
    else
      line++;
    delay(50);
  }
}

void menu_lcd() {
  for (int prog = 0; prog <= 15; prog = prog + 1) {
    lcd.setCursor(prog, 1);
    lcd.print("\4");
    lcd.leftToRight();
  }
  if (line == 1) {
    lcd.setCursor(0, 0);
    lcd.print("\3""1");
    lcd.setCursor(4, 0);
    lcd.print(float(stemp1 * 0.1), 1);
    lcd.setCursor(8, 0);
    lcd.print("\2");
    lcd.setCursor(10, 0);
    lcd.print(float(rtemp1 * 0.1), 1);
    lcd.setCursor(14, 0);
    lcd.print("\2");
    if (analog < 5 && analog > -1) {
      stemp1--;
      delay(10);

    }
    if (analog < 170 && analog > 160) {
      stemp1++;
      delay(10);

    }
    EEPROM.write(5, stemp1);

  }
  if (line == 2) {
    lcd.setCursor(0, 0);
    lcd.print("\3""2");
    lcd.setCursor(4, 0);
    lcd.print(float(stemp2 * 0.1), 1);
    lcd.setCursor(8, 0);
    lcd.print("\2");
    lcd.setCursor(10, 0);
    lcd.print(float(rtemp2 * 0.1), 1);
    lcd.setCursor(14, 0);
    lcd.print("\2");
    if (analog < 5 && analog > -1) {
      stemp2--;
      delay(10);

    }
    if (analog < 170 && analog > 160) {
      stemp2++;
      delay(10);

    }
    EEPROM.write(10, stemp2);

  }
  if (line == 3) {
    lcd.setCursor(0, 0);
    lcd.print("\3""3");
    lcd.setCursor(4, 0);
    lcd.print(float(stemp3 * 0.1), 1);
    lcd.setCursor(8, 0);
    lcd.print("\2");
    lcd.setCursor(10, 0);
    lcd.print(float(rtemp3 * 0.1), 1);
    lcd.setCursor(14, 0);
    lcd.print("\2");
    if (analog < 5 && analog > -1) {
      stemp3--;
      delay(10);

    }
    if (analog < 170 && analog > 160) {
      stemp3++;
      delay(10);

    }
    EEPROM.write(15, stemp3);

  }
}

void rele() {
  lcd.setCursor(0, 2);
  lcd.print("ALERT");
  if (rtemp1 <= stemp1) {
    digitalWrite(8, HIGH);

  } else {
    digitalWrite(8, LOW);
    lcd.setCursor(7, 2);
    lcd.print("\3""1");

  }
  if (rtemp2 <= stemp2) {
    digitalWrite(9, HIGH);

  } else {
    digitalWrite(9, LOW);
    lcd.setCursor(10, 2);
    lcd.print("\3""2");

  }
  if (rtemp3 <= stemp3) {
    digitalWrite(10, HIGH);

  } else {
    digitalWrite(10, LOW);
    lcd.setCursor(13, 2);
    lcd.print("\3""3");

  }
}

void uptime_lcd() {
  lcd.setCursor(0, 3);
  lcd.print("UPTIME");
  lcd.setCursor(8, 3);
  lcd.print(hours);
  lcd.setCursor(10, 3);
  lcd.print(":");
  lcd.setCursor(11, 3);
  lcd.print(mins);
  lcd.setCursor(13, 3);
  lcd.print(":");
  lcd.setCursor(14, 3);
  lcd.print(secs);
}

void clear() {
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 2);
  lcd.print("                ");
  lcd.setCursor(0, 3);
  lcd.print("                ");
}

void setup()
{
  lcd.begin(16, 4);
  symbols[3][8];
  syminit();
  logo();
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

}

void loop()
{
  analog = analogRead(A0);
  load();
  choose_menu_lcd();
  menu_lcd();
  rele();
  time();
  time_convert();
  uptime_lcd();
  delay(60);
  clear();
}
