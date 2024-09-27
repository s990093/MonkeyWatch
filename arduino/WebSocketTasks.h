// WebSocketTasks.h

#ifndef WEBSOCKET_TASKS_H
#define WEBSOCKET_TASKS_H

#include <ArduinoJson.h>
#include "websocket_server.h"
#include "config.h"
#include "GPIO.h"
#include "tcp_client.h"

extern PrintHelper printHelper;

class MymyWebSocketClient : public WebSocketClient
{
public:
    MymyWebSocketClient(const char *ssid, const char *password);

protected:
    void onMessageCallback(WebsocketsMessage message) override;
};

extern MymyWebSocketClient myWebSocketClient;

#endif // WEBSOCKET_TASKS_H
