#include <Adafruit_NeoPixel.h>

#define PIN 0
#define LEDS 16
#define DECAY 8

const int buttonPin = 1;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS, PIN, NEO_GRB + NEO_KHZ800);

const uint8_t PROGMEM gamma[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };

const int maxModes = 3;
int mode = 0;
long debounceDelay = 50;

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

char blue, red, green;
int blue_pos, red_pos, green_pos;
unsigned int j;
void loop() {
  if(digitalRead(buttonPin) == HIGH) {
    delay(debounceDelay);
    if(digitalRead(buttonPin) == HIGH) {
      mode = (mode + 1) % maxModes;
      while(digitalRead(buttonPin) != LOW){}
    }
  }

  switch(mode) {
    case 0:
      for(int i = 0; i < LEDS; i++){
        blue = pgm_read_byte(&gamma[256 - (((j/5) + 16 - i) % LEDS) * (256 / LEDS)]);
        strip.setPixelColor(i, strip.Color(0, 0, blue));
      }
      strip.show();
      break;
      
    case 1:
      for(int i = 0; i < LEDS; i++){
        blue = pgm_read_byte(&gamma[256 - (((j/5) + 16 - i) % LEDS) * (256 / LEDS)]);
        red = pgm_read_byte(&gamma[((LEDS - (i + (j/11)) % LEDS)) * (180 / LEDS)]);
        strip.setPixelColor(i, strip.Color(red, 0, blue));
      }
      strip.show();
      break;
      
    case 2:
      strip.clear();
      for(int i = 0; i < 3; i++){
        strip.setPixelColor((j/11 + i) % LEDS, strip.Color(0, 236, 0));
        strip.setPixelColor((j/11 + i + LEDS/2) % LEDS, strip.Color(0, 236, 0));
      }
      strip.show();
      break;
  }
      
  j++;
  delay(5);
}
