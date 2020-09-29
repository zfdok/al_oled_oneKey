#include "config.h"

// 获取温度和湿度
void getTempAndHumi()
{
  currentTemp = sht20.temperature();
  currentHumi = sht20.humidity();
}
