/*
https://lastminuteengineers.com/creating-esp8266-web-server-arduino-ide/
*/
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "page.h"
#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <FastLED.h>

#define LED_PIN     2 //D4 on NodeMCU
#define NUM_LEDS    300
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 100

CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

int BRIGHTNESS = 100;

/* network info */
const char *ssid = "YourSSID";
const char *password = "YourPassword"; //at least 8 chars long

/* setup ip */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

/* init webserver */
ESP8266WebServer server(80);

/* lightMode var */
int lightMode = 0;
int tempCase = lightMode;

const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
   CRGB::Red,
   CRGB::Gray, // 'white' is too bright compared to red and blue
   CRGB::Blue,
   CRGB::Black,

   CRGB::Red,
   CRGB::Gray,
   CRGB::Blue,
   CRGB::Black,

   CRGB::Red,
   CRGB::Red,
   CRGB::Gray,
   CRGB::Gray,
   CRGB::Blue,
   CRGB::Blue,
   CRGB::Black,
   CRGB::Black
};

const TProgmemPalette16 myGreenPurpleWhitePallete_p PROGMEM =
{
   CRGB::Green,
   CRGB::Green,
   CRGB::Gray,
   CRGB::Gray,
   CRGB::Purple,
   CRGB::Purple,
   CRGB::Gray,
   CRGB::Gray,
   CRGB::Green,
   CRGB::Green,
   CRGB::Gray,
   CRGB::Gray,
   CRGB::Purple,
   CRGB::Purple,
   CRGB::Gray,
   CRGB::Gray
};

const TProgmemPalette16 myRedPinkPurple_p PROGMEM =
{
   CRGB::Red,
   CRGB::Red,
   CRGB::Indigo,
   CRGB::Indigo,
   CRGB::Purple,
   CRGB::Purple,
   CRGB::Red,
   CRGB::Red,
   CRGB::Indigo,
   CRGB::Indigo,
   CRGB::Purple,
   CRGB::Purple,
   CRGB::Red,
   CRGB::Red,
   CRGB::Indigo,
   CRGB::Indigo
};


void setup()
{
   /* init serial */
   Serial.begin(115200);

   /* configure wifi with defined settings */
   WiFi.softAP(ssid, password);
   WiFi.softAPConfig(local_ip, gateway, subnet);

   FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
   FastLED.setBrightness(BRIGHTNESS);

   delay(100);

   /* create the directories on webserver */
   server.on("/lightModeDim", handle_lightModeDim);
   server.on("/lightModeBright", handle_lightModeBright);
   server.on("/", handle_lightModeOff);
   server.on("/lightMode0", handle_lightMode0);
   server.on("/lightMode1", handle_lightMode1);
   server.on("/lightMode2", handle_lightMode2);
   server.on("/lightMode3", handle_lightMode3);
   server.on("/lightMode4", handle_lightMode4);
   server.on("/lightMode5", handle_lightMode5);
   server.on("/lightMode6", handle_lightMode6);
   server.on("/lightMode7", handle_lightMode7);
   server.on("/lightMode8", handle_lightMode8);
   server.on("/lightMode9", handle_lightMode9);
   server.on("/lightMode10", handle_lightMode10);
   server.on("/lightMode11", handle_lightMode11);
   server.on("/lightMode12", handle_lightMode12);
   server.on("/lightMode13", handle_lightMode13);
   server.on("/lightMode14", handle_lightMode14);
   server.on("/lightMode15", handle_lightMode15);
   server.on("/lightMode16", handle_lightMode16);
   server.on("/lightMode17", handle_lightMode17);
   server.on("/lightMode18", handle_lightMode18);
   server.on("/lightMode19", handle_lightMode19);
   server.on("/lightMode20", handle_lightMode20);
   server.on("/lightMode21", handle_lightMode21);
   server.on("/lightMode22", handle_lightMode22);
   server.on("/lightMode23", handle_lightMode23);
   server.on("/lightMode24", handle_lightMode24);
   server.on("/lightMode25", handle_lightMode25);
   server.on("/lightMode26", handle_lightMode26);
   server.on("/lightMode27", handle_lightMode27);
   server.on("/lightMode28", handle_lightMode28);
   server.on("/lightMode29", handle_lightMode29);
   server.on("/lightMode30", handle_lightMode30);
   server.on("/lightMode31", handle_lightMode31);
   server.on("/lightMode32", handle_lightMode32);
   server.on("/lightMode33", handle_lightMode33);
   server.on("/lightMode34", handle_lightMode34);
   server.on("/lightMode35", handle_lightMode35);
   server.onNotFound(handle_NotFound);

   /* start the server */
   server.begin();
   Serial.println("http server started");
}


