#include <sstream>
#include <vector>

class SensorDistance {
private:
  unsigned char triggerPin;
  unsigned char echoPin;
  unsigned char state;
public:
  SensorDistance(unsigned char triggerPin, unsigned char echoPin, unsigned char state) {
    this->triggerPin = triggerPin;
    this->echoPin = echoPin;
    this->state = state;
  }

  float calculateDistance() {
    pinMode(triggerPin, OUTPUT);
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    pinMode(echoPin, INPUT);
    return 0.01723 * pulseIn(echoPin, HIGH);
  }

  void checkDistance(std::string ranges) {
    std::vector<float> values;
    std::string temp;
    std::stringstream ss(ranges);
    
    while (getline(ss, temp, '.')) {
      values.push_back(std::stof(temp));
    }

    if (values.size() == 4) {
      printDistance();
      float distance = calculateDistance();
      if(distance <= values[3] && distance >= 5.0){
        state = (distance < values[2]) ? 3: 4;
        state = (distance < values[1]) ? 2: state;
        state = (distance < values[0]) ? 1: state;
      }
      else
        state = 5;
    } else{
      Serial.println("Error extracting ranges");
    }
  }

  unsigned char getState(){
    return state;
  }

  void printDistance() {
    	Serial.print(calculateDistance());
  		Serial.println("cm");
  }
};