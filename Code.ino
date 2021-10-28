#include <LiquidCrystal.h>

const int rs=11, en=10, d4=2, d5=3, d6=4, d7=5;  //LCD pins
const int pirPin=13, pr=A0, relay=12 ;			 //other pins
int prValue,pir,motion=0,flag=0;						 //values
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int calculateprValue() 							 //Function to calculate
{												 //Photoresistor value
  int value= analogRead(pr);
  value=map(value,1,310,0,100);
  return value; 								 //Value of PR
}

void setup()
{
  pinMode(pr, INPUT);
  pinMode(relay,OUTPUT);
  pinMode(pirPin,INPUT);
  digitalWrite(relay,LOW);						 //Switching off relay module if on
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("WELCOME");
  delay(2000);
  lcd.clear();
  lcd.home();
  lcd.print("Calibrating PIR");					 //PIR sensor needs caliberating
  lcd.setCursor(0,1);
  for(int i=0;i<16;i++)
  {
    lcd.print("*");
  	delay(150);
  }
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("CALIBRATED");
  delay(3000);
  lcd.clear();
  lcd.home();
  lcd.print("Brightness: ");
  lcd.setCursor(0,1);
  lcd.print("Motion det.:"); 
}
void loop()
{
  if(prValue==100)								 //Checking if previous value of
  {												 //PR is 100, then we need to clear	
    lcd.setCursor(14,0);						 //3rd digit of value on display
    lcd.print(" ");								 //to observe proper output on lcd
  }
  
  prValue= calculateprValue();
  pir= digitalRead(pirPin);
  if(pir==HIGH && prValue<20)					 //Condition to detect motion as 
  {												 //well as low brightness in the room
    digitalWrite(relay,HIGH);
    if(flag!=1)
    	motion++;
    flag=1;
    lcd.setCursor(12,1);
  	lcd.print(motion);
    delay(5000);
  }
  else{
    digitalWrite(relay,LOW);
    flag=0;
  }
  lcd.setCursor(12,0);
  lcd.print(prValue);
  lcd.setCursor(12,1);
  lcd.print(motion);
  delay(500);
}
