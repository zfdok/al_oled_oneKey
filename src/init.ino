#include "config.h"

void hardware_init()
{
  Serial.begin(115200);
  Serial.println("wakeup");
  Wire.begin();
  sht20.begin();
  display.init();
  display.flipScreenVertically();
  key_init();
}

void software_init()
{
  loopStartTime = millis();
  screen_loopEnabled = true;
  show_tip_screen_last = 3000;
  show_BLE_screen_last = 8000;
  show_rec_stop_screen_last = 2000;
  rec_span = 20000;
  screen_On_last_span = 60000;
  screen_Off_to_sleep_span = 5000;
  screen_On_Start = millis();
  screen_On_now = millis();
  workingState = WORKING;
  oledState = OLED_ON;
  screenState = MAIN_TEMP_SCREEN;
  keyState = NOKEYDOWN;
}