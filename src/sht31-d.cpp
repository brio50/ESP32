#include <Wire.h>
#include <SHT31.h>
#include <U8x8lib.h>

#define SHT31_ADDRESS 0x44
int t, dt, error;
float C, F, H;
uint16_t status;
uint32_t start;
uint32_t stop;
uint32_t fails = 0;
SHT31 sht;

U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/OLED_CLOCK, /* data=*/OLED_DATA, /* reset=*/OLED_RESET);

void setup()
{
    // sensor
    Wire.begin();
    sht.begin(SHT31_ADDRESS);
    Wire.setClock(100000);
    status = sht.readStatus();

    // serial
    Serial.begin(115200);
    Serial.println(__FILE__);
    Serial.print("SHT31_LIB_VERSION:\t");
    Serial.println(SHT31_LIB_VERSION);
    Serial.print("readStatus:\t\t");
    Serial.println(status, HEX);

    // display
    u8x8.begin();
    u8x8.setFont(u8x8_font_chroma48medium8_r);
}

void loop()
{

    char buffer[200], debug[100], sensor[100];

    t = millis(); // microsecond

    if (sht.isConnected())
    {
        start = millis();
        sht.read(true); // Update Rate: true = fast (default), false = slow
        stop = millis();
        dt = stop - start;
        error = sht.getError();
        status = sht.readStatus();

        sprintf(debug, "[%08i ms] t_read = %i ms , error = %i , status = %02X , ", t, dt, error, status);
        strcat(buffer, debug);

        C = sht.getTemperature(); // celsius
        F = sht.getFahrenheit();  // fahrenheit
        H = sht.getHumidity();    // %

        sprintf(sensor, "T = %.2f °C (%.2f °F) , H = %.2f %%", C, F, H);
        strcat(buffer, sensor);
    }
    else
    {
        fails++;
        sprintf(buffer, "[%08i ms] No Connection , Failures = %i ", t, fails);
        // sht.reset();
    }

    // serial
    Serial.println(buffer);

    // display
    u8x8.drawString(0, 0, sensor);

    // 1000 ms = 1 sec
    delay(1000);
}
