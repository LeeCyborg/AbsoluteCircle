#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <Adafruit_NeoPixel.h>
#define BNO055_SAMPLERATE_DELAY_MS (100)
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_BNO055 bno = Adafruit_BNO055(55);
void setup()
{
  Serial.begin(9600);
  strip.begin();
  strip.show();
  if (!bno.begin())
  {
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }
}

void loop() {
  sensors_event_t event;
  bno.getEvent(&event);
  colorGo(strip.Color(0,0,0), 50);
  strip.setPixelColor(map((int)event.orientation.z, -300, 300, 0, 16), strip.Color(255, 0,0));
  strip.setPixelColor(map((int)event.orientation.y, -300, 300, 0, 16), strip.Color(0, 255,0));
  strip.setPixelColor(map((int)event.orientation.x, -300, 300, 0, 16), strip.Color(0, 0,255));
  strip.show();
  delay(BNO055_SAMPLERATE_DELAY_MS);
}

void colorGo(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
}
