#ifndef SENSORLIB_HPP
#define SENSORLIB_HPP
#include "hwlib.hpp" // This library is used to setup pins
#include <array> // This is used to be able to use arrays

/// @file

/// \brief
/// DS18B20
/// \details
/// This class includes functions for reading the 64-BIT lasered ROM code of the DS18B20 Temperature sensor.
/// And uses this 64-BIT Lasered ROM code for applications. For example: a Key.
/// The DS18B20 uses the one wire protocol so it only uses one data wire
/// The one wire pin is defined as "datapin".
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
  /// The reset functions performs a reset.
  void pin_reset();



  /// \brief
  /// Find correct bit.
  /// \details
  /// This function finds the correct bit to write for the function write_byte.
  /// This functions requires the place of the bit and a 8-bit number.
  bool bit_find(uint8_t byte, int position);



  /// \brief
  /// Write correct bit.
  /// \details
  /// This function writes a 1 or 0 to the DS18B20.
  void write_bit(bool bit);



  /// \brief
  /// write byte.
  /// \details
  /// This function writes a byte using the write_bit function.
  void write_byte(uint8_t byte);



  /// \brief
  /// Read slot.
  /// \details
  /// This function makes a read slot which gives a 0 or a 1 back.
  /// For more information refer to page 16 of the DS18B20 datasheet.
  bool read_slot();





public:
  /// \brief
  /// Constructor of DS18B20 class.
  /// \details
  /// This constructor sets up the data pin
  /// A reference will be used so it will be affected in the real world.
  DS18B20( hwlib::pin_oc & datapin ):
  datapin ( datapin )
  {}

  /// \brief
  /// Lasered ROM Code.
  /// \details
  /// This function reads the DS18B20 64-BIT lasered ROM code.
  /// The function puts this ROM code in an array and puts this array in the memory using a pointer.
  int * lasered_rom_code(uint8_t byte);

  /// \brief
  /// Password Function.
  /// \details
  /// This function compares the correct password with the 64-BIT Lasered ROM code from the connected DS18B20
  /// This function returns true or false.
  bool password();



  /// \brief
  /// Print function.
  /// \details
  /// This function cout's in the terminal the 64-BIT Lasered ROM code in binary from the function lasered_rom_code.
  void print();
};

#endif //SENSORLIB_HPP
