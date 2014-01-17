/**
 *  Trail.cpp
 *
 *  Created by Marek Bereza on 17/01/2014.
 */

#include "Trail.h"

int Trail::MAX_LENGTH = 90;

Trail::Trail() {
	colour.set(1, 0, 0);
}
void Trail::smoothTrail() {
	deque<ofVec2f>::reverse_iterator it = points.rbegin();
	
	while(it!=points.rend()) {
		ofVec2f &prev = (*it);
		it++;
		if(it!=points.rend()) {
			float h = 0.5;
			(*it) = prev * h + (*it) * (1.f - h);
		}
	}
}
	
void Trail::update(ofVec2f p) {
	smoothTrail();
	
	
	points.push_back(p);
	while(points.size()>MAX_LENGTH) {
		points.pop_front();
	}
	

}

void Trail::draw() {
	deque<ofVec2f>::iterator it;
	it = points.begin();
	int numPoints = points.size();
	int i =0 ;
	ofSetColor(colour);
	ofNoFill();
	glBegin(GL_LINE_STRIP);


	while(it!=points.end()) {
		float alpha = ofMap(i, numPoints, 0, 1, 0, true);
		glColor4f(colour.r, colour.g, colour.b, alpha);
		glVertex2f((*it).x,(*it).y);
		it++;
		i++;
		printf("Alpha %f\n", alpha);
	}
	
	glEnd();
	
	ofFill();
}


