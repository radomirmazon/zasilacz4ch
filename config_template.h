#ifndef MqttModule_h
#define MqttModule_h

class Config {
  public:

    // WiFi settings
    const char *ssid = "SSID";             // Replace with your WiFi name
    const char *password = "**********8";   // Replace with your WiFi password

    // MQTT Broker settings
    const char *mqtt_broker = "192.168.???.???";

    //%d 1 - state / command
    //%d 2 - deviceName
    //%d 3 - channel
    const char *mqtt_topic_template = "%s/%s/%s";

    const char *mgtt_topic_irda = "irda";
    const char *mgtt_topic_curtain = "curtain";
    const char *mgtt_topic_ch0 = "ch0";
    const char *mgtt_topic_ch1 = "ch1";
    const char *mgtt_topic_ch2 = "ch2";
    const char *mgtt_topic_ch3 = "ch3";
  

    const char *mqtt_username = "mqtt_user";  // MQTT username for authentication
    const char *mqtt_password = "**********";  // MQTT password for authentication
    const int mqtt_port = 1883;  // MQTT port (TCP)

};

#endif