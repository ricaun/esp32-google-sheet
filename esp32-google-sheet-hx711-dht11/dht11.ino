#include <dht.h>

#define DHT11_PIN 18

dht dht11;

void dht_begin()
{

}

float dht_read_temperature()
{
    int chk = dht11.read11(DHT11_PIN);
    float f = dht11.temperature;
    Serial.print("dht11 temperature: ");
    Serial.println(f);
    return f;
}

float dht_read_humidity()
{
    int chk = dht11.read11(DHT11_PIN);
    float f = dht11.humidity;
    Serial.print("dht11 humidity: ");
    Serial.println(f);
    return f;
}