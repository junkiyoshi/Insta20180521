#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofBackground(39);
	ofSetWindowTitle("Insta");

	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);

	int rect_len = ofGetWidth() > ofGetHeight() ? ofGetWidth() : ofGetHeight();
	for (int z = 0; z < 2048; z += 64) {

		ofRotate(ofGetFrameNum() * 0.03);
		this->draw_shit_world(ofPoint(0, 0, z), rect_len);
	}
	
	this->cam.end();
}

//--------------------------------------------------------------
void ofApp::draw_shit_world(ofPoint point, int rect_len) {

	ofPushMatrix();
	ofTranslate(point);

	int radius = rect_len * 0.5;

	ofColor color = ofColor(239);
	ofSetColor(color, point.z < 1024 ? ofMap(point.z, 0, 1024, 32, 255) : 255);

	vector<ofPoint> vertices;
	vector<ofPoint> mini_vertices;
	for (int deg = 0; deg < 360; deg++) {

		int x = radius * cos(deg * DEG_TO_RAD);
		int y = radius * sin(deg * DEG_TO_RAD);
		int z = point.z;

		float noise_value = ofMap(ofNoise(x * 0.01, y * 0.01, z * 0.05, ofGetFrameNum() * 0.005), 0, 1, 0.5, 1);
		x = radius * noise_value * cos(deg * DEG_TO_RAD);
		y = radius * noise_value * sin(deg * DEG_TO_RAD);
		vertices.push_back(ofPoint(x, y));

		x *= 0.95;
		y *= 0.95;
		mini_vertices.push_back(ofPoint(x, y));
	}

	ofBeginShape();
	ofVertex(-rect_len, -rect_len);
	ofVertex(rect_len, -rect_len);
	ofVertex(rect_len, rect_len);
	ofVertex(-rect_len, rect_len);
	ofNextContour(true);
	ofVertices(vertices);
	ofEndShape(true);

	color = ofColor(39);
	ofSetColor(color);

	ofBeginShape(); 
	ofVertices(vertices);
	ofNextContour();
	ofVertices(mini_vertices);
	ofEndShape(true);

	ofPopMatrix();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}