// BeetleMeter2.0 with ATtiny402
// ---------- PARAMETER SETTING ----------
// measurement ranges
const byte max_temp = 30;
const byte min_temp = 15;
const byte max_humy = 80;
const byte min_humy = 40;

// include ATtiny I2C library
#include <Wire.h>
#include <SensirionI2CSht4x.h>
// init sensor
SensirionI2CSht4x sht4x;

// init measure variables
float temp = 0;
float humy = 0;
// init LEDs
byte temp_led = 0;
byte humy_led = 0;

// ---------- LED FUNCTION ----------
void setLED(byte ledNum){
  if(ledNum == 0){
    // All LEDs OFF
    PORTA.DIRCLR = PIN3_bm;
    PORTA.DIRCLR = PIN6_bm;
    PORTA.DIRCLR = PIN7_bm;
  }
  if(ledNum == 1){
    // PA3 -> PA6
    PORTA.DIR = PIN3_bm | PIN6_bm;
    PORTA.DIRCLR = PIN7_bm;
    PORTA.OUTSET = PIN3_bm;           
    PORTA.OUTCLR = PIN6_bm;
  }
  if(ledNum == 2){
    // PA6 -> PA3
    PORTA.DIR = PIN3_bm | PIN6_bm;
    PORTA.DIRCLR = PIN7_bm;
    PORTA.OUTSET = PIN6_bm;           
    PORTA.OUTCLR = PIN3_bm;
  }
  if(ledNum == 3){
    // PA6 -> PA7
    PORTA.DIR = PIN6_bm | PIN7_bm;
    PORTA.DIRCLR = PIN3_bm;
    PORTA.OUTSET = PIN6_bm;           
    PORTA.OUTCLR = PIN7_bm;
  }
  if(ledNum == 4){
    // PA7 -> PA6
    PORTA.DIR = PIN6_bm | PIN7_bm;
    PORTA.DIRCLR = PIN3_bm;
    PORTA.OUTSET = PIN7_bm;           
    PORTA.OUTCLR = PIN6_bm;
  }
  if(ledNum == 5){
    // PA3 -> PA7
    PORTA.DIR = PIN3_bm | PIN7_bm;
    PORTA.DIRCLR = PIN6_bm;
    PORTA.OUTSET = PIN3_bm;           
    PORTA.OUTCLR = PIN7_bm;
  }
  if(ledNum == 6){
    // PA7 -> PA3
    PORTA.DIR = PIN3_bm | PIN7_bm;
    PORTA.DIRCLR = PIN6_bm;
    PORTA.OUTSET = PIN7_bm;           
    PORTA.OUTCLR = PIN3_bm;
  }
}

// ---------- SETUP CODE ---------- 
void setup(){
  // all LEDs OFF
  setLED(0);

  // init wire
  Wire.begin();
  // init SHT40 with high res measurement and measure
  sht4x.begin(Wire);
  sht4x.measureHighPrecision(temp, humy);

  // get temp and humy status LEDs
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
}

// ---------- MAIN LOOP ---------- 
void loop(){
  // turn on LEDs
  setLED(temp_led);
  delay(1);
  setLED(humy_led);
  delay(1);
  
}
