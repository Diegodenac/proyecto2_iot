class Led {
  private:
    const unsigned char OFF = 0;
    const unsigned char ON = 1;

    unsigned char pin;
    unsigned char state;

  public:
    Led(unsigned char pin) {
      this->pin = pin;
      pinMode(pin, OUTPUT);
      turnOff();
    }

    void turnOff() {
      state = OFF;
	    digitalWrite(pin, state);
    }

    void turnOn() {
      state = ON;
  	  digitalWrite(pin, state);
    }
};