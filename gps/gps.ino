/**
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
static const int TX_PIN = 4;
static const int RX_PIN = 3;

// creates serial and parser objects
TinyGPSPlus gpsParser;
SoftwareSerial gpsSerial(RX_PIN, TX_PIN);

void setup() {

  // starts the serial port to print results
  Serial.begin(115200);
  Serial.print(F("GPS library version: "));
  Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println();

  // starts the serial port to communicate with the GPS module
  gpsSerial.begin(9600);
}

void loop() {

  // waits data to be available before reading it
  while (gpsSerial.available() > 0) {

    // encode method receives information until
    // it's finished, then calls displayInfo()
    if (gpsParser.encode(gpsSerial.read())) {
      displayInfo();
    }
  }
}

void displayInfo() {

  // LOCATION

  Serial.print(F("Location  : "));
  if (gpsParser.location.isValid()) {
    Serial.print(gpsParser.location.lat(), 6);
    Serial.print(F(", "));
    Serial.println(gpsParser.location.lng(), 6);
  }
  else {
    Serial.println(F("INVALID"));
  }

  // DATE / TIME

  Serial.print(F("Date/time : "));
  if (gpsParser.date.isValid()) {
    static char dateStr[] = "00/00/0000 - 00:00:00.000";
    sprintf(dateStr, "%02d/%02d/%04d - %02d:%02d:%02d.%03d",
      gpsParser.date.day(), gpsParser.date.month(), gpsParser.date.year(),
      gpsParser.time.hour(), gpsParser.time.minute(), gpsParser.time.second(),
      gpsParser.time.centisecond());
    Serial.println(dateStr);
  }
  else {
    Serial.println(F("INVALID"));
  }

  Serial.println();
}
