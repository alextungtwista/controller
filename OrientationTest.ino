#include "CurieIMU.h"
#include "CurieTimerOne.h"

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Serial Initialised, 115200 baud.");   // Initialise Serial
  CurieIMU.begin();
  CurieIMU.setAccelerometerRange(2);
  Serial.println("Curie IMU Initialised, 2G range.");   // Initialise IMU

  CurieTimerOne.start(100000, &report);                    // Start timer, samples every 100ms
}

int orient, oldorient;    // Initialise global variables

void report() {
  float x, y, z;
  CurieIMU.readAccelerometerScaled(x,y,z);

  if (0.9<x && x<1.1) orient = 0;
  else if (-1.1<x && x<-0.9) orient = 1;      // Set x ranges for portrait
  else if (0.9<y && y<1.1) orient = 2;
  else if (-1.1<y && y<-0.9) orient = 3;      // Set y ranges for landscape
}

void loop() {
  if (oldorient != orient) {    // Values are printed only if orientation changes
    oldorient = orient;
    switch (orient){
      case 0:
        Serial.println("Orientation changed: Portrait-2 (USB port down)");
        break;
      case 1:
        Serial.println("Orientation changed: Portrait-1 (USB port up)");
        break;
      case 2:
        Serial.println("Orientation changed: Landscape-1 (text right side up)");
        break;
      case 3:
        Serial.println("Orientation changed: Landscape-2 (text upside down)");
        break;
    }
  }
}
