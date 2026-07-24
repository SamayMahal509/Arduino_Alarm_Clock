#include <LiquidCrystal.h>
int rs = 7;
int en = 8;
int d4 = 9;
int d5 = 10;
int d6 = 11;
int d7 = 12;
int input = 2;
int AlarmInput = 4;
int timeChange = A0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int AlarmOutPut = 5;
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  pinMode(input, INPUT);
 
  pinMode(timeChange, INPUT);
  lcd.setCursor(0,0);
  lcd.print("12:00");
  Serial.begin(9600);
  pinMode(AlarmInput, INPUT);
  pinMode(AlarmOutPut, OUTPUT);
}
int hour = 12;
int min = 0;
int x = 0;

int oldInput = 0;
int curInput = 0;
int ms = 0;
int oldAlarm = 0;
int newAlarm = 0;
boolean changeTime = false;
boolean setAlarmTime = false;

int AlarmHour = 0;
int AlarmMin = 0;
boolean AlarmOn = false;
void loop() {
  if (AlarmOn) {
    digitalWrite(5, HIGH);
    delay(50);
    digitalWrite(5, LOW);
    
  }
  if (hour == AlarmHour && min == AlarmMin && !setAlarmTime) {
     AlarmOn = true;
  }
  else if (hour != AlarmHour || min != AlarmMin) {
    AlarmOn = false;
  }
  curInput = digitalRead(input);
  newAlarm = digitalRead(AlarmInput);


  if (newAlarm == 1 && oldAlarm != 1 && !setAlarmTime) {
    setAlarmTime = true;
  }
  else {
  if (curInput == 1 && oldInput != 1 && !changeTime) {
   
   Serial.println("time "+ changeTime);
   lcd.clear();
   changeTime = true;
  }
  else if (!changeTime && !setAlarmTime) {
    // put your main code here, to run repeatedly:
    delay(100);
    ms++;
    if (hour < 10) {
      x = 1;
    }
    else {
      x = 0;
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(hour);
    lcd.setCursor(2 - x, 0);
    lcd.print(":");
    lcd.setCursor(3 - x, 0);
    if (min < 10) {
      lcd.print(0);
      lcd.setCursor(4 - x, 0);
      lcd.print(min);
    }
    else {
      lcd.print(min);
    }
    if (ms % 600 == 0) {
      ms = 0;
      min++;
    }
   
    if (min == 60) {
      hour = (hour + 1) %  12;
      if (hour == 0) {
        hour = 12;
      }
      min = 0;
    }
   
   
  }
  else if (changeTime){
    int a = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("change the time");
    lcd.setCursor(0, 1);
    hour = floor(analogRead(timeChange) * (770./1014.)/60.);
    min = (((analogRead(timeChange) * 770./1014.)/60. - hour) * 60);
    String time = hour + ":" + min;
    
    if (hour < 1) {
      hour = 12;
    }
    if (hour <= 9) {
      a = 1;
    }
    lcd.print(hour);
    lcd.setCursor(2 - a, 1);
    lcd.print(":");
    lcd.setCursor(3 - a, 1);
    if (min < 10) {
      lcd.print(0);
      lcd.setCursor(4 - a, 1);
    }
    lcd.print(min);
    delay(100);
    if (curInput == 1 && oldInput != 1) {
      changeTime = false;
      ms = 0;
    }
  }
  else if(setAlarmTime) {
    int a = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("change Alarm");
    
    lcd.setCursor(0, 1);
    AlarmHour = floor((analogRead(timeChange) * 770./1014.)/60.);
    AlarmMin = (((analogRead(timeChange) * 770./1014.)/60. - AlarmHour) * 60);
    Serial.println(AlarmHour);
    String time = AlarmHour + ":" + AlarmMin;
    
    if (AlarmHour == 0) {
      AlarmHour = 12;
    }
    if (AlarmHour <= 9) {
      a = 1;
    }
    lcd.print(AlarmHour);
    lcd.setCursor(2 - a, 1);
    lcd.print(":");
    lcd.setCursor(3 - a, 1);
    if (AlarmMin < 10) {
      lcd.print(0);
      lcd.setCursor(4 - a, 1);
    }
    
    lcd.print(AlarmMin);
    delay(100);
     
    if (newAlarm == 1 && oldAlarm != 1) {
      setAlarmTime = false;
      ms = 0;
    }
   

  }
  }
  oldInput = curInput;
  oldAlarm = newAlarm;

}
