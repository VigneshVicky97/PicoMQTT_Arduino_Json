#include "LAN8720.h"


void LAN8720::init()
{
    Serial.print("\nStarting HelloServer on " + String(ARDUINO_BOARD));
    Serial.println(" with " + String(SHIELD_TYPE));
    // Serial.println(WEBSERVER_WT32_ETH01_VERSION);

    // To be called before ETH.begin()
    WT32_ETH01_onEvent();

    ETH.begin(ETH_PHY_ADDR, ETH_PHY_POWER);
}

void LAN8720::config(IPAddress local_ip, IPAddress gateway, IPAddress subnet, IPAddress dns1)
{
    myIP = local_ip;
    myGW = gateway;
    mySN = subnet;
    myDNS = dns1;
    // Static IP, leave without this line to get IP via DHCP
    //bool config(IPAddress local_ip, IPAddress gateway, IPAddress subnet, IPAddress dns1 = 0, IPAddress dns2 = 0);
    ETH.config(myIP, myGW, mySN, myDNS);
}

void LAN8720::connect()
{
    WT32_ETH01_waitForConnect();

    Serial.print(F("HTTP EthernetWebServer is @ IP : "));
    Serial.println(ETH.localIP());
}