void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
   uint8_t brightness = 255;

   for( int i = 0; i < NUM_LEDS; i++)
   {
      leds[i] = ColorFromPalette(currentPalette, colorIndex, brightness,
            currentBlending);
      colorIndex += 3;
   }
}


void loop()
{
   /* handle any incoming http request */
   server.handleClient();

   Serial.print("Mode = ");
   Serial.println(lightMode);

   switch (lightMode)
   {
      case -3: // Dim - lower brightness 10%
         if(BRIGHTNESS > 10)
            BRIGHTNESS -= 10;
         FastLED.setBrightness(BRIGHTNESS);
         FastLED.show();
         delay(150);
         break;
      case -2: // Bright - raise brightness 10%
         if(BRIGHTNESS < 100)
            BRIGHTNESS += 10;
         FastLED.setBrightness(BRIGHTNESS);
         FastLED.show();
         delay(150);
         break;
      case -1: // Off
         tempCase = lightMode;
         for(int dot = 0; dot < NUM_LEDS; dot++)
            leds[dot] = CRGB::Black;
         FastLED.show();
         while(true)
         {
            server.handleClient();
            if(tempCase != lightMode)
               break;
         }
         break;
      case 0: // Rainbow colors
         tempCase = lightMode;
         currentPalette = RainbowColors_p;
         currentBlending = LINEARBLEND;
         while(true)
         {
            static uint8_t startIndex = 0;
            startIndex = startIndex + 1; /* motion speed */
            FillLEDsFromPaletteColors(startIndex);
            FastLED.show();
            FastLED.delay(1000 / UPDATES_PER_SECOND);
            server.handleClient();
            if(tempCase != lightMode)
               break;
         }
         break;
      case 1: // Lava colors
         tempCase = lightMode;
         currentPalette = LavaColors_p;
         currentBlending = LINEARBLEND;
         while(true)
         {
            static uint8_t startIndex = 0;
            startIndex = startIndex + 1; /* motion speed */
            FillLEDsFromPaletteColors(startIndex);
            FastLED.show();
            Serial.println("here");
            FastLED.delay(1000 / UPDATES_PER_SECOND);
            server.handleClient();
            if(tempCase != lightMode)
               break;
         }
         break;
      case 2: // Party wave (rainbow no green)
         tempCase = lightMode;
         currentPalette = PartyColors_p;
         currentBlending = LINEARBLEND;
         while(true)
         {
            static uint8_t startIndex = 0;
            startIndex = startIndex + 1; /* motion speed */
            FillLEDsFromPaletteColors(startIndex);
            FastLED.show();
            FastLED.delay(1000 / UPDATES_PER_SECOND);
            server.handleClient();
            if(tempCase != lightMode)
               break;
         }
         break;
      case 3: // Forest wave (green and white with yellow accent)
         tempCase = lightMode;
         currentPalette = ForestColors_p;
         currentBlending = LINEARBLEND;
         while(true)
         {
            static uint8_t startIndex = 0;
            startIndex = startIndex + 1; /* motion speed */
            FillLEDsFromPaletteColors(startIndex);
            FastLED.show();
            FastLED.delay(1000 / UPDATES_PER_SECOND);
            server.handleClient();
            if(tempCase != lightMode)
               break;
         }
         break;
      case 4: // Steady white light
         tempCase = lightMode;
         for(int dot = 0; dot < NUM_LEDS; dot++)
            leds[dot].setRGB(255,255,255);
         FastLED.show();
         while(true)
         {
            server.handleClient();
            if(tempCase != lightMode)
               break;
         }
         break;
      case 5: // Steady dim orange light
         tempCase = lightMode;
         for(int dot = 0; dot < NUM_LEDS; dot++)
            leds[dot].setRGB(30, 8, 0);
         FastLED.show();
         while(true)
         {
            server.handleClient();
            if(tempCase != lightMode)
               break;
         }
         break;
      case 6: // Steady periwinkle light
         tempCase = lightMode;
         for(int dot = 0; dot < NUM_LEDS; dot++)
            leds[dot].setRGB(113, 102, 255);
         FastLED.show();
         while(true)
         {
            server.handleClient();
            if(tempCase != lightMode)
               break;
         }
         break;
      case 7: // Red green blue flash
         tempCase = lightMode;
         delay(350);
         while(true)
         {
            for(int dot = 0; dot < NUM_LEDS; dot++)
               leds[dot].setRGB(255, 0, 0);
            FastLED.show();
            delay(50);
            for(int dot = 0; dot < NUM_LEDS; dot++)
               leds[dot].setRGB(0, 255, 0);
            FastLED.show();
            delay(50);
            for(int dot = 0; dot < NUM_LEDS; dot++)
               leds[dot].setRGB(0, 0, 255);
            FastLED.show();
            delay(50);
            server.handleClient();
            if(tempCase != lightMode)
               break;
         }
         break;
      case 8: // Normal strobe
         tempCase = lightMode;
         while(true)
         {
            for(int dot = 0; dot < NUM_LEDS; dot++)
               leds[dot].setRGB(255, 255, 255);
            FastLED.show();
            delay(5);
            for(int dot = 0; dot < NUM_LEDS; dot++)
               leds[dot].setRGB(0, 0, 0);
            FastLED.show();
            delay(90);
            server.handleClient();
            if(tempCase != lightMode)
               break;
         }
         break;
      case 9: // Blue strobe
         tempCase = lightMode;
         while(true)
         {
            for(int dot = 0; dot < NUM_LEDS; dot++)
               leds[dot].setRGB(0, 0, 255);
            FastLED.show();
            delay(5);
            for(int dot = 0; dot < NUM_LEDS; dot++)
               leds[dot].setRGB(0, 0, 0);
            FastLED.show();
            delay(90);
            server.handleClient();
            if(tempCase != lightMode)
               break;
         }
         break;
      case 10: // Red green blue strobe
         tempCase = lightMode;
         while(true)
         {
            for(int dot = 0; dot < NUM_LEDS; dot++)
               leds[dot].setRGB(0, 0, 255);
            FastLED.show();
            delay(5);
            for(int dot = 0; dot < NUM_LEDS; dot++)
               leds[dot].setRGB(0, 0, 0);
            FastLED.show();
            delay(90);
            for(int dot = 0; dot < NUM_LEDS; dot++)
               leds[dot].setRGB(0, 255, 0);
            FastLED.show();
            delay(5);
            for(int dot = 0; dot < NUM_LEDS; dot++)
               leds[dot].setRGB(0, 0, 0);
            FastLED.show();
            delay(90);
            for(int dot = 0; dot < NUM_LEDS; dot++){
               leds[dot].setRGB(255, 0, 0);}
            FastLED.show();
            delay(5);
            for(int dot = 0; dot < NUM_LEDS; dot++)
               leds[dot].setRGB(0, 0, 0);
            FastLED.show();
            delay(90);
            server.handleClient();
            if(tempCase != lightMode)
               break;
         }
         break;
      case 11: // Blue and teal wave with white accent
         tempCase = lightMode;
         currentPalette = OceanColors_p;
         currentBlending = LINEARBLEND;
         while(true)
         {
            static uint8_t startIndex = 0;
            startIndex = startIndex + 1; /* motion speed */
            FillLEDsFromPaletteColors(startIndex);
            FastLED.show();
            FastLED.delay(1000 / UPDATES_PER_SECOND);
            server.handleClient();
            if(tempCase != lightMode)
               break;
         }
         break;
      case 12: // Blue and white wave
         tempCase = lightMode;
         currentPalette = RainbowStripeColors_p;
         currentBlending = LINEARBLEND;
         while(true)
         {
            static uint8_t startIndex = 0;
            startIndex = startIndex + 1; /* motion speed */
            FillLEDsFromPaletteColors(startIndex);
            FastLED.show();
            FastLED.delay(1000 / UPDATES_PER_SECOND);
            server.handleClient();
            if(tempCase != lightMode)
               break;
         }
         break;
      case 13: // ROYGBV back fill
         tempCase = lightMode;
         while (1)
         {
            int del = 10;
            for (int i = 5; i < NUM_LEDS; i += 6)
            {
               if (i >= 300)
                  i = 299;
               leds[i - 0] = CRGB::Red;
               FastLED.show();
               delay(del);
               leds[i - 1] = CRGB::Orange;
               FastLED.show();
               delay(del);
               leds[i - 2] = CRGB::Yellow;
               FastLED.show();
               delay(del);
               leds[i - 3] = CRGB::Green;
               FastLED.show();
               delay(del);
               leds[i - 4] = CRGB::Blue;
               FastLED.show();
               delay(del);
               leds[i - 5] = CRGB::Violet;
               FastLED.show();
               server.handleClient();
               if(tempCase != lightMode)
                  break;
            }
            for (int i = (NUM_LEDS - 6); i > 0; i -= 6)
            {
               if (i <= 0)
                  i = 0;
               leds[i + 0] = CRGB::Red;
               FastLED.show();
               delay(del);
               leds[i + 1] = CRGB::Orange;
               FastLED.show();
               delay(del);
               leds[i + 2] = CRGB::Yellow;
               FastLED.show();
               delay(del);
               leds[i + 3] = CRGB::Green;
               FastLED.show();
               delay(del);
               leds[i + 4] = CRGB::Blue;
               FastLED.show();
               delay(del);
               leds[i + 5] = CRGB::Violet;
               FastLED.show();
               server.handleClient();
               if(tempCase != lightMode)
                  break;
            }
            server.handleClient();
            if(tempCase != lightMode)
               break;
         }
         break;
      case 14: // red white and blue
         tempCase = lightMode;
         currentPalette = myRedWhiteBluePalette_p;
         currentBlending = LINEARBLEND;
         while(true)
         {
            static uint8_t startIndex = 0;
            startIndex = startIndex + 1; /* motion speed */
            FillLEDsFromPaletteColors(startIndex);
            FastLED.show();
            FastLED.delay(1000 / UPDATES_PER_SECOND);
            server.handleClient();
            if(tempCase != lightMode)
               break;
         }
         break;
      case 15: // green purple and white
         tempCase = lightMode;
         currentPalette = myGreenPurpleWhitePallete_p;
         currentBlending = LINEARBLEND;
         while(true)
         {
            static uint8_t startIndex = 0;
            startIndex = startIndex + 1; /* motion speed */
            FillLEDsFromPaletteColors(startIndex);
            FastLED.show();
            FastLED.delay(1000 / UPDATES_PER_SECOND);
            server.handleClient();
            if(tempCase != lightMode)
               break;
         }
         break;
      case 16: // Red pink purple
         tempCase = lightMode;
         currentPalette = myRedPinkPurple_p;
         currentBlending = NOBLEND;
         while(true)
         {
            static uint8_t startIndex = 0;
            startIndex = startIndex + 1; /* motion speed */
            FillLEDsFromPaletteColors(startIndex);
            FastLED.show();
            FastLED.delay(1);
            server.handleClient();
            if(tempCase != lightMode)
               break;
         }
         break;
      default:
         break;
   }
}


