#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <Intpressor.h>
#include <Arduino.h>
#include <ArduinoJson.h>

class Bluetooth
{
public:
    Bluetooth(Stream *iSerial, int *iSizes, int iNumValues, char iEndChar);
    bool receive();
    bool send();
    void empty();
    char endChar;
    Stream *serial;
    StaticJsonDocument<300> json;
    DeserializationError lastError;
    class Message
    {
    public:
        int get(int key);
        void set(int key, int value);
        char bytes[Intpressor::MAX_VALUES];
        int values[Intpressor::MAX_VALUES];
        int *sizes;
        int numValues;
    } message;
};

#endif // BLUETOOTH_H
