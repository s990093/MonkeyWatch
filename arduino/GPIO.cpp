#include "GPIO.h"
#include "PrintHelper.h"

const int NUM_STRAPPING_PINS = sizeof(STRAPPING_PINS) / sizeof(STRAPPING_PINS[0]);
const int NUM_SPI_FLASH_PINS = sizeof(SPI_FLASH_PINS) / sizeof(SPI_FLASH_PINS[0]);
const int NUM_INPUT_ONLY_PINS = sizeof(INPUT_ONLY_PINS) / sizeof(INPUT_ONLY_PINS[0]);

void setupSensor(PrintHelper printHelper)
{

    pinMode(Debug_LED, OUTPUT);
    pinMode(OUTPUT_SIGNAL_ARDUINO, OUTPUT);
    pinMode(OUTPUT_SIGNAL_ESP32, OUTPUT);

    digitalWrite(OUTPUT_SIGNAL_ARDUINO, LOW);
    digitalWrite(OUTPUT_SIGNAL_ESP32, LOW);

    // for (long i = 0; i < duration * 1000L; i += tone * 2)
    // {
    //     digitalWrite(speakerPin, HIGH);
    //     delayMicroseconds(tone);
    //     digitalWrite(speakerPin, LOW);
    //     delayMicroseconds(tone);
    // }
    //   pinMode(speakerPin, OUTPUT);

    /*


    check


    */
    // 检查是否使用不建议使用的引脚
    // for (int i = 0; i < NUM_STRAPPING_PINS; i++)
    // {
    //     if (pinMode(STRAPPING_PINS[i]) != INPUT)
    //     {
    //         Serial.printf("Error: Using strapping pin GPIO %d\n", STRAPPING_PINS[i]);
    //         while (true)
    //             ; // 停止程序
    //     }
    // }

    // for (int i = 0; i < NUM_SPI_FLASH_PINS; i++)
    // {
    //     if (pinMode(SPI_FLASH_PINS[i]) != INPUT)
    //     {
    //         Serial.printf("Error: Using SPI flash pin GPIO %d\n", SPI_FLASH_PINS[i]);
    //         while (true)
    //             ; // 停止程序
    //     }
    // }

    // for (int i = 0; i < NUM_INPUT_ONLY_PINS; i++)
    // {
    //     if (pinMode(INPUT_ONLY_PINS[i]) != INPUT)
    //     {
    //         Serial.printf("Error: Using input-only pin GPIO %d\n", INPUT_ONLY_PINS[i]);
    //         while (true)
    //             ; // 停止程序
    //     }
    // }
    printHelper.printDebug("Sensor setup complete");
}

void heartbeat(void *parameter)
{
    bool *continueBlinkingPtr = (bool *)parameter; // Cast parameter to bool pointer

    for (;;)
    {
        if (*continueBlinkingPtr) // Dereference the pointer to check the value
        {
            digitalWrite(Debug_LED, LED_ON); // Turn LED on
            vTaskDelay(pdMS_TO_TICKS(20));   // Delay 500 milliseconds (half second)

            digitalWrite(Debug_LED, LED_OFF); // Turn LED off
            vTaskDelay(pdMS_TO_TICKS(20));    // Delay 500 milliseconds (half second)
        }
        else
        {
            digitalWrite(Debug_LED, LED_OFF); // Ensure LED is off when blinking is stopped
            vTaskDelay(pdMS_TO_TICKS(100));   // Delay to conserve CPU resources
        }
    }
}
