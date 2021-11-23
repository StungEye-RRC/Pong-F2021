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

		// Reposition ball and paddles to center points.
		ballXPosition = ofGetWidth() / 2.0f;
		ballYPosition = p2YPosition = p1YPosition = ofGetHeight() / 2.0f;

		// Pick random Y speed from a predefined selection.
		std::vector<float> startSpeeds{-105.0, -70.0f, -35.0f, 35.0f, 70.0f, 105.0f};
		ofRandomize(startSpeeds);
		ballYSpeed = startSpeeds[0];

		// Set X speed (horizontal direction) depending on who is serving.
		ballXSpeed = p1Serves ? 300 : -300;
	}

	// MOVE PADDLES
	// FPS independent speedChance for paddles using the oF version of delta time.
	const double speedChange{300 * ofGetLastFrameTime()};

	// Move player 1 paddle if necessary.
	if (p1UpPressed) p1YPosition -= speedChange;
	if (p1DownPressed) p1YPosition += speedChange;

	// Move player 2 paddle if necessary.
	if (p2UpPressed) p2YPosition -= speedChange;
	if (p2DownPressed) p2YPosition += speedChange;

	// Ensure neither paddle leaves the canvas.
	p1YPosition = ofClamp(p1YPosition, 50, 450);
	p2YPosition = ofClamp(p2YPosition, 50, 450);

	// MOVE BALL
	// Move ball's position by its speed using FPS independent motion (delta time).
	ballXPosition += ballXSpeed * ofGetLastFrameTime();
	ballYPosition += ballYSpeed * ofGetLastFrameTime();

	// BALL EDGE BOUNCE
	if (ballYPosition <= 10 || ballYPosition >= canvasHeight - 10) {
		// Reverse vertical direction if ball hits top or bottom edge of canvas.
		ballYSpeed *= -1;
		// Ensure that ball's y position is "pushed" back into the canvas if necessary.
		ballYPosition = ofClamp(ballYPosition, 10, canvasHeight - 10);
	}

	// BALL PADDLE 1 BOUNCE
	if ((ballXPosition > 50 && ballXPosition < 70)
		&& (ballYPosition > p1YPosition - 60)
		&& (ballYPosition < p1YPosition + 60)) {
		// Reverse horizontal direction.
		ballXSpeed *= -1;
		// Increase or decrease vertical speed depending on where ball hits paddle.
		ballYSpeed += ballYPosition - p1YPosition;
		// Ensure that ball's x position is "pushed" away from the interior of the paddle.
		ballXPosition = 70;
	}

	// BALL PADDLE 2 BOUNCE
	if ((ballXPosition > 730 && ballXPosition < 750)
		&& (ballYPosition > p2YPosition - 60)
		&& (ballYPosition < p2YPosition + 60)) {
		// Reverse horizontal direction.
		ballXSpeed *= -1;
		// Increase or decrease vertical speed depending on where ball hits paddle.
		ballYSpeed += ballYPosition - p1YPosition;
		// Ensure that ball's x position is "pushed" away from the interior of the paddle.
		ballXPosition = 730;
	}

	// CHECK IF PLAYER 1 SCORES POINT 
	if (ballXPosition > canvasWidth) {
		// Increase player 1 score and flags to ensure p1 serves next.
		++p1Score;
		startRally = true;
		p1Serves = true;
	}

	// CHECK IF PLAYER 2 SCORES POINT 
	if (ballXPosition < 0) {
		// Increase player 2 score and flags to ensure p2 serves next.
		++p2Score;
		startRally = true;
		p1Serves = false;
	}
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
// Is player 1 or player 2 requesting to move their paddles up or down using the keyboard.
void ofApp::keyPressed(int key) {
	if (key == 'w') p1UpPressed = true;
	if (key == 's') p1DownPressed = true;
	if (key == 'i') p2UpPressed = true;
	if (key == 'k') p2DownPressed = true;
}

//--------------------------------------------------------------
// Has player 1 or player 2 released their movement keys?
void ofApp::keyReleased(int key) {
	if (key == 'w') p1UpPressed = false;
	if (key == 's') p1DownPressed = false;
	if (key == 'i') p2UpPressed = false;
	if (key == 'k') p2DownPressed = false;
}

//--------------------------------------------------------------
// This function will be called if the user attempts to resize the canvas.
// We can prevent the resize by overriding it back to the defaults. Kludge.
void ofApp::windowResized(int w, int h) {
	if (w != canvasWidth || h != canvasHeight) {
		ofSetWindowShape(canvasWidth, canvasHeight);
	}
}
