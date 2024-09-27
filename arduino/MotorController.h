#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include <Arduino.h>
#include "config.h"

class MotorController
{
public:
    virtual void begin() = 0;
    virtual void setSpeed(int speed) = 0;
    virtual void stop() = 0;
};

class DCMotorController : public MotorController
{
public:
    DCMotorController(int pin1, int pin2, int enablePin)
        : pin1(pin1), pin2(pin2), enablePin(enablePin) {}

    void begin() override
    {
        pinMode(pin1, OUTPUT);
        pinMode(pin2, OUTPUT);
        pinMode(enablePin, OUTPUT);
        stop();
    }

    void forward()
    {
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
        analogWrite(enablePin, 255); // Full speed
    }

    void backward()
    {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, HIGH);
        analogWrite(enablePin, 255); // Full speed
    }

    void stop() override
    {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        analogWrite(enablePin, 0); // Stop
    }

    void setSpeed(int speed) override
    {
        if (speed < 0)
            speed = 0;
        if (speed > 255)
            speed = 255;
        analogWrite(enablePin, speed);
    }

private:
    int pin1;
    int pin2;
    int enablePin;
};

class StepperMotorController : public MotorController
{
public:
    StepperMotorController(int stepPin, int dirPin)
        : stepPin(stepPin), dirPin(dirPin) {}

    void begin() override
    {
        pinMode(stepPin, OUTPUT);
        pinMode(dirPin, OUTPUT);
        stop();
    }

    void setSpeed(int speed) override
    {
        // Implement stepper motor speed control
    }

    void stepForward()
    {
        digitalWrite(dirPin, HIGH);
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(stepDelay);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(stepDelay);
    }

    void stepBackward()
    {
        digitalWrite(dirPin, LOW);
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(stepDelay);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(stepDelay);
    }

    void stop() override
    {
        digitalWrite(stepPin, LOW);
    }

private:
    int stepPin;
    int dirPin;
    int stepDelay = 1000; // Adjust step delay as needed
};

class ServoMotorController : public MotorController
{
public:
    ServoMotorController(int pin) : pin(pin) {}

    void begin() override
    {
        servo.attach(pin);
        stop();
    }

    void setSpeed(int speed) override
    {
        // For servos, speed control is typically not applicable
    }

    void setPosition(int angle)
    {
        servo.write(angle);
    }

    void stop() override
    {
        servo.write(90); // Neutral position for most servos
    }

private:
    int pin;
    Servo servo;
};

#endif // MOTOR_CONTROLLER_H
