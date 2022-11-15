#ifndef WIFI_CONNECTION_MANAGER_H
#define WIFI_CONNECTION_MANAGER_H

#include <vector>
#include <string>

class WifiConnectionManager
{
  const char *apSSID = "MyESP8266";
  int networksFound = 0;

  public: 
    bool setup();
    bool connected();
    void scanNetworksAsync();
    bool scanIsDone();
    std::vector<std::string> getNetworks();
    void connect(const char * ssid, const char * password);
};

#endif
