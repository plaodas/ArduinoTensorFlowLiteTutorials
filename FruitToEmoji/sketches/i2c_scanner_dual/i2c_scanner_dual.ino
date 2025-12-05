#include <Wire.h>

#ifdef Wire1
extern TwoWire Wire1;
#endif

void scanBus(TwoWire &wire, const char *name) {
  Serial.print("Scanning ");
  Serial.println(name);
  wire.begin();
  byte error, address;
  int nDevices = 0;

  for (address = 1; address < 127; ++address) {
    wire.beginTransmission(address);
    error = wire.endTransmission();

    if (error == 0) {
      Serial.print("  I2C device found at 0x");
      if (address < 16) Serial.print("0");
      Serial.print(address, HEX);
      Serial.println();
      nDevices++;
    } else if (error == 4) {
      Serial.print("  Unknown error at 0x");
      if (address < 16) Serial.print("0");
      Serial.print(address, HEX);
      Serial.println();
    }
  }
  if (nDevices == 0) {
    Serial.println("  No I2C devices found");
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  scanBus(Wire, "Wire (default)");
#ifdef Wire1
  scanBus(Wire1, "Wire1 (secondary)");
#else
  Serial.println("Wire1 not available on this core.");
#endif
}

void loop() {
  delay(10000);
}