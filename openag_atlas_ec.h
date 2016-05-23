/**
 *  \file openag_atlas_ec.h
 *  \brief Electrical conductivity sensor.
 */
#ifndef OPENAG_ATLAS_EC_H
#define OPENAG_ATLAS_EC_H

#include "Arduino.h"
#include <Wire.h>
#include <openag_peripheral.h>

/**
 * \brief Electrical conductivity sensor.
 */
 class AtlasEc : public Peripheral {
   public:
     // Public variables
     String id;
     float electrical_conductivity;

     // Public functions
     AtlasEc(String id, String* parameters); // constructor
     ~AtlasEc(); // destructor
     void begin(void);
     String get(String key);
     String set(String key, String value);

   private:
     // Private variables
     String _electrical_conductivity_message;
     uint32_t _time_of_last_reading;
     const static uint32_t _min_update_interval = 0;
     String _electrical_conductivity_key;
     int _electrical_conductivity_channel;

     // Private functions
     void getData();
     String getElectricalConductvity();
     String getMessage(String key, String value);
     String getErrorMessage(String key);
 };

 #endif
