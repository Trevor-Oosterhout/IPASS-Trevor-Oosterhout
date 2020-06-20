#include "mpu6050.hpp"
#include <array>
#include "misc.hpp"
#include "hwlib.hpp"


/// @file

const unsigned int accel_measurements_size = 3;
const unsigned int gyro_measurements_size  = 3;


/// \brief
/// turns off sleep mode
/// \details
/// turns of sleep mode in register 107
void mpu6050::disable_sleep_mode(){
  {
    auto mpu = ((hwlib::i2c_bus*)&i2c)->write(adres);
    mpu.write(0x6B);
    mpu.write(0x00);
  }
}


/// \brief
/// returns accel -x -y -z (signed) 16 bit integers in array in that order in milli m/s^2
/// \details
/// this function returns the sensors acceleration measurements as (signed) 16 bit integers
/// in an array in the order of x, y, z the return values should be interpeted
/// as milli m/s^2
std::array<int16_t, accel_measurements_size> mpu6050::accel_measurements(){
  int16_t accel_x, accel_y, accel_z;
  uint8_t result [6];
  int sensitivity = 2048 * exponent(2, accel_sensitivity);


  {
    auto mpu = ((hwlib::i2c_bus*)&i2c)->write(adres);
    mpu.write(0x3B);
  }
  {
    auto mpu = ((hwlib::i2c_bus*)&i2c)->read(adres);
    mpu.read(result, 6);
  }
  accel_x = result[0] << 8 | result[1];
  accel_y = result[2] << 8 | result[3];
  accel_z = result[4] << 8 | result[5];

  accel_x = accel_x * 1000 / sensitivity;
  accel_y = accel_y * 1000 / sensitivity;
  accel_z = accel_z * 1000 / sensitivity;

  std::array<int16_t, accel_measurements_size> measurements = {accel_x, accel_y, accel_z};

  return measurements;
}


/// \brief
/// returns temprature as (signed) 16 bit integer in degrees Celsius
/// \details
/// this function returns the sensors temprature measurements as a (signed) 16 bit integer
/// the integer should be interpeted in degrees Celsius
int16_t mpu6050::temp_measurements(){
  int16_t temprature;
  uint8_t result [2];
  {
    auto mpu = ((hwlib::i2c_bus*)&i2c)->write(adres);
    mpu.write(0x41);
  }
  {
    auto mpu = ((hwlib::i2c_bus*)&i2c)->read(adres);
    mpu.read(result, 2);
  }
  temprature = result[0] << 8 | result[1];

  temprature = temprature / 340 + 37;

  return temprature;
}


/// \brief
/// returns accel -x -y -z (signed) 16 bit integers in array in that order in degrees/s
/// \details
/// this function returns the sensors gyro measurements as (signed) 16 bit integers
/// in an array in the order of x, y, z the return values should be interpeted
/// as degrees per second
std::array<int16_t, gyro_measurements_size> mpu6050::gyro_measurements(){
  int16_t gyro_x, gyro_y, gyro_z;
  uint8_t result [6];
  int sensitivity = 16.4 * exponent(2, gyro_sensitivity);

  {
    auto mpu = ((hwlib::i2c_bus*)&i2c)->write(adres);
    mpu.write(0x43);
  }
  {
    auto mpu = ((hwlib::i2c_bus*)&i2c)->read(adres);
    mpu.read(result, 6);
  }
  gyro_x = result[0] << 8 | result[1];
  gyro_y = result[2] << 8 | result[3];
  gyro_z = result[4] << 8 | result[5];

  gyro_x = gyro_x / sensitivity;
  gyro_y = gyro_y / sensitivity;
  gyro_z = gyro_z / sensitivity;

  std::array<int16_t, gyro_measurements_size> measurements = {gyro_x, gyro_y, gyro_z};

  return measurements;
}


/// \brief
///
/// \details
///
void mpu6050::calibrate_accel_sensitivity(uint8_t range){
  if(range < 4){
    gyro_sensitivity = range;
    range = range << 3;
    {
      auto mpu = ((hwlib::i2c_bus*)&i2c)->write(adres);
      mpu.write(0x1C);
      mpu.write(range);
    }
  }
}
