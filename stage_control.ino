/*******************************************************************
* This is an arduino script to use wheelencoder as a stage controller. 
* The controller could switch between different axis, x,y,z,rotation. 
* The center button is used to switch between coarse and fine motion of the stage.
* MIT License
* Copyright(c) [2022] [Dapeng]
**********************************************************************/

#include <Adafruit_NeoPixel.h>
#include <RotaryEncoder.h>

#define PIN_ENCODER_A 2
#define PIN_ENCODER_B 3
#define BUTTON_IN 4         // pin4, sw1, 
#define BUTTON_DOWN 5       // pin5, sw2, 
#define BUTTON_RIGHT 6	    // pin6, sw3, 
#define BUTTON_UP 7         // pin7, sw4, 
#define BUTTON_LEFT 8       // pin8, sw5, 

// #define COM_A    11
// #define COM_B    SDA

RotaryEncoder encoder(PIN_ENCODER_A, PIN_ENCODER_B, RotaryEncoder::LatchMode::TWO03);
// This interrupt will do our encoder reading/checking!
void checkPosition() {
  encoder.tick(); // just call tick() to check the state.
}
int last_rotary = 0;
int axis = 0; // 0 for x, 1 for y, 2 for z, 3 for rotation
int fine = 1; // 1 for fine, 5 for coarse

long currcount = 0;
#define NUMPIXELS 35L
Adafruit_NeoPixel pixels(NUMPIXELS, A0, NEO_GRB + NEO_KHZ800);


void setup(void) {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("ANO Rotary Encoder Demo");

  attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_A), checkPosition, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_B), checkPosition, CHANGE);

  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  pinMode(BUTTON_IN, INPUT_PULLUP);
  pixels.begin();
  pixels.setBrightness(30);
  pixels.show();
}


void loop(void) {
  // read encoder
  int curr_rotary = encoder.getPosition();
  RotaryEncoder::Direction direction = encoder.getDirection();
  
  pixels.clear();
  
  if (curr_rotary != last_rotary) {
    Serial.print("Encoder value: ");
    Serial.print(curr_rotary);
    Serial.print(" direction: ");
    Serial.print((int)direction);
    currcount += (int)direction * fine ;
    Serial.print(" currcount: ");
    Serial.println(currcount);
  }
  last_rotary = curr_rotary;
  pixels.setPixelColor((currcount + 3000000 * NUMPIXELS) % NUMPIXELS, pixels.Color(0, 150, 0));

  if (! digitalRead(BUTTON_LEFT)) {
    pixels.setPixelColor(NUMPIXELS*3/4, pixels.Color(150, 0, 0));
    if (axis != 0){
      axis = 0; // x
      Serial.println(" x-axis");
    }
  }
  if (! digitalRead(BUTTON_UP)) {
    pixels.setPixelColor(0, pixels.Color(150, 0, 0));
    if(axis !=1){
      axis = 1; // y
      Serial.println(" y-axis");
    }
  }
  if (! digitalRead(BUTTON_RIGHT)) {
    pixels.setPixelColor(NUMPIXELS/4, pixels.Color(150, 0, 0));
    if(axis != 2){
      axis = 2; // z
      Serial.println(" z-axis");
    }
  }
  if (! digitalRead(BUTTON_DOWN)) {
    pixels.setPixelColor(NUMPIXELS/2, pixels.Color(150, 0, 0));
    if(axis != 3){
       axis = 3; // rotation
       Serial.println(" rotation");
    }
  }
  if (! digitalRead(BUTTON_IN)) {
    pixels.fill(pixels.Color(50, 50, 50));

    while (! digitalRead(BUTTON_IN)){;}

    Serial.print(" Resolution: ");
    if (fine == 5){
      fine = 1;
      Serial.println("fine");

    }
    else if (fine == 1){
      fine = 5;
      Serial.println("coarse");
     
    }
      
  }
  pixels.show();

  delay(20);
}
