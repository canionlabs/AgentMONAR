
#include <Arduino.h>
#include <Homie.h>

#define LED_PIN 2

int wifi_attempt = 30;

HomieNode switchNode("switch", "switch");

void onHomieEvent(const HomieEvent &event)
{
    switch (event.type)
    {
    case HomieEventType::STANDALONE_MODE:
        Serial << "Standalone mode started" << endl;
        break;
    case HomieEventType::CONFIGURATION_MODE:
        Serial << "Configuration mode started" << endl;
        break;
    case HomieEventType::NORMAL_MODE:
        Serial << "Normal mode started" << endl;
        break;
    case HomieEventType::OTA_STARTED:
        Serial << "OTA started" << endl;
        break;
    case HomieEventType::OTA_PROGRESS:
        Serial << "OTA progress, " << event.sizeDone << "/" << event.sizeTotal << endl;
        break;
    case HomieEventType::OTA_FAILED:
        Serial << "OTA failed" << endl;
        break;
    case HomieEventType::OTA_SUCCESSFUL:
        Serial << "OTA successful" << endl;
        break;
    case HomieEventType::ABOUT_TO_RESET:
        Serial << "About to reset" << endl;
        break;
    case HomieEventType::WIFI_CONNECTED:
        Serial << "Wi-Fi connected, IP: " << event.ip << ", gateway: " << event.gateway << ", mask: " << event.mask << endl;
        break;
    case HomieEventType::WIFI_DISCONNECTED:
        Serial << "Wi-Fi disconnected, reason: " << (int8_t)event.wifiReason << endl;
        break;
    case HomieEventType::MQTT_READY:
        Serial << "MQTT connected" << endl;
        break;
    case HomieEventType::MQTT_DISCONNECTED:
        Serial << "MQTT disconnected, reason: " << (int8_t)event.mqttReason << endl;
        break;
    case HomieEventType::MQTT_PACKET_ACKNOWLEDGED:
        Serial << "MQTT packet acknowledged, packetId: " << event.packetId << endl;
        break;
    case HomieEventType::READY_TO_SLEEP:
        Serial << "Ready to sleep" << endl;
        break;
    }
}

void configure()
{

}

void service()
{

}

void setup()
{
    Serial.begin(115200);
    Serial << endl
           << endl;

    Homie_setBrand("CanionLabs_MONAR");
    Homie_setFirmware("monar", "1.0.0");

    Homie.setSetupFunction(configure).setLoopFunction(service);

    // Homie.disableLogging();
    Homie.setLedPin(LED_PIN, LOW);
    Homie.onEvent(onHomieEvent);
    Homie.setup();
}

void loop()
{
    Homie.loop();
}