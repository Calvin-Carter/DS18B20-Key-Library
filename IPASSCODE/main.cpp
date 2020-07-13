#include "SensorLib.hpp"

int main(){
  hwlib::wait_ms(2000);
  namespace target = hwlib::target;
  WDT->WDT_MR = WDT_MR_WDDIS; // Kill watchdogs
  auto datapin = target::pin_oc( target::pins::d2); // Set pin

  //Functions

  auto temp_sensor = DS18B20( datapin );
  temp_sensor.lasered_rom_code();
}
