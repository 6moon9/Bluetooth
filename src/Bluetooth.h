#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Json.h>

class Bluetooth
{
    public:
        void setup();
        bool loop();
        char read();
        void print(String data);
        void println(String data);
        String message;
        uint8_t RXpin;
        uint8_t TXpin;
        long bauds = 9600;
        SoftwareSerial serial;
        Json json;
};
