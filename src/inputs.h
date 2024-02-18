// inputs.h

#ifndef _INPUTS_h
  #define _INPUTS_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "arduino.h"
#else
  #include "WProgram.h"
#endif

enum stateT
{
  FREE,  // button is not pressed
  PUSH,  // first encounter of pushed button, appear once per getState() invoke
  HOLD,  // button will maintain this state when pressed shorter than longPressDuration ms 
  RELEASE,  // appear once if button is released before longPressDuration ms are passed
  SHORTPASS,  // we still hold the button, longPressDuration ms has passed just now, appear once
  LONGHOLD,  // continious state, while press time is between longPressDuration and extraLongPressDuration
  LONGRELEASE,  // released button before extraLPressDuration has passed
  LONGPASS,  // extraLongPressDuration ms has just passed, appear once
  EXTRALONGHOLD,  // we still hold the button, press time is bigger than extraLongPressDuration
  EXTRALONGRELEASE  // we finally released the button after a looooong time of holding it
};

enum timeT
{
  SIMPLE,  // detects press and hold states
  LONGPRESS,  // also detects longpress
  EXTRALONGPRESS,  // also extralongpress
  SWITCH,  // returns PUSHED while pressed
  TRIGGER,  // returns PUSHED only once pressed, release ignored
  TRIGGER_W_RELEASE,  // returns push and release, otherwise state is free
  TOGGLE
};

class Button
{
protected:
  unsigned long duration, releaseDuration;
  bool filter(int pin);
  bool prevIn, position;
  long pushNum;
public:
  int numStates;
  long filterTime;
  long longPressDuration;
  long extraLongPressDuration;
  Button(int pinNumber, timeT timeType = SIMPLE, int inputType = INPUT_PULLUP);
  Button();
  stateT state, prevState;
  timeT timeType;
  int pin;
  int inputType;
  long pressTime;
  long releaseTime;
  long switchTime;
  bool pressState, prevPressState;
  stateT getState();
  void setFilterTime(int time);
  void setDebounceTime(int time);
  void setLongPressDuration(int time);
  void setExtraLongPressDuration(int time);
};

class Switch : public Button
{
public:
  Switch(int pinNumber, int inType = INPUT_PULLUP);
};

class Trigger : public Button
{
public:
  Trigger(int pinNumber, int inType = INPUT_PULLUP);
};

class Toggle : public Button
{
public:
  Toggle(int pinNumber, int numStates = 2, int inType = INPUT_PULLUP);
};

#endif



