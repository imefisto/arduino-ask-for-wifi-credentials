#include <ESP8266WiFi.h>
#include "wifi_connection_manager.h"

bool WifiConnectionManager::setup()
{
  WiFi.mode(WIFI_AP_STA);
  return WiFi.softAP(apSSID);
}

bool WifiConnectionManager::connected()
{
  return WiFi.status() == WL_CONNECTED;
}

void WifiConnectionManager::scanNetworksAsync()
{
  WiFi.scanNetworks(true);
  networksFound = -1;
}

bool WifiConnectionManager::scanIsDone()
{
  networksFound = WiFi.scanComplete();
  return networksFound >= 0;
}

std::vector<std::string> WifiConnectionManager::getNetworks()
{
  std::vector<std::string> networks;

  for (int i = 0; i < networksFound; ++i){
    networks.push_back(WiFi.SSID(i).c_str());
  }

  return networks;
}

void WifiConnectionManager::connect(const char* ssid, const char* password)
{
  WiFi.begin(ssid, password);
}
