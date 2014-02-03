#ifdef _WIN32
#include "Microsoft_ofxOpenNI.h"






void ofxOpenNIUser::init(int i, Skeleton &skel) { 
	this->skel = skel;
	index = i;
}

void ofxOpenNIUser::drawMask() {
	
}


ofPixels &ofxOpenNIUser::getMaskPixels() {
	return ofPixels();
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
	kinect.initSensor();
	kinect.initDepthStream(640, 480);
	kinect.initColorStream(640, 480);
	kinect.initSkeletonStream(false);
	kinect.start();
}


void ofxOpenNI::update() {
	kinect.update();
	users.clear();
	vector<Skeleton> &skels = kinect.getSkeletons();
	for(int i = 0; i <skels.size(); i++) {
		users.push_back(ofxOpenNIUser());
		users.back().init(i, skels[i]);
	}
}


void ofxOpenNI::stop() {
	//kinect.stop();
}


void ofxOpenNI::drawDebug() {
	glPushMatrix();
	glScalef(ofGetWidth()/getWidth(), ofGetHeight()/getHeight(), 1);

	kinect.drawDepth(0, 0, getWidth(), getHeight());
	int sk = getNumTrackedUsers();
	for(int i = 0; i < sk; i++) {
		kinect.drawSkeleton(i);
	}
	glPopMatrix();
}


float ofxOpenNI::getFrameRate() {
	return 30;
}


void ofxOpenNI::drawImage(float x, float y, float w, float h) {
	kinect.draw(x, y, w, h);
}


void ofxOpenNI::drawSkeletons(float x, float y, float w, float h) {
	glPushMatrix();
	glScalef(ofGetWidth()/getWidth(), ofGetHeight()/getHeight(), 1);

	int sk = getNumTrackedUsers();
	for(int i = 0; i < sk; i++) {
		kinect.drawSkeleton(i);
	}
	glPopMatrix();
}


	
void ofxOpenNI::drawMask() {

}


float ofxOpenNI::getWidth() {
	return 640;
}


float ofxOpenNI::getHeight() {
	return 480;
}


int ofxOpenNI::getNumTrackedUsers() {
	return users.size();
}


ofxOpenNIUser &ofxOpenNI::getTrackedUser(int pos) {
	return users[pos];
}



#endif