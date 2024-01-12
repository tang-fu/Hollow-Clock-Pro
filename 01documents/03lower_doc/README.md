# Lower相关说明 

## 环境准备

请使用ArduinoIDE2.0以下的版本

## 代码烧录

具体分为两次烧录
- 烧录hollow-clock-pro.ino到esp8266  
编译前请提前安装相关的依赖库文件  
- 烧录data目录到esp8266  
该目录存放网页相关文件 
具体用于烧录到8266的flash中，以便快速响应  
data目录具体烧录方法参考链接[点击传送](http://www.taichi-maker.com/homepage/esp8266-nodemcu-iot/iot-c/spiffs/upload-files/)

## 相关说明

### 灯带控制

#### 灯效

新增或修改灯效  

1. 请在led.cpp文件中led_control()函数中新增或修改函数选项  
2. 并在头文件led.h自定义宏  
3. 新增web.cpp中handleLED()函数选项 
4. 修改data中的网页文件

#### 灯珠数量

灯珠数量：更具自己喜好即可 根据灯珠数量，修改led.h中的宏参数`NUM_LEDS`，其中默认为21颗灯珠，不建议太多灯珠，板子功耗未经测试

### 驱动板控制

关于自行使用ESP8266nodemcu控制ULN2003驱动板和LED灯带，请修改`led.h`文件中的第5行的LED控制IO，修改`.ino`文件中第28行的`int` 所对应的电机驱动控制IO

## 更新说明

暂无更新
