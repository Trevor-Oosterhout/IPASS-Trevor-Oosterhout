#include "mpu6050.hpp"
#include <array>
#include "hwlib.hpp"

/// @file


const unsigned int accel_measurements_size = 3;
const unsigned int gyro_measurements_size  = 3;
int16_t gyro_x_d, gyro_y_d, gyro_z_d;
float current_time, prev_time, elapsed_time;


/// \brief
/// turns off sleep mode
/// \details
/// turns of sleep mode in register 107
void mpu6050::disable_sleep_mode(){
  current_time = hwlib::now_us();
  {
    auto wtrans = ((hwlib::i2c_bus*)&i2c)->write(address);
    wtrans.write(0x6B);
    wtrans.write(0x00);
  }
}


/// \brief
/// returns accel -x -y -z (signed) 16 bit integers in array in that order in milli gravitational acceleration
/// \details
/// this function returns the sensors acceleration measurements as (signed) 16 bit integers
/// in an array in the order of x, y, z the return values should be interpeted
/// as milli gravitational acceleration
std::array<int16_t, accel_measurements_size> mpu6050::accel_measurements(){
  int16_t accel_x, accel_y, accel_z;
  uint8_t result [6];
  int sensitivity = 16384 / exponent(2, accel_sensitivity);

  {
    auto wtrans = ((hwlib::i2c_bus*)&i2c)->write(address);
    wtrans.write(0x3B);
  }
  {
    auto rtrans = ((hwlib::i2c_bus*)&i2c)->read(address);
    rtrans.read(result, 6);
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
    auto wtrans = ((hwlib::i2c_bus*)&i2c)->write(address);
    wtrans.write(0x41);
  }
  {
    auto rtrans = ((hwlib::i2c_bus*)&i2c)->read(address);
    rtrans.read(result, 2);
  }
  temprature = result[0] << 8 | result[1];

  temprature = temprature / 340 + 37;

  return temprature;
}


/// \brief
/// returns gyro -x -y -z (signed) 16 bit integers in array in that order in degrees/s
/// \details
/// this function returns the sensors gyro measurements as (signed) 16 bit integers
/// in an array in the order of x, y, z the return values should be interpeted
/// as degrees per second
std::array<int16_t, gyro_measurements_size> mpu6050::gyro_measurements(){
  int16_t gyro_x, gyro_y, gyro_z;
  uint8_t result [6];
  int sensitivity = 131 / exponent(2, gyro_sensitivity);
  prev_time = current_time;
  current_time = hwlib::now_us();
  elapsed_time = (current_time - prev_time) / 1000000;

  {
    auto wtrans = ((hwlib::i2c_bus*)&i2c)->write(address);
    wtrans.write(0x43);
  }
  {
    auto rtrans = ((hwlib::i2c_bus*)&i2c)->read(address);
    rtrans.read(result, 6);
  }
  gyro_x = result[0] << 8 | result[1];
  gyro_y = result[2] << 8 | result[3];
  gyro_z = result[4] << 8 | result[5];

  gyro_x = gyro_x / sensitivity;
  gyro_y = gyro_y / sensitivity;
  gyro_z = gyro_z / sensitivity;

  gyro_x_d = gyro_x_d + gyro_x * elapsed_time;
  gyro_y_d = gyro_y_d + gyro_y * elapsed_time;
  gyro_z_d = gyro_z_d + gyro_z * elapsed_time;


  hwlib::cout << "gyro_x = " << gyro_x_d << "      |";
  hwlib::cout << "gyro_y = " << gyro_y_d << "      |";
  hwlib::cout << "gyro_z = " << gyro_z_d << "\n";


  std::array<int16_t, gyro_measurements_size> measurements = {gyro_x, gyro_y, gyro_z};

  return measurements;
}


/// \brief
/// changes the mpu6050 gyro sensitivity (parameter 0-3)
/// \details
/// changes the mpu6050 gyro sensitivity to one of 4 options (0, 1, 2, 3)
void mpu6050::calibrate_gyro_sensitivity(uint8_t range){
  if(range < 4){
    gyro_sensitivity = range;
    range = range << 3;
    {
      auto wtrans = ((hwlib::i2c_bus*)&i2c)->write(address);
      wtrans.write(0x1B);
      wtrans.write(range);
    }
  }
}


/// \brief
/// changes the mpu6050 acceleration sensitivity (parameter 0-3)
/// \details
/// changes the mpu6050 acceleration sensitivity to one of 4 options (0, 1, 2, 3)
void mpu6050::calibrate_accel_sensitivity(uint8_t range){
  if(range < 4){
    accel_sensitivity = range;
    range = range << 3;
    {
      auto wtrans = ((hwlib::i2c_bus*)&i2c)->write(address);
      wtrans.write(0x1C);
      wtrans.write(range);
    }
  }
}


/// \brief
/// exponent arithmetic function (not public)
/// \details
/// calculate (signed) integer to the power of an unsigned integer
int mpu6050::exponent(int base, unsigned int power){
  if(power > 0){
    int result = base;
    for(unsigned int i = 0; i < power - 1; i++){
      result = result * base;
    }
    return result;
  }
  else{
    return 1;
  }

}


/// \brief
/// read given register
/// \details
/// read given register should register not exist it will return 0
uint8_t mpu6050::read_register(const uint8_t read_address){
  uint8_t result [1];
  if(read_address < 0x75){
    {
      auto wtrans = ((hwlib::i2c_bus*)&i2c)->write(address);
      wtrans.write(read_address);
    }
    {
      auto rtrans = ((hwlib::i2c_bus*)&i2c)->read(address);
      rtrans.read(result, 1);
    }

    return result[0];
  }
  else{
    return 0;
  }


}


/// \brief
/// resets all registers to default values
/// \details
/// calling this function will write a 1 to de DEVICE_RESET bit in the mpu6050
/// will reset all registers to default value according to the datasheet
void mpu6050::reset(){
  {
    auto wtrans = ((hwlib::i2c_bus*)&i2c)->write(address);
    wtrans.write(0x6B);
    wtrans.write(0x80);
  }

}
