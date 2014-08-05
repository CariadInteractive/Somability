
#pragma once

#include "ofxState.h"
#include "SharedData.h"

class SomabilityApp: public itg::ofxState<SharedData> {
public:
	virtual void setupGui(SomabilityGui *gui) {};
	virtual void stateEnter() {
		ofSetWindowTitle(getName());
		getSharedData().gui->gui.clear();
		printf("BOGGIE!\n");
		setupGui(getSharedData().gui);
	}
};

