#ifdef _WIN32
#include "Microsoft_ofxOpenNI.h"
#include "constants.h"

ofxKinectCommonBridge *ofxOpenNI::kinect = NULL;




void ofxOpenNIUser::init(int i, Skeleton &skel) { 
	this->skel = skel;
	index = i;
	
}


void ofxOpenNIUser::drawMask() {
	ofxOpenNI::kinect->drawPlayerTextures(0,0,WIDTH,HEIGHT);
}

ofPixels &ofxOpenNIUser::getMaskPixels() {
	return ofxOpenNI::kinect->getPlayerPixels(index+1);
}


int ofxOpenNIUser::getNumLimbs() {
	return skel.size();
}

ofxOpenNILimb &ofxOpenNIUser::getLimb(int pos) {
	limbMap[pos] = ofxOpenNILimb();//skel[pos]);
	limbMap[pos].setup(skel, pos);
	return limbMap[pos];
}


ofxOpenNIJoint &ofxOpenNIUser::getJoint(int pos) {
	jointMap[pos] = ofxOpenNIJoint();

	map<_NUI_SKELETON_POSITION_INDEX,SkeletonBone>::iterator it = skel.find((_NUI_SKELETON_POSITION_INDEX)pos);
	if(it!=skel.end()) {
		jointMap[pos].setup((*it).second);
	}
	//jointMap[pos].setup(skel[(_NUI_SKELETON_POSITION_INDEX)pos]);
	return jointMap[pos];
}



int ofxOpenNIUser::getXnID() {
	return index;
}



void ofxOpenNI::setup() {
	kinect = new ofxKinectCommonBridge();
	bool r = kinect->initSensor();
	if(!r) ofLogError() << "Couldn't init sensor!";

	r = kinect->initDepthStream(640, 480, true, false);
	if(!r) ofLogError() << "Couldn't init depth stream!";

	r = kinect->initColorStream(640, 480, true);
	if(!r) ofLogError() << "Couldn't init color stream!";

	r = kinect->initSkeletonStream(false);
	if(!r) ofLogError() << "Couldn't init skeleton stream!";
	r = kinect->start();
	if(!r) ofLogError() << "Couldn't start kinect!";
	
	ofLogNotice() << "Started kinect";

}


void ofxOpenNI::update() {
	//printf("Update\n");
	kinect->update();
	users.clear();
	vector<Skeleton> &skels = kinect->getSkeletons();
	for(int i = 0; i <skels.size(); i++) {
		users.push_back(ofxOpenNIUser());
		users.back().init(i, skels[i]);
	}
}


void ofxOpenNI::stop() {
	//printf("Stop\n");
	kinect->stop();
}


void ofxOpenNI::drawDebug() {
	ofPushMatrix();
	ofScale(WIDTH/getWidth(), HEIGHT/getHeight(), 1);

	kinect->drawDepth(0, 0, WIDTH, HEIGHT);
	int sk = getNumTrackedUsers();
	for(int i = 0; i < sk; i++) {
		kinect->drawSkeleton(i);
	}
	ofPopMatrix();
}


float ofxOpenNI::getFrameRate() {
	return 30;
}

void ofxOpenNI::drawImage(float x, float y, float w, float h) {

	//printf("%f  %f  %f %f\n", x, y, w, h);
	ofDisableAlphaBlending();
	//kinect->drawDepth(x, y, w, h);
	kinect->draw(x, y, w, h);
	ofEnableAlphaBlending();
	//kinect.getColorPixelsRef().draw(x, y, w, h);

}


void ofxOpenNI::drawSkeletons(float x, float y, float w, float h) {
	ofPushMatrix();
	ofScale(w/getWidth(), h/getHeight(), 1);

	int sk = getNumTrackedUsers();






	for(int i = 0; i < sk; i++) {
		// Iterate through joints
		for ( Skeleton::iterator it = kinect->getSkeletons()[i].begin(); it != kinect->getSkeletons()[i].end(); ++it ) {

			// Get position and rotation
			SkeletonBone bone	= it->second;

			ofSetColor(255, 255, 255);
			ofSetLineWidth(3.0); // fat lines
			int startJoint = bone.getStartJoint();
			// do we have a start joint?
			if ( kinect->getSkeletons()[i].find( ( NUI_SKELETON_POSITION_INDEX ) startJoint ) != kinect->getSkeletons()[i].end() ) 
			{
				// draw the line
				ofLine( bone.getScreenPosition(), kinect->getSkeletons()[i].find( ( NUI_SKELETON_POSITION_INDEX ) startJoint )->second.getScreenPosition() );
			}

			// Draw joint
			ofCircle( bone.getScreenPosition(), 3 );
		}
	}
	

	ofPopMatrix();
}


	
void ofxOpenNI::drawMask() {
	kinect->drawPlayerTextures(0,0,VISION_WIDTH, VISION_HEIGHT);
}


float ofxOpenNI::getWidth() {
	return VISION_WIDTH;
}


float ofxOpenNI::getHeight() {
	return VISION_HEIGHT;
}


int ofxOpenNI::getNumTrackedUsers() {
	return users.size();
}


ofxOpenNIUser &ofxOpenNI::getTrackedUser(int pos) {
	return users[pos];
}



#endif