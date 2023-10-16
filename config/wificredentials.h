#ifndef __WIFICREDENTIALS_H__
#define __WIFICREDENTIALS_H__

#include <ESP8266WiFi.h>
#include "ZylOsConfig.h"

namespace wificredentials{
	const String 	ssid = 			"LED-Wlan";
	const String	password = 		"44957070";
	const IPAddress mqttServerIp = 	IPAddress(10,42,0,42);
	const String	deviceName = 	Z_DEVICE_NAME;
}


#endif // __WIFICREDENTIALS_H__