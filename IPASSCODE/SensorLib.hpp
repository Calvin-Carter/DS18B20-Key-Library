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
  ///
  void pin_reset();



  /// \brief
  ///
  /// \details
  ///
  bool bit_find(uint8_t byte, int position);



  /// \brief
  ///
  /// \details
  ///
  void write_byte(uint8_t byte);



  /// \brief
  ///
  /// \details
  ///
  void write_bit(bool bit);



  /// \brief
  ///
  /// \details
  ///
  bool read_slot();



public:

  /// \brief
  ///
  /// \details
  ///
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
  /// This function cout's the 64-BIT Lasered ROM code from
  void print();



  /// \brief
  ///
  /// \details
  ///
  int * read_and_write_byte(uint8_t byte);
};

#endif //SENSORLIB_HPP
