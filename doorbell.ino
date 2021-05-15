#include <WiFi.h>
#include <PubSubClient.h>
#include "config.h"

WiFiClient espClient;
PubSubClient client(espClient);

const int MAX_RETIES = 5;
int attempts = 0;

bool wifiConnect()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("WiFi -- attempting connection");
    while (WiFi.status() != WL_CONNECTED && attempts < MAX_RETIES)
    {
      delay(500);
      Serial.print(".");
      attempts++;
    }
    Serial.print("connected, IP address: ");
    Serial.println(WiFi.localIP());
  }
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("WiFi -- failed to connect");
  }
  return (WiFi.status() == WL_CONNECTED);
}

String clientId()
{
  String clientId = APP_NAME;
  clientId += String(random(0xffff), HEX);
  return clientId;
}

void callback(char *topic, byte *payload, unsigned int length)
{
  digitalWrite(A3, HIGH);
  delay(4000);
  digitalWrite(A3, LOW);
}

bool mqttConnect()
{
  attempts = 0;
  while (!client.connected() && attempts < MAX_RETIES)
  {
    client.setServer(MQTT_SERVER, MQTT_PORT).setCallback(callback);
    Serial.print("MQTT -- attempting connection...");
    if (client.connect(clientId().c_str(), MQTT_USER, MQTT_PASSWORD))
    {
      Serial.println("connected");
      return true;
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.println(client.state());
      attempts++;
      delay(500);
    }
  }
  Serial.println("MQTT -- failed to connect");
  return false;
}

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    delay(10);

  pinMode(A3, OUTPUT);

  Serial.println(APP_NAME);
  Serial.println("------------------------------\n");

  if (wifiConnect() && mqttConnect())
  {
    client.subscribe(DOORBELL_PRESSED);
  }
  else
  {
    ESP.restart();
  }
}

void loop()
{
  client.loop();
}