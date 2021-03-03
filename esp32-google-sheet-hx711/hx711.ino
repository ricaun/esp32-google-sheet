#include "HX711.h"

#define HX711_DT 27
#define HX711_SCK 26
#define HX711_SCALE 446930.55
#define HX711_TARE 20
#define HX711_UNITS 10

HX711 hx711;

void hx711_begin()
{
    hx711.begin(HX711_DT, HX711_SCK);
    Serial.print("Start... HX711: ");
    Serial.println(hx711.read());
    hx711.set_scale(HX711_SCALE);
    hx711.tare(HX711_TARE);
}

float hx711_read()
{
    float f = hx711.get_units(HX711_UNITS);
    Serial.print("HX711: ");
    Serial.println(f);
    return f;
}