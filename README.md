# Heltec ESP32 Platform IO Development Environment

- Forked from https://github.com/m1k0s/ESP32-HelloWorld3D
- Assumes https://platformio.org/platformio-ide & VSCode installed
  - [Heltec ESP32 Dev-Boards](https://registry.platformio.org/libraries/heltecautomation/Heltec%20ESP32%20Dev-Boards) library not needed

## Using

1. Modify `platformio.ini`'s `src_filter` to execute the `*.cpp` of your choosing in the `/src` directory.
   - `./src/main.cpp` is the example provided by [m1k0s](https://github.com/m1k0s) @ [ESP32-HelloWorld3D](https://github.com/m1k0s/ESP32-HelloWorld3D)
   - `./src/hello.cpp` is a step backward, just a simple serial and display hello world to get my bearings.
   - `./src/sht31.cpp` is a step forward, temperature and humidity sensor with serial output.
   - `./src/sht31-d.cpp` adds u8g2 display output to `sht31.cpp`
2. Build
3. Upload

![](https://user-images.githubusercontent.com/12156/170900373-3bed94a0-c299-4927-aed1-b9afa4e5ccaf.mp4)

## Hardware References

### Heltec Kit 32 (ESP32)

- https://heltec.org/project/wifi-kit-32/
- https://resource.heltec.cn/download/WiFi_Kit_32/WIFI_Kit_32_pinoutDiagram_V2.pdf
  - `SDA=21`, `SCL=22`
  - ![WIFI_Kit_32_pinoutDiagram_V2](https://user-images.githubusercontent.com/12156/171037611-bd17732e-420a-4890-98af-4e5cab34068c.png)

> **NOTE**: With platform.io + vscode, the following installation instructions were _not_ necessary:
>
> - https://heltec.org/wifi_kit_install/
> - https://github.com/HelTecAutomation/Heltec_ESP32
> - https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series

#### Onboard Display

- https://robotzero.one/heltec-wifi-kit-32/
- [u8g2 library](https://github.com/olikraus/u8g2)
  - [c++ introduction](https://github.com/olikraus/u8g2/wiki/u8g2setupcpp#introduction)
  - [full buffer vs page buffer](https://github.com/olikraus/u8g2/wiki/setup_tutorial#u8g2-full-buffer--page-buffer-and-u8x8-mode)

### Sensor

- [SHT31-D](https://www.amazon.com/gp/product/B07ZSZW92J/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1) Temperature and Humidity Sensor
  - Output: I2C, voltage output
  - Power supply voltage: 2.4 to 5.5V
  - Relative Humidity (RH) range: 0-99.99%RH
  - Operating Temperature range: -40° to 125°C (-40° to 257°F)
  - RH response time: 8 seconds (tau63%)
- **Library**: https://github.com/RobTillaart/SHT31
- [**Needed additional pull-up resistors**, used a pair of 1k-ohm on SDA and SCL](https://github.com/espressif/arduino-esp32/issues/1395#issuecomment-387771512)
  - [Software Alternative to pull-up resistor?](https://www.upesy.com/blogs/tutorials/how-to-use-gpio-pins-of-esp32-with-arduino)
- https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series/issues/62#issuecomment-449690785
  - I had to switch I2C sensor inputs to pins `SDA=4` and `SCL=15` when using the Arduino IDE, however in Platform IO IDE pins `SDA=21`, `SCL=22` work!

### Misc

- [.webp github gist](https://gist.github.com/witmin/1edf926c2886d5c8d9b264d70baf7379)
  - Could not get this to actually reduce the `.mp4` file size. Just dragged and dropped into `README.md` via github website, seems to store file in github object/cloud storage rather than in project (preferred)!

```
ffmpeg -i IMG_2409.mp4 -vcodec libwebp -filter:v fps=fps=source_fps -lossless 0 -compression_level 7 -q:v 70 -loop 0 -an -vsync passthrough output.webp
```
