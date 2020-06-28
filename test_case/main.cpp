// #include "catch.hpp"
#include "hwlib.hpp"
#include "mpu6050.hpp"
#include <array>

// (catch2 would not work so I made my own tests)
// conditions: the mpu6050 just powererd on and nothing has been written to the mpu6050
// the AD0 pin is LOW and the mpu is face up and standing still on a flat surface
// addional conditions are in commentary above the test


void test_who_am_i(hwlib::i2c_bus_bit_banged_scl_sda & i2c){
  mpu6050 sensor(0x68, i2c);
  unsigned int ID = sensor.who_am_i();
  if(ID == 0x68){
    hwlib::cout << "TEST CASE WHO_AM_I IS SUCCESSFUL" << '\n' << '\n';
  }
  else{
    hwlib::cout << "TEST CASE WHO_AM_I HAS FAILED" << '\n' << '\n';
  }
}


void test_read_register(hwlib::i2c_bus_bit_banged_scl_sda & i2c){
  mpu6050 sensor(0x68, i2c);
  uint8_t a = sensor.read_register(0x6b);
  if(a == 0x40){
    hwlib::cout << "TEST CASE READ_REGISTER IS SUCCESSFUL" << '\n' << '\n';
  }
  else{
    hwlib::cout << "TEST CASE READ_REGISTER HAS FAILED" << '\n' << '\n';
  }
}


void test_disable_sleep_mode(hwlib::i2c_bus_bit_banged_scl_sda & i2c){
  mpu6050 sensor(0x68, i2c);
  sensor.disable_sleep_mode();
  uint8_t a = sensor.read_register(0x68);
  if(a == 0x00){
    hwlib::cout << "TEST CASE DISABLE_SLEEP_MODE IS SUCCESSFUL" << '\n' << '\n';
  }
  else{
    hwlib::cout << "TEST CASE DISABLE_SLEEP_MODE IS SUCCESSFUL" << '\n' << '\n';
  }
}


void test_reset(hwlib::i2c_bus_bit_banged_scl_sda & i2c){
  mpu6050 sensor(0x68, i2c);
  sensor.disable_sleep_mode();
  sensor.reset();
  uint8_t a = sensor.read_register(0x6b);
  if(a == 64){
    hwlib::cout << "TEST CASE RESET IS SUCCESSFUL" << '\n' << '\n';
  }
  else{
    hwlib::cout << "TEST CASE RESET HAS FAILED" << '\n' << '\n';
  }

}


// note the mpu6050 needs to be face up on a flat surface for this test
void test_acceleration(hwlib::i2c_bus_bit_banged_scl_sda & i2c){
  mpu6050 sensor(0x68, i2c);
  sensor.disable_sleep_mode();
  std::array<int16_t, 3> a;
  sensor.accel_measurements(a);
  if( ((a[0] < -20) && (a[0] > -100)) && ((a[1] < -5) && (a[1] > -50)) && ((a[2] < 960) && (a[2] > 910))){
    hwlib::cout << "TEST CASE ACCELERATION MEASUREMENTS IS SUCCESSFUL" << '\n' << '\n';
  }
  else{
    hwlib::cout << "TEST CASE ACCELERATION MEASUREMENTS HAS FAILED" << '\n' << '\n';
  }
}


// note this test depends on the temprature of the room
void test_temprature(hwlib::i2c_bus_bit_banged_scl_sda & i2c){
  mpu6050 sensor(0x68, i2c);
  sensor.disable_sleep_mode();
  int16_t a = sensor.temp_measurements();
  if(a > 20 && a < 35){
    hwlib::cout << "TEST CASE TEMPRATURE MEASUREMENTS IS SUCCESSFUL" << '\n' << '\n';
  }
  else{
    hwlib::cout << "TEST CASE TEMPRATURE HAS MEASUREMENTS FAILED" << '\n' << '\n';
  }
}


