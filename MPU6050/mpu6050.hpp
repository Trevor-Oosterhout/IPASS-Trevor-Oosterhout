#ifndef MPU6050_HPP
#define MPU6050_HPP
#include "hwlib.hpp"

/// @file

// this file contains doxygen lines


/// \brief
/// sensor mpu6050 class
/// \details
/// this class implements functions to use a part of its functions

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
  /// constructor initializes i2c channel and address
  /// \details
  /// this constructor initializes i2c channel and its address
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
  /// turns of sleep mode by writing a 0 to register 107
  void disable_sleep_mode();


  /// \brief
  /// reads acceleration -x -y -z in that order in milli gravitational acceleration to measurements<>
  /// \details
  /// this function reads the sensors acceleration measurements as (signed) 16 bit integers
  /// in an array in the order of x, y, z the values should be interpeted
  /// as milli gravitational acceleration
  void accel_measurements(std::array<int16_t, 3> & measurements);


  /// \brief
  /// returns temprature as (signed) 16 bit integer in degrees Celsius
  /// \details
  /// this function returns the sensors temprature measurements as a (signed) 16 bit integer
  /// the value should be interpeted in degrees Celsius
  int16_t temp_measurements();


  /// \brief
  /// reads gyro -x -y -z in that order in degrees/s to measurements<>
  /// \details
  /// this function reads the sensors gyro measurements as (signed) 16 bit integers
  /// in an array in the order of x, y, z the values should be interpeted
  /// as degrees per second
  void gyro_measurements(std::array<int16_t, 3> & measurements);


  /// \brief
  /// returns x acceleration as (signed) 16 bit integer in milli gravitational acceleration
  /// \details
  /// this function returns the sensors acceleration x measurements as a (signed) 16 bit integer
  /// the value should be interpeted in milli gravitational acceleration
  int16_t accel_x_measurement();


  /// \brief
  /// returns y acceleration as (signed) 16 bit integer in milli gravitational acceleration
  /// \details
  /// this function returns the sensors acceleration y measurements as a (signed) 16 bit integer
  /// the value should be interpeted in milli gravitational acceleration
  int16_t accel_y_measurement();


  /// \brief
  /// returns z acceleration as (signed) 16 bit integer in milli gravitational acceleration
  /// \details
  /// this function returns the sensors acceleration z measurements as a (signed) 16 bit integer
  /// the value should be interpeted in milli gravitational acceleration
  int16_t accel_z_measurement();


  /// \brief
  /// returns x gyro as (signed) 16 bit integer in degrees/s
  /// \details
  /// this function returns the sensors gyro x measurements as a (signed) 16 bit integer
  /// the value should be interpeted in degrees per second
  int16_t gyro_x_measurement();


  /// \brief
  /// returns y gyro as (signed) 16 bit integer in degrees/s
  /// \details
  /// this function returns the sensors gyro y measurements as a (signed) 16 bit integer
  /// the value should be interpeted in degrees per second
  int16_t gyro_y_measurement();


  /// \brief
  /// returns z gyro as (signed) 16 bit integer in degrees/s
  /// \details
  /// this function returns the sensors gyro z measurements as a (signed) 16 bit integer
  /// the value should be interpeted in degrees per second
  int16_t gyro_z_measurement();



  /// \brief
  /// changes the mpu6050 acceleration sensitivity to range [0-3]
  /// \details
  /// changes the mpu6050 acceleration sensitivity to one of 4 options (0, 1, 2, 3)
  /// sensitivity scale: 0 = +/- 2g, 1 = +/- 4g, 2 = +/- 8g, 3 = +/- 16g
  void calibrate_accel_sensitivity(uint8_t range);



  /// \brief
  /// changes the mpu6050 gyro sensitivity to range [0-3]
  /// \details
  /// changes the mpu6050 gyro sensitivity to one of 4 options (0, 1, 2, 3)
  /// sensitivity scale: 0 = +/- 250 degrees/s, 1 = +/- 500 degrees/s,
  /// 2 = +/- 1000 degrees/s, 3 = +/- 2000 degrees/s
  void calibrate_gyro_sensitivity(uint8_t range);


  /// \brief
  /// reads given register
  /// \details
  /// read given register should register not exist it will return 0
  uint8_t read_register(const uint8_t read_address);


  /// \brief
  /// resets all registers to default values
  /// \details
  /// calling this function will write a 1 to de DEVICE_RESET bit in the mpu6050 and
  /// will reset all registers to default value according to the datasheet
  void reset();


  /// \brief
  /// returns devices ID
  /// \details
  /// calling this function will give the identity of the device
  unsigned int who_am_i();


  /// \brief
  /// returns acceleration sensitivity
  /// \details
  /// calling this function will give the current acceleration sensitivity
  unsigned int get_accelleration_sensitivity();


  /// \brief
  /// returns devices gyro sensitivity
  /// \details
  /// calling this function will give the current gyro sensitivity
  unsigned int get_gyro_sensitivity();


  // \brief
  // reads gyro -x -y -z in that order in degrees to measurements<>
  // \details
  // this function reads the sensors gyro measurements as float
  // in an array in the order of x, y, z the values should be interpeted
  // as degree
  // note: this functions in currently non functional. I could not test this properly
  // void mpu6050::gyro_in_degrees(std::array<float, gyro_measurements_size> & angles){


};




#endif // MPU6050_HPP
