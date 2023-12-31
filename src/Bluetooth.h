#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <Intpressor.h>
#include <Arduino.h>

class Bluetooth
{
public:
    Bluetooth(Stream *iSerial, int *iSizes, int iNumValues);
    bool receive();
    bool send();
    void empty();
    Stream *serial;
    class Message
    {
    public:
        int get(int key);
        void set(int key, int value);
        char bytes[Intpressor::MAX_VALUES];
        int values[Intpressor::MAX_VALUES];
        int *sizes;
        int numValues;
        int byteIndex = 0;
    } message;
};

#endif // BLUETOOTH_H
