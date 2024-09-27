#ifndef GPIO_H
#define GPIO_H

#include <Arduino.h>
#include <ESP32Servo.h>
#include <driver/gpio.h>

#include "PrintHelper.h"
#include "config.h"

// extern unsigned long lastPingTime;
// extern const unsigned long pingInterval;

// extern unsigned long lastReconnectAttempt;
// extern const unsigned long reconnectDelay;

void setupSensor(PrintHelper printHelper);
// int readSensor();
// bool buttonPressed(int pin);
void heartbeat(void *parameter);

// //
// void led_run();
// void sg90();
// void song();
#endif
