#include <LiquidCrystal.h>

#include <LiquidCrystal.h>
#include <Keypad.h>

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

byte pin_rows[ROW_NUM] = {48, 46, 44, 42}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {40, 38, 36, 34}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

// LCD pins <--> Arduino pins
const int RS = 11, EN = 12, D4 = 2, D5 = 3, D6 = 4, D7 = 5;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

void setup()

{
  Serial.begin(9600);
  lcd.begin(16, 2); // set up number of columns and rows
  lcd.setCursor(0, 0);
  lcd.print("Hello");
  lcd.setCursor(2,1);
  lcd.print("World");
}

void loop()
{
  char key = keypad.getKey();
  if(key){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(key);
  }

}