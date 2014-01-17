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

#define MAX_SHAPE_AGE 20



bool CollectingState::shapeIsTooOld(float currTime, ofxBox2dBaseShape *shape) {
	if(data.find(shape)!=data.end()) {
		return (currTime - data[shape].birthday)>MAX_SHAPE_AGE;
	}
	return false;
}

void CollectingState::update()
{
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

void CollectingState::draw()
{
    getSharedData().drawCorrectDisplayMode();
	
	ofFill();
	ofSetColor(ofColor::red);
	
    for(int i=0; i<shapes.size(); i++) {
		ShapeID t = data[shapes[i].get()].type;
		if(t==CIRCLE) {
			ofSetColor(255, 0, 0);
		} else if(t==HEXAGON) {
			ofSetColor(0, 255, 0);
		} else if(t==TRIANGLE) {
			ofSetColor(0, 255,255);
		} else if(t==SQUARE) {
			ofSetColor(0, 0, 255);
		}

		shapes[i].get()->draw();
	}
	
}

string CollectingState::getName()
{
	return "collecting";
}

//--------------------------------------------------------------
void CollectingState::keyPressed(int k) {

	
	if(k=='j') {
		addShape(CIRCLE, ofVec2f(ofGetMouseX(), ofGetMouseY()));
	} else if(k=='k') {
		addShape(HEXAGON, ofVec2f(ofGetMouseX(), ofGetMouseY()));
	} else if(k=='l') {
		addShape(TRIANGLE, ofVec2f(ofGetMouseX(), ofGetMouseY()));
	} else if(k==';') {
		addShape(SQUARE, ofVec2f(ofGetMouseX(), ofGetMouseY()));
	//} else if(k=='\'') {
	//	addShape(CROSS, ofVec2f(ofGetMouseX(), ofGetMouseY()));
	}
	
	
}

void CollectingState::mousePressed(int x, int y, int button)
{
    shapes.clear();
	data.clear();
	changeState("choice");
}

void CollectingState::addShape(ShapeID type, ofVec2f pos) {
	ofxBox2dBaseShape *shape = NULL;
	if(type==CIRCLE) {
		
		ofxBox2dCircle *c = new ofxBox2dCircle();
		
		float r = ofRandom(20, 42);
		c->setPhysics(3.0, 0.53, 0.1);
		c->setup(getSharedData().box2d.getWorld(), pos.x, pos.y, r);
		shape = c;
		
	} else if(type==SQUARE) {
		float w = ofRandom(20, 42);
		float h = w;
		ofxBox2dRect *r = new ofxBox2dRect();
		r->setPhysics(3.0, 0.53, 0.1);
		r->setup(getSharedData().box2d.getWorld(), ofGetMouseX(), ofGetMouseY(), w, h);
		shape = r;
	} else if(type==TRIANGLE) {
		float w = ofRandom(20, 42);
		float h = w*1.73;
		ofxBox2dPolygon *p = new ofxBox2dPolygon();
		p->setPhysics(3.0, 0.53, 0.1);

		p->addTriangle(ofVec2f(-w, h/2),ofVec2f(w, h/2), ofVec2f(0, -h/2));
		p->create(getSharedData().box2d.getWorld());
		p->setPosition(pos.x, pos.y);
		shape = p;
	} else if(type==HEXAGON) {
		ofVec2f a, b;
		float h = ofRandom(20, 42);
		a = b = ofVec2f(h, 0);
		a.rotate(-30);
		b.rotate(30);
		
		ofxBox2dPolygon *p = new ofxBox2dPolygon();
		p->setPhysics(3.0, 0.53, 0.1);
		for(int i = 0; i < 6; i++) {
			p->addTriangle(ofVec2f(0,0),a, b);
			a.rotate(60);
			b.rotate(60);
		}
		
		p->create(getSharedData().box2d.getWorld());
		p->setPosition(pos.x, pos.y);
		shape = p;
	/*}  else if(type==CROSS) {

		float h = ofRandom(20, 42);
		float w = ofRandom(4, 15);
		
		
		ofxBox2dPolygon *p = new ofxBox2dPolygon();
		p->setPhysics(3.0, 0.53, 0.1);
		
		p->addTriangle(ofVec2f(-w/2,-h/2),ofVec2f(w/2,-h/2), ofVec2f(w/2,h/2));
		p->addTriangle(ofVec2f(w/2,h/2), ofVec2f(-w/2,h/2),ofVec2f(w/2,-h/2));
		
		p->addTriangle(ofVec2f(-h/2,-w/2),ofVec2f(w/2,-w/2), ofVec2f(w/2,w/2));
		p->addTriangle(ofVec2f(h/2,w/2), ofVec2f(-h/2,w/2),ofVec2f(h/2,-w/2));
		
		p->create(getSharedData().box2d.getWorld());
		p->setPosition(pos.x, pos.y);
		shape = p;*/
	}

	
	if(shape!=NULL) {
		shapes.push_back(ofPtr<ofxBox2dBaseShape>(shape));
		data[shape] = ShapeData(type, ofGetElapsedTimef());
	}

}
