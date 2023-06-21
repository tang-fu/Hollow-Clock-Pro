#include "web.h"
#include "led.h"
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

extern int LED_State;
extern int NIGHT_KEY;

#define STEPS_PER_ROTATION 30743  // 4096 * 90 / 12 = 30720 default

WiFiManager wifiManager;
String LocalIP = "";
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ntp1.aliyun.com", 60 * 60 * 8, 30 * 60 * 1000);  //偏移
int currentHour = 0;
int currentMinute = 0;
//int currentSeconds = 0;
int night_mode_flag1 = 23;//默认夜间模式设置为23点——6点
int night_mode_flag2 = 6;

int dt = 20;
int delaytime = 1;
static long prev_pos, pos;
static int num, prev_min, cur_min;
int port[4] = { 16, 14, 12, 13 };
//int port[4] = { 13, 12, 14, 16 };
//int port[4] = { 15, 13, 12, 14 };//nodemcu
int seq[8][4] = {  // sequence of stepper motor control
  { LOW, HIGH, HIGH, LOW },
  { LOW, LOW, HIGH, LOW },
  { LOW, LOW, HIGH, HIGH },
  { LOW, LOW, LOW, HIGH },
  { HIGH, LOW, LOW, HIGH },
  { HIGH, LOW, LOW, LOW },
  { HIGH, HIGH, LOW, LOW },
  { LOW, HIGH, LOW, LOW }
};

void setup() {
  Serial.begin(115200);

  Led_Init();

  pinMode(port[0], OUTPUT);
  pinMode(port[1], OUTPUT);
  pinMode(port[2], OUTPUT);
  pinMode(port[3], OUTPUT);

  //wifiManager.setSTAStaticIPConfig(IPAddress(192, 168, 119, 45), IPAddress(192, 168, 119, 1), IPAddress(255, 255, 255, 0));  //配置静态ip
  wifiManager.autoConnect("Hollow-Clock-Pro");
  LocalIP = WiFi.localIP().toString().c_str();
  //wifiManager.resetSettings();//重置热点信息
  //Serial.println(WiFi.getMode());//查看WiFi模式

  timeClient.begin();
  for (num = 0; num < 10; num++) {
    timeClient.update();
    currentHour = timeClient.getHours();
    currentMinute = timeClient.getMinutes();
    Serial.print("当前时间:");
    Serial.print(currentHour);
    Serial.print(":");
    Serial.println(currentMinute);
  }
  Time_Correction(currentHour);

  ArduinoOTA.setHostname("Hollow_Clock_Pro");
  ArduinoOTA.setPassword("88888888");
  ArduinoOTA.begin();
  Server_Init();
}

void loop() {
  ArduinoOTA.handle();
  Server_handle();

  Led_Control(LED_State);

  cur_min = Get_Current_Time();

  if (prev_min == cur_min) {
    return;
  }
  /*********************************************************/
  prev_min = cur_min;
  pos = (STEPS_PER_ROTATION * cur_min) / 60;
  if (pos > prev_pos) {
    rotate(pos - prev_pos);
  }
  //分钟数从60到1会使pos<prev_pos，需要特殊处理
  if (pos < prev_pos) {
    rotate(STEPS_PER_ROTATION / 60);
  }
  prev_pos = pos;
}
/**
    @brief  控制电机转动
    @param  none
    @retval none
*/
void rotate(int step) {
  static int i, j, phase = 0;
  int delta = (step > 0) ? 1 : 7;

  step = (step > 0) ? step : -step;
  for (j = 0; j < step; j++) {
    phase = (phase + delta) % 8;
    for (i = 0; i < 4; i++) {
      digitalWrite(port[i], seq[phase][i]);
    }
    delay(dt);
    if (dt > delaytime) dt--;
  }
  // power cut
  for (i = 0; i < 4; i++) {
    digitalWrite(port[i], LOW);
  }
}
/**
    @brief  获取当前网络时间
    @param  none
    @retval 返回分钟整数
*/
int Get_Current_Time() {
  timeClient.update();
  currentHour = timeClient.getHours();
  currentMinute = timeClient.getMinutes();
  //currentSeconds = timeClient.getSeconds();
  //Serial.println(currentMinute);//串口检查时间
  if (currentMinute == 0) {
    return 60;
  } else {
    return currentMinute;
  }
}
/**
    @brief  自动校时函数，根据当前网络时间，控制指针自动旋转到指定位置
*/
void Time_Correction(int hour) {
  Led_Control(LED_OFF);  //清除灯效
  int i = 0;
  if (hour >= 12) {
    hour -= 12;
  }
  Serial.print("当前正转校时 小时差为:");
  Serial.println(hour);
  for (i = 1; i <= NUM_LEDS; i++) {
    rotate(STEPS_PER_ROTATION * hour / NUM_LEDS);
    Led_Control(LED_TIME_CORRECTION);
  }
  Serial.println("校准完毕");


  Led_Control(LED_OFF);
}
