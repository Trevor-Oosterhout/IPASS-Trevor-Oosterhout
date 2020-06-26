#include "security.hpp"
#include "hwlib.hpp"
#include "mpu6050.hpp"
#include <array>


void security::reset(){
  speaker.write(0);
  green_led.write(0);
  red_led.write(0);
  display.clear();
  display.flush();
  sensor.reset();

}


void security::setup(){
  sensor.disable_sleep_mode();
  green_led.write(1);
}


bool security::detect(){
  std::array<int16_t, 3> g_measurements;
  g_measurements = sensor.accel_measurements();
  if((g_measurements[2] < 900 || g_measurements[2] > 960) ||
    (g_measurements[1] < -60 ||  g_measurements[1] > 0)){
      // hwlib::cout << "acg = " << g_measurements[2] << "   |";
      // hwlib::wait_ms(500);
      // hwlib::cout << "acy = " << g_measurements[1] << "   |" << '\n';
      return true;
    }
  else{
    return false;
  }
}

void security::triggerd(){
  red_led.write(1);
  green_led.write(0);
  speaker.write(1);
}


// hwlib::cout << "acx = " << g_measurements[0] << "   |";
// hwlib::wait_ms(500);
// hwlib::cout << "acy = " << g_measurements[1] << "   |";
// hwlib::wait_ms(200);
// hwlib::cout << "acz = " << g_measurements[2] << '\n';
