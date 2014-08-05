

#pragma once

#include "ofMain.h"

class Icon: public ofRectangle {
public:
	Icon(string appName) {
		this->appName = appName;
		img.loadImage("img/icons/"+appName+".png");
		this->width = img.getWidth();
		this->height = img.getHeight();
		down = false;
		over = false;
	}

	
	void setPosition(int x, int y) {
		setFromCenter(x, y, width, height);
	}
	void draw() {
		if(down) {
			ofSetColor(150);
		} else if(over) {
			ofSetColor(200);
		} else {
			ofSetColor(255);
		}
		img.draw(*this);

		ofSetColor(255);
	}
	void mouseMoved(ofMouseEventArgs &m) {
		over = inside(m.x, m.y);
	
	}

	void mousePressed(ofMouseEventArgs &m) {
		down = inside(m.x, m.y);
	}

	void mouseDragged(ofMouseEventArgs &m) {
		down = inside(m.x, m.y);
		over = inside(m.x, m.y);
	}

	bool mouseReleased(ofMouseEventArgs &m) {
		down = false;
		if(inside(m.x, m.y)) {
			return true;
		}
		return false;
	}


	
	bool down;
	bool over;

	string appName;
	ofImage img;
	
};

