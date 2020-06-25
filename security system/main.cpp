#include "hwlib.hpp"
#include "mpu6050.hpp"
#include "security.hpp"
#include <array>


int main( void ){
  auto scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
  auto sda = hwlib::target::pin_oc( hwlib::target::pins::sda );

  auto i2c = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );

  auto keypadrow_0 = due::pin_oc(1, 25);
  auto keypadrow_1 = due::pin_oc(2, 28);
  auto keypadrow_2 = due::pin_oc(2, 26);
  auto keypadrow_3 = due::pin_oc(2, 25);

  auto keypadrcol_0 = hwlib::target::pin_in(2, 24);
  auto keypadrcol_1 = hwlib::target::pin_in(2, 23);
  auto keypadrcol_2 = hwlib::target::pin_in(2, 22);
  auto keypadrcol_3 = hwlib::target::pin_in(2, 21);

  auto keyrows =  hwlib::port_oc_from_pins_t(keypadrow_0, keypadrow_1, keypadrow_2, keypadrow_3);
  auto keycolums =  hwlib::port_in_from_pins_t(keypadrcol_0, keypadrcol_1, keypadrcol_2, keypadrcol_3);

  auto keypad_matrix = hwlib::matrix_of_switches(keyrows, keycolums);


  auto keypad = hwlib::keypad< 16 >(keypad_matrix, "D#0*C987B654A321");
  auto speaker = hwlib::target::pin_out(2, 29);
  auto red_led = hwlib::target::pin_out(3, 7);
  auto green_led = hwlib::target::pin_out(3, 8);
  mpu6050 sensor(0x68, i2c);
  auto display = hwlib::glcd_oled(i2c, 0x3C);



}

  // mpu6050 sensor(0x68, i2c);
  //
  // sensor.disable_sleep_mode();
  //
  // int16_t temp;
  // std::array<int16_t, 3> accel;
  //
  // sensor.calibrate_accel_sensitivity(3);
  //
  // for(;;){
  //   temp = sensor.temp_measurements();
  //   accel = sensor.accel_measurements();
  //   hwlib::wait_ms(200);
  //   hwlib::cout << "temp = " << temp << "   |";
  //   hwlib::wait_ms(200);
  //   hwlib::cout << "acx = " << accel[0] << "   |";
  //   hwlib::wait_ms(200);
  //   hwlib::cout << "acy = " << accel[1] << "   |";
  //   hwlib::wait_ms(200);
  //   hwlib::cout << "acz = " << accel[2] << '\n';


 //  uint8_t x = 2;
 //  int y = x;
 //  hwlib::cout << "x = " << x <<  '\n';
 //  hwlib::cout << "y = " << y <<  '\n';
 //
 //
 // ic2 bus
 //  auto i2c = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
 //
 //  int16_t acx, acy , acz, tmp, gyx, gyy, gyz;
 //  uint8_t result [14];
 //
 //  // uint8_t read [1];
 //
 // // I2C adress without read/write bit
 //  uint8_t adress = 0x68;
 //  {
 //    auto mpu = ((hwlib::i2c_bus*)&i2c)->write(adress);
 //    mpu.write(0x6b);
 //    mpu.write(0);
 //  }
 //  {
 //    auto mpu = ((hwlib::i2c_bus*)&i2c)->write(adress);
 //    mpu.write(0x1c);
 //    mpu.write(0x18);
 //  }
  // {
  //   auto mpu = ((hwlib::i2c_bus*)&i2c)->write(adress);
  //   mpu.write(0x1c);
  // }
  // {
  //   auto mpu = ((hwlib::i2c_bus*)&i2c)->read(adress);
  //   mpu.read(read, 1);
  // }

  // hwlib::cout << "1c register "  << read[0] << "\n";

  // {
  //   auto mpu = ((hwlib::i2c_bus*)&i2c)->write(adress);
  //   mpu.write(0x1B);
  //   mpu.write(0x00);
  // }

  // hwlib::wait_ms(50);
  // for(;;){
  //
  //   {
  //     auto mpu = ((hwlib::i2c_bus*)&i2c)->write(adress);
  //     mpu.write(0x3b);
  //   }
  //   hwlib::wait_ms(50);
  //
  //   {
  //     auto mpu = ((hwlib::i2c_bus*)&i2c)->read(adress);
  //     mpu.read(result, 14);
  //   }
  //   hwlib::wait_ms(100);
  //
  //   acx = result[0] << 8 | result[1];
  //   acy = result[2] << 8 | result[3];
  //   acz = result[4] << 8 | result[5];
  //   tmp = result[6] << 8 | result[7];
  //   gyx = result[8] << 8 | result[9];
  //   gyy = result[10] << 8 | result[11];
  //   gyz = result[12] << 8 | result[13];
  //
  //   tmp = tmp / 340 + 36;
  //   acx = acx * 1000 / 2048;
  //   acy = acy * 1000 / 2048;
  //   acz = acz * 1000 / 2048;
  //   gyx = gyx / 131;
  //   gyy = gyy / 131;
  //   gyz = gyz / 131;
  //
  //   // int16_t acc_all = (acx*acx + acy*acy + acz*acz);
  //
  //
  //   hwlib::wait_ms(100);
  //   hwlib::cout << "acx = " << acx << '\n';
  //   hwlib::wait_ms(100);
  //   hwlib::cout << "acy = " << acy << '\n';
  //   hwlib::wait_ms(100);
  //   hwlib::cout << "acz = " << acz << '\n';
  //   hwlib::wait_ms(100);
  //   // hwlib::cout << "acc_all = " << acc_all << '\n';
  //   // hwlib::cout << "tmp = " << tmp << '\n';
  //   // hwlib::wait_ms(100);
  //   // hwlib::cout << "gyx = " << gyx << '\n';
  //   // hwlib::wait_ms(100);
  //   // hwlib::cout << "gyy = " << gyy << '\n';
  //   // hwlib::wait_ms(100);
  //   // hwlib::cout << "gyz = " << gyz << '\n';
  //
  // }
// }
