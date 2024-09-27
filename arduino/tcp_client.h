#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <Arduino.h>
#include <WiFi.h> // 如果使用WiFi连接
#include "config.h"
#include <HTTPClient.h>
#include "PrintHelper.h"
#include "PrintHelper.h"
// 定义服务器地址和端口号

// 定义数据结构
struct RequestData
{
    String endpoint;
    String body; // 可以根据需要定义其他字段
};

struct ResponseData
{
    int statusCode;
    String body; // 可以根据需要定义其他字段
};

// 函数声明
void setupWiFi(PrintHelper printHelper);
void checkWiFiConnection(PrintHelper printHelper);
ResponseData sendGetRequest(const String &endpoint);
ResponseData sendPostRequest(const String &endpoint, const String &body);
ResponseData sendPutRequest(const String &endpoint, const String &body);
ResponseData sendDeleteRequest(const String &endpoint);
#endif // TCP_CLIENT_H
