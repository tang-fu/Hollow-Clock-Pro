# 代码说明 
***

### 准备
请使用ArduinoIDE2.0以下的版本

### 烧录
具体分为两次烧录  
- 烧录hollow-clock-pro.ino到esp8266  
编译前请提前安装相关的依赖库文件  
- 烧录data目录到esp8266  
该目录存放网页相关文件 
具体用于烧录到8266的flash中，以便快速响应  
data目录具体烧录方法参考链接[点击传送](https://www.taichi-maker.com/homepage/esp8266-nodemcu-iot/iot-c/spiffs/upload-files/)

### 具体文件说明
- 关于新增或修改灯效  
1.请在led.cpp文件中led_control()函数中新增选项  
2.并在头文件led.h自定义宏  
3.新增web.cpp中handleLED()函数选项  
4.修改data中的网页文件

### 更新说明

