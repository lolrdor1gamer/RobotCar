#include "LED.h"

void LED::OneColorStripe(LEDSide side, byte cr, byte cg, byte cb)
{
    switch (side)
    {
    case LEDSide::LEDLeft:
        for (int i = 0; i < LED_COUNT; i++)
        {
            l_leds[i] = CRGB(cr, cg, cb);
        }
        break;
    case LEDSide::LEDRight:
        for (int i = 0; i < LED_COUNT; i++) {
            r_leds[i] = CRGB(cr, cg, cb);
        }
        break;
    case LEDSide::LEDBoth:
        for (int i = 0; i < LED_COUNT; i++) {
            l_leds[i] = CRGB(cr, cg, cb);
            r_leds[i] = CRGB(cr, cg, cb);
        }
        break;
    default:
        for (int i = 0; i < LED_COUNT; i++) {
            l_leds[i] = CRGB(cr, cg, cb);
            r_leds[i] = CRGB(cr, cg, cb);
        }
        break;
    }
}
void LED::OneColorStripe(LEDSide side, CRGB color)
{
    switch (side)
    {
    case LEDSide::LEDLeft:
        for (int i = 0; i < LED_COUNT; i++)
        {
            l_leds[i] = color;
        }
        break;
    case LEDSide::LEDRight:
        for (int i = 0; i < LED_COUNT; i++) {
            r_leds[i] = color;
        }
        break;
    case LEDSide::LEDBoth:
        for (int i = 0; i < LED_COUNT; i++) {
            l_leds[i] = color;
            r_leds[i] = color;
        }
        break;
    default:
        for (int i = 0; i < LED_COUNT; i++) {
            l_leds[i] = color;
            r_leds[i] = color;
        }
        break;
    }
}
void LED::SetupLEDs()
{
    controllers[0] = &FastLED.addLeds<WS2811, LEFT_LED, GRB>(l_leds, LED_COUNT);
    controllers[1] = &FastLED.addLeds<WS2811, RIGHT_LED, GRB>(r_leds, LED_COUNT);
    //OneColorStripe(LEDSide::LEDBoth, 255, 255, 255);
}

void LED::Blink(Blinking* blinking)
{
    /*if (blinking->LEDCounter == blinking->LEDAmount - 1)
    {
        blinking->LEDCounter = blinking->LEDStart;
    }*/
    if (blinking->LEDCounter == blinking->LEDAmount - 1)
    {
        blinking->IsNeededToBlink = false;
        return;
    }
    //OneColorStripe(blinking->Side, 0, 0, 0);
    l_leds[blinking->LEDCounter] = blinking->Color;
    blinking->LEDCounter++;
}