void handle_lightModeDim()
{
   lightMode = -3;
   Serial.println("lightMode dim");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(-3));
}


void handle_lightModeBright()
{
   lightMode = -2;
   Serial.println("lightMode bright");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(-2));
}


void handle_lightModeOff()
{
   lightMode = -1;
   Serial.println("lightMode off");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(-1));
}


void handle_lightMode0()
{
   lightMode = 0;
   Serial.println("lightMode 0");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(0));
}


void handle_lightMode1()
{
   lightMode = 1;
   Serial.println("lightMode 1");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(1));
}


void handle_lightMode2()
{
   lightMode = 2;
   Serial.println("lightMode 2");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(2));
}


void handle_lightMode3()
{
   lightMode = 3;
   Serial.println("lightMode 3");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(3));
}


void handle_lightMode4()
{
   lightMode = 4;
   Serial.println("lightMode 4");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(4));
}


void handle_lightMode5()
{
   lightMode = 5;
   Serial.println("lightMode 5");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(5));
}


void handle_lightMode6()
{
   lightMode = 6;
   Serial.println("lightMode 6");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(6));
}


void handle_lightMode7()
{
   lightMode = 7;
   Serial.println("lightMode 7");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(7));
}


void handle_lightMode8()
{
   lightMode = 8;
   Serial.println("lightMode 8");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(8));
}


