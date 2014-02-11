/*
 *  RhythmState.cpp
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
#include "RhythmState.h"
void RhythmState::setup() {
	sound.loadSound("chime-up-short.wav");
}



void RhythmState::update() {
	
	// get number of current users
    int numUsers = getSharedData().openNIDevice.getNumTrackedUsers();
    
    // iterate through users
    for (int i = 0; i < numUsers; i++){
        
        // get a reference to this user
        ofxOpenNIUser & user = getSharedData().openNIDevice.getTrackedUser(i);
        
        // draw the mask texture for this user
		// user.drawMask();
		int id = user.getXnID();
		updateFeet(id, user.getJoint(JOINT_LEFT_FOOT).getProjectivePosition(),
				   user.getJoint(JOINT_RIGHT_FOOT).getProjectivePosition());
		
		
	}
}

void RhythmState::updateFeet(int id, ofVec2f l, ofVec2f r) {
	feet[id].update(l, r);
	int f = feet[id].justStamped();
		
	if(f!=0) {
		if(f==1) trigger(l);
		else trigger(r);
	}
}

void RhythmState::stateEnter() {
	ofSetWindowTitle(getName());
}
void RhythmState::draw()
{
	getSharedData().drawCorrectDisplayMode();
    
	glPushMatrix();
	
	
	glScalef((float)ofGetWidth()/getSharedData().openNIDevice.getWidth(),
			 (float)ofGetHeight()/getSharedData().openNIDevice.getHeight(),
			 1);

	
	
    ofSetColor(255, 0, 0);
	getSharedData().font.drawString(getName(), 5, 30);
	
	
	
	for(int i = 0; i < dings.size(); i++) {
		dings[i].draw();
		if(dings[i].isDead()) {
			dings.erase(dings.begin() + i);
			i--;
		}
	}
	
	glPopMatrix();
}

void RhythmState::trigger(ofVec2f p) {
	sound.play();
	dings.push_back(Ding(p));
}

string RhythmState::getName()
{
	return "rhythm";
}

void RhythmState::mousePressed(int x, int y, int button)
{
//	ofVec2f m(ofGetMouseX(), ofGetMouseY());
//	ofVec2f k(getSharedData().openNIDevice.getWidth(), getSharedData().openNIDevice.getHeight());
//	ofVec2f s(ofGetWidth(), ofGetHeight());
//	
//	m = m*k/s;
//	
//
//	trigger(m);
	changeState("choice");
}

