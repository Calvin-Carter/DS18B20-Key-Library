#include "SensorLib.hpp"

void DS18B20::pin_reset(){ // Gives reset pulse, will give back presence of all devices on the bus.
    datapin.write(0);
    datapin.flush();
    hwlib::wait_us(480);
    datapin.write(1);
    datapin.flush();
}



void DS18B20::write_bit(bool bit){
  if(bit == 1){
    datapin.write(0);
    datapin.flush();
    hwlib::wait_us(4);
    datapin.write(1);
    datapin.flush();
    hwlib::wait_us(70);
  }
  if(bit == 0){
    datapin.write(0);
    datapin.flush();
    hwlib::wait_us(70);
    datapin.write(1);
    datapin.flush();
    hwlib::wait_us(2);
  }
}



bool DS18B20::read_slot(){
  datapin.write(0);
  datapin.flush();
  hwlib::wait_us(4);
  datapin.write(1);
  datapin.flush();
  hwlib::wait_us(10);
  bool result = datapin.read();
  hwlib::wait_us(60);
  return result;
}



bool DS18B20::bit_find(uint8_t byte, int position){
  int x = 0;
  if(byte & (1 << position)){
    x = 1;
  }
  return x;
}



void DS18B20::write_byte(uint8_t byte){
  for(int i = 0; i < 8; i++){
    write_bit(bit_find(byte, i));
  }
}



int * DS18B20::read_and_write_byte(uint8_t byte){
   pin_reset();
   hwlib::wait_ms(1);
   int static rom_code[64];
   int counter = 0;
   write_byte(0x33);
   for(int j = 0; j < 8; j++){
     for(int i =0; i < 8; i++){
       counter++;
       datapin.refresh();
       rom_code[counter - 1] = read_slot();
     }
   }
     std::swap(rom_code[7], rom_code[0]);
     std::swap(rom_code[6], rom_code[1]);
     std::swap(rom_code[5], rom_code[2]);
     std::swap(rom_code[4], rom_code[3]);
     std::swap(rom_code[8], rom_code[55]);
     std::swap(rom_code[9], rom_code[54]);
     std::swap(rom_code[10], rom_code[53]);
     std::swap(rom_code[11], rom_code[52]);
     std::swap(rom_code[12], rom_code[51]);
     std::swap(rom_code[13], rom_code[50]);
     std::swap(rom_code[14], rom_code[49]);
     std::swap(rom_code[15], rom_code[48]);
     std::swap(rom_code[16], rom_code[47]);
     std::swap(rom_code[17], rom_code[46]);
     std::swap(rom_code[18], rom_code[45]);
     std::swap(rom_code[19], rom_code[44]);
     std::swap(rom_code[20], rom_code[43]);
     std::swap(rom_code[21], rom_code[42]);
     std::swap(rom_code[22], rom_code[41]);
     std::swap(rom_code[23], rom_code[40]);
     std::swap(rom_code[24], rom_code[39]);
     std::swap(rom_code[25], rom_code[38]);
     std::swap(rom_code[26], rom_code[37]);
     std::swap(rom_code[27], rom_code[36]);
     std::swap(rom_code[28], rom_code[35]);
     std::swap(rom_code[29], rom_code[34]);
     std::swap(rom_code[30], rom_code[33]);
     std::swap(rom_code[31], rom_code[32]);
     std::swap(rom_code[59], rom_code[60]);
     std::swap(rom_code[58], rom_code[61]);
     std::swap(rom_code[57], rom_code[62]);
     std::swap(rom_code[56], rom_code[63]);

return rom_code;
}



void DS18B20::print(){
  int * rom_code;
  rom_code = read_and_write_byte(0x33);
  hwlib::cout << "Lasered_Rom_Code: " << hwlib::endl;
  for(int i = 0; i < 64; i++){
    hwlib::cout << rom_code[i];
  }
  hwlib::cout << hwlib::endl;
}



bool DS18B20::password(){
  int counter = 0;
  int correct_password[64] = {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1};
  int * rom_code;
  rom_code = read_and_write_byte(0x33);

  for(int i = 0; i < 64; i++){
    if(correct_password[i] == rom_code[i]){
      counter++;
    }
  }
  if(counter == 64){
    return true;
  }
  return false;
}
