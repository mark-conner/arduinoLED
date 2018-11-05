#include "Arduino.h"
#include "led.h"

/*
 * Start LED class
 */

Led::Led()
// overloaded default constructor
{
    gpioPin = 16;
    pinMode(gpioPin, OUTPUT);
    setLedOn(false);
}

Led::Led(int pin, bool inv)
// overloaded constructor
{
    gpioPin = pin;
    invert = inv;
    pinMode(gpioPin, OUTPUT);
    setLedOn(false);
}

void Led::setLedOn(bool on)
// correctly turns LED on or off given true or false, respectively
{
    ledOn = on;
    digitalWrite(gpioPin, invert ^ ledOn ? HIGH : LOW);
}

void Led::setLedLevel(int level)
{
    level = level > 255 ? 255 : level;  // Max value is 255
    ledOn = level > 0;  // if level is not 0, then LED is on some amount
    level = invert ? 255-level : level; // invert the PWM
    analogWrite(gpioPin, level);
}

bool Led::getLedOn()
// return the status of the LED
{
    return ledOn;
}

/**
 * Start blink LED class
 */

BlinkLed::BlinkLed() : Led()
// overloaded default constructor
{
    gpioPin = 16;
    invert = false;
    pinMode(gpioPin, OUTPUT);
    setLedOn(false);
    onTime = 1000;
    offTime = 1000;
    lastSwitchCount = millis();
}

BlinkLed::BlinkLed(int pin, unsigned long timeOn, unsigned long timeOff, bool inv) :
    Led(pin, inv)
// overloaded constructor
{
    gpioPin = pin;
    invert = inv;
    pinMode(gpioPin, OUTPUT);
    setLedOn(true);
    onTime = timeOn;
    offTime = timeOff;
    lastSwitchCount = millis();
}

void BlinkLed::checkLedCount(unsigned long count)
// checks the count value against the last switch count plus the on/off time
{
    // check if LED on time has elapsed, if so turn LED off
    if (ledOn && count >= lastSwitchCount + onTime) {
    setLedOn(false);
    lastSwitchCount = count;
    }

    // check if LED off time has elapsed, if so turn LED on
    else if (!ledOn && count >= lastSwitchCount + offTime) {
    setLedOn(true);
    lastSwitchCount = count;
    }
}

/* 
 * strart RGB LED class
 */

RgbLed::RgbLed()
// overloaded default constructor
{
    // ends up assinging all three LEDs to same pin.
    // suggest not using default constructor.
    Led red();
    Led green();
    Led blue();
    bool ledOn = false;
    RgbColor ledRGB = {0, 0 , 0};
}

RgbLed::RgbLed(int redPin, int greenPin, int bluePin, bool inv)
// overloaded constructor
{
    Led red(redPin, inv);
    Led green(greenPin, inv);
    Led blue(bluePin, inv);
    bool ledOn = false;
    RgbColor ledRGB = {0, 0, 0};
}

void RgbLed::setRgbLedOn(bool on)
// sets all LEDs on or off
{
    rgbLedOn = on;
    red.setLedOn(on);
    green.setLedOn(on);
    blue.setLedOn(on);
}

void RgbLed::setRLedOn(bool on)
// sets just red LED on or off
{
    rgbLedOn = on || green.getLedOn() || blue.getLedOn();
    red.setLedOn(on);
}

void RgbLed::setGLedOn(bool on)
// sets just green LED on or off
{
    rgbLedOn = red.getLedOn() || on || blue.getLedOn();
    green.setLedOn(on);
}

void RgbLed::setBLedOn(bool on)
// sets just blue LED on or off
{
    rgbLedOn = red.getLedOn() || green.getLedOn() || on;
    blue.setLedOn(on);
}

void RgbLed::setLedRGB(int r, int g, int b)
// sets the specific color of the LED according to RGB color levels
{
    red.setLedLevel(r);
    green.setLedLevel(g);
    blue.setLedLevel(b);
    rgbLedOn = red.getLedOn() || green.getLedOn() || blue.getLedOn();
}

bool RgbLed::getRgbLedOn()
// gets the status of the entire LED (if anything is on, then true)
{
    return rgbLedOn;
}

bool RgbLed::getRLedOn()
// gets the stats of the Red LED
{
    return red.getLedOn();
}

bool RgbLed::getGLedOn()
// gets the stats of the Green LED
{
    return green.getLedOn();
}

bool RgbLed::getBLedOn()
// gets the stats of the Blue LED
{
    return blue.getLedOn();
}
