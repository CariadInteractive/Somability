#pragma once

#include "ofMain.h"

#include "ofxStateMachine.h"
#include "SharedData.h"
#include "ChoiceState.h"
#include "RhythmState.h"
#include "FlowState.h"
#include "BalanceState.h"
#include "ReachState.h"
#include "Centerer.h"

class testApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

    void drawKinectDebug(); //just draws more information about the Kinect    
private:
    itg::ofxStateMachine<SharedData> stateMachine;
	Centerer centerer;

};
