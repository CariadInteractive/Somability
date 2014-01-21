/**     ___           ___           ___                         ___           ___     
 *     /__/\         /  /\         /  /\         _____         /  /\         /__/|    
 *    |  |::\       /  /::\       /  /::|       /  /::\       /  /::\       |  |:|    
 *    |  |:|:\     /  /:/\:\     /  /:/:|      /  /:/\:\     /  /:/\:\      |  |:|    
 *  __|__|:|\:\   /  /:/~/::\   /  /:/|:|__   /  /:/~/::\   /  /:/  \:\   __|__|:|    
 * /__/::::| \:\ /__/:/ /:/\:\ /__/:/ |:| /\ /__/:/ /:/\:| /__/:/ \__\:\ /__/::::\____
 * \  \:\~~\__\/ \  \:\/:/__\/ \__\/  |:|/:/ \  \:\/:/~/:/ \  \:\ /  /:/    ~\~~\::::/
 *  \  \:\        \  \::/          |  |:/:/   \  \::/ /:/   \  \:\  /:/      |~~|:|~~ 
 *   \  \:\        \  \:\          |  |::/     \  \:\/:/     \  \:\/:/       |  |:|   
 *    \  \:\        \  \:\         |  |:/       \  \::/       \  \::/        |  |:|   
 *     \__\/         \__\/         |__|/         \__\/         \__\/         |__|/   
 *
 *  Description: 
 *				 
 *  Ding.h, created by Marek Bereza on 20/01/2014.
 */



class Ding {
public:

	bool isDead() {
		return dead;
	}
	int maxAge;
	Ding(ofVec2f epi) {
		this->epi = epi;
		frame = 0;
		dead = false;
		maxAge = 30;
	}
	void update() {
		if(frame<10) {
			ofRectangle d;
			d.setFromCenter(epi, 20, 10);
			dingRings.push_back(d);
		}
		ofVec2f increment(15, 10);
		for(int i = 0; i < dingRings.size(); i++) {
			dingRings[i].x -= increment.x/2;
			dingRings[i].y -= increment.y/2;
			dingRings[i].width += increment.x;
			dingRings[i].height += increment.y;
		}
		frame++;
		if(frame>maxAge-dingRings.size() && dingRings.size()>0) dingRings.erase(dingRings.begin());
		if(frame>maxAge) dead = true;
	}
	
	void draw() {
		update();
		ofNoFill();
		glLineWidth(20);

		for(int i = 0; i < dingRings.size(); i++) {
		ofSetColor(255, 255, ofMap(i, 0, dingRings.size(), 0, 255, true),
				   ofMap(frame, 0, maxAge, 255, 0, true));
			ofEllipse(dingRings[i].getCenter(), dingRings[i].getWidth(), dingRings[i].getHeight());
		}
		glLineWidth(1);
	}
	vector<ofRectangle> dingRings;
	ofVec2f epi;
	int frame;
	bool dead;
};