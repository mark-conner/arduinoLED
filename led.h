#pragma once
#ifndef LED_H_
#define LED_H_

class Led {
  protected:
  int gpioPin;  // GPIO pin that the LED is connected to
  bool invert;  // default false, invert High / Low to turn on led
  bool ledOn;

  public:
  Led();
  Led(int, bool);
  void setLedOn(bool);
  void setLedLevel(int);
  bool getLedOn();
};

class BlinkLed : public Led {
  private:
  unsigned long lastSwitchCount;  // in milliseconds
  unsigned long offTime;  // in milliseconds
  unsigned long onTime; // in milliseconds

  public:
  BlinkLed();
  BlinkLed(int, unsigned long, unsigned long, bool);
  void checkLedCount(unsigned long);
};

class RgbLed {
  private:
  Led red;
  Led green;
  Led blue;
  bool rgbLedOn;
  
  public:
  RgbLed();
  RgbLed(int, int, int, bool);
  void setRgbLedOn(bool);
  void setRLedOn(bool);
  void setGLedOn(bool);
  void setBLedOn(bool);
  void setLedRGB(int, int, int);
  bool getRgbLedOn();
  bool getRLedOn();
  bool getGLedOn();
  bool getBLedOn();
};

#endif