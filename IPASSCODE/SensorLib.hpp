#ifndef SENSORLIB_HPP
#define SENSORLIB_HPP
#include "hwlib.hpp" // This library is used to setup pins
#include <array> // This is used to be able to use arrays

/// @file

/// \brief
/// DS18B20
/// \details
/// This class includes functions for reading of the DS18B20 Temperature sensor
/// The DS18B20 uses the one wire protocol so it only uses one data wire
/// The pin name is datapin
/// DS18B20 Datasheet: https://datasheets.maximintegrated.com/en/ds/DS18B20.pdf.
class DS18B20 {
private:

  /// \brief
  /// Data pin.
  /// \details
  /// The pin setup is located in the main
  /// The data wire is used by the functions to communicate with the DS18B20.
  hwlib::pin_oc & datapin;



  /// \brief
  /// Reset Function.
  /// \details
  /// The reset function will give a presence back from the DS18B20 temperatur sensor.
  void pin_reset();



  /// \brief
  /// Find correct bit.
  /// \details
  /// This function finds the correct bit to write for the function write_bit.
  bool bit_find(uint8_t byte, int position);



  /// \brief
  /// write byte.
  /// \details
  /// This function writes a byte using the write_bit function.
  void write_byte(uint8_t byte);



  /// \brief
  /// Write correct bit.
  /// \details
  /// This function writes a specific bit given from the function bit_find.
  void write_bit(bool bit);



  /// \brief
  /// Read slot.
  /// \details
  /// This function makes a read slot which gives a 0 or a 1
  bool read_slot();



  /// \brief
  /// Read_and_write function.
  /// \details
  ///This function reads the DS18B20 temperatur sensor for the 64-BIT lasered ROM code.
  ///The function puts this ROM code in an array and puts this array in the memory using a pointer.
  int * lasered_rom_code(uint8_t byte);

public:

  /// \brief
  /// Constructor of DS18B20 class.
  /// \details
  /// This constructor sets up the data pin
  /// A reference will be used so it will be affected in the real world
  DS18B20( hwlib::pin_oc & datapin ):
  datapin ( datapin )
  {}



  /// \brief
  /// Password Function.
  /// \details
  /// This function compares the correct password with the 64-BIT Lasered ROM code from the connected DS18B20
  bool password();



  /// \brief
  /// Print function.
  /// \details
  /// This function cout's the 64-BIT Lasered ROM code from the function lasered_rom_code
  void print();
};

#endif //SENSORLIB_HPP
