#include "html.h"
#include "web_server.h"

void WebServer::setup()
{
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", index_html);
  });

  server.on("/scan", HTTP_POST, [this](AsyncWebServerRequest *request) {
    wifi.scanNetworksAsync();
    request->send(202);
  });

  server.on("/networks", HTTP_GET, [this](AsyncWebServerRequest *request) {
    if (!wifi.scanIsDone()) {
      request->send(202);
      return;
    }
    
    auto doc = buildJsonWithNetworks(wifi.getNetworks());
    request->send(200, "application/json", doc.c_str());
  });
  
  server.on("/connect", HTTP_POST, [this](AsyncWebServerRequest *request) {
    wifi.connect(
      request->getParam("ssid", true)->value().c_str(),
      request->getParam("password", true)->value().c_str()
    );

    request->send(202);
  });

  server.on("/connected", HTTP_GET, [this](AsyncWebServerRequest *request) {
    std::string status;
    if (wifi.connected()) {
      status = "{\"status\": \"connected\"}";
    } else {
      status = "{\"status\": \"not connected\"}";
    }

    request->send(200, "application/json", status.c_str());
  });
  
  server.begin();
}

const std::string WebServer::buildJsonWithNetworks(std::vector<std::string> networks)
{
  std::string json = "[";

  for (auto i : networks) {
    json.append("\"");
    json.append(i);
    json.append("\",");
  }

  if (json.length() > 1) {
    json.erase(json.length() - 1, 1);
  }

  json.append("]");

  return json;
}
