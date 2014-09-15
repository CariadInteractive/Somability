#include "testApp.h"
#include "constants.h"
#include "SomabilityGui.h"

int WIDTH  = 1024;
int HEIGHT = 768; 


SomabilityGui gui;
//--------------------------------------------------------------
void testApp::setup() {
	centerer.setup(WIDTH, HEIGHT);
    ofSetCircleResolution(80);
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetFrameRate(30);
    ofBackground(ofColor::black);
    
    // setup shared data
	stateMachine.getSharedData().counter = 0;
	stateMachine.getSharedData().lastUpdate = ofGetElapsedTimeMillis();
	stateMachine.getSharedData().font.loadFont("verdana.ttf", 24);
	
    //openni into state machine now
    stateMachine.getSharedData().openNIDevice.setup();
#ifndef _WIN32 
	stateMachine.getSharedData().openNIDevice.addImageGenerator();
    stateMachine.getSharedData().openNIDevice.addDepthGenerator();
    stateMachine.getSharedData().openNIDevice.setRegister(true);
    stateMachine.getSharedData().openNIDevice.setMirror(true);
    stateMachine.getSharedData().openNIDevice.addUserGenerator();
    stateMachine.getSharedData().openNIDevice.setMaxNumUsers(2);
    stateMachine.getSharedData().openNIDevice.start();
    // set properties for all user masks and point clouds
	stateMachine.getSharedData().openNIDevice.setMaskPixelFormatAllUsers(OF_PIXELS_MONO);

    //openNIDevice.setUseMaskPixelsAllUsers(true); // if you just want pixels, use this set to true
    stateMachine.getSharedData().openNIDevice.setUseMaskTextureAllUsers(true); // this turns on mask pixels internally AND creates mask textures efficiently
    stateMachine.getSharedData().openNIDevice.setUsePointCloudsAllUsers(true);
    stateMachine.getSharedData().openNIDevice.setPointCloudDrawSizeAllUsers(2); // size of each 'point' in the point cloud
    stateMachine.getSharedData().openNIDevice.setPointCloudResolutionAllUsers(2); // resolution of the mesh created for the point cloud eg., this will use every second depth pixel
 #endif   
    //now do box2D
	stateMachine.getSharedData().box2d->init();
	stateMachine.getSharedData().box2d->setGravity(0, 10);
	stateMachine.getSharedData().box2d->createBounds(0,0,WIDTH, HEIGHT);
	stateMachine.getSharedData().box2d->setFPS(30.0);
	//stateMachine.getSharedData().box2d.registerGrabbing();
	stateMachine.getSharedData().gui = &gui;
	
	// initialise state machine
	stateMachine.addState<ChoiceState>();
	printf("kkkk\n");
	stateMachine.addState<FlowState>();
		printf("4444\n");
	stateMachine.addState<BalanceState>();
		printf("5555\n");
    stateMachine.addState<ReachState>();
	stateMachine.changeState("choice");
	printf("5132");
    stateMachine.getSharedData().theDisplayMode = MIRROR; //default to mirror mode
	stateMachine.disableAppEvents();
	stateMachine.disableMouseEvents();
	printf("12345");
	ofSetFullscreen(true);
}

//--------------------------------------------------------------
void testApp::update(){
    stateMachine.getSharedData().openNIDevice.update();
	stateMachine.update();
}

void testApp::drawKinectDebug(){
	ofSetColor(255, 255, 255);
    
    ofPushMatrix();
    // draw debug (ie., image, depth, skeleton)
    stateMachine.getSharedData().openNIDevice.drawDebug();
    ofPopMatrix();
	
   
    ofPushMatrix();
    // use a blend mode so we can see 'through' the mask(s)
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    // get number of current users
    int numUsers = stateMachine.getSharedData().openNIDevice.getNumTrackedUsers();
    
    // iterate through users
    for (int i = 0; i < numUsers; i++){
        
        // get a reference to this user
        ofxOpenNIUser & user = stateMachine.getSharedData().openNIDevice.getTrackedUser(i);
        
        // draw the mask texture for this user
        user.drawMask();
        
        // you can also access the pixel and texture references individually:
        
        // TEXTURE REFERENCE
        //ofTexture & tex = user.getMaskTextureReference();
        // do something with texture...
        
        // PIXEL REFERENCE
        //ofPixels & pix = user.getMaskPixels();
        // do something with the pixels...
        
        // and point clouds:
        
        ofPushMatrix();
        // move it a bit more central
        ofTranslate(320, 240, 10);
//        user.drawPointCloud();
        
        // you can also access the mesh:
        
        // MESH REFERENCE
        //ofMesh & mesh = user.getPointCloud();
        // do something with the point cloud mesh
        
        ofPopMatrix();
        
    }
    
    ofDisableBlendMode();
    ofPopMatrix();
    
    // draw some info regarding frame counts etc
	ofSetColor(0, 255, 0);
	string msg = " MILLIS: " + ofToString(ofGetElapsedTimeMillis()) + " FPS: " + ofToString(ofGetFrameRate()) + " Device FPS: " + ofToString(stateMachine.getSharedData().openNIDevice.getFrameRate());
    

}

//--------------------------------------------------------------
void testApp::draw(){
//	ofSetColor(255);
//	stateMachine.getSharedData().openNIDevice.drawMask();
	ofBackground(255);
	centerer.begin();
	stateMachine.draw();
	
	centerer.end();
	gui.draw();
}

//--------------------------------------------------------------
void testApp::exit(){
 //   stateMachine.getSharedData().openNIDevice.stop();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch (key) {
        case 'f':
            ofToggleFullscreen();
            break;
        case '1':
            stateMachine.getSharedData().theDisplayMode = MIRROR;
            break;
        case '2':
            stateMachine.getSharedData().theDisplayMode = MIRROR_SKELETON;
			break;
		case '3':
            stateMachine.getSharedData().theDisplayMode = SILHOUETTE;
            break;
        case '4':
            stateMachine.getSharedData().theDisplayMode = INVISIBLE;
            break;
		case ' ':
			gui.toggle();
			break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	ofMouseEventArgs m;
	m.x = x;
	m.y = y;
	if(gui.mouseMoved(m)) {
		centerer.transformMouse(m);
	
		stateMachine.onMouseMoved(m);
	}
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    ofMouseEventArgs m;
	m.x = x;
	m.y = y;
	
	if(!gui.mouseDragged(m)) {
		centerer.transformMouse(m);
		stateMachine.onMouseDragged(m);
	}
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    ofMouseEventArgs m;
	m.x = x;
	m.y = y;
	
	if(!gui.mousePressed(m)) {
		centerer.transformMouse(m);
		stateMachine.onMousePressed(m);
	}
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    ofMouseEventArgs m;
	m.x = x;
	m.y = y;
	
	if(!gui.mouseReleased(m)) {
		centerer.transformMouse(m);
		stateMachine.onMouseReleased(m);
	}
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}