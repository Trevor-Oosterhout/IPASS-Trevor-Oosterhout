#include "mpu6050.hpp"
#include "hwlib.hpp"
#include <array>

const unsigned int accel_measurements_size = 3;
const unsigned int gyro_measurements_size  = 3;


void mpu6050::disable_sleep_mode(){
  {
    auto wtrans = ((hwlib::i2c_bus*)&i2c)->write(address);
    wtrans.write(0x6B);
    wtrans.write(0x00);
  }
}


void mpu6050::accel_measurements(std::array<int16_t, accel_measurements_size> & measurements){
  int16_t accel_x, accel_y, accel_z;
  uint8_t result [6];
  int sensitivity = 16384 / exponent(2, accel_sensitivity);

  {
    auto wtrans = ((hwlib::i2c_bus*)&i2c)->write(address);
    wtrans.write(0x3B);
  }
  hwlib::wait_ms(6);
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


  measurements = {accel_x, accel_y, accel_z};

}


int16_t mpu6050::temp_measurements(){
  int16_t temprature;
  uint8_t result [2];
  {
    auto wtrans = ((hwlib::i2c_bus*)&i2c)->write(address);
    wtrans.write(0x41);
  }
  hwlib::wait_ms(6);
  {
    auto rtrans = ((hwlib::i2c_bus*)&i2c)->read(address);
    rtrans.read(result, 2);
  }
  temprature = result[0] << 8 | result[1];

  temprature = temprature / 340 + 37;

  return temprature;
}


void mpu6050::gyro_measurements(std::array<int16_t, gyro_measurements_size> & measurements){
  int16_t gyro_x, gyro_y, gyro_z;
  uint8_t result [6];
  int sensitivity = 131 / exponent(2, gyro_sensitivity);


  {
    auto wtrans = ((hwlib::i2c_bus*)&i2c)->write(address);
    wtrans.write(0x43);
  }
  hwlib::wait_ms(6);
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


  measurements = {gyro_x, gyro_y, gyro_z};

}


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


int mpu6050::exponent(int base, unsigned int power){
  if(power > 0){
    int result = base;
    for(unsigned int i = 1; i < power; i++){
      result = result * base;
    }
    return result;
  }
  else{
    return 1;
  }

}


uint8_t mpu6050::read_register(const uint8_t read_address){
  uint8_t result [1];
  if(read_address < 0x76){
    {
      auto wtrans = ((hwlib::i2c_bus*)&i2c)->write(address);
      wtrans.write(read_address);
    }
    hwlib::wait_ms(6);
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


unsigned int mpu6050::who_am_i(){
  uint8_t result [1];
    {
      auto wtrans = ((hwlib::i2c_bus*)&i2c)->write(address);
      wtrans.write(0x75);
    }
    hwlib::wait_ms(6);
    {
      auto rtrans = ((hwlib::i2c_bus*)&i2c)->read(address);
      rtrans.read(result, 1);
    }
    return result[0];
}


void mpu6050::reset(){
  {
    auto wtrans = ((hwlib::i2c_bus*)&i2c)->write(address);
    wtrans.write(0x6B);
    wtrans.write(0x80);
  }
  accel_sensitivity = 0;
  gyro_sensitivity = 0;
  hwlib::wait_ms(6);
}


unsigned int mpu6050::get_accelleration_sensitivity(){
  return accel_sensitivity;
}


unsigned int mpu6050::get_gyro_sensitivity(){
  return gyro_sensitivity;
}


// int past_time, present_time, passed_time;
//
//
// void mpu6050::gyro_in_degrees(std::array<float, gyro_measurements_size> & angles){
//   int16_t gyro_x, gyro_y, gyro_z;
//   uint8_t result [6];
//   int sensitivity = 131 / exponent(2, gyro_sensitivity);
//   past_time = present_time;
//   present_time = hwlib::now_us();
//   passed_time = present_time - past_time;
//
//   float seconds = passed_time / 1000000;
//
//   {
//     auto wtrans = ((hwlib::i2c_bus*)&i2c)->write(address);
//     wtrans.write(0x43);
//   }
//   hwlib::wait_ms(6);
//   {
//     auto rtrans = ((hwlib::i2c_bus*)&i2c)->read(address);
//     rtrans.read(result, 6);
//   }
//   gyro_x = result[0] << 8 | result[1];
//   gyro_y = result[2] << 8 | result[3];
//   gyro_z = result[4] << 8 | result[5];
//
//   gyro_x = gyro_x / sensitivity;
//   gyro_y = gyro_y / sensitivity;
//   gyro_z = gyro_z / sensitivity;
//
//   float angle_x = gyro_x * seconds;
//   float angle_y = gyro_y * seconds;
//   float angle_z = gyro_y * seconds;
//
//   angle_x = angles[0] + angle_x;
//   angle_y = angles[1] + angle_y;
//   angle_z = angles[2] + angle_z;
//
//
//
//   angles = {angle_x, angle_y, angle_z};
// }
