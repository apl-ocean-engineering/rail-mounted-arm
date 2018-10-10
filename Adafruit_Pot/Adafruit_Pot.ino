unsigned long timer = 0;
unsigned long interval = 1000;
boolean LEDstate;
int value = 0;

#if defined(ARDUINO_SAMD_ZERO) && defined(SERIAL_PORT_USBVIRTUAL)
  // Required for Serial on Zero based boards
  #define Serial SERIAL_PORT_USBVIRTUAL
#endif

void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  value = analogRead(A0);
  interval = map(value, 0, 1024, 500,0);
  
  if (millis() - timer > interval) { //Toggle LED state every time interval has elapsed
    timer = millis();
    LEDstate = !LEDstate;
  }
  digitalWrite(13, LEDstate);   // Write LED state
  analogWrite(11, value);       // Write PWM Output to pin11
  Serial.println(value);
}
