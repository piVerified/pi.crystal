const int ledPin = 0;   // PB0 
const int ldrPin = 3;   // PB3 
const int threshold = 550; // sensitivity 


const float blinkSpeed = 0.05; 
float angle = 0;             

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT); // Photoresistor with internal pull-up 

  startupPulse();
}

void loop() {
  // Read the analog voltage from the LDR
  // 0 = Full Brightness, 1023 = Full Darkness
  int lightLevel = analogRead(ldrPin);

  // If the light level is HIGH (LDR is in shadow)
  if (lightLevel > threshold) {
    breathe();
  } else {
    // If the cover is removed, turn the LED off instantly
    analogWrite(ledPin, 0);
    angle = 0;
  }
}

// Function to calculate a non-linear, soft pulsing effect
void breathe() {
  // Convert an angle into a non-linear brightness value (0-255)

  float brightness = (exp(sin(angle)) - 0.36787944) * 108.0;

  analogWrite(ledPin, brightness);


  angle += blinkSpeed;


  if (angle > (2 * PI)) angle = 0;

  delay(20); // fade smoothness
}
// power on sequence
void startupPulse() {
  for (int j = 0; j < 2; j++) {
    for (int i = 0; i < 200; i++) { analogWrite(ledPin, i); delay(3); }
    for (int i = 200; i >= 0; i--) { analogWrite(ledPin, i); delay(5); }
    analogWrite(ledPin, 0); delay(300);
  }
}
