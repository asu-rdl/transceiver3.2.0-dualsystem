#include <arduino.h>
#include <SPI.h>

#define SPI_CHIPEN_PIN 10

void setup(){
    Serial.begin(115200);
    SPI.begin();
    pinMode(SPI_CHIPEN_PIN, OUTPUT);
    digitalWrite(SPI_CHIPEN_PIN, HIGH);
    
}

void loop(){
    byte data[2];
	while(Serial.available() < 2);

    String str = Serial.readStringUntil('\n');
    if (str.equals("get_id")){
        //ensure empty input
        while(Serial.available()>0){
            Serial.read();
        }
        Serial.println("transceiver_3.2.0");
    }
    else if (str.equals("set_atten"))
    {
        Serial.readBytes(data, 2);
        if (data[0] == 0 || data[0] > 4){
            Serial.println("FAIL, BAD ADDRESS NOT BETWEEN 1 THROUGH 4");
            return;
        }
        if (data[1] > 127){
            Serial.println("FAIL, ATTENUATION VALUE IS TOO LARGE");
            return;
        }
        //ensure empty input
        while(Serial.available()>0){
            Serial.read();
        }

        //send command to attenuator
        SPI.beginTransaction(SPISettings(4000000, LSBFIRST, SPI_MODE0));
        digitalWrite(SPI_CHIPEN_PIN, LOW);
        SPI.transfer(data[1]);
        SPI.transfer(data[0]);
        SPI.endTransaction();
        digitalWrite(SPI_CHIPEN_PIN, HIGH);
        int status = 0;
        Serial.println("OK");
    } else {
        Serial.println("BAD COMMAND");
    }

}