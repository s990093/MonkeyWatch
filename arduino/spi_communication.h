// spi_communication.h

#ifndef SPI_COMMUNICATION_H
#define SPI_COMMUNICATION_H

#include <Arduino.h>
#include <SPI.h>
#include "config.h"

class SPIMaster
{
public:
    SPIMaster(uint8_t chipSelectPin);
    void begin();
    void transfer(uint8_t slaveSelectPin, const uint8_t *data, size_t length);

private:
    uint8_t chipSelectPin_;
};

class SPISlave
{
public:
    SPISlave(uint8_t slaveSelectPin);
    void begin();
    void listen();

private:
    uint8_t slaveSelectPin_;
};

#endif // SPI_COMMUNICATION_H
