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

void ChoiceState::update()
{
}

void ChoiceState::stateEnter() {
	ofSetWindowTitle(getName());
}
void ChoiceState::draw()
{
    ofPushStyle(); //be polite
    
    float halfWindowWidth = WIDTH/2.f;
    float halfWindowHeight = HEIGHT/2.f;
    
    ofRectangle topLeft = ofRectangle(0,0,halfWindowWidth, halfWindowHeight);
    ofRectangle topRight = ofRectangle(halfWindowWidth,0,halfWindowWidth, halfWindowHeight);
    ofRectangle bottomLeft = ofRectangle(0,halfWindowHeight,halfWindowWidth, halfWindowHeight);
    ofRectangle bottomRight = ofRectangle(halfWindowWidth,halfWindowHeight,halfWindowWidth, halfWindowHeight);
    
    ofFill();
    ofSetColor(ofColor::red);
    ofRect(topLeft);
    ofSetColor(ofColor::green);
    ofRect(topRight);
    ofSetColor(ofColor::blue);
    ofRect(bottomLeft);
    ofSetColor(ofColor::yellow);
    ofRect(bottomRight);
    
    ofSetColor(ofColor::black);
    getSharedData().font.drawString("Rhythm", topLeft.getCenter().x, topLeft.getCenter().y);
    getSharedData().font.drawString("Stillness", topRight.getCenter().x, topRight.getCenter().y);
    getSharedData().font.drawString("Togetherness", bottomLeft.getCenter().x, bottomLeft.getCenter().y);
    getSharedData().font.drawString("Collecting", bottomRight.getCenter().x, bottomRight.getCenter().y);
	getSharedData().font.drawString("Click a Choice, click any time to return to this screen", 10.f, HEIGHT/2.f);
    ofPopStyle();
}

string ChoiceState::getName()
{
	return "choice";
}



void ChoiceState::mousePressed(int x, int y, int button)
{
	
	if(y < (HEIGHT/2.f)){
        if(x < (WIDTH/2.f)){
            changeState("rhythm");
        }else{
            changeState("stillness");
        }
    }else{
        if(x < (WIDTH/2.f)){
            changeState("togetherness");
        }else{
            changeState("collecting");
        }
    }
    
    
}
