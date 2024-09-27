#include "spi_communication.h"

// SPIMaster Implementation
SPIMaster::SPIMaster(uint8_t chipSelectPin) : chipSelectPin_(chipSelectPin) {}

void SPIMaster::begin()
{
    SPI.begin();
}

void SPIMaster::transfer(uint8_t slaveSelectPin, const uint8_t *data, size_t length)
{
    digitalWrite(chipSelectPin_, LED_OFF);                           // Select the slave device
    SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0)); // Start SPI transaction
    SPI.transfer(slaveSelectPin);                                    // Send slave select pin
    for (size_t i = 0; i < length; ++i)
    {
        SPI.transfer(data[i]); // Transfer data byte by byte
    }
    SPI.endTransaction();                 // End SPI transaction
    digitalWrite(chipSelectPin_, LED_ON); // Deselect the slave device
}

// SPISlave Implementation
SPISlave::SPISlave(uint8_t slaveSelectPin) : slaveSelectPin_(slaveSelectPin) {}

void SPISlave::begin()
{
    pinMode(slaveSelectPin_, INPUT);
    SPI.begin();
}

void SPISlave::listen()
{
    if (digitalRead(slaveSelectPin_) == LED_OFF)
    {
        SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0)); // Start SPI transaction
        uint8_t data = SPI.transfer(0);                                  // Dummy transfer to receive data
        // Process received data here
        SPI.endTransaction(); // End SPI transaction
    }
}
