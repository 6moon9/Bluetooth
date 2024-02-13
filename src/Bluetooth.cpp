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
int Bluetooth::receive()
{
    while (serial->available() > 0)
    {
        char c = serial->read();
        // Serial.print(c);
        if (c == endChar)
        {
            lastError = deserializeJson(json, *serial);
            if (lastError == DeserializationError::Ok)
            {
                Intpressor::extract(json["a"], message.sizes, message.numValues, message.values);
                json.clear();
                empty();
                return 0;
            }
            return 1;
        }
    }
    return 2;
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
    // for (int i = 0; i < message.numValues; i++){
    //     Serial.print(message.values[i]); Serial.print(" ");
    // }
    serializeJson(json, *serial);
    // serializeJson(json, Serial);
    // Serial.println();
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

int Bluetooth::Message::get(int key, bool signit)
{
    return values[key] - 255;
}

void Bluetooth::Message::set(int key, int value)
{
    values[key] = value;
}
