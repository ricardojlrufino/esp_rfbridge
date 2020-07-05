#include "esphome.h"
#include <RCSwitch.h>

#define RC_DEBOUNCE_INTERVAL 500

class RcSwitchSensor: public Component, public Sensor {
public:
	RCSwitch mySwitch = RCSwitch();
	bool pressed = false;
	unsigned long pressedTime;

	void setup() override {
		mySwitch.enableReceive(D2);
	}

	void loop() override {

		// Release button after RC_DEBOUNCE_INTERVAL
		if(pressed && (millis() - pressedTime) > RC_DEBOUNCE_INTERVAL){
			publish_state(0);
			pressed = false;
		}

		if (mySwitch.available() && !pressed) {

			publish_state(mySwitch.getReceivedValue());

			pressed = true;

			pressedTime = millis();

			mySwitch.resetAvailable();
		}
	}
};
