#define BLYNK_TEMPLATE_ID "Template ID"
#define BLYNK_DEVICE_NAME "Device name"
#define BLYNK_AUTH_TOKEN "Auth Token"

#include <SoftwareSerial.h>
SoftwareSerial mySerial(D6, D7);

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "********"; // Change your Wifi/ Hotspot Name
char pass[] = "********"; // Change your Wifi/ Hotspot Password

int x = 0;
bool text = false;
String textIn = "";
String text_speed = "";
BLYNK_WRITE(V0)
{
  textIn = param.asStr();
  if (textIn) // working for text Input Widget
  {
    text = true;
    x = 0;
    mySerial.print(String("!") + textIn + String("\r\n"));
    Serial.print(String("!") + textIn + String("\r\n"));
    text = false;
    mySerial.flush();
  }
}

BLYNK_WRITE(V1)
{
  text_speed = param.asStr();
/* Control the speed of the scrolling texts
 *  0xF0 = Static Mode, No scrolling
 *  0xF1 to 0xFF = You can send any hex values frmo 0xF1 to 0xFF, where 0xF1 is the fastest and 0xFF is the
 *  lowest scrolling speed. Default power up speed is medium at 0xFA 
 */
  if (text_speed == "0") // working for text Input Widget
  {
    mySerial.write(0xF0); 
    Serial.print(text_speed);
  }
  if (text_speed == "50") // working for text Input Widget
  {
    mySerial.write(0xFF); 
    Serial.print(text_speed);
  } 
  if (text_speed == "100") // working for text Input Widget
  {
    mySerial.write(0xF1); 
    Serial.println(text_speed);
  } 
  delay(100);
  mySerial.flush();
}

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  delay(1000);
}

void loop()
{
  Blynk.run();
}