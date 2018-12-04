#if defined(ARDUINO_SAMD_ZERO) && defined(SERIAL_PORT_USBVIRTUAL)
// Required for Serial on Zero based boards
#define Serial SERIAL_PORT_USBVIRTUAL
#endif

boolean serialPlotter = false;

// Light One:    Analog in: A0      PWM Out: 13  (pin 13 also has RED LED)
// Light Two:    Analog in: A1      PWM out: 12

const int L1IN = A0;
const int L1PWM = 13;

const int L2IN = A1;
const int L2PWM = 12;

// The enable signal on the LEDs are active LOW!


void setup() {

  pinMode(L1PWM, OUTPUT);
  digitalWrite(L1PWM, HIGH);

  pinMode(L2PWM, OUTPUT);
  digitalWrite(L2PWM, HIGH);

  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  control_pwm( analogRead(L1IN), L1PWM );
  control_pwm( analogRead(L2IN), L2PWM );
  Serial.println("");
  // No need to update any faster than a few Hz
  delay(100);
}


void control_pwm( int ain, int pwm_pin ) {

  int pwm = map(ain, 0, 1023, 255, 0);

  if ( pwm >= 254 ) {
    digitalWrite( pwm_pin, HIGH );
  } else if ( pwm <= 2 ) {
    digitalWrite( pwm_pin, LOW );
  } else {
    analogWrite( pwm_pin, pwm );
  }
  if (serialPlotter) {
    Serial.print(pwm);
    Serial.print(", ");
  } else {
    Serial.print(pwm_pin);
    Serial.print(" : ");
    Serial.print(pwm);
    Serial.print("\t\t");
  }
}
