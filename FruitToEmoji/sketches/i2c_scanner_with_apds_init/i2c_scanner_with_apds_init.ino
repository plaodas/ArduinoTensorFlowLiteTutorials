#include <Wire.h>
#include <Arduino_APDS9960.h>

void scanBus(TwoWire &wire, const char *name) {
  Serial.print("Scanning ");
  Serial.println(name);
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

  // APDS を初期化して（必要なら）電源などを有効化
  Serial.println("Calling APDS.begin() to ensure sensor is powered/initialized...");
  if (!APDS.begin()) {
    Serial.println("APDS.begin() failed (sensor not initialized).");
  } else {
    Serial.println("APDS initialized OK.");
  }

  // 少し待ってからスキャン
  delay(200);
  Wire.begin();
  scanBus(Wire, "Wire (default)");
}

void loop() {
  delay(10000);
}