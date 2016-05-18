#include "openag_atlas_ec.h"

AtlasEc atlas_ec("electrical_conductivity", 100);

void setup() {
  Serial.begin(9600);
  atlas_ec.begin();
}

void loop() {
  Serial.println(atlas_ec.get("electrical_conductivity"));
  delay(1000);
}

