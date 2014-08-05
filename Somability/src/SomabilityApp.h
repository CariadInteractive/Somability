
#pragma once

#include "ofxState.h"
#include "SharedData.h"

class SomabilityApp: public itg::ofxState<SharedData> {
public:
	virtual void setupGui(SomabilityGui *gui) {};
	void stateEnter() {
		ofSetWindowTitle(getName());
		setupGui(getSharedData().gui);
	}
};

