#include <Adafruit_NeoPixel.h>

#define CIRCLEPIN 6

#define PIXELCOUNT 28

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXELCOUNT,CIRCLEPIN,
  NEO_GRB+NEO_KHZ800);

int degree = 0;
#define TRIGGERPIN 13
#define ECHOPIN 12

int delayMove = 50;

void setup() {
  pixels.begin();
  for(int i=0;i<PIXELCOUNT;i++){
    pixels.setPixelColor(i, pixels.Color(0,0,0));
  }
  pixels.show();
  pinMode(TRIGGERPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
}

void loop() {
  long duration, distanceCM;
  digitalWrite(TRIGGERPIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIGGERPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGERPIN, LOW);
  duration = pulseIn(ECHOPIN, HIGH);
  distanceCM = (duration/2) / 29.1;
  for(int i=0;i<PIXELCOUNT;i++){
    pixels.setPixelColor(i, pixels.Color(0,0,0));
  }
  for (int i=16;i<16+distanceCM/2;i++) {
    pixels.setPixelColor(i, pixels.Color(0,50,0));
  }
  int thisPixel = (degree*16)/360;
  pixels.setPixelColor((thisPixel+3)%16,pixels.Color(255,0,0));
  pixels.setPixelColor((thisPixel+2)%16,pixels.Color(100,0,0));
  pixels.setPixelColor((thisPixel+1)%16,pixels.Color(40,0,0));
  pixels.setPixelColor((thisPixel)%16,pixels.Color(15,0,0));
  pixels.show();
  if (distanceCM>=200) {
    delayMove = 200;
  } else {
    delayMove = distanceCM;
  }
  delay(delayMove);
  degree += 10;
  if (degree>=360) {
    degree -= 360;
  }
}

