#ifndef SECURITY_HPP
#define SECURITY_HPP

#include "hwlib.hpp"
#include "mpu6050.hpp"
#include <array>

/// @file

// this file contains doxygen documentation

/// \brief
///
/// \details
///

class security{
private:
  mpu6050 & sensor;
  hwlib::pin_out & speaker, & red_led, & green_led;
  hwlib::keypad< 16 > & keypad;
  hwlib::glcd_oled & display;
  const std::array<char, 4> & password;


public:
  security(mpu6050 & sensor, hwlib::pin_out & speaker, hwlib::pin_out & red_led,
  hwlib::pin_out & green_led, hwlib::keypad< 16 > & keypad,
  hwlib::glcd_oled & display, std::array<char, 4> & password):
  sensor (sensor),
  speaker (speaker),
  red_led (red_led),
  green_led (green_led),
  keypad (keypad),
  display (display),
  password (password)
  {}


  /// \brief
  ///
  /// \details
  ///
  void setup();


  /// \brief
  ///
  /// \details
  ///
  void reset();


  /// \brief
  ///
  /// \details
  ///
  bool detect(std::array<int16_t, 3> & accel_measurements);

  /// \brief
  ///
  /// \details
  ///
  void triggerd();


  /// \brief
  ///
  /// \details
  ///
  void input_password();


  /// \brief
  ///
  /// \details
  ///
  void activate();

};

#endif // SECURITY_HPP
