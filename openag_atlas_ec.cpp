/**
 *  \file openag_atlas_ec.cpp
 *  \brief Electrical conductivity sensor.
 */
#include "openag_atlas_ec.h"

AtlasEc::AtlasEc(int i2c_address) {
  status_level = OK;
  status_msg = "";
  _send_water_electrical_conductivity = false;
  _time_of_last_reading = 0;
  _time_of_last_query = 0;
  _waiting_for_response = false;
  _i2c_address = i2c_address;
}

void AtlasEc::begin() {
  Wire.begin();
}

void AtlasEc::update() {
  if (_waiting_for_response) {
    if (millis() - _time_of_last_query > 1000) {
      _waiting_for_response = false;
      _time_of_last_reading = millis();
      read_response();
    }
  }
  else if (millis() - _time_of_last_reading > _min_update_interval) {
    send_query();
  }
}

bool AtlasEc::get_water_electrical_conductivity(std_msgs::Float32 &msg) {
  msg.data = _water_electrical_conductivity;
  bool res = _send_water_electrical_conductivity;
  _send_water_electrical_conductivity = false;
  return res;
}

void AtlasEc::send_query() {
  Wire.beginTransmission(_i2c_address); // read message response state
  Wire.print("r");
  Wire.endTransmission();
  _waiting_for_response = true;
  _time_of_last_query = millis();
}

void AtlasEc::read_response() {
  Wire.requestFrom(_i2c_address, 20, 1);
  byte response = Wire.read();
  String string = Wire.readStringUntil(0);
  status_level = OK;
  status_msg = "";

  // Check for failure
  if (response == 255) {
    status_level = ERROR;
    status_msg = "No data returned";
  }
  else if (response == 254) {
    status_level = ERROR;
    status_msg = "Tried to read data before request was processed";
  }
  else if (response == 2) {
    status_level = ERROR;
    status_msg = "Request failed";
  }
  else if (response == 1) { // good reading
    _water_electrical_conductivity = string.toFloat() / 1000;
    _send_water_electrical_conductivity = true;
  }
  else {
    status_level = ERROR;
    status_msg = "Unknown error";
  }
}
