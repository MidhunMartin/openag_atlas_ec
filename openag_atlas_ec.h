/** 
 *  \file openag_atlas_ec.h
 *  \brief Electrical conductivity sensor.
 */
#ifndef OPENAG_ATLAS_EC_H
#define OPENAG_ATLAS_EC_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>

/**
 * \brief Electrical conductivity sensor.
 */
class AtlasEc {
  public:
  // Public Functions
  AtlasEc(String electrical_conductivity_id, int electrical_conductivity_channel);
  void begin(void);
  String get(String id);
  String set(String id, String value);

  // Public Variables
  float electrical_conductivity;
    
  private:
  // Private Functions
  float getElectricalConductivity(void);
    
  // Private Variables
  String _electrical_conductivity_id;
  int _electrical_conductivity_channel;
};

#endif