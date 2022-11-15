#include "wifi_connection_manager.h"
#include "web_server.h"

WifiConnectionManager wifi;
WebServer server(wifi);

void setup()
{
  Serial.begin(115200);

  if (!wifi.setup()) {
    Serial.println("Error while setup softAP");
  }

  server.setup();
}

void loop()
{
}
