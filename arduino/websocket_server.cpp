#include "websocket_server.h"

// 静态成员初始化
Body WebSocketClient::body;
String WebSocketClient::currentDevice;
String WebSocketClient::currentState;

// WebSocket timeout in milliseconds
unsigned long lastPingTime = 0;
const unsigned long pingInterval = 15000;

unsigned long lastReconnectAttempt = 0;
const unsigned long reconnectDelay = 5000;

WebSocketClient::WebSocketClient(const char *ssid, const char *password)
    : ssid(ssid), password(password)
{
    // Constructor implementation
}

void WebSocketClient::onEventsCallback(WebsocketsEvent event, String data)

{
    if (event == WebsocketsEvent::ConnectionOpened)
    {
        printHelper.printInfo("Connection Opened");
    }
    else if (event == WebsocketsEvent::ConnectionClosed)
    {
        printHelper.printInfo("Connection Closed");
        lastReconnectAttempt = millis(); // 记录断开连接的时间
    }
    else if (event == WebsocketsEvent::GotPing)
    {
        printHelper.printInfo("Got a Ping!");
    }
    else if (event == WebsocketsEvent::GotPong)
    {
        printHelper.printInfo("Got a Pong!");
    }
}

void WebSocketClient::setup(PrintHelper printHelper)
{
    // Connect to WiFi
    WiFi.begin(ssid, password);

    // Wait some time to connect to WiFi
    for (int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++)
    {
        Serial.print(".");
        delay(1000);
    }

    // Run callback when messages are received
    // client.onMessage(onMessageCallback);
    client.onMessage([this](WebsocketsMessage message)
                     { this->onMessageCallback(message); });

    // Run callback when events are occurring
    client.onEvent(onEventsCallback);

    // Connect to WebSocket server
    connectWebSocket();

    printHelper.printDebug("WebSocket client setup complete");
}

void WebSocketClient::loop()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        // 尝试重新连接WiFi
        printHelper.printDebug("WiFi disconnected. Attempting to reconnect...");
        WiFi.reconnect();
        delay(1000);
    }

    if (!client.available() && millis() - lastReconnectAttempt > reconnectDelay)
    {
        // WebSocket断开连接且已经等待了足够长时间，尝试重新连接
        printHelper.printDebug("WebSocket disconnected. Attempting to reconnect...");
        connectWebSocket();
        lastReconnectAttempt = millis();
    }

    client.poll();

    // 发送ping消息作为心跳检测
    if (millis() - lastPingTime > pingInterval)
    {
        client.ping();
        lastPingTime = millis();
    }
}

void WebSocketClient::connectWebSocket()
{
    // Build the WebSocket connection string
    String websocketConnectionString = String("ws://") + WEBSOCKET_SERVER;

    printHelper.printDebug(websocketConnectionString);

    // Connect to server
    client.connect(websocketConnectionString.c_str());

    if (client.available())
    {
        // 连接成功后发送初始消息
        client.send("Hello Server");
    }
}

// 获取最新的设备信息
String WebSocketClient::getDevice() const
{
    return this->currentDevice;
}

// 获取最新的状态信息
String WebSocketClient::getState() const
{
    return this->currentState;
}

// @brief send message
void WebSocketClient::sendMessage(const std::string &jsonString)
{
    // If brightness is a member variable, ensure it is declared in the class header
    int brightness = 0; // Example assignment, change as needed
    StaticJsonDocument<200> doc;
    doc["brightness"] = brightness;

    String jsonStringToSend;
    serializeJson(doc, jsonStringToSend);

    client.send(jsonStringToSend);
}

bool Body::fromJson(const String &jsonString)
{

    return true;
}
