#include <FastLED.h>
#include "led.h"

int LED_State = LED_ON;  //灯效变量，默认工作灯效
int NIGHT_KEY = 0;       //夜间模式，太晚了自动闭灯（23点至6点），默认关闭
int hue = 0;             //色差
int num_leds = NUM_LEDS;
int num_keys = 0;
extern int currentHour;
extern int night_mode_flag1;
extern int night_mode_flag2;

CRGB leds[NUM_LEDS];

/**
    @brief  初始化led
*/
void Led_Init() {
  LEDS.addLeds<WS2812, LED_PIN, RGB>(leds, NUM_LEDS);  //初始化led
  FastLED.setBrightness(150);
}

/*
    @brief  模式切换前准备
*/
void Led_Ready() {
}

/**
    @brief  led灯控制函数
*/
void Led_Control(int LED_KEYS) {
  if (NIGHT_KEY == 1) {  //夜间模式判断
    if (night_mode_flag1 >= night_mode_flag2) {
      if (currentHour >= night_mode_flag1 || currentHour <= night_mode_flag2) {
        LED_KEYS = LED_OFF;
      } else {
        LED_KEYS = LED_ON;
      }
    } else {
      if (currentHour >= night_mode_flag1 && currentHour <= night_mode_flag2) {
        LED_KEYS = LED_OFF;
      } else {
        LED_KEYS = LED_ON;
      }
    }
  }
  switch (LED_KEYS) {
    case 0:  //灯效关闭
      {
        num_leds = NUM_LEDS;
        num_keys = 0;
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        break;
      }
    case 1:  //工作灯效 彩色RGB
      {
        fill_rainbow(leds, NUM_LEDS, hue, 7);
        FastLED.show();
        delay(30);
        hue <= 255 ? hue++ : hue = 0;  //ledrainbow
        break;
      }
    case 2:  //校时充能灯效/green
      {
        for (num_keys = 0; num_keys < num_leds; num_keys++) {
          FastLED.show();
          leds[num_keys] = CRGB(255, 0, 0);  //g r b
          FastLED.show();
          delay(5);
          leds[num_keys] = CRGB::Black;
        }
        leds[num_keys - 1] = CRGB(255, 0, 0);
        num_leds--;
        break;
      }
    case 3:  //流水灯效
      {
        // FastLED.show();//ticker库使用三目运算符
        // num_keys < NUM_LEDS ? num_keys++ : num_keys = 0;
        // leds[num_keys] = CRGB(207, 82, 224);  //g r b 银蓝色
        // FastLED.show();
        // leds[num_keys] = CRGB::Black;
        // break;
        for (num_keys = 0; num_keys < NUM_LEDS; num_keys++) {
          FastLED.show();
          leds[num_keys] = CRGB(207, 82, 224);  //g r b 银蓝色
          FastLED.show();
          delay(20);
          leds[num_keys] = CRGB::Black;
        }
        break;
      }
    case 4:  //渐变灯效
      {
        fill_gradient(leds, 0, CHSV(50, 255, 255), 20, CHSV(150, 255, 255), LONGEST_HUES);
        FastLED.show();
        break;
      }
  }
}
