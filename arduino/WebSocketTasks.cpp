// WebSocketTasks.cpp
#include "WebSocketTasks.h"

MymyWebSocketClient::MymyWebSocketClient(const char *ssid, const char *password)
    : WebSocketClient(ssid, password)
{
}

void MymyWebSocketClient::onMessageCallback(WebsocketsMessage message)
{
    printHelper.printKeyValue("Got Message: ", message.data());

    // Create a static JSON buffer
    StaticJsonDocument<200> doc;

    // Parse the JSON message
    DeserializationError error = deserializeJson(doc, message.data());

    // Check for parsing errors
    if (error)
    {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.f_str());
        return;
    }

    // Extract fields from JSON data
    const char *device = doc["device"];
    const char *state = doc["state"];

    // Update current device and state
    this->currentDevice = String(device);
    this->currentState = String(state);

    printHelper.printKeyValue("currentState", currentState);

    if (currentState == STATE_PLAY)
    {
        digitalWrite(OUTPUT_SIGNAL_ARDUINO, LED_ON); // Turn LED on
    }
    else if (currentState == STATE_STOP)
    {
        digitalWrite(OUTPUT_SIGNAL_ARDUINO, LED_OFF); // Turn LED off
    }
    else if (currentState == STATE_ON)
    {
        digitalWrite(OUTPUT_SIGNAL_ESP32, LED_ON); // Turn ESP32 signal on
    }
    else if (currentState == STATE_OFF)
    {
        digitalWrite(OUTPUT_SIGNAL_ESP32, LED_OFF); // Turn ESP32 signal off
    }
    else
    {
        digitalWrite(Debug_LED, LED_OFF);           // Turn LED off (default action)
        digitalWrite(OUTPUT_SIGNAL_ESP32, LED_OFF); // Turn ESP32 signal off (default action)
    }
}
