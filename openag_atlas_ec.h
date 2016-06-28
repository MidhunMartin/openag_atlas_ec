/**
 *  \file openag_atlas_ec.h
 *  \brief Electrical conductivity sensor.
 */
#ifndef OPENAG_ATLAS_EC_H
#define OPENAG_ATLAS_EC_H

#include "Arduino.h"
#include <Wire.h>
#include <std_msgs/Float32.h>

/**
 * \brief Electrical conductivity sensor.
 */
class AtlasEc {
  public:
    // Constructor
    AtlasEc(int i2c_address);

    // Public variables
    bool has_error;
    char* error_msg;

    // Public functions
    void begin();
    bool get_water_electrical_conductivity(std_msgs::Float32 &msg);

  private:
    // Private variables
    float _water_electrical_conductivity;
    uint32_t _time_of_last_reading;
    uint32_t _time_of_last_query;
    bool _waiting_for_response;
    const static uint32_t _min_update_interval = 2000;
    int _i2c_address;

    // Private functions
    void send_query();
    bool read_response();
};

 #endif
