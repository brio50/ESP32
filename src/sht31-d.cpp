#include <Wire.h>
#include <SHT31.h>
#include <U8g2lib.h>

#define SHT31_ADDRESS 0x44
int t, dt, error;
float C, F, H;
uint16_t status;
uint32_t start;
uint32_t stop;
uint32_t fails = 0;
SHT31 sht;

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/OLED_CLOCK, /* data=*/OLED_DATA, /* reset=*/OLED_RESET);

void setup(void)
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
    u8g2.begin();
    u8g2.enableUTF8Print();
}

void loop(void)
{
    char debug[100];
    char temp[50], humid[50], sensor[100];
    char buffer[200];

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
        strcpy(buffer, debug); // copy

        C = sht.getTemperature(); // celsius
        F = sht.getFahrenheit();  // fahrenheit
        H = sht.getHumidity();    // %

        sprintf(temp, "T = %.2f °C (%.2f °F)", C, F);
        sprintf(humid, "H = %.2f %%", H);
        sprintf(sensor, "%s , %s", temp, humid);
        strcat(buffer, sensor); // append
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
    u8g2.clearBuffer();
    u8g2.setContrast(100);
    u8g2.setFont(u8g2_font_helvR08_tf);
    u8g2.drawUTF8(0, 10, temp);
    u8g2.drawUTF8(0, 22, humid);
    u8g2.sendBuffer();

    // 1000 ms = 1 sec
    delay(1000);
}
