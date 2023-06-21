#include <ESP8266WebServer.h>
#include <FS.h>
#include "led.h"

extern int LED_State;
extern int currentHour;
extern int currentMinute;
extern String LocalIP;
extern int NIGHT_KEY;
extern int night_mode_flag1;
extern int night_mode_flag2;

String getContentType(String filename);
void handleLED();
void handleTime();
void handleUserRequest();
bool handleFileRead(String resource);
void Server_Init();
void Server_handle();
void handle_Night_Mode();
void handle_Night_Mode_State();

ESP8266WebServer server(80);

void handleLED() {
  String LED = server.arg("LEDstate");
  // Serial.print("接受到指令:");
  // Serial.println(LED);
  if (LED == "1") {
    LED_State = LED_ON;  //工作灯效
    //Serial.println("打开工作灯效");
  }
  if (LED == "0") {
    LED_State = LED_OFF;  //关闭灯效
  }
  if (LED == "3") {
    LED_State = LED_BLUE;  //银蓝流水灯效
  }
  if (LED == "4") {
    LED_State = LED_GRADIENT;  //渐变流水灯效
  }
}
/*
    @brief  处理网络时间
*/
void handleTime() {
  String TimeValue = String(currentHour) + ":" + String(currentMinute);
  server.send(200, "text/plain", TimeValue);
}
/*
    @brief  返回LocalIP
*/
void handleIP() {
  server.send(200, "text/plain", LocalIP);
}
/*
    @brief  夜间模式开关
*/
void handle_Night_Mode() {
  String night = server.arg("Night_Mode_Value");
  if (night == "1") {
    NIGHT_KEY = 1;  //夜间模式开
  }
  if (night == "0") {
    NIGHT_KEY = 0;
  }
}
//夜间模式状态
void handle_Night_Mode_State() {
  String NightMode = "";
  if (NIGHT_KEY == 1) {
    NightMode = "ON";
  }
  if (NIGHT_KEY == 0) {
    NightMode = "OFF";
  }
  server.send(200, "text/plain", NightMode);
}
void Set_Night_Time() {
  String time1 = server.arg("time1");
  String time2 = server.arg("time2");
  int value1 = time1.toInt();
  int value2 = time2.toInt();
  night_mode_flag1 = value1;
  night_mode_flag2 = value2;
}
/*
    @brief  其他处理函数
*/
void handleUserRequest() {
  String reqResource = server.uri();              //获取用户请求资源
  bool fileReadOK = handleFileRead(reqResource);  //通过handleFileRead函数处处理用户请求资源
  if (!fileReadOK) {
    server.send(404, "text/plain", "404 Not Found");
  }
}
/*
    @brief  处理用户访问文件，并判断是否存在,处理浏览器HTTP访问
*/
bool handleFileRead(String resource) {
  if (resource.endsWith("/")) {  // 如果访问地址以"/"为结尾
    resource = "/index.html";    // 则将访问地址修改为/index.html便于SPIFFS访问
  }

  String contentType = getContentType(resource);  // 获取文件类型

  if (SPIFFS.exists(resource)) {             // 如果访问的文件可以在SPIFFS中找到
    File file = SPIFFS.open(resource, "r");  // 则尝试打开该文件
    server.streamFile(file, contentType);    // 并且将该文件返回给浏览器
    file.close();                            // 并且关闭文件
    return true;                             // 返回true
  }
  return false;  // 如果文件未找到，则返回false
}
/*
    @brief  文件类型匹配
*/
String getContentType(String filename) {
  if (filename.endsWith(".htm")) return "text/html";
  else if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".png")) return "image/png";
  else if (filename.endsWith(".gif")) return "image/gif";
  else if (filename.endsWith(".jpg")) return "image/jpeg";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".xml")) return "text/xml";
  else if (filename.endsWith(".pdf")) return "application/x-pdf";
  else if (filename.endsWith(".zip")) return "application/x-zip";
  else if (filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}
/*
    @brief  初始化webserver
*/
void Server_Init() {
  if (SPIFFS.begin()) {  // 启动闪存文件系统
    Serial.println("SPIFFS Started");
  } else {
    Serial.println("SPIFFS Failed to Start");
  }

  server.on("/getIP", handleIP);
  server.on("/setLED", handleLED);
  server.on("/readTime", handleTime);
  server.on("/Night_Mode", handle_Night_Mode);
  server.on("/Set_Night_Time", Set_Night_Time);
  server.on("/Night_Mode_State", handle_Night_Mode_State);
  server.onNotFound(handleUserRequest);
  server.begin();
}
/*
    @brief  监听客户请求并处理
*/
void Server_handle() {
  server.handleClient();
}
