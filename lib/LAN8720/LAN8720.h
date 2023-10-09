#pragma once

#ifndef LAN8720_H
#define LAN8720_H

#define DEBUG_ETHERNET_WEBSERVER_PORT       Serial
// Debug Level from 0 to 4
#define _ETHERNET_WEBSERVER_LOGLEVEL_       3

#include "Arduino.h"
// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "WebServer_WT32_ETH01.hpp"     //https://github.com/khoih-prog/WebServer_WT32_ETH01

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
// uncomment the below line
// #include "WebServer_WT32_ETH01.h"           //https://github.com/khoih-prog/WebServer_WT32_ETH01


class LAN8720
{
  private:
    // Select the IP address according to your local network
    IPAddress myIP;
    IPAddress myGW;
    IPAddress mySN;
    // Google DNS Server IP
    IPAddress myDNS;

  public:

    LAN8720() {}

    void init();
    void config(IPAddress local_ip, IPAddress gateway, IPAddress subnet, IPAddress dns1);
    void connect();
};

#endif