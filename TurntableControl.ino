#Arduino table control
#Copyright 2022 intellar@intellar.ca
#Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
#The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.



#define PIN_D2 2
#define PIN_D3 3
#define PIN_D4 4
#define PIN_D5 5
int delayms = 2;
int direction = 1;
int nbRemainingSteps = 0;
void setup(){
  pinMode(PIN_D2,OUTPUT);
  pinMode(PIN_D3,OUTPUT);
  pinMode(PIN_D4,OUTPUT);
  pinMode(PIN_D5,OUTPUT);
  Serial.begin(115200);
  Serial.setTimeout(1);
  nbRemainingSteps = 0;
  delayms = 2;
  direction = 1;

  pinMode(LED_BUILTIN, OUTPUT);


}

void write(int a,int b,int c,int d){
  digitalWrite(PIN_D2,a);
  digitalWrite(PIN_D3,b);
  digitalWrite(PIN_D4,c);
  digitalWrite(PIN_D5,d);
}



void onestepFwd(){ 
  write(1,0,0,0);
  delay(delayms);
  write(1,1,0,0);
  delay(delayms);
  write(0,1,0,0);
  delay(delayms);
  write(0,1,1,0);
  delay(delayms);
  write(0,0,1,0);
  delay(delayms);
  write(0,0,1,1);
  delay(delayms);
  write(0,0,0,1);
  delay(delayms);
  write(1,0,0,1);
  delay(delayms);
}
void onestepRev(){ 
  
  write(1,0,0,1);
  delay(delayms);
  write(0,0,0,1);
  delay(delayms);
  write(0,0,1,1);
  delay(delayms);
  write(0,0,1,0);
  delay(delayms);
  write(0,1,1,0);
  delay(delayms);
  write(0,1,0,0);
  delay(delayms);
  write(1,1,0,0);
  delay(delayms);
  write(1,0,0,0);
  delay(delayms);
}

void loop()
{
  
  
  if(nbRemainingSteps > 0)
  {
    if(direction>0)
      onestepFwd();
    else
      onestepRev();
    nbRemainingSteps--;

  }else
  {
    write(0,0,0,0);
    delay(1);
  }
  if(Serial.available()) {
      String data = Serial.readString();
      data.trim();
      char cmd = data[0];
      String arg = data.substring(1,data.length());     

      if(cmd == 'F')
      {
        direction = 1;
        nbRemainingSteps = arg.toInt();
        Serial.print(cmd);
        Serial.print(nbRemainingSteps);
      }  
      if(cmd == 'R')
      {
        direction = -1;
        nbRemainingSteps = arg.toInt();
        Serial.print(cmd);
        Serial.print(nbRemainingSteps);
      }
      if(cmd == 'D')
      {
        delayms = arg.toInt();
        if(delayms<1)
        {
          delayms = 1;
          Serial.print(cmd);
          Serial.print(" invalid delay");
        }else
        {
          Serial.print(cmd);
          Serial.print(delayms);
        }
        
      }        
    }
}
