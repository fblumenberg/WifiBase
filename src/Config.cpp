#include <ArduinoJson.h>
#include "FS.h"
//#include "SPIFFS.h"
#include "Config.h"

Config config;

bool loadConfig()
{
  // start with a sane default
  config.mqttClientName = "ESP" + String(ESP.getChipId());

  File configFile = SPIFFS.open("/config.json", "r");
  if (!configFile)
  {
    Serial.println("Failed to open config file");
    return false;
  }

  DynamicJsonDocument jsonDoc(1024);

  auto error = deserializeJson(jsonDoc, configFile);
  if (error)
  {
    Serial.print(F("deserializeJson() failed with code "));
    Serial.println(error.c_str());
    return false;
  }

  config.mqttServer = String((const char *)jsonDoc["mqttServer"]);
  config.mqttClientName = String((const char *)jsonDoc["mqttClientName"]);
  config.mqttPort = jsonDoc["mqttPort"];

  Serial.print("Loaded serverName: ");
  Serial.println(config.mqttServer);
  Serial.print("Loaded clientName: ");
  Serial.println(config.mqttClientName);

  return true;
}

bool saveConfig()
{

  File configFile = SPIFFS.open("/config.json", "w");
  if (!configFile)
  {
    Serial.println("Failed to open config file for writing");
    return false;
  }

  DynamicJsonDocument doc(1024);

  doc["mqttServer"] = config.mqttServer;
  doc["mqttPort"] = config.mqttPort;
  doc["mqttClientName"] = config.mqttClientName;

  // Serialize JSON to file
  if (serializeJson(doc, configFile) == 0)
  {
    Serial.println(F("Failed to write to file"));
    return false;
  }

  return true;
}
