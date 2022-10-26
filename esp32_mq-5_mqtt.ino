#include "ThingSpeak.h"
#include <WiFi.h>
#include "mysecret.h"

unsigned long myChannelNumber = 1898172;
const char * myWriteAPIKey = "M5BMU8SW099Y9JRO";
const char * myReadAPIKey = "D3O86YSOYT68NNTY";
char ssid[] = myWifiSSID;   // your network SSID (name)ReadAPIKeyReadAPIKeyReadAPIKeyReadAPIKeyReadAPIKey
char pass[] = myWifiPwd;   // your network password
WiFiClient  client;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  analogSetAttenuation(ADC_11db);
  analogSetWidth(10);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println("IP address:");
  Serial.println(WiFi.localIP());
}

void loop() {
  uint16_t adc = analogRead(A0);
  Serial.printf("MQ-5 read value: %u\n", adc);
  ThingSpeak.setField(4, (int)adc);
  int httpCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (httpCode == 200) {
    Serial.println("Channel write successful.");
  }
  else {
    Serial.println("Problem writing to channel. HTTP error code " + String(httpCode));
  }
  vTaskDelay(15000 / portTICK_PERIOD_MS); 
}
