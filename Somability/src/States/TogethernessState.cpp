/*
 *  TogethernessState.cpp
 *
 *  based on TogethernessState.cpp Copyright (c) 2011, Neil Mendoza, http://www.neilmendoza.com
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
#include "TogethernessState.h"
void TogethernessState::setup() {
	soundStream.setup(0, 2, 44100, 512, 1);
	soundStream.setInput(this);
	soundStream.stop();
	volumeThreshold = 0.2;
	audioFramesSinceLastFired = 0;
	MIN_FRAMES_BETWEEN_FIRES = 0.3 * 44100; // 0.3 seconds at 44.1kHz
	boing.loadSound("boing.wav");
	mustFire = false;
	MAX_SHAPE_AGE = 20;
}

void TogethernessState::shoot() {
	ofxBox2dCircle *c = new ofxBox2dCircle();
	
	float r = ofRandom(20, 42);
	c->setPhysics(3.0, 0.53, 0.1);
	c->setup(getSharedData().box2d.getWorld(), ofGetMouseX(), ofGetMouseY(), r);
	c->setVelocity(5,0 );
	shapes.push_back(ofPtr<ofxBox2dBaseShape>(c));
	data[c] = ShapeData(ofGetElapsedTimef());

}


bool TogethernessState::shapeIsTooOld(float currTime, ofxBox2dBaseShape *shape) {
	if(data.find(shape)!=data.end()) {
		return (currTime - data[shape].birthday)>MAX_SHAPE_AGE;
	}
	return false;
}

void TogethernessState::update()
{
	if(mustFire) {
		boing.play();
		shoot();
		
		
		mustFire = false;

	}
	
	getSharedData().box2d.update();
    
    // remove shapes offscreen
    //ofRemove(shapes, ofxBox2dBaseShape::shouldRemoveOffScreen);
	float currTime = ofGetElapsedTimef();
	for(int i =0 ; i < shapes.size(); i++) {
		if(ofxBox2dBaseShape::shouldRemoveOffScreen(shapes[i]) || shapeIsTooOld(currTime, shapes[i].get())) {
			data.erase(shapes[i].get());
			shapes.erase(shapes.begin() + i);
			i--;
		}
	}

	
	
	
}

void TogethernessState::draw()
{
//    getSharedData().drawCorrectDisplayMode();
	ofSetColor(255);
	getSharedData().openNIDevice.drawDepth(0, 0, ofGetWidth(), ofGetHeight());
	ofSetColor(255, 0, 0);
	getSharedData().font.drawString("Togetherness", ofGetWidth() >> 1, ofGetHeight() >> 1);
	
	
	ofFill();
	ofSetColor(ofColor::red);
	
    for(int i=0; i<shapes.size(); i++) {
		shapes[i].get()->draw();
	}

	

}

string TogethernessState::getName()
{
	return "togetherness";
}

void TogethernessState::mousePressed(int x, int y, int button)
{
	changeState("choice");
}

void TogethernessState::tryToFire() {
	mustFire = true;
}


void TogethernessState::audioIn(float *samples, int length, int numChannels) {
	for(int i =0 ; i < length; i++) {
		float f = ABS(samples[i]);
		if(volume<f) volume = f;
		else volume *= 0.999;
		if(volume>volumeThreshold) {
			if(audioFramesSinceLastFired>MIN_FRAMES_BETWEEN_FIRES) {
				tryToFire();
				audioFramesSinceLastFired = 0;
			}
		}
		
		audioFramesSinceLastFired++;
	}
}

void TogethernessState::stateEnter() {
	soundStream.start();
}
void TogethernessState::stateExit() {

	soundStream.stop();
}