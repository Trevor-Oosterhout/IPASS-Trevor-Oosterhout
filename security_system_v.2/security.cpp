#include "security.hpp"


void security::reset(){
  speaker.write(0);
  green_led.write(0);
  red_led.write(0);
  terminal << '\f' << hwlib::flush;
  sensor.reset();
}


void security::setup(){
  sensor.disable_sleep_mode();
  green_led.write(1);
  terminal << "STATUS" << '\n' << "GOOD" <<hwlib::flush;
}


bool security::detect(){
  int16_t accel_measurements = sensor.accel_z_measurement();
  if(accel_measurements > 1100){
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
  unsigned int index = 0;
  char buffer = '\0';
  while(input != password){
    index = 0;
    buffer = '\0';
    terminal << '\f';
    terminal << "PASSWORD" << '\n' << "$ " << hwlib::flush;
    while(buffer != '#'){
        buffer = keypad.pressed();
        if(buffer != '\0' && buffer != '#' && index < 4){
          terminal << buffer << hwlib::flush;
          input[index] = buffer;
          index++;
          hwlib::wait_ms(100);
        }
    }
    terminal << '\f' << "PASSWORD" << '\n';
    if(input == password){
      terminal << "VALID" << hwlib::flush;
      hwlib::wait_ms(2000);
    }
    else{
      terminal << "INVALID" << hwlib::flush;
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
