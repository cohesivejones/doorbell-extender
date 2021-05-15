# Doorbell Extender

This project is hosted on a [Adafruit Feather ESP32](https://www.adafruit.com/product/3405) board. The executing code behaves like a doorbell extender. By subscribing to doorbell events on the mqtt server, this circuit activates a buzzer to notify users when the doorbell has been pressed.  

You will need to add a config.h header file to get things going:

```C
/* config.h */

#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

#define MQTT_SERVER "YOUR_MQQT_HOST"     /* Ex. "driver.cloudmqtt.com" */
#define MQTT_PORT YOUR_MQQT_PORT         /* Ex. 18846 */
#define MQTT_USER "YOUR_MQQT_USERNAME"
#define MQTT_PASSWORD "YOUR_MQQT_PASSWORD"

#define APP_NAME "DOORBELL-EXTENDER"

/* List of MQTT topics accepted by server */
#define DOORBELL_INACTIVE "doorbell/inactive"
#define DOORBELL_ACTIVE "doorbell/active"
#define DOORBELL_OPEN_DOOR "doorbell/open-door"
#define DOORBELL_PRESSED "doorbell/pressed"
#define DOORBELL_BATTERY "doorbell/battery"
#define EMPTY_MESSAGE "test
```
