/*
 *  ChoiceState.cpp
 *
 *  based on GreenState.cpp Copyright (c) 2011, Neil Mendoza, http://www.neilmendoza.com
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of 16b.it nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include "ChoiceState.h"
#include "constants.h"

void ChoiceState::setupGui(SomabilityGui *gui) {
}

ChoiceState::ChoiceState() {
	logo.loadImage("img/logo.png");
	logo.setAnchorPercent(0.5, 0.5); 
	float h = HEIGHT * 0.65;
	icons.push_back(new Icon("reach", WIDTH/2 - 300, h));
	icons.push_back(new Icon("flow", WIDTH/2, h));
	icons.push_back(new Icon("balance", WIDTH/2 + 300, h));
}

void ChoiceState::update()
{
}

void ChoiceState::stateEnter() {
	SomabilityApp::stateEnter();
	ofSetWindowTitle(getName());
	for(int i = 0; i < icons.size(); i++) {
		icons[i]->down = false;
		icons[i]->over = false;
	}
}
void ChoiceState::draw()
{
   ofSetColor(255);
    logo.draw(WIDTH/2, HEIGHT/4);

	for(int i = 0; i < icons.size(); i++) {
		icons[i]->draw();
	}
}

string ChoiceState::getName()
{
	return "choice";
}



void ChoiceState::mouseMoved(int x, int y, int button)
{
	ofMouseEventArgs m;
	m.x = x;
	m.y = y;
	m.button = button;

	for(int i = 0; i < icons.size(); i++) {
		icons[i]->mouseMoved(m);
	}
}

void ChoiceState::mousePressed(int x, int y, int button)
{
	ofMouseEventArgs m;
	m.x = x;
	m.y = y;
	m.button = button;

	for(int i = 0; i < icons.size(); i++) {
		icons[i]->mousePressed(m);
	}
}

void ChoiceState::mouseDragged(int x, int y, int button)
{
	ofMouseEventArgs m;
	m.x = x;
	m.y = y;
	m.button = button;

	for(int i = 0; i < icons.size(); i++) {
		icons[i]->mouseDragged(m);
	}
}

void ChoiceState::mouseReleased(int x, int y, int button)
{
	ofMouseEventArgs m;
	m.x = x;
	m.y = y;
	m.button = button;
	string launchApp = "";
	for(int i = 0; i < icons.size(); i++) {
		if(icons[i]->mouseReleased(m)) {
			launchApp = icons[i]->appName;
		}
	}
	if(launchApp!="") {
		changeState(launchApp);
	}
}


