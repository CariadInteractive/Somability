



#ifdef _WIN32

#include "ofMain.h"
#include "ofxKinectCommonBridge.h"

#define LIMB_COUNT NUI_SKELETON_POSITION_COUNT

typedef int Limb;

#define JOINT_LEFT_FOOT NUI_SKELETON_POSITION_FOOT_LEFT
#define JOINT_RIGHT_FOOT NUI_SKELETON_POSITION_FOOT_RIGHT
#define JOINT_LEFT_HAND NUI_SKELETON_POSITION_HAND_LEFT
#define JOINT_RIGHT_HAND NUI_SKELETON_POSITION_HAND_RIGHT


class ofxOpenNIJoint {
public:
	void setup(SkeletonBone &bone) {
		p = bone.getScreenPosition();
	}

	ofVec3f getProjectivePosition() {
		return p;
	}

	ofVec3f p;
};

class ofxOpenNILimb {
public:
	
	ofxOpenNIJoint &getStartJoint() { return start; }
	ofxOpenNIJoint &getEndJoint() { return end; }

	ofxOpenNILimb() {}
	
	
	void setup(map<_NUI_SKELETON_POSITION_INDEX,SkeletonBone> &bones, int boneIndex) {
		map<_NUI_SKELETON_POSITION_INDEX,SkeletonBone>::iterator startIt, endIt;
		startIt = bones.find((_NUI_SKELETON_POSITION_INDEX)boneIndex);

		if(startIt!=bones.end()) {
			start.setup((*startIt).second);
		

			endIt = bones.find((_NUI_SKELETON_POSITION_INDEX)(*startIt).second.getEndJoint());
			if(endIt!=bones.end()) {
				end.setup((*endIt).second);
			}
		} else {
			printf("startIt==bones.end()\n");
		}
		
		//start.setup(bones[(_NUI_SKELETON_POSITION_INDEX)boneIndex]);
		//int bi = bones[(_NUI_SKELETON_POSITION_INDEX)boneIndex].getEndJoint();
		//end.setup(bones[(_NUI_SKELETON_POSITION_INDEX)bi]);
	}
	ofxOpenNIJoint start, end;
};

class ofxOpenNIUser {
public:
	int index;
	void init(int index, Skeleton &skel);
	void drawMask();
	ofPixels &getMaskPixels();
	int getNumLimbs();
	ofxOpenNILimb &getLimb(int pos);
	ofxOpenNIJoint &getJoint(int pos);
	int getXnID(); 
	Skeleton skel;

	// some persistence for when passing out object references
	map<int,ofxOpenNILimb> limbMap;
	map<int,ofxOpenNIJoint> jointMap;
};
#define USER_SKELETON_LOST 0
#define USER_TRACKING_STOPPED 1

class ofxOpenNIUserEvent {
public:
	int userStatus;
};

class ofxOpenNI {
	
public:
	void setup();
	void update();
	void stop();
	void drawDebug();
	float getFrameRate();
	void drawImage(float x, float y, float w, float h);
	void drawImage() { drawImage(0, 0, getWidth(), getHeight()); } 
	void drawSkeletons(float x, float y, float w, float h);
	
	void drawMask();
	float getWidth();
	float getHeight();
	int getNumTrackedUsers();
	ofxOpenNIUser &getTrackedUser(int pos);
	ofEvent<ofxOpenNIUserEvent> userEvent;
	vector<ofxOpenNIUser> users;
	static ofxKinectCommonBridge *kinect;
};


#endif


