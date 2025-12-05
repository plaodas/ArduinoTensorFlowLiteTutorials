# FruitToEmoji

Classifies fruit using the RGB color and proximity sensors of the Arduino Nano 33 BLE Sense, using a TensorFlow Lite Micro model trained on data captured from the same hardware

## 備考
  - Arduino_APDS9960ライブラリを追加
  ```
  $ arduino-cli lib install Arduino_APDS9960
  ```

  - [I2Cスキャナ](sketches/i2c_scanner_with_apds_init/i2c_scanner_with_apds_init.ino)でデバイスが見えない理由の可能性
    - ボードのセンサーが電源制御やI2Cスイッチ経由で接続されており、汎用スキャナ（電源を入れない／初期化しない状態）では応答しない。
    - センサーが専用のSERCOM/TwoWireインスタンスや内部バスに接続されていて、単純な Wire スキャナでは見えない（ただし今回のコアでは Wire1 が無いのでこの可能性は低い）。
    - センサーが I2C の ACK を返さない特殊な動作モードになっている（ライブラリが特定の初期化手順を踏むと通信可能になる）。