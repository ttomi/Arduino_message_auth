#include <AESLib.h> 
#include <string.h>
#include <Time.h>
#include <TimeLib.h>

uint8_t key[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
char data[] = {'0','1','2','3','4','5'};
int senderID = 1;
int counter = 0;
int payload = 10;
int dataLenght = sizeof(data);
int macLength = payload - dataLenght;

void setup()
{
    Serial.begin(57600);
}

void loop()
{
    char mac[16];
    char message[17];
    memset(mac, 0, sizeof(mac));
    memset(message, 0, sizeof(message));
    
    counter++;
    time_t t = now();
    memcpy(mac, data, sizeof(data));
    
    aes128_enc_single(key, mac);
    Serial.print("mac:");
    Serial.println(mac);

    constructMessage(message, data);
    Serial.println(message);
    
    delay(2000);
}

void constructMessage(char *message, char *data, char *mac)
{
    message[0] = (senderID + '0');
    int i = 0;
    for(i; i < dataLenght; i++)
    {
        message[i+1] = data[i];
        Serial.print(data[i]);
    }
    for(int j = 0; j < macLength; j++)
    {
        message[++i] = mac[j];
        Serial.print(mac[j]);
    }
    message[++i] = (counter + '0');     //payload + 1
    message[++i] = (day() + '0');       //payload + 2
    message[++i] = (hour() + '0');      //payload + 3
    message[++i] = (minute() + '0');    //payload + 4
    message[++i] = (second() + '0');    //payload + 5
    //strcat(message, '\0');
}

