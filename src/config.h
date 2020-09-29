#if !defined(CONFIG_H)
#define CONFIG_H

#include "SH1106Wire.h"
#include "images.h"
#include "uFire_SHT20.h"
#include "OneButton.h"

#define PIN_INPUT 4
uFire_SHT20 sht20;
OneButton button(PIN_INPUT, true);
SH1106Wire display(0x3c, 21, 22);
//state of OLED
#define OLED_ON 1
#define OLED_OFF 0
//define state of workingState
#define NOT_WORKING 0
#define WORKING 1
//state of Screens
#define MAIN_TEMP_SCREEN 0
#define MAIN_HUMI_SCREEN 1
#define TIPS_SCREEN 2
#define LOGO_SCREEN 4
#define BLE_SCREEN 5
#define TEMP_HUMI_SCROLL_SCREEN 6
#define HUMI_TEMP_SCROLL_SCREEN 7
#define SETTING_SUCCESS 8
#define REC_START_SCREEN 9
#define REC_STOP_SCREEN 10
#define REC_COUNT_SCREEN 11
//state of key
#define NOKEYDOWN 0
#define CLICK 1
#define DOUBLECLICK 2
#define LONGPRESS_START 3
#define LONGPRESS_END 4
#define LONGPRESS_DURRING 5

TaskHandle_t task1; //第二核创建一个任务句柄

float currentTemp;
float currentHumi;
int workingState;                 //工作状态机
int keyState;                     //按键状态机
int oledState;                    //OLED工作状态机
int screenState;                  //屏幕状态机
bool screen_loopEnabled;          //是否允许滚屏
time_t loopStartTime;             //计算主屏幕滚屏的起始时间
time_t loopnowTime;               //计算主屏幕滚屏的当前时间
time_t looptimeSpan;              //计算滚屏间隔时间
time_t keyScreen_Start;           //计算按键触发的当前屏的起始时间
time_t keyScreen_Now;             //计算当前屏的当前时间
time_t screen_On_Start;           //计算息屏的亮屏起点
time_t screen_On_now;             //计算息屏的当前时间
time_t screen_On_last_span;       //亮屏时间间隔
time_t screen_Off_to_sleep_span;  //息屏到休眠时间间隔
time_t show_tip_screen_last;      //提示界面自动返回的时间
time_t show_BLE_screen_last;      //蓝牙界面自动返回的时间
time_t show_rec_stop_screen_last; //停止测量界面自动返回的时间
time_t last_rec_stamp;            //上次记录时间
time_t now_rec_stamp;             //计算现在记录时间
time_t rec_span;                  //记录时间间隔

/********************************************************************/
void hardware_init();
void software_init();
/********************************************************************/
void getTempAndHumi();
/********************************************************************/
void showWelcome();
void screen_loop();
void screen_show();
void upload_while_oled_on();
void oled_on_off_switch();
/********************************************************************/

void key_init();
void key_loop();
void key_attach_null();


#endif // CONFIG_H
