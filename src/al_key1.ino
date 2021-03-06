#include "config.h"

void nullfunc()
{
  screen_On_Start = millis();
  screen_On_now = millis();
}

void doubleclick()
{
  if (oledState == OLED_ON)
  {
    Serial.println("doubleclick");
    keyState = DOUBLECLICK;
  }

  screen_On_Start = millis();
  screen_On_now = millis();
}
void click()
{
  if (oledState == OLED_ON)
  {
    Serial.println("click");
    keyState = CLICK;
  }
  screen_On_Start = millis();
  screen_On_now = millis();
}
void longPressStart()
{
  if (oledState == OLED_ON)
  {
    Serial.println("longPressStart");
    keyState = LONGPRESS_START;
  }
  screen_On_Start = millis();
  screen_On_now = millis();
}
void duringLongPress()
{
  if (oledState == OLED_ON)
  {
    screen_On_Start = millis();
    screen_On_now = millis();
  }
  if (button.isLongPressed())
  {
    Serial.print("duringLongPress:");
    Serial.println(button.getPressedTicks());
    keyScreen_Start = millis(); //处理长按界面下的长按
    keyScreen_Now = millis();   //处理长按界面下的长按
    delay(50);
    keyState = LONGPRESS_DURRING;
  }
}
void longPressStop()
{
  if (oledState == OLED_ON)
  {
    screen_On_Start = millis();
    screen_On_now = millis();
  }
  Serial.println("longPressStop");
  keyState = LONGPRESS_END;
}
void key_loop()
{
  switch (keyState)
  {
  case CLICK:
    if (screenState == MAIN_TEMP_SCREEN || screenState == MAIN_HUMI_SCREEN)
    {
      screen_loopEnabled = false;
      screenState = TIPS_SCREEN;
      keyScreen_Start = millis();
      keyScreen_Now = millis();
      keyState = NOKEYDOWN;
    }
    else if (screenState == TIPS_SCREEN || screenState == BLE_SCREEN || screenState == REC_STOP_SCREEN)
    {
      screen_loopEnabled = true;
      Serial.println("anjianfanhui");
      keyState = NOKEYDOWN;
    }
    break;
  case DOUBLECLICK:
    if (screenState == MAIN_TEMP_SCREEN || screenState == MAIN_HUMI_SCREEN || screenState == TIPS_SCREEN)
    {
      screen_loopEnabled = false;
      screenState = BLE_SCREEN;
      keyScreen_Start = millis();
      keyScreen_Now = millis();
      keyState = NOKEYDOWN;
    }
    break;
  case LONGPRESS_END:
    if (screenState == MAIN_TEMP_SCREEN || screenState == MAIN_HUMI_SCREEN || screenState == TIPS_SCREEN)
    {
      if (workingState == NOT_WORKING)
      {
        screen_loopEnabled = false;
        screenState = REC_START_SCREEN;
        workingState = WORKING;
        last_rec_stamp = millis() - rec_span + 2000;
        now_rec_stamp = millis();
        Serial.println("workingState = WORKING;");
        keyState = NOKEYDOWN;
      }
      else if (workingState == WORKING)
      {
        screen_loopEnabled = false;
        screenState = REC_STOP_SCREEN;
        workingState = NOT_WORKING;
        Serial.println("workingState = NOT_WORKING;");
        keyScreen_Start = millis();
        keyScreen_Now = millis();
        keyState = NOKEYDOWN;
      }
    }
    keyState = NOKEYDOWN; //处理长按界面下的长按
    break;
  default:
    break;
  }
}
void key_init()
{
  button.reset(); //清除一下按钮状态机的状态
  button.attachClick(click);
  button.attachDoubleClick(doubleclick);
  button.attachLongPressStart(longPressStart);
  button.attachDuringLongPress(duringLongPress);
  button.attachLongPressStop(longPressStop);
}
void key_attach_null()
{
  button.attachClick(nullfunc);
  button.attachDoubleClick(nullfunc);
  button.attachLongPressStart(nullfunc);
  button.attachDuringLongPress(nullfunc);
  button.attachLongPressStop(nullfunc);
}