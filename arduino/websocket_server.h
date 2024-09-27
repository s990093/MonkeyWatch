#ifndef WEBSOCKET_SERVER_H
#define WEBSOCKET_SERVER_H

#include <ArduinoWebsockets.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include "config.h"
#include "PrintHelper.h"

using namespace websockets;
extern PrintHelper printHelper;

class Body
{
public:
    String type;
    String content;

    bool fromJson(const String &jsonString);
};

class WebSocketClient
{
public:
    WebSocketClient(const char *ssid, const char *password);
    virtual ~WebSocketClient() {}

    // 存储接收到的设备和状态信息
    static String currentDevice;
    static String currentState;

    void setup(PrintHelper printHelper);
    void loop();
    String getDevice() const;
    String getState() const;

    void sendMessage(const std::string &jsonString);

protected:
    virtual void onMessageCallback(WebsocketsMessage message) = 0;

private:
    const char *ssid;
    const char *password;

    WebsocketsClient client;

    void connectWebSocket();
    static void onEventsCallback(WebsocketsEvent event, String data);
    static Body body;
};

// void webSocketEvent_v2(WStype_t type, const uint8_t *payload, size_t length);

#endif // WEBSOCKET_SERVER_H