void handle_lightMode9()
{
   lightMode = 9;
   Serial.println("lightMode 9");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(9));
}


void handle_lightMode10()
{
   lightMode = 10;
   Serial.println("lightMode 10");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(10));
}


void handle_lightMode11()
{
   lightMode = 11;
   Serial.println("lightMode 11");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(11));
}


void handle_lightMode12()
{
   lightMode = 12;
   Serial.println("lightMode 12");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(12));
}


void handle_lightMode13()
{
   lightMode = 13;
   Serial.println("lightMode 13");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(13));
}


void handle_lightMode14()
{
   lightMode = 14;
   Serial.println("lightMode 14");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(14));
}


void handle_lightMode15()
{
   lightMode = 15;
   Serial.println("lightMode 15");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(15));
}


void handle_lightMode16()
{
   lightMode = 16;
   Serial.println("lightMode 16");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(16));
}


void handle_lightMode17()
{
   lightMode = 17;
   Serial.println("lightMode 17");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(17));
}


void handle_lightMode18()
{
   lightMode = 18;
   Serial.println("lightMode 18");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(18));
}


void handle_lightMode19()
{
   lightMode = 19;
   Serial.println("lightMode 19");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(19));
}


void handle_lightMode20()
{
   lightMode = 20;
   Serial.println("lightMode 20");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(20));
}


