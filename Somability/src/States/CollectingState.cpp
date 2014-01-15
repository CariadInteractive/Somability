/*
 *  CollectingState.cpp
 *
 *  based on CollectingState.cpp Copyright (c) 2011, Neil Mendoza, http://www.neilmendoza.com
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
#include "CollectingState.h"

void CollectingState::update()
{
    getSharedData().box2d.update();
    
    // remove shapes offscreen
    ofRemove(boxes, ofxBox2dBaseShape::shouldRemoveOffScreen);
    ofRemove(circles, ofxBox2dBaseShape::shouldRemoveOffScreen);
}

void CollectingState::draw()
{
    getSharedData().drawCorrectDisplayMode();
    
    for(int i=0; i<circles.size(); i++) {
		ofFill();
		ofSetColor(ofColor::red);
		circles[i].get()->draw();
	}
	
	for(int i=0; i<boxes.size(); i++) {
		ofFill();
		ofSetColor(ofColor::blue);
		boxes[i].get()->draw();
	}
    
	ofSetColor(255, 0, 0);
	getSharedData().font.drawString("Collecting", ofGetWidth() >> 1, ofGetHeight() >> 1);
    
    ofDrawBitmapStringHighlight("b to add boxes, c to add circles", 10, 10);
}

string CollectingState::getName()
{
	return "collecting";
}

//--------------------------------------------------------------
void CollectingState::keyPressed(int key) {
	
	if(key == 'c') {
		float r = ofRandom(20, 42);
		circles.push_back(ofPtr<ofxBox2dCircle>(new ofxBox2dCircle));
		circles.back().get()->setPhysics(3.0, 0.53, 0.1);
		circles.back().get()->setup(getSharedData().box2d.getWorld(), ofGetMouseX(), ofGetMouseY(), r);
		
	}
	
	if(key == 'b') {
		float w = ofRandom(20, 42);
		float h = ofRandom(20, 42);
		boxes.push_back(ofPtr<ofxBox2dRect>(new ofxBox2dRect));
		boxes.back().get()->setPhysics(3.0, 0.53, 0.1);
		boxes.back().get()->setup(getSharedData().box2d.getWorld(), ofGetMouseX(), ofGetMouseY(), w, h);
	}
}

void CollectingState::mousePressed(int x, int y, int button)
{
    circles.clear();
    boxes.clear();
	changeState("choice");
}
