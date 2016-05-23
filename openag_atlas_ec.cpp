/**
 *  \file openag_atlas_ec.cpp
 *  \brief Electrical conductivity sensor.
 */
#include "openag_atlas_ec.h"

AtlasEc::AtlasEc(String id, String* parameters) : Peripheral(id, parameters){
  this->id = id;
  _electrical_conductivity_key = "electrical_conductivity";
  _electrical_conductivity_channel = parameters[0].toInt();
}

AtlasEc::~AtlasEc() {}

void AtlasEc::begin() {
  Wire.begin();
  _time_of_last_reading = 0;
}

String AtlasEc::get(String key) {
  if (key == String(_electrical_conductivity_key)) {
    return getElectricalConductvity();
  }
}

String AtlasEc::set(String key, String value) {
  if (key == String(_electrical_conductivity_key)) {
    return getErrorMessage(_electrical_conductivity_key);
  }
}

String AtlasEc::getElectricalConductvity(){
  if (millis() - _time_of_last_reading > _min_update_interval){ // can only read sensor so often
    getData();
    _time_of_last_reading = millis();
  }
  return _electrical_conductivity_message;
}

void AtlasEc::getData() {
  boolean is_good_reading = true;

  // Read sensor
  Wire.beginTransmission(_electrical_conductivity_channel); // read message response state
  Wire.print("r");
  Wire.endTransmission();
  delay(1000);
  Wire.requestFrom(_electrical_conductivity_channel, 20, 1);
  byte response = Wire.read();
  String string = Wire.readStringUntil(0);

  // Check for failure
  if (response == 255) {
    is_good_reading = false; // no data
  }
  else if (response == 254) {
    is_good_reading = false; // request pending
  }
  else if (response == 2) {
    is_good_reading = false; // request failed
  }
  else if (response == 1) { // good reading
    electrical_conductivity = string.toFloat() / 1000;
  }
  else {
    is_good_reading = false; // unknown error
  }

  // Update messages
  if (is_good_reading) {
    _electrical_conductivity_message = getMessage(_electrical_conductivity_key, String(electrical_conductivity, 1));
  }
  else { // read failure
    _electrical_conductivity_message = getErrorMessage(_electrical_conductivity_key);
  }
}

String AtlasEc::getMessage(String key, String value) {
  return String(id + "," + key + "," + value);
}

String AtlasEc::getErrorMessage(String key) {
  return String(id + "," + key + ",error");
}
