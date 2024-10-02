#include "LedActuatorsControl.h"
#include "ManagerNetwork.h"

const unsigned char ledPinRed = 27;
const unsigned char ledPinYellow1 = 25;
const unsigned char ledPinYellow2 = 26;
const unsigned char ledPinGreen = 33;

char* ssid = "Android4444";
char* password = "jdp269gaj";
char* serverIP = "192.168.220.60";
int serverPort = 5000;

unsigned long previousMillis = 0;
const long interval = 10;

LedActuatorsControl ledsControl(ledPinRed, ledPinYellow1, ledPinYellow2, ledPinGreen);

ManagerNetwork network(ssid, password, serverIP, serverPort);

void setup() {
  Serial.begin(115200);
  network.connectWifi();
  network.connectServer();
}

void loop() {  
  unsigned long currentMillis = millis();
  if (network.verifyWifiConnection()) {
    if(network.verifyServerConnection()){
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        unsigned char actualState = network.recieveState();
        ledsControl.checkState(actualState);
      }
    }
    else{
      Serial.println("Server connection lost. Trying to reconnect...");
      network.connectServer();
    }
  }
  else {
    Serial.println("WiFi connection lost. Trying to reconnect...");
    network.connectWifi();
    network.connectServer();
  }
}