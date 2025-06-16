
#include <FastLED.h>
#include <EasyUltrasonic.h>

// If you want to use your HC-SR04/Ping))) ultrasonic sensor in the 3 Pin Mode, then the TRIGPIN value will need to be the same as the ECHOPIN value (The digital pin that is connected to your ultrasonic sensor):
#define TRIGPIN A3 // Digital pin connected to the trig pin of the ultrasonic sensor (mCore Port 3)
#define ECHOPIN A3 // Digital pin connected to the echo pin of the ultrasonic sensor

EasyUltrasonic ultrasonic; // Create the ultrasonic object

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 13
// How many leds in your strip?
#define NUM_LEDS 2
// Define the array of leds
CRGB leds[NUM_LEDS];

#define ledPin 13   // PIN D13 connected to led builtin and to RGB led WS2812 serial pin
#define buzPin 8    
#define IRledPin 3
#define pwm1Pin 6   // motor 1 PWM out
#define pwm2Pin 5   // motor 2 PWM out
#define dir1Pin 7   // motor 1 direction
#define dir2Pin 4   // motor 2 direction (direction command is reversed between the 2 motors because one is mechanichally mounted in opposite direction)


#define lightSensorPin A6
#define pulsPin A7  // onboard button connected to pin A7 (read it as analog input)
#define fc1Pin 9    // line follower sensors connected to mCore port 2
#define fc2Pin 10   // line follower sensors connected to mCore port 2

int state = 0;
int pulsState= 0;   // onboard button connected to pin A7 (read it as analog input)
int fc1State= 0;    
int fc2State= 0;
int lightSensor= 0;
float distanceCM= 0;

void setup() {
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);
    pinMode(buzPin, OUTPUT);
    pinMode(IRledPin, OUTPUT);
    pinMode(dir1Pin, OUTPUT);
    pinMode(dir2Pin, OUTPUT);

    pinMode(fc1Pin, INPUT);  // line follower sensor
    pinMode(fc2Pin, INPUT);  // line follower sensor
    
    FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    ultrasonic.attach(TRIGPIN, ECHOPIN); // Attaches the ultrasonic sensor on the specified pins on the ultrasonic object
}

void loop() {

    fc1State= digitalRead(fc1Pin);
    fc2State= digitalRead(fc2Pin);
    pulsState= analogRead(pulsPin);
    lightSensor= analogRead(lightSensorPin);
    distanceCM = ultrasonic.getDistanceCM(); // Read the distance in centimeters

    delay(100); // delay for sonar readings

    Serial.print("Distance: ");
    Serial.print(distanceCM); 
    Serial.println(" cm");

    Serial.print("Light: ");
    Serial.print(lightSensor); 
    Serial.println(" u");

    if(fc1State== 1){
      leds[1] = CRGB::DarkGreen;
      FastLED.show();
      }
    else{
      leds[1] = CRGB::Black;
      FastLED.show();
      }
    if(fc2State== 1){
      leds[0] = CRGB::DarkGreen;
      FastLED.show();
      }
    else{
      leds[0] = CRGB::Black; 
      FastLED.show(); 
      }

    if(pulsState< 100){ // button pressed

      for (int i= 0; i<5; i++) {
        tone(buzPin, 2500);  // 2kHz  on buzPin
        delay(100); // pausa
        noTone(buzPin); // questa istruzione serve a spegnere il pin se sopra non ho messo il tempo o se ho più buzzer
        delay(100); // pausa
      }
      for (int i= 0; i<5; i++) {
        digitalWrite(ledPin, HIGH);
        delay(100);
        digitalWrite(ledPin, LOW);
        delay(100);
      }
      for (int i= 0; i<5; i++) {
        digitalWrite(IRledPin, HIGH);
        delay(100);
        digitalWrite(IRledPin, LOW);
        delay(100);
      }

      digitalWrite(dir1Pin, LOW); // motor 1 two directions test
      analogWrite(pwm1Pin, 100);
      delay(200);
      analogWrite(pwm1Pin, 0);
      delay(200);
      digitalWrite(dir1Pin, HIGH);
      analogWrite(pwm1Pin, 100);
      delay(200);
      analogWrite(pwm1Pin, 0);
      delay(200);
      digitalWrite(dir2Pin, LOW); // motor 2 two directions test
      analogWrite(pwm2Pin, 100);
      delay(200);
      analogWrite(pwm2Pin, 0);
      delay(200);
      digitalWrite(dir2Pin, HIGH);
      analogWrite(pwm2Pin, 100);
      delay(200);
      analogWrite(pwm2Pin, 0);

      leds[0] = CRGB::Red; // RGB onboard leds 8 colors test
      leds[1] = CRGB::Red;
      FastLED.show();
      delay(500);
      leds[0] = CRGB::Green;
      leds[1] = CRGB::Green;
      FastLED.show();
      delay(500);
      leds[0] = CRGB::Blue;
      leds[1] = CRGB::Blue;
      FastLED.show();
      delay(500);
      leds[0] = CRGB::Yellow;
      leds[1] = CRGB::Yellow;
      FastLED.show();
      delay(500);
      leds[0] = CRGB::Magenta;
      leds[1] = CRGB::Magenta;
      FastLED.show();
      delay(500);
      leds[0] = CRGB::Cyan;
      leds[1] = CRGB::Cyan;
      FastLED.show();
      delay(500);
      leds[0] = CRGB::White;
      leds[1] = CRGB::White;
      FastLED.show();
      delay(500);
      leds[0] = CRGB::Black;
      leds[1] = CRGB::Black;
      FastLED.show();
  }   
    

 }