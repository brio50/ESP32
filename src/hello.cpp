#include <Arduino.h>
#include "display.h"
#include "viewport.h"

Display g_Display = Display();

uint32_t g_ScreenWidth;
uint32_t g_ScreenHeight;
uint32_t g_LineHeight;
uint32_t g_MaxCharWidth;

Viewport g_Viewport;

void setup()
{
    // serial
    Serial.begin(115200);

    // display
    g_Display.Init();
    g_ScreenWidth = g_Display.Width();
    g_ScreenHeight = g_Display.Height();
    g_LineHeight = g_Display.FontHeight();
    g_MaxCharWidth = g_Display.FontMaxCharWidth();
    g_Viewport.halfWidth = 0.5f * g_ScreenWidth;
    g_Viewport.halfHeight = 0.5f * g_ScreenHeight;
    g_Viewport.fov = g_ScreenWidth < g_ScreenHeight ? g_ScreenWidth : g_ScreenHeight;
    g_Viewport.eyeDistance = 4.0f;
}

void loop()
{
    char buffer[30];
    int cnt = 0;

    while (cnt != -1) // infinite loop
    {
        // serial
        sprintf(buffer, "%03d: %s %s", cnt++, "Hello", "World");
        Serial.println(buffer);

        // display
        g_Display.Clear();
        g_Display.PrintF(g_ScreenWidth - 10 * g_MaxCharWidth, 0, "cnt = %03d", cnt);
        g_Display.SendBuffer();

        // 1000 ms = 1 second
        delay(1000);
    }
}
