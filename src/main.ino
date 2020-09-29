#include "config.h"

//第二核创建任务代码
void codeForTask1(void *parameter)
{
  while (1) //这是核1 的loop
  {
    delay(10);
    button.tick(); //扫描按键
  }
}

void setup()
{
  hardware_init();
  showWelcome();
  //3. 将任务句柄和任务代码传与某个核连接起来, 开始执行
  xTaskCreatePinnedToCore(codeForTask1, //任务函数名
                          "task1",      //用户起的任务名
                          1000,         //栈区分配大小
                          NULL,         //创建任务时传入的参数
                          1,            //优先级
                          &task1,       //用于传回创建任务的句柄,
                          0);           //用哪个核执行
  software_init();
}
void loop()
{
  if (oledState == OLED_ON)
  {
    getTempAndHumi();
    screen_loop(); //展示和滚屏
    key_loop();
    screen_show(); //OLED最终显示
    upload_while_oled_on();
  }
  oled_on_off_switch();
}
