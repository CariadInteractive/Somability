
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
	void mouseMoved(ofMouseEventArgs &m);
	void mousePressed(ofMouseEventArgs &m);
	void mouseDragged(ofMouseEventArgs &m);
	void mouseReleased(ofMouseEventArgs &m);


	xmlgui::SimpleGui gui;
	bool enabled;

};