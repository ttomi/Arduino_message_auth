#include <AESLib.h> 
#include <string.h>
#include <Time.h>
#include <TimeLib.h>

uint8_t key[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
char data[] = {'0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','\0'};
int senderID = 1;
int counter = 0;
int x = 5;

void setup()
{
    Serial.begin(57600);
}

void loop()
{
    char mac[16];
    char message[16];
    counter++;
    time_t t = now();
    memcpy(mac, data, sizeof(data));
    
    //aes128_enc_single(key, mac);
    //Serial.print("encrypted:");
    //Serial.println(mac);

    //aes128_dec_single(key, mac);
    //Serial.print("original:");
    //Serial.println(mac);

    modifyMac(mac, x);
    Serial.println(mac);

    constructMessage(message, data);
    Serial.println(message);

    memset(message, 0, sizeof(message));
    memset(mac, 0, sizeof(mac));

    delay(2000);
}

void modifyMac(char *mac, int x)
{
    for(int i = x; i < 16; i++)
    {
        mac[i] = '0';
    }
}

void constructMessage(char *message, char *data)
{
    int z = 0;
    message[0] = (senderID + '0');
    for(int i = 1; i < 11; i++)
    {
        message[i] = data[z];
        z++;
    }
    message[11] = (counter + '0');
    message[12] = (day() + '0');
    message[13] = (hour() + '0');
    message[14] = (minute() + '0');
    message[15] = (second() + '0');
    strcat(message, '\0');
}

