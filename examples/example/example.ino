#include "openag_atlas_ec.h"
String parameters[] = {"100"};
AtlasEc atlas_ec_1("atlas_ec_1", parameters);

void setup() {
  Serial.begin(9600);
  atlas_ec_1.begin();
}

void loop() {
  Serial.println(atlas_ec_1.get("electrical_conductivity"));
  delay(1000);
}
