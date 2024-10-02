#include <WiFi.h>

class ManagerNetwork{
    private:
        char* ssidName;
        char* ssidPassword;
        char* serverIP;
        int serverPort;
        WiFiClient client;
        String ranges;
        String identification;
    public:
        ManagerNetwork(char* ssid, char* password, char* IP, int port){
            this->ssidName = ssid;
            this->ssidPassword = password;
            this->serverIP = IP;
            this->serverPort = port;
            this->ranges = "";
            this->identification = "";
        }

        void connectWifi(){
            WiFi.begin(ssidName, ssidPassword);
            while (!verifyWifiConnection()) {
                delay(1000);
                Serial.print(".");
            }
            Serial.print("Connected to WiFi\n");
        }

        void connectServer(){
            if (client.connect(serverIP, serverPort)) {
            Serial.println("Connected to the server");
            client.println("sensor-distance\n");

            identification = client.readStringUntil('\n'); 
            Serial.println("Recieved message: " + identification);
            
            ranges = client.readStringUntil('\n');
            Serial.println("Ranges received: " + ranges);
            } else {
              Serial.println("Error trying to connect to the server");
            }
        }

        String getRanges(){
          return ranges;
        }

        bool verifyWifiConnection(){
            return WiFi.status() == WL_CONNECTED;
        }

        bool verifyServerConnection(){
            return client.connected();
        }

        void sendState(String state){
          client.println(state);
        }
};