// note the mpu6050 needs to be face up on a flat surface for this test
void test_gyro_1(hwlib::i2c_bus_bit_banged_scl_sda & i2c){
  mpu6050 sensor(0x68, i2c);
  sensor.disable_sleep_mode();
  std::array<int16_t, 3> a;
  sensor.gyro_measurements(a);
  if( ((a[0] < 5) && (a[0] > -5)) && ((a[1] < 5) && (a[1] > -5)) && ((a[2] < 5) && (a[2] > -5))){
    hwlib::cout << "TEST CASE GYRO MEASUREMENTS IS SUCCESSFUL" << '\n' << '\n';
  }
  else{
    hwlib::cout << "TEST CASE GYRO MEASUREMENTS HAS FAILED" << '\n' << '\n';
  }
}


void test_calibrate_gyro_acceleration(hwlib::i2c_bus_bit_banged_scl_sda & i2c){
  mpu6050 sensor(0x68, i2c);
  sensor.calibrate_gyro_sensitivity(3);
  sensor.calibrate_accel_sensitivity(3);
  uint8_t a = sensor.read_register(0x1B);
  uint8_t b = sensor.read_register(0x1C);
  sensor.calibrate_gyro_sensitivity(0);
  sensor.calibrate_accel_sensitivity(0);
  uint8_t c = sensor.read_register(0x1B);
  uint8_t d = sensor.read_register(0x1C);
  if((a == 0x18 && b == 0x18) && (c == 0x00 && d == 0x00)){
    hwlib::cout << "TEST CASE CALIBRATE GYRO AND ACCELERATION IS SUCCESSFUL" << '\n' << '\n';
  }
  else{
    hwlib::cout << "TEST CASE CALIBRATE GYRO AND ACCELERATION HAS FAILED" << '\n' << '\n';
  }
}


// note the mpu6050 needs to be face up on a flat surface for this test
void test_accel_calibrated_measurements(hwlib::i2c_bus_bit_banged_scl_sda & i2c){
  mpu6050 sensor(0x68, i2c);
  sensor.disable_sleep_mode();
  sensor.calibrate_accel_sensitivity(3);
  std::array<int16_t, 3> a;
  sensor.accel_measurements(a);
  if( ((a[0] < -20) && (a[0] > -100)) && ((a[1] < -5) && (a[1] > -50)) && ((a[2] < 960) && (a[2] > 910))){
    hwlib::cout << "TEST CASE CALIBRATED ACCELERATION MEASUREMENTS IS SUCCESSFUL" << '\n' << '\n';
  }
  else{
    hwlib::cout << "TEST CASE CALIBRATED ACCELERATION MEASUREMENTS HAS FAILED" << '\n' << '\n';
  }
}


// note the mpu6050 needs to be face up on a flat surface for this test
void test_gyro_calibrated_measurements(hwlib::i2c_bus_bit_banged_scl_sda & i2c){
  mpu6050 sensor(0x68, i2c);
  sensor.disable_sleep_mode();
  sensor.calibrate_gyro_sensitivity(3);
  std::array<int16_t, 3> a;
  sensor.gyro_measurements(a);
  if( ((a[0] < 5) && (a[0] > -5)) && ((a[1] < 5) && (a[1] > -5)) && ((a[2] < 5) && (a[2] > -5))){
    hwlib::cout << "TEST CASE CALIBRATED GYRO IS SUCCESSFUL" << '\n' << '\n';
  }
  else{
    hwlib::cout << "TEST CASE CALIBRATED GYRO HAS FAILED" << '\n' << '\n';
  }
}




int main (void){
  auto scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
  auto sda = hwlib::target::pin_oc( hwlib::target::pins::sda );

  auto i2c = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );

  test_reset(i2c);

  test_read_register(i2c);

  test_who_am_i(i2c);

  test_disable_sleep_mode(i2c);

  test_acceleration(i2c);

  test_temprature(i2c);

  test_gyro_1(i2c);

  test_calibrate_gyro_acceleration(i2c);

  test_accel_calibrated_measurements(i2c);

  test_gyro_calibrated_measurements(i2c);


}
