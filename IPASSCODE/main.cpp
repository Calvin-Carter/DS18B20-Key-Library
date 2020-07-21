#include "SensorLib.hpp"

int main(){
  hwlib::wait_ms(2000);
  namespace target = hwlib::target;
  WDT->WDT_MR = WDT_MR_WDDIS; // Kill watchdogs

  //Setting pins
  auto datapin = target::pin_oc( target::pins::d2);
  auto scl = target::pin_oc( target::pins::scl );
  auto sda = target::pin_oc( target::pins::sda );
  auto button = target::pin_in( target::pins::d9);


  auto temp_sensor = DS18B20( datapin );
  auto i2c_bus     = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
  auto screen = hwlib::glcd_oled( i2c_bus, 0x3c );
  auto font        = hwlib::font_default_8x8();
  auto display     = hwlib::terminal_from( screen, font );


  screen.clear();
  temp_sensor.print();


  for(;;){
  button.refresh();
  while(button.read() == 0){
    if(temp_sensor.password() == 1){
      hwlib::cout << hwlib::endl;
      hwlib::cout << hwlib::endl;
      hwlib::cout << hwlib::endl;
      hwlib::cout << "Correct Password" << hwlib::endl;
      display << '\f' << "Correct Password" << '\n';
      display << '\n';
      display << "Welcome User";
      screen.flush();
      temp_sensor.print();
      hwlib::wait_ms(5000);
    }
    else if(temp_sensor.password() == 0){
      hwlib::cout << hwlib::endl;
      hwlib::cout << hwlib::endl;
      hwlib::cout << hwlib::endl;
      hwlib::cout << "Incorrect Password" << hwlib::endl;
      display << '\f' << "Incorrect Password" << '\n';
      display << '\n';
      display << "     x   x" << '\n';
      display << "      x x" << '\n';
      display << "       x" << '\n';
      display << "      x x" << '\n';
      display << "     x   x" << '\n';
      screen.flush();
      temp_sensor.print();
      hwlib::wait_ms(5000);
      }
  }
  display << '\f' << "Insert Key " << '\n';
  display << '\n';
  display << "And Press Button" << '\n';
  display << '\n';
  display << "To Continue";
  screen.flush();
}
}
