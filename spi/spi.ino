#include <SPI.h>

const int slaveSelectPin = 10;

void setup() {
    pinMode (slaveSelectPin, OUTPUT);
    SPI.begin();
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);
    SPI.setClockDivider(SPI_CLOCK_DIV128);
}

void loop() {
    digitalWrite(slaveSelectPin,LOW);
    SPI.transfer(1);
    SPI.transfer(2);
    SPI.transfer(3);
    SPI.transfer(4);
    digitalWrite(slaveSelectPin,HIGH);
}
