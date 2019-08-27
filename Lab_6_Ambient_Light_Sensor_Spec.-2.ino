#include <WiFi.h>
#include <IoTStarterKit_WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

IoTMakers g_im;

#define deviceID    "Dian17D1566882826606"
#define authnRqtNo  "woj8gmlfi"
#define extrSysID   "OPEN_TCP_001PTL001_1000007616"

#define WIFI_SSID   "ICT-LAB-2.4G"
#define WIFI_PASS   "12345678"

#define ONE_WIRE_BUS 2
#define LIGHT A3
int BUZZER = 6;

#define TAG_ID "Spec2"

OneWire ourWire(ONE_WIRE_BUS);
DallasTemperature sensors(&ourWire);

void init_iotmakers()
{
  while(1)
  {
    Serial.print(F("Connect to AP..."));
    while(g_im.begin(WIFI_SSID, WIFI_PASS) < 0)
    {
      Serial.println(F("retrying"));
      delay(100);
    }

    Serial.println(F("Success"));

    g_im.init(deviceID, authnRqtNo, extrSysID);
  
    Serial.print(F("Connect to platform..."));
    while(g_im.connect() < 0)
    {
      Serial.println(F("retrying."));
      delay(100);
    }
    Serial.println(F("Success"));
  
    Serial.print(F("Auth..."));
    if(g_im.auth_device() >= 0)
    {
      Serial.println(F("Success..."));
      return;
    }
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(LIGHT, INPUT);
  pinMode (BUZZER, OUTPUT);
  sensors.begin();
  init_iotmakers();
}

void loop() {

  static unsigned long tick = millis();

  if(g_im.isServerDisconnected() == 1)
  {
    init_iotmakers();
  }

  if((millis() - tick) > 1000)
  {
    send_ambient();
    tick = millis();
  }

  g_im.loop();
}



int send_ambient()
{
  int value = analogRead(LIGHT);
  int data = map(value,0,1023,0,255);
  if (data < 100){
  tone(BUZZER,400);
  delay (500);
  }
  else{
  noTone(BUZZER);
  delay(500);
    }

  Serial.print("LIGHT : ");
  Serial.println(data);
    
  delay(1000);
  if(g_im.send_numdata(TAG_ID, (double)data) < 0)
  {
    Serial.println(F("fail"));
    return -1;
  }

  return 0;
}
