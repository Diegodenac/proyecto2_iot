#include <WiFi.h>

class ManagerNetwork{
    private:
        char* ssidName;
        char* ssidPassword;
        char* serverIP;
        int serverPort;
        WiFiClient client;
    public:
        ManagerNetwork(char* ssid, char* password, char* IP, int port){
            this->ssidName = ssid;
            this->ssidPassword = password;
            this->serverIP = IP;
            this->serverPort = port;
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
                Serial.println("Connected to Server.");
                client.println("actuator-leds\n");
            } 
            else{
                Serial.println("Error trying to connect to Server.");
            }
        }

        bool verifyWifiConnection(){
            return WiFi.status() == WL_CONNECTED;
        }

        bool verifyServerConnection(){
            return client.connected();
        }

        unsigned char recieveState(){
            String state = client.readStringUntil('\n');
            Serial.println("State recieved: " + state);
            unsigned char actualState = state.toInt();
            return actualState;
        }
};
