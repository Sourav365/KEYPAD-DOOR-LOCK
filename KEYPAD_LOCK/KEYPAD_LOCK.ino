#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
Servo ser;

const byte r= 4;
const byte c = 3;
char keys[r][c]={
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rPins[r] = {1, 2, 3, 4}; 
byte cPins[c] = {5, 6, 7}; 
Keypad kpad( makeKeymap(keys), rPins, cPins,r,c);

const char key[5]="1234";
char pass[5];
int i=0,j=0;
int state=0;

void setup()
{
  lcd.begin(16, 2);
  ser.attach(9);
  ser.write(0);
}

void loop()
{
  lcd.setCursor(0,0);
  lcd.print("* ENTER PASSWORD");
  delay(100);
  char num=kpad.getKey();
  if (num)
  {
         pass[i]=num;
         lcd.setCursor(i,1);
         lcd.print(num);
         i++; 
         int* p=&i;
         cancel(num,p);/////////CANCEL A DIGIT OR CORRECT
    }

  /*if(num=='*'){
    //servoOff();
    i=0;
    lcd.clear();
    return;state=0;
    }*/
    
  if(i==4){
        pass[i]='\0';
        if(strcmp(pass,key)==0)
        {
           if(state==0)
             {
              open();
              state=1;
             }
          }
        else{
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("!!  RE-ENTER  !!");
            lcd.setCursor(0,1);
            lcd.print("  ! PASSWORD !");
            delay(4000);
            state=0;
            lcd.clear();
            i=0;return;
        }
     }   
}

void open(){
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("* PASS DETECTED");
            lcd.setCursor(0,1);
            lcd.print("* DOOR OPENING");
            servoOn();
            delay(1000);
            lcd.clear();
            i=0;
}
void servoOn()
{
   for(j=0;j<180;j++)
   {
     ser.write(j);
     delay(20);
    }
    state=1;
  }

void servoOff()
{
   for(j=180;j>=0;j--)
     {
        ser.write(j);
        delay(20);
      }
}

void cancel(char num,int* p)
 {
    if(num=='#')
      i=i-2;  
  }
