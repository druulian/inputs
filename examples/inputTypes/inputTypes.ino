#include <inputs.h>

Button btn1(12), btn2(11, EXTRALONGPRESS);
Switch sw1(10), sw2(9, INPUT);
Trigger trg(8);
Toggle tgl(7);

void setup()
{
  Serial.begin(9600);
  btn1.setDebounceTime(500);
  sw1.setFilterTime(50);
}


void loop()
{
  Serial.print(btn1.getState());
  Serial.print(' ');
  Serial.print(btn2.getState());
  Serial.print(' ');
  Serial.print(sw1.getState());
  Serial.print(' ');
  Serial.print(sw2.getState());
  Serial.print(' ');
  Serial.print(trg.getState());
  Serial.print(' ');
  Serial.println(tgl.getState());
  delay(50);

}
