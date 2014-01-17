/*
 *  StillnessState.cpp
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
#include "StillnessState.h"

void StillnessState::update()
{
	int numUsers = getSharedData().openNIDevice.getNumTrackedUsers();
	for(int i =0 ; i < numUsers; i++) {
		ofxOpenNIUser &user = getSharedData().openNIDevice.getTrackedUser(i);
		int numJoints = user.getNumJoints();
		int id = user.getXnID();
		for(int j = 0; j < JOINT_COUNT; j++) {
			int myId = id * 100 + j;
			trails[myId].update(user.getJoint((Joint)j).getProjectivePosition());
		}
	}
	//trails[0].update(ofVec2f(ofGetMouseX(), ofGetMouseY()));
}

void StillnessState::draw()
{
	ofSetColor(255);
	//getSharedData().openNIDevice.drawDepth(0, 0, ofGetWidth(), ofGetHeight());
	ofSetColor(0);
	glPushMatrix();
	
	
	glScalef((float)ofGetWidth()/getSharedData().openNIDevice.getWidth(),
			 (float)ofGetHeight()/getSharedData().openNIDevice.getHeight(),
			 1);
	
			 
	getSharedData().openNIDevice.drawSkeletons();
//	getSharedData().drawCorrectDisplayMode();
	glLineWidth(25);
    ofSetColor(255, 0, 0);
	getSharedData().font.drawString("Stillness", ofGetWidth() >> 1, ofGetHeight() >> 1);
	map<int,Trail>::iterator it = trails.begin();
	while(it!=trails.end()) {
		(*it).second.draw();
		it++;
	}
	glPopMatrix();
	glLineWidth(1);
}

void StillnessState::userEvent(ofxOpenNIUserEvent & event) {
	if(event.userStatus==USER_SKELETON_LOST || event.userStatus==USER_TRACKING_STOPPED) {
		// delete user trails

	}
}


string StillnessState::getName()
{
	return "stillness";
}

void StillnessState::mousePressed(int x, int y, int button)
{
	changeState("choice");
}


void StillnessState::mouseMoved(int x, int y, int button) {
	
}

void StillnessState::stateEnter() {
	ofRemoveListener(getSharedData().openNIDevice.userEvent, this, &StillnessState::userEvent);
}
void StillnessState::stateExit() {
	ofAddListener(getSharedData().openNIDevice.userEvent, this, &StillnessState::userEvent);
}