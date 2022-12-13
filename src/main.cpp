#include <RF24.h>
#include <nRF24L01.h>
#define PIN_CE 9
#define PIN_CSN 10

RF24 radio(PIN_CE, PIN_CSN);
const int TRANSMITTER_BUFFER_SIZE = 32;
String receivedString;
char buffer[TRANSMITTER_BUFFER_SIZE+1];
int receiving = 0;
char symbol_start = 1;
char symbol_stop = 3;

void setup(){
    radio.begin();
    radio.setDataRate(RF24_1MBPS);
    radio.setPALevel(RF24_PA_HIGH);
    radio.openReadingPipe(1, 0x7878787878LL);
    radio.startListening();
    Serial.begin(9600);
}

void loop() {
    if (radio.available() > 0) {
        if(receiving == 1){
            radio.read(&buffer, TRANSMITTER_BUFFER_SIZE);
            if (buffer[0] == symbol_stop){
                receiving = 0;
                Serial.println(receivedString);
            } else {
                if (strlen(buffer) > 0){
                    receivedString += String(buffer);
                }
            }
        } else {
            radio.read(&buffer, TRANSMITTER_BUFFER_SIZE);
            if (buffer[0] == symbol_start) {
                receiving = 1;
                receivedString = "";
            }
        }
    }
}
