
#pragma once

#include "xmlgui/container/SimpleGui.h"
/**
 * This class handles events for the gui instead of running it through oF's event system 
 * in order for us to be able to route the mouse coords through the centerer.
 */
class SomabilityGui {
public:
	SomabilityGui();
	void enable();
	void disable();
	void setEnabled(bool enabled);
	void toggle();

	void draw();
	bool mouseMoved(ofMouseEventArgs &m);
	bool mousePressed(ofMouseEventArgs &m);
	bool mouseDragged(ofMouseEventArgs &m);
	bool mouseReleased(ofMouseEventArgs &m);


	void addSlider(string name, float &val, float min, float max);
	void addMeter(string name, float &val, float min, float max);

	xmlgui::SimpleGui gui;
	bool enabled;
	ofImage banner;
};