
#include <WiFi.h>
#include <PubSubClient.h>

#define ID_MQTT "esp32_mqtt"
#define BROKER_MQTT "broker.hivemq.com"
#define BROKER_PORT 1883
#define MQTT_UPDATE 5000

#define TOPIC_ANALOG "analog"
#define TOPIC_HX711 "hx711"
#define TOPIC_DHT_TEMPERATURE "temperature"
#define TOPIC_DHT_HUMIDITY "humidity"
#define TOPIC_TSL "light"

WiFiClient espClient;
PubSubClient MQTT(espClient);

void mqtt_setup()
{
    Serial.println("MQTT Start!");
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);
    MQTT.setCallback(mqtt_callback);
    mqtt_reconect();
}

void mqtt_loop()
{
    if (mqtt_runEvery(MQTT_UPDATE))
    {
        mqtt_reconect();
        mqtt_update();
    }
}

void mqtt_update()
{
    mqtt_publish(TOPIC_ANALOG, readAnalogPin());
    mqtt_publish(TOPIC_HX711, hx711_read());
    mqtt_publish(TOPIC_DHT_TEMPERATURE, dht_read_temperature());
    mqtt_publish(TOPIC_DHT_HUMIDITY, dht_read_humidity());
    mqtt_publish(TOPIC_TSL, tsl_read());
}

void mqtt_publish(String topic, float number)
{
    if (!MQTT.connected())
        return;
    char buffer[16] = {0};
    sprintf(buffer, "%.2f", number);
    MQTT.publish(topic.c_str(), buffer);
}

void mqtt_callback(char *topic, byte *payload, unsigned int length)
{
    String msg;
    for (int i = 0; i < length; i++)
    {
        char c = (char)payload[i];
        msg += c;
    }

    Serial.print("MQTT: ");
    Serial.println(msg);
}

void mqtt_reconect()
{
    if (!MQTT.connected())
    {
        Serial.print("MQTT Connect: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ID_MQTT))
        {
        }
    }
}

boolean mqtt_runEvery(unsigned long interval)
{
    static unsigned long previousMillis = 0;
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval)
    {
        previousMillis = currentMillis;
        return true;
    }
    return false;
}