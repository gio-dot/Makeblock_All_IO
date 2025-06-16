
#include <FastLED.h>
#include <EasyUltrasonic.h>

// If you want to use your HC-SR04/Ping))) ultrasonic sensor in the 3 Pin Mode, then the TRIGPIN value will need to be the same as the ECHOPIN value (The digital pin that is connected to your ultrasonic sensor):
#define TRIGPIN A3 // Digital pin connected to the trig pin of the ultrasonic sensor
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

#define ledPin 13   // il PIN D13 è collegato al led builtin e alla seriale dei led WS2812
#define buzPin 8    // il PIN D13 è collegato al led builtin e alla seriale dei led WS2812
#define IRledPin 3
#define pwm1Pin 6
#define pwm2Pin 5
#define dir1Pin 7
#define dir2Pin 4


#define lightSensorPin A6
#define pulsPin A7  // Il pulsante è collegato al pin A7 che posso leggere solo in analogico
#define fc1Pin 9
#define fc2Pin 10

int state = 0;
int pulsState= 0;   // Il pulsante è collegato al pin A7 che posso leggere solo in analogico
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

    pinMode(fc1Pin, INPUT_PULLUP);
    pinMode(fc2Pin, INPUT_PULLUP);
    
    FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    ultrasonic.attach(TRIGPIN, ECHOPIN); // Attaches the ultrasonic sensor on the specified pins on the ultrasonic object
}

void loop() {

    fc1State= digitalRead(fc1Pin);
    fc2State= digitalRead(fc2Pin);
    pulsState= analogRead(pulsPin);
    lightSensor= analogRead(lightSensorPin);
    distanceCM = ultrasonic.getDistanceCM(); // Read the distance in centimeters

    delay(100); // delay per il buon funzionamento del sonar

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

    if(pulsState< 100){ // pulsante premuto

      for (int i= 0; i<5; i++) {
        tone(buzPin, 2500);  // 2kHz  su pin buzPin
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

      digitalWrite(dir1Pin, LOW);
      analogWrite(pwm1Pin, 100);
      delay(200);
      analogWrite(pwm1Pin, 0);
      delay(200);
      digitalWrite(dir1Pin, HIGH);
      analogWrite(pwm1Pin, 100);
      delay(200);
      analogWrite(pwm1Pin, 0);
      delay(200);
      digitalWrite(dir2Pin, LOW);
      analogWrite(pwm2Pin, 100);
      delay(200);
      analogWrite(pwm2Pin, 0);
      delay(200);
      digitalWrite(dir2Pin, HIGH);
      analogWrite(pwm2Pin, 100);
      delay(200);
      analogWrite(pwm2Pin, 0);

      leds[0] = CRGB::Red;
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