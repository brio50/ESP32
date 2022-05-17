#include <Wire.h>
#include <SHT31.h>

#define SHT31_ADDRESS 0x44
int t, dt, error;
float C, F, H;
uint16_t status;
uint32_t start;
uint32_t stop;
uint32_t fails = 0;
SHT31 sht;

// inspired by https://github.com/RobTillaart/SHT31/blob/master/examples/SHT31_isConnected/SHT31_isConnected.ino

void setup()
{
    Serial.begin(115200);
    Serial.println(__FILE__);
    Serial.print("SHT31_LIB_VERSION:\t");
    Serial.println(SHT31_LIB_VERSION);

    Wire.begin();
    sht.begin(SHT31_ADDRESS);
    Wire.setClock(100000);

    status = sht.readStatus();
    Serial.print("readStatus:\t\t");
    Serial.println(status, HEX);
}

void loop()
{

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

        sprintf(buffer, "[%08i ms] t_read = %i ms , error = %i , status = %02X , ", t, dt, error, status);

        C = sht.getTemperature(); // celsius
        F = sht.getFahrenheit();  // fahrenheit
        H = sht.getHumidity();    // %

        sprintf(buffer + strlen(buffer), "T = %.2f °C (%.2f °F) , H = %.2f %%", C, F, H);
        Serial.println(buffer);
    }
    else
    {
        fails++;
        sprintf(buffer, "[%08i ms] No Connection , Failures = %i ", t, fails);
        Serial.println(buffer);
        // sht.reset();
    }

    // 1000 ms = 1 sec
    delay(1000);
}
