#ifndef _LED_H_
#define _LED_H_

#define NUM_LEDS 21  //led 灯珠数
#define LED_PIN 4    //led 控制IO

#define LED_GRADIENT 4         //渐变流水灯效
#define LED_BLUE 3             //银蓝流水灯效
#define LED_TIME_CORRECTION 2  //校时灯效
#define LED_ON 1               //工作灯效(rgb流水)
#define LED_OFF 0              //关闭灯效

void Led_Init();
void Led_Control(int LED_KEYS);
void Led_Ready();

#endif
