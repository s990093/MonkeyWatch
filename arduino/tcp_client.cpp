#include "tcp_client.h"

void setupWiFi(PrintHelper printHelper)
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        printHelper.printSuccess("Connecting to WiFi...");
    }
    printHelper.printSuccess("Connected to WiFi");
}

void checkWiFiConnection(PrintHelper printHelper)
{
    if (WiFi.status() != WL_CONNECTED)
    {
        printHelper.printDebug("WiFi disconnected. Reconnecting...");
        setupWiFi(printHelper);
    }
}

// WiFiClient 连接
ResponseData sendGetRequest(const String &endpoint)
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    HTTPClient http;
    String serverAddress = SERVER_ADDRESS + endpoint; // Append the endpoint to the base URL

    Serial.println("GET " + serverAddress);

    http.begin(serverAddress);

    int httpResponseCode = http.GET();
    String responseBody = "";

    if (httpResponseCode > 0)
    {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);

        responseBody = http.getString();
        Serial.println("Response data:");
        Serial.println(responseBody);
    }
    else
    {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }

    http.end();

    // Create and return ResponseData object
    ResponseData response;
    response.statusCode = httpResponseCode;
    response.body = responseBody;
    return response;
}

// 发送 POST 请求
ResponseData sendPostRequest(const String &endpoint, const String &body)
{
    WiFiClient client;
    // 打印调试信息
    Serial.print("Connecting to ");
    Serial.println(SERVER_ADDRESS);

     // 构建 HTTP POST 请求
    String request = "POST " + endpoint + " HTTP/1.1\r\n" +
                     "Host: " + String(SERVER_ADDRESS) + "\r\n" +
                     "Connection: close\r\n" +
                     "Content-Type: application/json\r\n" +
                     "Content-Length: " + String(body.length()) + "\r\n" +
                     "\r\n" +
                     body + "\r\n";

    // 发送请求
    client.print(request);
    Serial.println("POST request sent");

    // 等待服务器响应
    while (client.connected() && !client.available())
    {
        delay(10); // 等待数据
    }

    // 读取响应
    ResponseData response;
    response.statusCode = -1;
    response.body = "";

    while (client.available())
    {
        response.body += client.readStringUntil('\r');
    }

    response.statusCode = 200; // 假设成功的状态码
    Serial.println("Response:");
    Serial.println(response.body);

    // 断开连接
    client.stop();
    Serial.println("Disconnected");

    return response;
}

ResponseData sendPutRequest(const String &endpoint, const String &body)
{
    HTTPClient http;
    ResponseData response;
    http.begin(endpoint);
    http.addHeader("Content-Type", "application/json");
    response.statusCode = http.PUT(body);
    if (response.statusCode > 0)
    {
        response.body = http.getString();
    }
    else
    {
        response.body = "Error on HTTP request";
    }
    http.end();
    return response;
}

ResponseData sendDeleteRequest(const String &endpoint)
{
    HTTPClient http;
    ResponseData response;
    http.begin(endpoint);
    response.statusCode = http.sendRequest("DELETE");
    if (response.statusCode > 0)
    {
        response.body = http.getString();
    }
    else
    {
        response.body = "Error on HTTP request";
    }
    http.end();
    return response;
}