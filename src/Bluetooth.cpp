#include <Arduino.h>

#include "Bluetooth.h"

/**
 * Setup the bluetooth communication
 */
void Bluetooth::setup()
{
    serial.begin(bauds);
}

/**
 * Function to call each loops of the program
 * 
 * @return bool true if a complet new message is detected and false otherwise
 */
bool Bluetooth::loop()
{
    while (serial.available() > 0)
    {
        char c = read();
        if (c == '.')
        {
            return true;
        }
        else
        {
            message += c;
        }
    }
    return true;
}

/**
 * Function to read current char
 * 
 * @return char the current character in the bluetooth buffer
 */
char Bluetooth::read()
{
    return serial.read();
}

/**
 * Function to print data on bluetooth
 * 
 * @param String `data` to print on the bluetooth
 */
void Bluetooth::print(String data)
{
    serial.print(data);
}

/**
 * Function to println data on bluetooth
 * 
 * @return char the current character in the bluetooth buffer
 */
void Bluetooth::println(String data)
{
    serial.println(data);
}
