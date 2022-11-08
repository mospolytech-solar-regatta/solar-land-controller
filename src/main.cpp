#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "string.h"

RF24 radio(9,10);
const byte address[6] = "00001";

void setup()
{
    while (!Serial);
    Serial.begin(9600);
    radio.begin();
    radio.openReadingPipe(0, address);
    radio.startListening  ();
}

void loop()
{
    if (radio.available())
    {
        std::string output;
        while(radio.available()){
            char trash[2];
            radio.read(&trash, sizeof(1));
            if(trash[0] = char(1)) break;
        }
            while(radio.available()){
                char checkSymbol[2];
                radio.read(&checkSymbol, sizeof(1));
                if(checkSymbol[0] = char(1)) break;
                output+=checkSymbol[0];
            }
        }
    Serial.println(output);
    }