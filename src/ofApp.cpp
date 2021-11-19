#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(100);
	ofSetWindowShape(canvasWidth, canvasHeight);
	ofSetRectMode(OF_RECTMODE_CENTER);
}

//--------------------------------------------------------------
void ofApp::update() {
	// RALLY RESTART
	if (startRally) {
		startRally = false;

		ballXPosition = ofGetWidth() / 2.0f;
		ballYPosition = p2YPosition = p1YPosition = ofGetHeight() / 2.0f;

		std::vector<float> startSpeeds{-105.0, -70.0f, -35.0f, 35.0f, 70.0f, 105.0f};
		ofRandomize(startSpeeds);

		ballYSpeed = startSpeeds[0];
		ballXSpeed = p1Serves ? 300 : -300;
	}

	// MOVE PADDLES

	const double speedChange{300 * ofGetLastFrameTime()};

	if (p1UpPressed) p1YPosition -= speedChange;
	if (p1DownPressed) p1YPosition += speedChange;
	if (p2UpPressed) p2YPosition -= speedChange;
	if (p2DownPressed) p2YPosition += speedChange;

	p1YPosition = ofClamp(p1YPosition, 50, 450);
	p2YPosition = ofClamp(p2YPosition, 50, 450);


	// MOVE BALL

	// BALL EDGE BOUNCE

	// BALL PADDLE BOUNCE

	// CHECK FOR WIN
}

//--------------------------------------------------------------
void ofApp::draw() {
	// DRAW SCORES
	ofDrawBitmapString("P1: " + std::to_string(p1Score), 200, 40);
	ofDrawBitmapString("P2: " + std::to_string(p2Score), 550, 40);

	// DRAW PADDLES
	ofDrawRectangle(50, p1YPosition, 20, 100);
	ofDrawRectangle(750, p2YPosition, 20, 100);

	// DRAW BALL
	ofDrawRectangle(ballXPosition, ballYPosition, 20, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'w') p1UpPressed = true;
	if (key == 's') p1DownPressed = true;
	if (key == 'i') p2UpPressed = true;
	if (key == 'k') p2DownPressed = true;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	if (key == 'w') p1UpPressed = false;
	if (key == 's') p1DownPressed = false;
	if (key == 'i') p2UpPressed = false;
	if (key == 'k') p2DownPressed = false;
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
	if (w != canvasWidth || h != canvasHeight) {
		ofSetWindowShape(canvasWidth, canvasHeight);
	}
}
