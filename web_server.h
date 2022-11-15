#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <vector>
#include <string>
#include <ESPAsyncWebServer.h>
#include "Arduino.h"
#include <ArduinoJson.h>
#include "wifi_connection_manager.h"

class WebServer
{
  WifiConnectionManager wifi;
  AsyncWebServer server{80};
  const std::string buildJsonWithNetworks(std::vector<std::string> networks);

  public: 
    WebServer(WifiConnectionManager _wifi):
      wifi{_wifi}
    {}

    void setup();
};

#endif
