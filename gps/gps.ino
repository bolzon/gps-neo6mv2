/**
 * Dextra Digital - IoT Guild
 * Program to get GPS coords from module NEO-6M.
 * 14/nov/2018
 */

#include <SoftwareSerial.h>

// this lib parses the NMEA string returned by the GPS module
// https://github.com/mikalhart/TinyGPSPlus/releases
#include <TinyGPS++.h>

// documentation of the GPS module can be found in the link below
// https://www.u-blox.com/sites/default/files/products/documents/NEO-6_DataSheet_(GPS.G6-HW-09005).pdf

// pins configuration
static const int tx_pin = 4; // must be RX on module
static const int rx_pin = 3; // must be TX on module

TinyGPSPlus gps;
SoftwareSerial serialGPS(rx_pin, tx_pin);

void setup() {

  // starts the serial port to print results
  Serial.begin(115200);
  Serial.print(F("GPS library version: "));
  Serial.println(TinyGPSPlus::libraryVersion());

  // starts the serial port to communicate with the GPS module
  serialGPS.begin(9600);
}

void loop() {
  while (serialGPS.available() > 0) {
    // encode method receives information until
    // it's finished, then calls displayInfo()
    if (gps.encode(serialGPS.read())) {
      displayInfo();
    }
  }
}

void displayInfo() {

  // LOCATION

  Serial.print(F("Location  : "));
  if (gps.location.isValid()) {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(", "));
    Serial.println(gps.location.lng(), 6);
  }
  else {
    Serial.println(F("INVALID"));
  }

  // DATE / TIME

  Serial.print(F("Date/time : "));
  if (gps.date.isValid()) {
    static char dateStr[] = "00/00/0000 - 00:00:00.000";
    sprintf(dateStr, "%02d/%02d/%04d - %02d:%02d:%02d.%03d",
      gps.date.day(), gps.date.month(), gps.date.year(),
      gps.time.hour(), gps.time.minute(), gps.time.second(),
      gps.time.centisecond());
    Serial.println(dateStr);
  }
  else {
    Serial.println(F("INVALID"));
  }

  Serial.println();
}
