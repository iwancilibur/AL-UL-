#define BLYNK_PRINT Serial

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
char auth[] = "0f0dd9d944244d16b55ac1d9398b2f20";

char ssid[] = "www.interactiverobotics.club";
char pass[] = "cilibur2019";
#define EspSerial Serial1

#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);

BlynkTimer timer;

void myTimerEvent()
{
   Blynk.virtualWrite(V5, millis() / 1000);
}

void setup()
{
  Serial.begin(115200);
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
  Blynk.begin(auth, wifi, ssid, pass, "iwancilibur.my.id", 8080);
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run(); 
}
