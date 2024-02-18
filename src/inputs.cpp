// 
// 
// 

#include "inputs.h"

Button::Button(int pinNumber, timeT timeType, int inputType)
{
  pin = pinNumber;
  pinMode(pin, inputType);
  Button::filterTime = 20;
  Button::longPressDuration = 600;
  Button::extraLongPressDuration = 2000;
  Button::inputType = inputType;
  Button::timeType = timeType;
  position = digitalRead(pin);
  prevIn = position;

}

Button::Button()
{ }

Switch::Switch(int pinNumber, int inType) : Button(pinNumber, SWITCH, inType)
{
}

Trigger::Trigger(int pinNumber,  int inType) : Button(pinNumber, TRIGGER, inType)
{
}

Toggle::Toggle(int pinNumber, int numStates, int inType) : Button(pinNumber, TOGGLE, inType)
{
  pushNum = 0;
  Toggle::numStates = numStates;
}



stateT Button::getState()
{
  prevPressState = pressState;
  prevState = state;
  if (state != FREE)
    duration = millis() - pressTime;
  if (inputType == INPUT_PULLUP)
    pressState = !filter(pin);
  else
    pressState = filter(pin);
  



  if (!pressState && !prevPressState)
  {
    pressTime = 0;
    state = FREE;
  }

  else if (pressState && !prevPressState)
  {
    pressTime = millis() - filterTime;
    pushNum++;
    state = PUSH;
  }

  else if (pressState && prevPressState)
  {
    if (duration < longPressDuration)
      state = HOLD;
    else if (duration < extraLongPressDuration)
    {
      if (prevState == HOLD)
        state = SHORTPASS;
      else
        state = LONGHOLD;
    }
    else
    {
      if (prevState == LONGHOLD)
        state = LONGPASS;
      else
        state = EXTRALONGHOLD;
    }

  }

  else if (!pressState && prevPressState)
  {
    if (duration < longPressDuration)
      state = RELEASE;
    else if (duration < extraLongPressDuration)
      state = LONGRELEASE;
    else
      state = EXTRALONGRELEASE;
  }
  
  switch (timeType)
  {
  case SIMPLE:
    if (state == SHORTPASS || state == LONGHOLD || state == LONGPASS || state == EXTRALONGHOLD)
      return HOLD;
    else if (state == LONGRELEASE || state == EXTRALONGRELEASE)
      return RELEASE;
    else
      return state;
    break;
  case LONGPRESS:
    if (state == LONGPASS || state == EXTRALONGHOLD)
      return LONGHOLD;
    if (state == EXTRALONGRELEASE)
      return LONGRELEASE;
    else
      return state;
    break;
  case EXTRALONGPRESS:
    return state;
    break;
  case SWITCH:
    if (state == FREE || state == RELEASE || state == LONGRELEASE || state == EXTRALONGRELEASE)
      return FREE;
    else
      return PUSH;
    break;
  case TRIGGER:
    if (state == PUSH)
      return PUSH;
    else if (state == RELEASE || state == LONGRELEASE || state == EXTRALONGRELEASE)
      return RELEASE;
    else
      return FREE;
    break;
  case TRIGGER_W_RELEASE:
    if (state == PUSH)
      return PUSH;
    else if (state == RELEASE || state == LONGRELEASE || state == EXTRALONGRELEASE)
      return RELEASE;
    else
      return FREE;
    break;
  case TOGGLE:
    if (pushNum % numStates)
      return PUSH;
    else
      return FREE;
    break;
  }
  

  

}

bool Button::filter(int pin)
{
  bool in = digitalRead(pin);
  if (in != prevIn)
    switchTime = millis();
  if (millis() - switchTime > filterTime)
    position = in;
  prevIn = in;
  return position;

}


void Button::setFilterTime(int time)
{
  filterTime = time;
}

void Button::setDebounceTime(int time)
{
  filterTime = time;
}

void Button::setLongPressDuration(int time)
{
  longPressDuration = time;
}

void Button::setExtraLongPressDuration(int time)
{
  extraLongPressDuration = time;
}




