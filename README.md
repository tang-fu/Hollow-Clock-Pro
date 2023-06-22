# Hollow-Clock-Pro
RGB炫光3D打印悬浮时钟
***
### 声明 

该项目原作者为[shiura](https://www.youtube.com/@shiura/about)创作的作品[Hollow-Clock-4](https://www.instructables.com/Hollow-Clock-4/)  
**本项目基于原作的 CC-BY-NC-SA 4.0 协议 在原项目基础上做出改进，不用做商业用途，仅供学习参考使用**
***
### 简介

本项目基于Arduino IDE开发  
此次悬浮时钟，在上一个wifi版本的基础上，改进以及新增的功能：
- 新增rgb灯带，预置了3种灯效
- 新增了一键自动配网功能
- 支持反转校时
- 新增网页界面控制时钟，可自行内置其他功能
- 放弃esp8266nodemcu方案，重新绘制PCB，将ULN2003驱动与ESP模组结合在一块PCB上，并预留出灯带接口
- 除视频中的模型外，新设计了新的模型
*** 
### 注意

该项目没有采用电池供电方案，有需求的小伙伴可以自行修改设计，因为电机功耗较大，18650锂电池大约维持50~80h
***
项目效果：  
<img src="https://gitee.com/codesheep-tang/hollow-clock-pro/raw/master/Docs/Pic/pic1.jpg" height="400">
<img src="https://gitee.com/codesheep-tang/hollow-clock-pro/raw/master/Docs/Pic/pic2.jpg" height="400">

### 项目文件说明

- Codes  
[代码说明，点击跳转](https://gitee.com/codesheep-tang/hollow-clock-pro/tree/master/Codes/Hollow-Clock-Pro "代码说明")

- 3Dmodels  
3d模型文件  
其中包含两个版本

***
### 以下内容还未更新，为上一版，请耐心等待跟新！！！
***


> 预览链接[点击传送]()暂时关闭
- Docs  
相关的耗材清单，参考文件，图片等

| 耗材名称          | 规格/型号    | 数量          | 其他 |
| ----------------- | ------------ | ------------ | ---- |
| 铷磁铁            | 8x3mm        | 3            |      |
| 步进电机          | 28BYJ-48     | 1            |      |
| 电机驱动板        | ULN2003      | 1            | 绿板     |
| 自攻螺丝          | M2(6mm,10mm) | 6mm:7,10mm:1 | 4mm可替代6mm   |
| esp8266           | cp2102驱动   | 1            | 注意尺寸大小，有的板子过大，无法放入底座    |
| 线材              | \            | \            |      |

- Codes  
该目录下为arduino程序，需要使用`Arduino IDE`运行  
——time_correction为误差校准程序  
——wifi_main_program为主程序，需要安装三个库文件  
`#include<ESP8266WiFi.h>`  
`#include<NTPClient.h>`  
`#include<WiFiUdp.h>`  
***
## 使用说明
1. 接线说明，程序中`int port[4] = { 15, 13, 12, 14 };`对应8266引脚如下图，分别对应ULN2003驱动板`IN1,IN2,IN3,IN4`，驱动板的电源与接地可以接到`Vin,GND`  
CP2102驱动下载官网:[https://www.silabs.com/interface/usb-bridges/classic/device.cp2102?tab=softwareandtools](https://www.silabs.com/interface/usb-bridges/classic/device.cp2102?tab=softwareandtools)

> ![图片展示](./Docs/Images/esp8266.png)

2. 第一次使用请先烧录该代码`time_corrections`，并将***分针和时针指向12点位置***，该程序会执行12次校准，（这个过程会持续10+分钟）最终回到12点位置，通过最后的误差角度，调整主程序代码中STEPS_PER_ROTATION的数值来进行校准`STEPS_PER_ROTATION = 30720 +- 偏差值`
3. 安装好库文件后，需要将主程序内的`INPUT_YOUR_WIFI_ID`，`INPUT_YOUR_WIFI_PASSWORD`修改为自己的WiFi名和密码，**将分针和时针指向12点位置**，烧录后重新上电，等待连接wifi，指针会自动走向当前时间
4. 如下图，分针时针均指向12点钟
> <img src="./Docs/Images/using_example.jpg" height="534" width="400">
5. [视频展示，校时教程](https://www.bilibili.com/video/BV1U24y1u7f5/?spm_id_from=333.999.0.0&vd_source=2d5350a9e894031d65f0450846227793)
***
## 鸣谢
感谢[@shiura](https://www.youtube.com/@shiura/about)原作者提供的新奇创意  
感谢[@魔光堂_来一点光](https://space.bilibili.com/65500598)提供wifi自主校时的思路
***
## 赞助
如果你觉得这个项目对你有帮助，或者你有新的想法，欢迎你在此基础上继续创作  
并且情况允许的话，可以给我点一下star吗，总之非常感谢支持～
***
## License
This project is licensed under a [Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License](https://creativecommons.org/licenses/by-nc-sa/4.0/).
