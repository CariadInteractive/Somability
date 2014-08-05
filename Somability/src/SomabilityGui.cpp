
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

void SomabilityGui::mouseMoved(ofMouseEventArgs &m) {
	if(!enabled) return;
	gui.touchOver(m.x, m.y, m.button);
}


void SomabilityGui::mousePressed(ofMouseEventArgs &m) {
	if(!enabled) return;
	gui.touchDown(m.x, m.y, m.button);
}
void SomabilityGui::mouseDragged(ofMouseEventArgs &m) {
	if(!enabled) return;
	gui.touchMoved(m.x, m.y, m.button);

}
void SomabilityGui::mouseReleased(ofMouseEventArgs &m) {
	if(!enabled) return;
	gui.touchUp(m.x, m.y, m.button);
}
