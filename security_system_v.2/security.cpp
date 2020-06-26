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
  hwlib::wait_ms(20);
}


void security::setup(){
  sensor.disable_sleep_mode();
  green_led.write(1);
}


bool security::detect(){
  std::array<int16_t, 3> g_measurements;
  sensor.accel_measurements(g_measurements);
  if((g_measurements[2] < 900 || g_measurements[2] > 960)){
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

void security::input_password(){
  std::array<char, 4> input;
  char buffer;
  unsigned int index = 0;
  auto font = hwlib::font_default_16x16();
  auto terminal = hwlib::terminal_from(display, font);
  while(input != password){
    index = 0;
    terminal << '\f';
    terminal << "PASSWORD" << '\n' << "::" << hwlib::flush;
    while(index != 4){
        buffer = keypad.pressed();
        if(buffer != '\0'){
          terminal << buffer << hwlib::flush;
          input[index] = buffer;
          index++;
        }
    }
    if(input == password){
      terminal << '\f' << "PASSWORD" << '\n' << "VALID" << hwlib::flush;
      hwlib::wait_ms(2000);
    }
    else{
      terminal << '\f' << "PASSWORD" << '\n' << "INVALID" << hwlib::flush;
      hwlib::wait_ms(2000);
    }
  }
}

void security::activate(){
  for(;;){
    reset();
    setup();
    while (!detect()){}
    triggerd();
    input_password();
  }
}
