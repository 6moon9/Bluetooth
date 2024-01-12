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
    if (serial->available() > 0)
    {
        char c = serial->read();
        Serial.print(c);
        if (c == endChar)
        {
            // for (int i = 0; i < message.byteIndex; i++)
            // {
            //     for (int j = 7; j >= 0; j--) {
            //         Serial.print((message.bytes[i] >> j) & 1);
            //     }
            // }
            // Serial.println();
            // Intpressor::extract(message.bytes, message.sizes, message.numValues, message.values);
            // for (int i = 0; i < message.numValues; i++)
            // {
            //     Serial.print(message.bytes[i]);
            // }
            // Serial.println();
            Serial.println();
            memset(message.bytes, 0, sizeof(message.bytes));
            message.byteIndex = 0;
            return true;
        }
        else
        {
            message.bytes[message.byteIndex] = c;
            message.byteIndex++;
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
    int numBytes = Intpressor::compress(message.values, message.sizes, message.numValues, message.bytes);
    for (int i = 0; i < numBytes; i++)
    {
        serial->print(message.bytes[i]);
    }
    serial->print(endChar);
    return true;
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