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
- 新增OTA远程升级
- 放弃esp8266nodemcu方案，重新绘制PCB，将ULN2003驱动与ESP模组结合在一块PCB上，并预留出灯带接口
- 除视频中的模型外，新设计了新的模型
*** 
### 注意

该项目没有采用电池供电方案，有需求的小伙伴可以自行修改设计，因为电机功耗较大，18650锂电池大约维持50~80h
***
### 项目效果

<img src="https://gitee.com/codesheep-tang/hollow-clock-pro/raw/master/Docs/Pic/pic1.jpg" height="400">
<img src="https://gitee.com/codesheep-tang/hollow-clock-pro/raw/master/Docs/Pic/pic2.jpg" height="400">

### 项目文件说明

- Codes  
[代码说明，点击跳转](https://gitee.com/codesheep-tang/hollow-clock-pro/tree/master/Codes/Hollow-Clock-Pro "代码说明")

- 3Dmodels  
[3d模型文件，点击跳转](https://gitee.com/codesheep-tang/hollow-clock-pro/tree/master/3Dmodels)  
其中包含两个版本

- PCB  
包含原理图和PCB图，导入立创EDA

- Docs  
相关的耗材清单，参考文件，图片等
***

### 使用说明
[演示视频，校时教程](https://www.bilibili.com/video/BV1DL41167Pf/?spm_id_from=333.999.list.card_archive.click&vd_source=2d5350a9e894031d65f0450846227793)
如果你已经准备好了整套设备，请参考[使用说明书，点击跳转]()
***

### 鸣谢
感谢嘉立创提供的免费PCB!
***

### 赞助
如果你觉得这个项目对你有帮助，或者你有新的想法，欢迎你在此基础上继续创作  
并且情况允许的话，可以给我点一下star吗，总之非常感谢支持～
***

### License
This project is licensed under a [Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License](https://creativecommons.org/licenses/by-nc-sa/4.0/).
