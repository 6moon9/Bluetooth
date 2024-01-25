#include <Arduino.h>

#include "Bluetooth.h"

Bluetooth::Bluetooth(Stream *iSerial, int *iSizes, int iNumValues, char iEndChar)
{
    serial = iSerial;
    endChar = iEndChar;
    message.sizes = iSizes;
    message.numValues = iNumValues;
    memset(message.bytes, 0, sizeof(message.bytes));
    memset(message.values, 0, sizeof(message.values));
}

/**
 * Function to call each loop of the program
 *
 * @return bool true if a complet new message is detected and false otherwise
 */
bool Bluetooth::receive()
{
    while (serial->available() > 0)
    {
        char c = serial->read();
        if (c == '.')
        {
            lastError = deserializeJson(json, *serial);
            if (lastError == DeserializationError::Ok)
            {
                Intpressor::extract(json["a"], message.sizes, message.numValues, message.values);
                json.clear();
                return true;
            }
        }
    }
    return false;
}

/**
 * Function to send a message
 *
 * @return bool true if the operation succeeds and false otherwise
 */
bool Bluetooth::send()
{
    const int numBytes = Intpressor::compress(message.values, message.sizes, message.numValues, message.bytes);
    json["a"] = message.bytes;
    serializeJson(json, *serial);
    serializeJson(json, Serial);
    Serial.println();
    json.clear();
    serial->print(endChar);
}

void Bluetooth::empty()
{
    while (serial->available())
    {
        serial->read();
    }
}

int Bluetooth::Message::get(int key)
{
    return values[key];
}

void Bluetooth::Message::set(int key, int value)
{
    values[key] = value;
}
