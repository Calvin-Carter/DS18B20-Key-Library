#ifndef SENSORLIB_HPP
#define SENSORLIB_HPP
#include "hwlib.hpp"
#include <array>
#include <string>
#include <vector>


class DS18B20 {
private:
  hwlib::pin_oc & datapin;
public:
  DS18B20( hwlib::pin_oc & datapin ):
  datapin ( datapin )
  {}
  void pin_reset();
  bool bit_find(uint8_t byte, int position);
  void write_byte(uint8_t byte);
  void write_bit(bool bit);
  void lasered_rom_code();
  void skip_rom();
  void conversion();
  void scratchpad();
  bool read_slot();
  bool password();
  uint64_t read_and_write_byte(uint8_t byte);
};

#endif //SENSORLIB_HPP
