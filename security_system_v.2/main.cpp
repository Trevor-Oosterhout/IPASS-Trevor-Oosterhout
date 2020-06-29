#include "hwlib.hpp"
#include "mpu6050.hpp"
#include "security.hpp"
#include <array>


int main( void ){
  auto scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
  auto sda = hwlib::target::pin_oc( hwlib::target::pins::sda );

  auto i2c = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );

  auto keypadrow_0 = hwlib::target::pin_oc(1, 25);
  auto keypadrow_1 = hwlib::target::pin_oc(2, 28);
  auto keypadrow_2 = hwlib::target::pin_oc(2, 26);
  auto keypadrow_3 = hwlib::target::pin_oc(2, 25);

  auto keypadrcol_0 = hwlib::target::pin_in(2, 24);
  auto keypadrcol_1 = hwlib::target::pin_in(2, 23);
  auto keypadrcol_2 = hwlib::target::pin_in(2, 22);
  auto keypadrcol_3 = hwlib::target::pin_in(2, 21);

  auto keyrows =  hwlib::port_oc_from_pins_t(keypadrow_0, keypadrow_1, keypadrow_2, keypadrow_3);
  auto keycolums =  hwlib::port_in_from_pins_t(keypadrcol_0, keypadrcol_1, keypadrcol_2, keypadrcol_3);

  auto keypad_matrix = hwlib::matrix_of_switches(keyrows, keycolums);

  auto display = hwlib::glcd_oled(i2c, 0x3C);
  auto font = hwlib::font_default_16x16();

  auto terminal = hwlib::terminal_from(display, font);
  auto keypad = hwlib::keypad< 16 >(keypad_matrix, "D#0*C987B654A321");
  auto speaker = hwlib::target::pin_out(0, 28);
  auto red_led = hwlib::target::pin_out(3, 7);
  auto green_led = hwlib::target::pin_out(3, 8);
  mpu6050 sensor(0x68, i2c);
  std::array<char, 4> password = {'9', '2', '9', '2'};


  security s(sensor, speaker, red_led, green_led, keypad, terminal, password);


  s.activate();



}
