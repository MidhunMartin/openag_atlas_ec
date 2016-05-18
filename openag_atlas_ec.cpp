/** 
 *  \file openag_atlas_ec.cpp
 *  \brief Electrical conductivity sensor.
 */
#include "openag_atlas_ec.h"

AtlasEc::AtlasEc(String electrical_conductivity_id, int electrical_conductivity_channel) {
  _electrical_conductivity_id = electrical_conductivity_id;
  _electrical_conductivity_channel = electrical_conductivity_channel;
}


void AtlasEc::begin(void) {
  Wire.begin();
}


String AtlasEc::get(String id) {
  String message = "";
  if (id == _electrical_conductivity_id) {
    electrical_conductivity = getElectricalConductivity() / 1000;
    message = id + ":" + String(electrical_conductivity, 2);
  }
  return message;
}

String AtlasEc::set(String id, String value) {
  return "";
}


float AtlasEc::getElectricalConductivity(void) {
  char sensor_data[30];
  byte sensor_bytes_received = 0;
  byte code = 0;
  byte in_char = 0;
  
  Wire.beginTransmission(_electrical_conductivity_channel);     // call the circuit by its ID number.
  Wire.write('r');                          // request a reading by sending 'r'
  Wire.endTransmission();                         // end the I2C data transmission.

  delay(1000);  // AS circuits need a 1 second before the reading is ready
  
  sensor_bytes_received = 0;                        // reset data counter
  memset(sensor_data, 0, sizeof(sensor_data));        // clear sensordata array;

  Wire.requestFrom(_electrical_conductivity_channel, 48, 1);    // call the circuit and request 48 bytes (this is more then we need).
  code = Wire.read();

  while (Wire.available()) {          // are there bytes to receive?
    in_char = Wire.read();            // receive a byte.
  
    if (in_char == 0) {               // null character indicates end of command
      Wire.endTransmission();         // end the I2C data transmission.
      break;                          // exit the while loop, we're done here
    }
    else {
      sensor_data[sensor_bytes_received] = in_char;      // append this byte to the sensor data array.
      sensor_bytes_received++;
    }
  }
  return atof(sensor_data);
}

