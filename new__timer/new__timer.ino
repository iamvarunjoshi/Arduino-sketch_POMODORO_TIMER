
#include<LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#include<EEPROM.h>

  int val,i=0,eread;
  byte m=25,s=60,comp,cond;   // condition to know wheteher it was terminated or  not
  boolean c=false;
  const int buzzer = 10; byte bytenum;  
  void yidle();   void intro();  void beep();   void fprint(byte m1,byte s1);  void clearmem();
  
  void clearmem()
  {lcd.clear();
  lcd.setCursor(0,0);  lcd.print("clearing EEprom :");  delay(1000);  bytenum=0;  EEPROM.write(0,bytenum);  lcd.setCursor(0,1);   lcd.print("content :");  lcd.print(EEPROM.read(0), DEC);  delay(2000);  fprint(m,s);}
    
void setup() {
  if(EEPROM.read(3)==1)/*checking whether condition is true or not*/
  {m=EEPROM.read(1);  s=EEPROM.read(2);   }
  else
  {m=24;  s=60;    }
  
 lcd.begin(16, 2);  intro();  pinMode(6,INPUT);  pinMode(10,OUTPUT);  pinMode(8,INPUT);  pinMode(9,INPUT);    lcd.print("pomodoro done");  lcd.setCursor(0,1);  lcd.print(EEPROM.read(0),DEC);  delay(1000);  }
 
 void loop() {
 beep(); beep(); waits();}
  
   void TAime()  
  {int pause,wm,ws; fprint(25,60);
    for(m;m>=0;m--)
  {
    for(s;s>0;s--)
  { delay(10);
  EEPROM.write(3,1);
  EEPROM.write(1,m);
  EEPROM.write(2,s);
  val=digitalRead(6);
  /* reset option*/  lcd.clear(); fprint(m,s);   
  if(val==HIGH)
  { lcd.clear();  lcd.setCursor(0,1);  lcd.print("request for reset");  delay(400);  lcd.clear();  waits();  }
 
  pause=digitalRead(8);
  if(pause==HIGH)
  { lcd.clear();  lcd.setCursor(0,0);  lcd.print("pausing");  delay(400);  
   retake:   lcd.setCursor(0,0);  lcd.print("press button: ");  pause=digitalRead(8);  delay(1000);  lcd.setCursor(0,1);  lcd.print(pause);  delay(1000);  lcd.clear();   
   if(pause==LOW)
  {lcd.clear();  lcd.setCursor(0,0);    lcd.print("resume?");  delay(1000);  lcd.setCursor(0,0);    lcd.print("pressbut");  delay(1000);  ws=ws+3;  
  if(ws==60)
  {wm=wm+1; ws=0;}
  if(wm>10)
  {beep();}
 goto retake;
   pause=digitalRead(8);
  if(pause==HIGH)
  { lcd.clear();    lcd.print("resuming");    delay(400);lcd.print("total wait"); lcd.print(wm); lcd.print(":"); lcd.print(ws);     delay(1000);    fprint(m,s);}  }  }
    eread=digitalRead(9);
  if(eread==HIGH)
  { clearmem();  eread=LOW; } comp=1; EEPROM.write(3,comp);}  bytenum++;  comp=0;/*when loop ends*/    
    EEPROM.write(3,comp);
     EEPROM.write(0,bytenum);
     EEPROM.write(1,m);
     EEPROM.write(2,s);}
     EEPROM.write(3,0);
     

  }

void waits(){
  int ws=0,wm=0;
  intro();
   lcd.print("wait state");
  delay(500);
  lcd.clear(); 
  top:
     val=digitalRead(6);
    if(val==HIGH)
  {lcd.clear();  lcd.print("Wait time");  lcd.setCursor(0,1);
  lcd.print(wm);lcd.print(":"); lcd.print(ws);delay(1000); lcd.clear();  lcd.print("Starting timer");
  TAime();  
  }
  else
  ws=ws+1;  delay(1000);
  if(ws==60)
  {wm=wm+1; ws=0;}
  if(wm>10)
  {beep();}
    eread=digitalRead(9);
  if(eread==HIGH)
  { clearmem();
    }
 goto top;} 

      void fprint(byte m1,byte s1)
      {lcd.clear();
    lcd.setCursor(0,0);     lcd.print("Timer's starting"); delay(100);   lcd.clear();     lcd.setCursor(0, 0);     lcd.print("Time left : "); lcd.print(m1,DEC); lcd.print(s1,DEC);
    lcd.setCursor(0,1);    lcd.print("Interval : ");    lcd.print(EEPROM.read(0),DEC); }
  
  void intro ()
{  lcd.setCursor(0, 0);
  lcd.print("initialsing");
   delay(2000);
   lcd.clear();}

        
