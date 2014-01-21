/*
 *  RhythmState.h
 *
 *  based on GreenState.h Copyright (c) 2011, Neil Mendoza, http://www.neilmendoza.com
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
#pragma once

#include "ofxState.h"
#include "SharedData.h"
#include "Ding.h"

class Feet {
public:
	ofVec2f lFoot;
	ofVec2f rFoot;
	
	deque<ofVec2f> lHist;
	deque<ofVec2f> rHist;
	
	float lastTimeStamped;
	int MAX_LENGTH;
	Feet() {
		lastTimeStamped = 0;
		MAX_LENGTH = 5;
	}
	
	void update(ofVec2f left, ofVec2f right) {
		lHist.push_front(left);
		rHist.push_front(right);
		if(lHist.size()>MAX_LENGTH) lHist.pop_back();
		if(rHist.size()>MAX_LENGTH) rHist.pop_back();
	}
	
	float footDiff(int i) {
		return (lHist[i].y - rHist[i].y);
	}
	
	float footAbs(int i) {
		return ABS(footDiff(i));
	}
	
	int justStamped() {
		
		float minDiff = 2;
		float maxDiff = 10;
		
		if(ofGetElapsedTimef()-lastTimeStamped<0.2) return 0;
		if(lHist.size()<MAX_LENGTH || rHist.size()<MAX_LENGTH) return 0;
		if(footAbs(0)<minDiff && footAbs(MAX_LENGTH-1)>maxDiff) {
			return footDiff(MAX_LENGTH-1)>0?-1:1;
		}
		return 0;
	}
};

class RhythmState : public itg::ofxState<SharedData>
{
public:
	void setup();
	void update();
	void draw();
	void mousePressed(int x, int y, int button);
	void stateEnter();
	void trigger(ofVec2f p);
	string getName();
	ofSoundPlayer sound;
	vector<Ding> dings;
	
	void updateFeet(int id, ofVec2f l, ofVec2f r);
	map<int,Feet> feet;
};
