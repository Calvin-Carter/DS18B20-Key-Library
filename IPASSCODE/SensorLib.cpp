#include "SensorLib.hpp"

void DS18B20::pin_reset(){
    datapin.write(0);
    datapin.flush();
    hwlib::wait_us(480);
    datapin.write(1);
    datapin.flush();
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

uint64_t DS18B20::read_and_write_byte(uint8_t byte){
   uint64_t read_rom_result = 0;
   uint8_t temp = 0;
   int counter = 0;
   write_byte(0x33);
   for(int j = 0; j < 8; j++){
     for(int i =0; i < 8; i++){
       counter++;
       write_bit(bit_find(byte,i));
       hwlib::wait_us(15);
       datapin.refresh();
       temp = read_slot();
       temp = temp << (counter - 1);
       read_rom_result = read_rom_result | temp;
     }
   }
   return read_rom_result;
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

void DS18B20::skip_rom(){ // Writing Binary to temp_sensor 0xCC
  write_byte(0xCC);
}

void DS18B20::conversion(){
  write_byte(0x44);
}

void DS18B20::scratchpad(){
  write_byte(0xBE);
}

bool DS18B20::password(){
  pin_reset();
  hwlib::wait_ms(1);
  uint64_t input = read_and_write_byte(0x33);
  hwlib::cout << "test: " << input << hwlib::endl;
  if(input ==  86){
    hwlib::cout << "Correct Password" << hwlib::endl;
  }
  else {
    hwlib::cout << "Incorrect Password" << hwlib::endl;
  }
  return 0;
}

void DS18B20::lasered_rom_code(){
  pin_reset();
  hwlib::wait_ms(1);
  hwlib::cout << "lasered_rom_code: "<< read_and_write_byte(0x33) << hwlib::endl;
}

//Functies for temperature
  //hwlib::wait_us(15);
  //conversion();
  //hwlib::wait_ms(1);
  //pin_reset();
  //hwlib::wait_ms(1);
  //skip_rom();
  //hwlib::wait_us(15);
  //scratchpad();
  //hwlib::wait_us(1);
  //for(int i = 0; i<16; i++){
  //read_slot();
  //}
