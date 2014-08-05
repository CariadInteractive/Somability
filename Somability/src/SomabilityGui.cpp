
#include "SomabilityGui.h"
#include "constants.h"


SomabilityGui::SomabilityGui() {
	enabled = false;
}
void SomabilityGui::enable() {
	setEnabled(true);
}

void SomabilityGui::disable() {
	setEnabled(false);
}
void SomabilityGui::toggle() {
	setEnabled(!enabled);
}


void SomabilityGui::setEnabled(bool enabled) {
	if(enabled==this->enabled) {
		return;
	}
	this->enabled = enabled;
	// need to do anything here?
}


void SomabilityGui::draw() {
	if(!enabled) {
		return;
	}
	ofSetColor(0,0,0,150);
	ofRect(0, 0, WIDTH, HEIGHT);
	gui.draw();
}

bool SomabilityGui::mouseMoved(ofMouseEventArgs &m) {
	if(!enabled) return false;
	gui.touchOver(m.x, m.y, m.button);
	return true;
}


bool SomabilityGui::mousePressed(ofMouseEventArgs &m) {
	if(!enabled) return false;
	gui.touchDown(m.x, m.y, m.button);
	return true;
}

bool SomabilityGui::mouseDragged(ofMouseEventArgs &m) {
	if(!enabled) return false;
	gui.touchMoved(m.x, m.y, m.button);
	return true;
}
bool SomabilityGui::mouseReleased(ofMouseEventArgs &m) {
	if(!enabled) return false;
	gui.touchUp(m.x, m.y, m.button);
	return true;
}


void SomabilityGui::addSlider(string name, float &val, float min, float max) {
	gui.addSlider(name, val, min, max);
}
void SomabilityGui::addMeter(string name, float &val, float min, float max) {
	gui.addMeter(name, val, min, max);
}