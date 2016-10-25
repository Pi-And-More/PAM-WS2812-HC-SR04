//
// The library from Adafruit which enables the use of the WS2812
// or NeoPixel
//
#include <Adafruit_NeoPixel.h>

//
// The pin the circle of WS2812 leds is connected to
//
#define CIRCLEPIN 6
//
// The number of leds in our two circles (12+16)
//
#define PIXELCOUNT 28

//
// Initialize the Adafruit library
//
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXELCOUNT,CIRCLEPIN,
  NEO_GRB+NEO_KHZ800);

//
// The current position
//
int degree = 0;

//
// The trigger and echo pin for the HC-SR04
//
#define TRIGGERPIN 13
#define ECHOPIN 12

//
// How long we delay before the next read and update of the leds
//
int delayMove = 50;

void setup() {
  //
  // Start the led string and turn them all off
  //
  pixels.begin();
  for(int i=0;i<PIXELCOUNT;i++){
    pixels.setPixelColor(i, pixels.Color(0,0,0));
  }
  pixels.show();
  //
  // Prepare the HC-SR04 pins
  //
  pinMode(TRIGGERPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
}

void loop() {
  //
  // Determine the distance between object and HC-SR04
  // Read about it in more detail on
  // https://piandmore.wordpress.com/2016/10/04/arduino-hc-sr04-ultrasonic-distance/
  //
  long duration, distanceCM;
  digitalWrite(TRIGGERPIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIGGERPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGERPIN, LOW);
  duration = pulseIn(ECHOPIN, HIGH);
  //
  // The distance in cms
  //
  distanceCM = (duration/2) / 29.1;
  //
  // Turn all pixels off
  //
  for(int i=0;i<PIXELCOUNT;i++){
    pixels.setPixelColor(i, pixels.Color(0,0,0));
  }
  //
  // Turn on the inner circle leds
  // 1 led for every 2 cm of distance
  //
  for (int i=16;i<16+distanceCM/2;i++) {
    pixels.setPixelColor(i, pixels.Color(0,50,0));
  }
  //
  // Determine the current position led of the outer circle
  // and turn on the required leds
  //
  int thisPixel = (degree*16)/360;
  pixels.setPixelColor((thisPixel+3)%16,pixels.Color(255,0,0));
  pixels.setPixelColor((thisPixel+2)%16,pixels.Color(100,0,0));
  pixels.setPixelColor((thisPixel+1)%16,pixels.Color(40,0,0));
  pixels.setPixelColor((thisPixel)%16,pixels.Color(15,0,0));
  pixels.show();
  //
  // Depending on the distance of an object, make the circle move
  // faster (if it is closer) or slower (if it is farther away)
  // and take the maximum time of it is very far away or
  // if there is no object
  //
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

