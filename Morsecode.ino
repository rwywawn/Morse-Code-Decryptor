
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal.h>

LiquidCrystal_I2C lcd(0x27,20,4); 
int backlight_state = LOW;
long previous_millis = 0;
long interval = 1000;
unsigned long signal_len,t1,t2;  
int input_pin = 2;              
int led_pin = 4;                 
String code = "";                 
String text="";
void setup() {
  Serial.begin(9600);
  pinMode(input_pin, INPUT_PULLUP); 
  pinMode(led_pin,OUTPUT);

  }
void loop()
{
lcd.init(); 
lcd.backlight();
lcd.setCursor(0,0);
lcd.print(text);
is_dot_dash:
  while (digitalRead(input_pin) == LOW) {}
  t1 = millis();                            
  digitalWrite(led_pin, HIGH);              
  while (digitalRead(input_pin) == HIGH) {}
  t2 = millis();                           
  digitalWrite(led_pin, LOW);             
  signal_len = t2 - t1;                  
  Serial.print(signal_len);
  if (signal_len > 50)                      
    {code += readio();                      
  }
  while ((millis() - t2) < 500)          
  {     
    if (digitalRead(input_pin) == HIGH)
    {
      goto is_dot_dash;
    }
  }
  convertor();                        
}
char readio()
{
  if (signal_len < 600 && signal_len > 50)
  {
    return '.';                      
  }
  else if (signal_len > 600)
  {
    return '-';                       
  }
}
void convertor()
{ static String letters[] = {".-", "-...", "-.-.", 
"-..", ".", "..-.", "--.", "....", "..", ".---", 
"-.-", ".-..", "--", "-.", "---", ".--.", "--.-",
".-.", "...", "-", "..-", "...-", ".--", "-..-", 
"-.--", "--..", "E" };
  int i = 0;
  if (code == ".-.-.-")
  { Serial.print(" ");       
    text=(text+" ");
  }
  else
  { while (letters[i] != "E")  
    {
      if (letters[i] == code)
      {
        Serial.print(char('A' + i));
        text=(text+char('A'+i));
        break;
      }
      i++;
    }
    if (letters[i] == "E")
    { Serial.println("<Wrong input>"); 
      text=(text+"<Wrong input>");
    }
  } code = "";                           
}
