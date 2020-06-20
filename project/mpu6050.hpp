#ifndef MPU6050_HPP
#define MPU6050_HPP
#include "hwlib.hpp"

/// @file

/// \brief
/// sensor mpu6050 class
/// \details
/// this class implements functions to read its measurements
/// change its sensitivity

class mpu6050{
private:
  const uint8_t adres;
  hwlib::i2c_bus_bit_banged_scl_sda & i2c;
  unsigned int accel_sensitivity;
  unsigned int gyro_sensitivity;

public:
  /// \brief
  /// default constructor
  /// \details
  /// this constructor initializes all attributes
  /// (accel-/ gyro_sensitivity is set to default)
  mpu6050(const uint8_t adres, hwlib::i2c_bus_bit_banged_scl_sda & i2c):
  adres (adres),
  i2c (i2c),
  accel_sensitivity (0),
  gyro_sensitivity (0)
  {}

  void disable_sleep_mode();

  std::array<int16_t, 3> accel_measurements();

  int16_t temp_measurements();

  std::array<int16_t, 3> gyro_measurements();

  void calibrate_accel_sensitivity(uint8_t range);


};




#endif // MPU6050_HPP
