#include <ManagerNetwork.h>
#include <SensorDistance.h>

char* ssid = "Android4444";
char* password = "jdp269gaj";
char* serverIP = "192.168.220.60";
int serverPort = 5000;
int initialState = 0; 

SensorDistance sensorDistance(12,14, initialState);
ManagerNetwork network(ssid, password, serverIP, serverPort);

void setup() {
  Serial.begin(115200);
  network.connectWifi();
  network.connectServer();
}

void loop() {
  if (network.verifyWifiConnection()) {
    if(network.verifyServerConnection()){
      sensorDistance.checkDistance(network.getRanges().c_str());
      int state = sensorDistance.getState();

      if (initialState != state){
        network.sendState(String(state));
        Serial.println("State sent to the server: " + String(state));
        initialState = state;
      }
    }
    else{
      Serial.println("Server connection lost. Trying to reconnect...");
      network.connectServer();
    }
  } else {
    Serial.println("WiFi Connection lost. Trying to reconnect...");
    network.connectWifi();
    network.connectServer();
  }

  delay(200);
}