void handle_lightMode21()
{
   lightMode = 21;
   Serial.println("lightMode 21");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(21));
}


void handle_lightMode22()
{
   lightMode = 22;
   Serial.println("lightMode 22");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(22));
}


void handle_lightMode23()
{
   lightMode = 23;
   Serial.println("lightMode 23");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(23));
}


void handle_lightMode24()
{
   lightMode = 24;
   Serial.println("lightMode 24");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(24));
}


void handle_lightMode25()
{
   lightMode = 25;
   Serial.println("lightMode 25");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(25));
}


void handle_lightMode26()
{
   lightMode = 26;
   Serial.println("lightMode 26");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(26));
}


void handle_lightMode27()
{
   lightMode = 27;
   Serial.println("lightMode 27");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(27));
}


void handle_lightMode28()
{
   lightMode = 28;
   Serial.println("lightMode 28");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(28));
}


void handle_lightMode29()
{
   lightMode = 29;
   Serial.println("lightMode 29");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(29));
}


void handle_lightMode30()
{
   lightMode = 30;
   Serial.println("lightMode 30");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(30));
}


void handle_lightMode31()
{
   lightMode = 31;
   Serial.println("lightMode 31");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(31));
}


void handle_lightMode32()
{
   lightMode = 32;
   Serial.println("lightMode 32");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(32));
}


void handle_lightMode33()
{
   lightMode = 33;
   Serial.println("lightMode 33");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(33));
}


void handle_lightMode34()
{
   lightMode = 34;
   Serial.println("lightMode 34");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(34));
}


