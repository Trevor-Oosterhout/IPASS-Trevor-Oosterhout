#include "hwlib.hpp"
#include "mpu6050.hpp"

// uint16_t acx, acy , acz, tmp, gyx, gyy, gyz;


int main( void ){
  auto scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
  auto sda = hwlib::target::pin_oc( hwlib::target::pins::sda );

 // ic2 bus
  auto i2c = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );

  int acx, acy , acz, tmp, gyx, gyy, gyz;
  uint8_t result [14];

  uint8_t read [1];

 // I2C adress without read/write bit
  uint8_t adress = 0x68;
  {
    auto mpu = ((hwlib::i2c_bus*)&i2c)->write(adress);
    mpu.write(0x6b);
    mpu.write(0);
  }
  {
    auto mpu = ((hwlib::i2c_bus*)&i2c)->write(adress);
    mpu.write(0x1c);
    mpu.write(0x00);
  }
  {
    auto mpu = ((hwlib::i2c_bus*)&i2c)->write(adress);
    mpu.write(0x1c);
  }
  {
    auto mpu = ((hwlib::i2c_bus*)&i2c)->read(adress);
    mpu.read(read, 1);
  }

  hwlib::cout << "1c register "  << read[0] << "\n";

  {
    auto mpu = ((hwlib::i2c_bus*)&i2c)->write(adress);
    mpu.write(0x1B);
    mpu.write(0x00);
  }

  hwlib::wait_ms(50);
  for(;;){

    {
      auto mpu = ((hwlib::i2c_bus*)&i2c)->write(adress);
      mpu.write(0x3b);
    }
    hwlib::wait_ms(50);

    {
      auto mpu = ((hwlib::i2c_bus*)&i2c)->read(adress);
      mpu.read(result, 14);
    }
    hwlib::wait_ms(100);

    acx = (result[0] << 8 | result[1]) * 1000 / 16348;
    acy = (result[2] << 8 | result[3]) * 1000 / 16384;
    acz = (result[4] << 8 | result[5]) * 1000 / 16384;
    tmp = (result[6] << 8 | result[7]) / 340.0f + 36.53;
    gyx = (result[8] << 8 | result[9]) / 131;
    gyy = (result[10] << 8 | result[11]) /131;
    gyz = (result[12] << 8 | result[13]) /131;

    // hwlib::wait_ms(100);
    // hwlib::cout << "acx = " << acx << '\n';
    // hwlib::wait_ms(100);
    // hwlib::cout << "acy = " << acy << '\n';
    hwlib::wait_ms(100);
    hwlib::cout << "acz = " << acz << '\n';
    // hwlib::wait_ms(100);
    // hwlib::cout << "tmp = " << tmp << '\n';
    // hwlib::wait_ms(100);
    // hwlib::cout << "gyx = " << gyx << '\n';
    // hwlib::wait_ms(100);
    // hwlib::cout << "gyy = " << gyy << '\n';
    // hwlib::wait_ms(100);
    // hwlib::cout << "gyz = " << gyz << '\n';

  }
}
