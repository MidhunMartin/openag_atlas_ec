#include "openag_atlas_ec.h"

AtlasEc atlas_ec_1(100);

void setup() {
  Serial.begin(9600);
  atlas_ec_1.begin();
}

std_msgs::Float32 ec_msg;

void loop() {
  if (atlas_ec_1.get_water_electrical_conductivity(ec_msg)) {
    Serial.print("Electrical Conductivity: ");
    Serial.println(ec_msg.data);
  }
  if (atlas_ec_1.has_error) {
    Serial.print("Error: ");
    Serial.println(atlas_ec_1.error_msg);
    atlas_ec_1.has_error = false;
  }
}
