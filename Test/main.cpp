#include "../IPASSCODE/SensorLib.hpp"
#include "hwlib.hpp"

int main(){

hwlib::wait_ms(2000);
namespace target = hwlib::target;
WDT->WDT_MR = WDT_MR_WDDIS; // Kill watchdogs

//Setting pins
auto datapin = target::pin_oc( target::pins::d2);
auto temp_sensor = DS18B20( datapin );

int correct_bit_code1[64] = {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1};
int correct_bit_code2[64] = {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0};

int * rom_code;
rom_code = temp_sensor.read_and_write_byte(0x33);

int counter1 = 0;
int counter2 = 0;

for(int i = 0; i < 64; i++){
  if(correct_bit_code1[i] != rom_code[i]){
    counter1++;
  }
}

for(int j = 0; j < 64; j++){
  if(correct_bit_code2[j] != rom_code[j]){
    counter2++;
  }
}

if(counter1 > 0 && counter2 > 0){
  hwlib::cout << "Error, the 64-Bit ROM code is not correct";
}
else {
  hwlib::cout << "No errors found" << hwlib::endl;
}
}
