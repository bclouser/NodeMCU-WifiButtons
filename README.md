
Get the Code
------------
esp_mqtt (https://github.com/tuanpmt/esp_mqtt) is a submodule. 
`git clone --recursive`

Build
-----
In order to build you will need to create user/secrets.h.
It should look like this. 
```c
#ifndef SECRETS
#define SECRETS

#define WIFI_SSID "ssid"
#define WIFI_PASSWD "secret"

#endif
```