void handle_lightMode35()
{
   lightMode = 35;
   Serial.println("lightMode 35");

   /* code 200 = OK, content type = text/html, call SendHTML */
   /* updates the web server */
   server.send(200, "text/html", SendHTML(35));
}


void handle_NotFound()
{
   /* error 404, plain text, not found */
   server.send(404, "text/plain", "Not found");
}


String SendHTML(int pageStatus)
{
   String p = page;

   switch (pageStatus)
   {
      case -3: // Dim
         p += "<p>Dim</p><a class=\"button button-on\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case -2: // Bright
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-on\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case -1: // Off
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-on\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 0: // lightMode 0
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-on\" href=\"/lightMode0\">On</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 1: // lightMode 1
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-on\" href=\"/lightMode1\">On</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 2: // lightMode 2
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-on\" href=\"/lightMode2\">On</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 3: // lightMode 3
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-on\" href=\"/lightMode3\">On</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 4: // lightMode 4
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-on\" href=\"/lightMode4\">On</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 5: // lightMode 5
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-on\" href=\"/lightMode5\">On</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 6: // lightMode 6
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-on\" href=\"/lightMode6\">On</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 7: // lightMode 7
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-on\" href=\"/lightMode7\">On</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 8: // lightMode 8
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-on\" href=\"/lightMode8\">On</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 9: // lightMode 9
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-on\" href=\"/lightMode9\">On</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 10: // lightMode 10
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-on\" href=\"/lightMode10\">On</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 11: // lightMode 11
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-on\" href=\"/lightMode11\">On</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 12: // lightMode 12
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-on\" href=\"/lightMode12\">On</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 13: // lightMode 13
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-on\" href=\"/lightMode13\">On</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 14: // lightMode 14
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-on\" href=\"/lightMode14\">On</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 15: // lightMode 15
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-on\" href=\"/lightMode15\">On</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 16: // lightMode 16
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-on\" href=\"/lightMode16\">On</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 17: // lightMode 17
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-on\" href=\"/lightMode17\">On</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 18: // lightMode 18
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-on\" href=\"/lightMode18\">On</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 19: // lightMode 19
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-on\" href=\"/lightMode19\">On</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 20: // lightMode 20
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-on\" href=\"/lightMode20\">On</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 21: // lightMode 21
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-on\" href=\"/lightMode21\">On</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 22: // lightMode 22
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-on\" href=\"/lightMode22\">On</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 23: // lightMode 23
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-on\" href=\"/lightMode23\">On</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 24: // lightMode 24
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-on\" href=\"/lightMode24\">On</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 25: // lightMode 25
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-on\" href=\"/lightMode25\">On</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 26: // lightMode 26
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-on\" href=\"/lightMode26\">On</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 27: // lightMode 27
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-on\" href=\"/lightMode27\">On</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 28: // lightMode 28
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-on\" href=\"/lightMode28\">On</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 29: // lightMode 29
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-on\" href=\"/lightMode29\">On</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 30: // lightMode 30
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-on\" href=\"/lightMode30\">On</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 31: // lightMode 31
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-on\" href=\"/lightMode31\">On</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 32: // lightMode 32
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-on\" href=\"/lightMode32\">On</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 33: // lightMode 33
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-on\" href=\"/lightMode33\">On</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 34: // lightMode 34
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-on\" href=\"/lightMode34\">On</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-off\" href=\"/lightMode35\">Off</a>\n";
         break;
      case 35: // lightMode 35
         p += "<p>Dim</p><a class=\"button button-off\" href=\"/lightModeDim\">DIM</a>\n";
         p += "<p>Bright</p><a class=\"button button-off\" href=\"/lightModeBright\">Bright</a>\n";
         p += "<p>Off</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
         p += "<p>Rainbow Wave</p><a class=\"button button-off\" href=\"/lightMode0\">Off</a>\n";
         p += "<p>Lava Wave</p><a class=\"button button-off\" href=\"/lightMode1\">Off</a>\n";
         p += "<p>Party Wave</p><a class=\"button button-off\" href=\"/lightMode2\">Off</a>\n";
         p += "<p>Forest Wave</p><a class=\"button button-off\" href=\"/lightMode3\">Off</a>\n";
         p += "<p>Steady White</p><a class=\"button button-off\" href=\"/lightMode4\">Off</a>\n";
         p += "<p>Steady Dim Orange</p><a class=\"button button-off\" href=\"/lightMode5\">Off</a>\n";
         p += "<p>Steady Periwinkle</p><a class=\"button button-off\" href=\"/lightMode6\">Off</a>\n";
         p += "<p>RGB Flash</p><a class=\"button button-off\" href=\"/lightMode7\">Off</a>\n";
         p += "<p>Normal Strobe</p><a class=\"button button-off\" href=\"/lightMode8\">Off</a>\n";
         p += "<p>Blue Strobe</p><a class=\"button button-off\" href=\"/lightMode9\">Off</a>\n";
         p += "<p>RGB Strobe</p><a class=\"button button-off\" href=\"/lightMode10\">Off</a>\n";
         p += "<p>Cloud Wave</p><a class=\"button button-off\" href=\"/lightMode11\">Off</a>\n";
         p += "<p>Ocean Wave</p><a class=\"button button-off\" href=\"/lightMode12\">Off</a>\n";
         p += "<p>ROYGBV Back Fill</p><a class=\"button button-off\" href=\"/lightMode13\">Off</a>\n";
         p += "<p>AMERICA Wave</p><a class=\"button button-off\" href=\"/lightMode14\">Off</a>\n";
         p += "<p>Ethan Wave</p><a class=\"button button-off\" href=\"/lightMode15\">Off</a>\n";
         p += "<p>Michael Wave</p><a class=\"button button-off\" href=\"/lightMode16\">Off</a>\n";
         p += "<p>Mode 17</p><a class=\"button button-off\" href=\"/lightMode17\">Off</a>\n";
         p += "<p>Mode 18</p><a class=\"button button-off\" href=\"/lightMode18\">Off</a>\n";
         p += "<p>Mode 19</p><a class=\"button button-off\" href=\"/lightMode19\">Off</a>\n";
         p += "<p>Mode 20</p><a class=\"button button-off\" href=\"/lightMode20\">Off</a>\n";
         p += "<p>Mode 21</p><a class=\"button button-off\" href=\"/lightMode21\">Off</a>\n";
         p += "<p>Mode 22</p><a class=\"button button-off\" href=\"/lightMode22\">Off</a>\n";
         p += "<p>Mode 23</p><a class=\"button button-off\" href=\"/lightMode23\">Off</a>\n";
         p += "<p>Mode 24</p><a class=\"button button-off\" href=\"/lightMode24\">Off</a>\n";
         p += "<p>Mode 25</p><a class=\"button button-off\" href=\"/lightMode25\">Off</a>\n";
         p += "<p>Mode 26</p><a class=\"button button-off\" href=\"/lightMode26\">Off</a>\n";
         p += "<p>Mode 27</p><a class=\"button button-off\" href=\"/lightMode27\">Off</a>\n";
         p += "<p>Mode 28</p><a class=\"button button-off\" href=\"/lightMode28\">Off</a>\n";
         p += "<p>Mode 29</p><a class=\"button button-off\" href=\"/lightMode29\">Off</a>\n";
         p += "<p>Mode 30</p><a class=\"button button-off\" href=\"/lightMode30\">Off</a>\n";
         p += "<p>Mode 31</p><a class=\"button button-off\" href=\"/lightMode31\">Off</a>\n";
         p += "<p>Mode 32</p><a class=\"button button-off\" href=\"/lightMode32\">Off</a>\n";
         p += "<p>Mode 33</p><a class=\"button button-off\" href=\"/lightMode33\">Off</a>\n";
         p += "<p>Mode 34</p><a class=\"button button-off\" href=\"/lightMode34\">Off</a>\n";
         p += "<p>Mode 35</p><a class=\"button button-on\" href=\"/lightMode35\">On</a>\n";
         break;
      default:
         break;
   }

   p +="</body>\n";
   p +="</html>\n";
   return p;
}
