#ifndef SECURITY_HPP
#define SECURITY_HPP

#include "hwlib.hpp"
#include "mpu6050.hpp"
#include <array>

/// @file

// this file contains doxygen documentation

/// \brief
/// application for securing home with MPU6050
/// \details
/// this class implements a security system with the mpu6050 and the following peripherals:
/// oled 128x64, circel speaker, red_led, green_led and a keypad 4x4

class security{
private:
  mpu6050 & sensor;
  hwlib::pin_out & speaker, & red_led, & green_led;
  hwlib::keypad< 16 > & keypad;
  hwlib::terminal_from & terminal;
  const std::array<char, 4> & password;


public:
  /// \brief
  /// create a security system from: mpu6050, oled 128x64, circel speaker, red_led, green_led, keypad 4x4
  /// \details
  /// contructor initializes all attributes 
  security(mpu6050 & sensor, hwlib::pin_out & speaker, hwlib::pin_out & red_led,
  hwlib::pin_out & green_led, hwlib::keypad< 16 > & keypad,
  hwlib::terminal_from & terminal, const std::array<char, 4> & password):
  sensor (sensor),
  speaker (speaker),
  red_led (red_led),
  green_led (green_led),
  keypad (keypad),
  terminal (terminal),
  password (password)
  {}


  /// \brief
  /// turns on peripherals to detect and signal nothing is detected
  /// \details
  /// this function turns on the green_led and disables sleep mode form the mpu6050
  void setup();


  /// \brief
  /// turns all peripherals off/default state
  /// \details
  /// this function turns the speaker and LEDS off, clears the OLED screen
  /// and puts the mpu6050 in sleep mode
  void reset();


  /// \brief
  /// returns true when the mpu6050 detects a step
  /// \details
  /// this function checks if there is acceleration on the z axis. if there is enough acceleration
  /// it returns true if not returns false
  bool detect();

  /// \brief
  /// turns on peripherals to signal detection
  /// \details
  /// this function turns on speaker and red led and turns on green led
  void triggerd();


  /// \brief
  /// put in password via keypad on oled press '#' when done
  /// \details
  /// this function allows the user to put in a password. the password is shown on
  /// the oled. pressing '#' checks if the password is correct. will loop until
  /// correct password has been given
  void input_password();


  /// \brief
  /// activates the system
  /// \details
  /// this functions will activate all functions above in the correct order en loop forever
  void activate();

};

#endif // SECURITY_HPP
