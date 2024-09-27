#ifndef CONFIG_H
#define CONFIG_H

// Debug Configuration
/// @todo
#define DEBUG_MODE true // Enable or disable debug mode
#define CpuFrequencyMhz 240
#define CORE_0 0 // Typically used for system tasks
#define CORE_1 1 // Typically used for user tasks
#define CONTINUE_BREATHING true

// SPI Configuration
#define SPI_SELECT_PIN 5

// LED Configuration
#define LED_PIN 13 // Pin number for the LED
const int LED_ARRAY_PINS[] = {23, 22, 21};
#define LED_DELAY_TIME 100
#define NUM_LEDS 3
#define Debug_LED 2
#define OUTPUT_SIGNAL_ARDUINO 23
#define OUTPUT_SIGNAL_ESP32 22

// output configuration
#define OUTPUT_PALYE_MUSIC_PIN 6
#define TIMER_NUMBER 0               // 定时器编号
#define TIMER_PRESCALER 80           // 分频系数
#define TIMER_COUNT_UP true          // 是否向上计数
#define TIMER_INTERVAL_MICROS 500000 // 定时器间隔，单位为微秒

// state configuration
#define STATE_ON "on"
#define STATE_OFF "off"
#define STATE_PLAY "play"
#define STATE_STOP "stop"

// interrupts
#define prescaler 80
#define alarm_value 500000

// Base Configuration
#define SERIAL_BAUD_RATE 115200 // Baud rate for serial communication
#define BASE_DELAY 1000         // Base delay in milliseconds

// WiFi Configuration
#define WIFI_SSID "eric home"    // Your WiFi SSID
#define WIFI_PASSWORD "12345677" // Your WiFi password

// Server Configuration
#define SERVER_ADDRESS "http://49.213.238.75:8000"
#define SERVER_PORT 8000 // Your server port

// MQTT Configuration
#define MQTT_BROKER "your_mqtt_broker"                   // MQTT broker address
#define MQTT_PORT 1883                                   // MQTT broker port
#define MQTT_USER "your_mqtt_username"                   // MQTT username
#define MQTT_PASSWORD "your_mqtt_password"               // MQTT password
#define MQTT_TOPIC_SUBSCRIBE "your/mqtt/subscribe/topic" // MQTT subscription topic
#define MQTT_TOPIC_PUBLISH "your/mqtt/publish/topic"     // MQTT publish topic

// WebSocket Configuration
#define WEBSOCKET_SERVER "49.213.238.75:8000/ws/chat/test/" // WebSocket server address
#define WEBSOCKET_PORT 8000                                 // WebSocket server port
#define WEBSOCKET_TIMEOUT 5000

// Sensor Configuration
#define SENSOR_PIN 34             // Pin number for the sensor
#define SENSOR_TYPE "DHT22"       // Type of sensor (e.g., "DHT22", "DHT11")
#define SENSOR_READ_INTERVAL 2000 // Sensor read interval in milliseconds

// LED Configuration
#define LED_PIN 13     // Pin number for the LED
#define WIFI_OK_PIN 23 // Pin number for the LED
#define LED_ON HIGH    // LED on state
#define LED_OFF LOW    // LED off state

// Additional Configuration Parameters
#define DEVICE_NAME "ESP32"      // Name of your device
#define FIRMWARE_VERSION "1.0.0" // Firmware version
#define HEARTBEAT_INTERVAL 60000 // Heartbeat interval in milliseconds
#define RECONNECT_INTERVAL 10000 // Reconnect interval in milliseconds

// API Configuration
#define API_KEY "your_api_key"           // API key for your service
#define API_ENDPOINT "your_api_endpoint" // API endpoint URL

// Jobs
#define MAX_JOBS 10

// GPIO

// config.h
const int STRAPPING_PINS[] = {0, 2, 4, 5, 12, 15};
const int SPI_FLASH_PINS[] = {6, 7, 8, 9, 10, 11};
const int INPUT_ONLY_PINS[] = {34, 35, 36, 39};

#endif // CONFIG_H
