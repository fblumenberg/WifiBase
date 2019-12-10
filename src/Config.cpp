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

  StaticJsonDocument<200> jsonDoc;

  auto error = deserializeJson(jsonDoc, configFile);
  if (error)
  {
    Serial.print(F("deserializeJson() failed with code "));
    Serial.println(error.c_str());
    return false;
  }

  const char *jsonString;

  // config.doConnect = json["doConnect"];

  // jsonString = json["mqttServer"];
  // config.mqttServer = String((const char *)json["mqttServer"]);

  // jsonString = json["mqttClientName"];
  // config.mqttClientName = jsonString; //String(json["mqttClientName"]);

  // jsonString = json["mqttTopic"];
  // config.mqttTopic = jsonString; //String(json["mqttClientName"]);

  // config.mqttPort = json["mqttPort"];

  // Real world application would store these values in some variables for
  // later use.
  Serial.print("Loaded serverName: ");
  Serial.println(config.mqttServer);
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
  StaticJsonDocument<200> doc;

  doc["mqttServer"] = config.mqttServer;
  doc["mqttPort"] = config.mqttPort;
  doc["mqttClientName"] = config.mqttClientName;

  // Serialize JSON to file
  if (serializeJson(doc, configFile) == 0)
  {
    Serial.println(F("Failed to write to file"));
  }

  return true;
}
