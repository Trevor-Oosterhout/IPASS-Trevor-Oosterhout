#ifndef MPU6050_HPP
#define MPU6050_HPP
#include "hwlib.hpp"

/// @file

/// \brief
/// sensor mpu6050 class
/// \details
/// this class implements functions to read its measurements
/// change its sensitivity and read registers

class mpu6050{
private:
  const uint8_t address;
  hwlib::i2c_bus_bit_banged_scl_sda & i2c;
  unsigned int accel_sensitivity;
  unsigned int gyro_sensitivity;


  /// \brief
  /// exponent arithmetic function
  /// \details
  /// calculate (signed) integer to the power of an unsigned integer
  int exponent(int base, unsigned int power);

public:
  /// \brief
  /// default constructor
  /// \details
  /// this constructor initializes all attributes
  /// (accel-/ gyro_sensitivity is set to default)
  mpu6050(const uint8_t address, hwlib::i2c_bus_bit_banged_scl_sda & i2c):
  address (address),
  i2c (i2c),
  accel_sensitivity (0),
  gyro_sensitivity (0)
  {}


  /// \brief
  /// turns off sleep mode
  /// \details
  /// turns of sleep mode in register 107
  void disable_sleep_mode();


  /// \brief
  /// returns accel -x -y -z (signed) 16 bit integers in array in that order in milli gravitational acceleration
  /// \details
  /// this function returns the sensors acceleration measurements as (signed) 16 bit integers
  /// in an array in the order of x, y, z the return values should be interpeted
  /// as milli gravitational acceleration
  void accel_measurements(std::array<int16_t, 3> & measurements);


  /// \brief
  /// returns temprature as (signed) 16 bit integer in degrees Celsius
  /// \details
  /// this function returns the sensors temprature measurements as a (signed) 16 bit integer
  /// the integer should be interpeted in degrees Celsius
  int16_t temp_measurements();


  /// \brief
  /// returns gyro -x -y -z (signed) 16 bit integers in array in that order in degrees/s
  /// \details
  /// this function returns the sensors gyro measurements as (signed) 16 bit integers
  /// in an array in the order of x, y, z the return values should be interpeted
  /// as degrees per second
  void gyro_measurements(std::array<int16_t, 3> & measurements);


  /// \brief
  /// changes the mpu6050 acceleration sensitivity (parameter 0-3)
  /// \details
  /// changes the mpu6050 acceleration sensitivity to one of 4 options (0, 1, 2, 3)
  void calibrate_accel_sensitivity(uint8_t range);



  /// \brief
  /// changes the mpu6050 gyro sensitivity (parameter 0-3)
  /// \details
  /// changes the mpu6050 gyro sensitivity to one of 4 options (0, 1, 2, 3)
  void calibrate_gyro_sensitivity(uint8_t range);


  /// \brief
  /// read given register
  /// \details
  /// read given register should register not exist it will return 0
  uint8_t read_register(const uint8_t read_address);


  /// \brief
  /// resets all registers to default values
  /// \details
  /// calling this function will write a 1 to de DEVICE_RESET bit in the mpu6050
  /// will reset all registers to default value according to the datasheet
  void reset();

};




#endif // MPU6050_HPP
