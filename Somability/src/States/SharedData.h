/*
 *  SharedData.h
 *
 *  Copyright (c) 2011, Neil Mendoza, http://www.neilmendoza.com
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

#ifdef _WIN32
#include "Microsoft_ofxOpenNI.h"
#else
#include "ofxOpenNI.h"
#endif
#include "ofxBox2d.h"
#include "constants.h"

//enums http://www.cplusplus.com/doc/tutorial/other_data_types/
enum InteractionDisplayMode { MIRROR, MIRROR_SKELETON, SILHOUETTE, INVISIBLE};

class SharedData
{
public:
	int counter;
	int lastUpdate;
	ofxOpenNI openNIDevice;
    ofTrueTypeFont font;
    ofxBox2d *box2d; //	the box2d world
    InteractionDisplayMode theDisplayMode;
    
	//ofFbo fbo;
	//ofShader shader;
public:
	SharedData() {
		box2d = new ofxBox2d();
	}
    void drawCorrectDisplayMode(){
		
        switch (theDisplayMode){
            case MIRROR:
                drawMirrorDisplayMode();
                break;
            case SILHOUETTE:
                drawSilhouetteDisplayMode();
                break;
				
			case MIRROR_SKELETON:
                drawMirrorSkeletonDisplayMode();
                break;
            case INVISIBLE:
                drawInvisibleDisplayMode();
                break;
            default:
                break;
        }
    }
    
	
	void drawMirrorSkeletonDisplayMode() {
		
		ofSetColor(ofColor::white);
        openNIDevice.drawImage(0, 0, WIDTH,HEIGHT);
        openNIDevice.drawSkeletons(0, 0, WIDTH, HEIGHT);
		
		 ofDrawBitmapStringHighlight("Mirror + Skeletons Display Mode (2 / 4)", 10, HEIGHT-10);
	}

    void drawMirrorDisplayMode(){
        ofSetColor(ofColor::white);
		
        openNIDevice.drawImage(0, 0, WIDTH,HEIGHT);
        
        ofDrawBitmapStringHighlight("Mirror Display Mode (1 / 4)", 10, HEIGHT-10);
    }

    void drawSilhouetteDisplayMode(){
		// get number of current users
        int numUsers = openNIDevice.getNumTrackedUsers();

        
        // iterate through users
        for (int i = 0; i < numUsers; i++){
            
            // get a reference to this user
            ofxOpenNIUser & user = openNIDevice.getTrackedUser(i);
            
            // draw the skeleton
            // user.drawSkeleton();
			user.drawMask();
        }
        ofDrawBitmapStringHighlight("Silhouette Display Mode (3 / 4)", 10, HEIGHT-10);
    }

    void drawInvisibleDisplayMode(){
        //nothing as yet... (-;
        ofDrawBitmapStringHighlight("Invisible Display Mode (4 / 4)", 10, HEIGHT-10);
    }
};
