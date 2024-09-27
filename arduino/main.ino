#include <Arduino.h>
#include "config.h"
#include "PrintHelper.h"
#include "spi_communication.h"
#include "WebSocketTasks.h"

PrintHelper printHelper(DEBUG_MODE);
MymyWebSocketClient myWebSocketClient(WIFI_SSID, WIFI_PASSWORD);
SPIMaster spiMaster(SPI_SELECT_PIN);

bool continueBreathing = CONTINUE_BREATHING; // Global variable visible across the file

TaskHandle_t websocketTaskHandle;
TaskHandle_t spiTaskHandle;

void websocketTask(void *parameter);
void spiTask(void *parameter);

void setup()
{

    setCpuFrequencyMhz(CpuFrequencyMhz);

    Serial.begin(SERIAL_BAUD_RATE);
    setupWiFi(printHelper);
    setupSensor(printHelper);
    myWebSocketClient.setup(printHelper);

    // websocketTask
    xTaskCreatePinnedToCore(
        websocketTask,
        "WebSocket Task",
        10000,
        NULL,
        10,
        &websocketTaskHandle,
        CORE_0); // Core 0

    // // spi
    // xTaskCreatePinnedToCore(
    //     spiTask,        // 任务函数
    //     "SPITask",      // 任务名称
    //     2048,           // 任务堆栈大小（字节）
    //     NULL,           // 传递给任务函数的参数
    //     1,              // 任务优先级（1为最低，configMAX_PRIORITIES-1为最高）
    //     &spiTaskHandle, // 用于存储任务句柄的指针
    //     CORE_0          // core 0
    // );

    // xTaskCreatePinnedToCore(
    //     heartbeat,          // Task function
    //     "Heartbeat Task",   // Task name
    //     10000,              // Stack size (bytes)
    //     &continueBreathing, // Task parameter (passing address of continueBreathing)
    //     0,                  // Priority (0 is the lowest priority)
    //     NULL,               // Task handle (optional)
    //     CORE_1              // Core to run the task on
    // );

    const String tasks[][2] = {
        {"WebSocket Task", "Core 0"},
        {"SPI Task", "Core 0"},
        {"Heartbeat Task", "Core 1"}};

    // 打印系統總結

    printHelper.printSystemSummary("WiFi connected", "Core 0 and Core 1", tasks, 3);
}

void loop()
{
    // Empty loop as FreeRTOS is handling the tasks
}

void websocketTask(void *parameter)
{
    for (;;)
    {
        myWebSocketClient.loop();
        // myWebSocketClient.getDevice();
        // Check if there is an issue with myWebSocketClient
        // if (!myWebSocketClient.isConnected())
        // {
        //     continueBreathing = false; // Stop breathing if WebSocket client is not connected
        //     break;                     // Exit the loop
        // }
        vTaskDelay(1); // Yield to other tasks
    }
}

void spiTask(void *parameter)
{
    spiMaster.begin();

    // 准备要发送z的JSON数据
    DynamicJsonDocument doc(200); // 设置JSON文档大小
    doc["sensor"] = "temperature";
    doc["value"] = 25.5;

    // 将JSON数据转换为字符串
    String jsonString;
    serializeJson(doc, jsonString);

    // 将JSON字符串转换为字节数组
    uint8_t data[jsonString.length() + 1];
    jsonString.getBytes(data, jsonString.length() + 1);

    uint8_t slaveSelectPin = 10; // 从设备的选择引脚为GPIO10
    size_t dataLength = jsonString.length() + 1;

    while (1)
    {
        spiMaster.transfer(slaveSelectPin, data, dataLength);

        printHelper.printInfo("spiMaster Transfer");

        // 延时一段时间
        vTaskDelay(pdMS_TO_TICKS(1000)); // 延时1秒
    }
}