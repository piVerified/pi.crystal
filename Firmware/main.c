/* * ATtiny85-20PU LDR Crystal Blinky (Final Gift Code)
 * * Target: ATtiny85 (Internal 8MHz Clock RECOMMENDED for PWM smoothness)
 * Schematic: LED_D1 -> Pin 5 (PB0), LDR_R2 -> Pin 2 (PB3)
 * * While LDR is covered, the LED will blink (breathe) smoothly.
 */

const int ledPin = 0;   // PB0 (Physical Pin 5) - Driving 8mm LED via 10 Ohm 1W Resistor
const int ldrPin = 3;   // PB3 (Physical Pin 2) - Analog Input from LDR
const int threshold = 550; // Tweak this for sensitivity (Higher = needs more shadow)

// Speed settings for the "Smooth" Breathe
const float blinkSpeed = 0.05; // Lower is slower, higher is faster
float angle = 0;              // Used to calculate the Sine wave

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT); // Photoresistor with internal pull-up not usually used, but we are reading analog
  
  // Power-on Test: Quick soft double pulse to show it's alive
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
    angle = 0; // Reset the sine wave position
  }
}

// Function to calculate a non-linear, soft pulsing effect
void breathe() {
  // Convert an angle into a non-linear brightness value (0-255)
  // angle = sin(angle) gives a soft S-curve fade
  float brightness = (exp(sin(angle)) - 0.36787944) * 108.0;

  analogWrite(ledPin, brightness);

  // Increment the angle for the next step of the sine wave
  angle += blinkSpeed;

  // Keep angle within useful range
  if (angle > (2 * PI)) angle = 0;

  delay(20); // Small delay for fade smoothness
}

// Optional: A pleasing power-on confirmation sequence
void startupPulse() {
  for (int j = 0; j < 2; j++) {
    for (int i = 0; i < 200; i++) { analogWrite(ledPin, i); delay(3); }
    for (int i = 200; i >= 0; i--) { analogWrite(ledPin, i); delay(5); }
    analogWrite(ledPin, 0); delay(300);
  }
}
