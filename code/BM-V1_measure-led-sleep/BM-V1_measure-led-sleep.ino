// BeetleMeter1.0 with ATtiny85
// ---------- PARAMETER SETTING ---------- \\
// LED shining time in milliseoncds
const byte ton = 1000;
// LED numbering
byte temp_led = 0;
byte humy_led = 0;
// measurement ranges
const byte max_temp = 25;
const byte min_temp = 12;
const byte max_humy = 70;
const byte min_humy = 50;

// import sleep library
#include <avr/sleep.h>
#include <SHTSensor.h>
#include <Wire.h>

// create sensor object
SHTSensor sht;
// init measure variables
float temp = 0;
float humy = 0;

// ---------- LED FUNCTION ---------- \\
// function to turn ON a single LED (and turn OFF all the other ones)
// this part should not be changes, it is related to the hardware
void setLED(byte ledNum){
  if(ledNum == 0){
    // All LEDs OFF
    DDRB &= ~(1 << PB1);
    DDRB &= ~(1 << PB3);
    DDRB &= ~(1 << PB4);
  }
  if(ledNum == 1){
    // PB1 -> PB3
    DDRB |= (1 << PB1);
    DDRB |= (1 << PB3);
    DDRB &= ~(1 << PB4);
    PORTB |= (1 << PB1);            
    PORTB &= ~(1 << PB3);
  }
  if(ledNum == 2){
    // PB3 -> PB1
    DDRB |= (1 << PB1);
    DDRB |= (1 << PB3);
    DDRB &= ~(1 << PB4);
    PORTB |= (1 << PB3);            
    PORTB &= ~(1 << PB1);
  }
  if(ledNum == 3){
    // PB3 -> PB4
    DDRB |= (1 << PB3);
    DDRB |= (1 << PB4);
    DDRB &= ~(1 << PB1);
    PORTB |= (1 << PB3);            
    PORTB &= ~(1 << PB4);
  }
  if(ledNum == 4){
    // PB4 -> PB3
    DDRB |= (1 << PB3);
    DDRB |= (1 << PB4);
    DDRB &= ~(1 << PB1);
    PORTB |= (1 << PB4);            
    PORTB &= ~(1 << PB3);
  }
  if(ledNum == 5){
    // PB1 -> PB4
    DDRB |= (1 << PB1);
    DDRB |= (1 << PB4);
    DDRB &= ~(1 << PB3);
    PORTB |= (1 << PB1);            
    PORTB &= ~(1 << PB4);
  }
  if(ledNum == 6){
    // PB1 -> PB4
    DDRB |= (1 << PB1);
    DDRB |= (1 << PB4);
    DDRB &= ~(1 << PB3);
    PORTB |= (1 << PB4);            
    PORTB &= ~(1 << PB1);
  }
}

// ---------- SLEEP FUNCTION ---------- \\
// sleep function
void sleepnowake(void){
  // turn off all LEDs
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  // set sleep mode
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  // go to sleep
  sleep_enable();
  sleep_cpu();
}

// ---------- SETUP CODE ---------- \\
// the code below is performed only once at the beginning before the main loop
void setup(){
  // all LEDs OFF
  setLED(0);
  // disable ADC
  ADCSRA &= ~(1<<ADEN);

  // init wire
  Wire.begin();
  // init sensor
  sht.init();
  // get measurements
  if (sht.readSample()) {
    temp = sht.getTemperature();
    humy = sht.getHumidity();
  }
  if(humy > 100){
    humy = 100;
  } else if(humy < 0){
    humy = 0;
  }

  // get temp and humy status
  if(temp > max_temp){
    temp_led = 2;
  } else if(temp < min_temp){
    temp_led = 5;
  } else {
    temp_led = 3;
  }
  if(humy > max_humy){
    humy_led = 1;
  } else if(humy < min_humy){
    humy_led = 6;
  } else {
    humy_led = 4;
  }

  // turn on LEDs
  for (int i = 0; i < ton/2; i ++) {
    setLED(temp_led);
    delay(1);
    setLED(humy_led);
    delay(1);
  }
  
  // sleep without wakeup
  sleepnowake();
}

// ---------- MAIN LOOP ---------- \\
// once the programm enters this loop, it repeats indefinitly until power-off or reset 
void loop(){
  
}
