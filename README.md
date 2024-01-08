<p align="center">
  <img src="images/cover.JPG" height="200" />
</p>

# BeetleMeter
Raising a beetle is fun and wholesome but keeping an eye on the environment inside the little fella's enclosure can be stressful and complicated. For this reason, the BeetleMeter is a tiny battery-powered PCB that instantly notifies the beetle keeper if the temperature and humidity is too high, too low or just right, by the push of a button.

## Circuitry
The SHT40 sensor is used to measure temperature (0.2 °C accuracy) and humidity (1.8 %RH accuracy), and communicate those values through I2C. The result can then be displayed through six LEDs i.e. temperature too high, too low or good, and humidity too high, too low, or good. In the first version, the system is controlled with the ATtiny13A and powered through a CR2032 coin cell (210mAh), while the second version uses the smaller ATtiny402 and is powered through two in series connected LR44 coin cells (150mAh). Due to the limited amount of GPIO pins of these two microcontrollers, the LEDs are switched through Charlieplexing. V1.0 incorporates the button signal on one of the remaining GPIOs and in V2.0 the button is used to power the system.

<p align="center">
  <img src="images/v1_circuit.png" height="250" />
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  <img src="images/v1_circuit.png" height="250" />
</p>

## PCB design
Both versions board outline is defined by the dimensions of their battery holder, which is mounted on the bottom side of the PCB. The top side accomodates the remaining components in SMD format. The push button size was also chosen according to the board space left.

<p align="center">
  <img src="images/v1_front.JPG" height="150" />
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  <img src="images/v1_back.JPG" height="150" />
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  <img src="images/v1_assembled.JPG" height="150" /> <br/><br/>
  <img src="images/v2_front.JPG" height="150" />
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  <img src="images/v2_back.JPG" height="150" />
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  <img src="images/v1_assembled.JPG" height="150" />
</p>

## Code
V1.0 stays in sleep mode most of the time and only wakes up throug the button press after which the sensor is powered, measurements are read and the LEDs are turned ON for 1 second according to the suitable temperature and humidty range.

```ruby
code V1.0
```

V2.0 is basically the same code but without the need for a sleep mode since the system is not powered when the button is not pressed. Consequently, the LEDs stay turned ON until the button is released again.

```ruby
code V2.0
```
