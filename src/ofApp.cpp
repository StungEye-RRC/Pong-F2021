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
		const auto horizontalMiddle{canvasWidth / 2.0f};
		const auto verticalMiddle{canvasHeight / 2.0f};

		// Reposition ball and paddles to center points.
		ball.warpTo({horizontalMiddle, verticalMiddle});
		p1Paddle.warpTo({paddleEdgeBuffer, verticalMiddle});
		p2Paddle.warpTo({canvasWidth - paddleEdgeBuffer, verticalMiddle});

		// Pick random Y speed from a predefined selection.
		std::vector<float> startSpeeds{-105.0, -70.0f, -35.0f, 35.0f, 70.0f, 105.0f};
		ofRandomize(startSpeeds);

		// Set X speed (horizontal direction) depending on who is serving.
		ball.cruiseAt({p1Serves ? gameSpeed : -gameSpeed, 300}); // startSpeeds[0]});
	}

	// MOVE PADDLES
	// FPS independent speedChance for paddles using the oF version of delta time.
	const float deltaTime = ofGetLastFrameTime();
	p1Paddle.move(deltaTime);
	p2Paddle.move(deltaTime);

	// Ensure neither paddle leaves the canvas.
	p1Paddle.clampToBoundary({0, 0}, {canvasWidth, canvasHeight});
	p2Paddle.clampToBoundary({0, 0}, {canvasWidth, canvasHeight});

	// MOVE BALL
	// Move ball's position by its speed using FPS independent motion (delta time).
	ball.move(deltaTime);

	// BALL EDGE BOUNCE
	ball.bounceHorizontalWithEdge(0, canvasHeight);

	// BALL PADDLE BOUNCE
	ball.bounceVerticalWith(p1Paddle);
	ball.bounceVerticalWith(p2Paddle);

	// CHECK IF PLAYER 1 SCORES POINT 
	if (ball.position.x > canvasWidth) {
		// Increase player 1 score and flags to ensure p1 serves next.
		++p1Score;
		startRally = true;
		p1Serves = true;
	}

	// CHECK IF PLAYER 2 SCORES POINT 
	if (ball.position.x < 0) {
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
	p1Paddle.draw();
	p2Paddle.draw();

	// DRAW BALL
	ball.draw();
}

//--------------------------------------------------------------
// Is player 1 or player 2 requesting to move their paddles up or down using the keyboard.
void ofApp::keyPressed(int key) {
	if (key == 'w') p1Paddle.cruiseAt({0, -gameSpeed});
	if (key == 's') p1Paddle.cruiseAt({0, gameSpeed});
	if (key == 'i') p2Paddle.cruiseAt({0, -gameSpeed});
	if (key == 'k') p2Paddle.cruiseAt({0, gameSpeed});
}

//--------------------------------------------------------------
// Has player 1 or player 2 released their movement keys?
void ofApp::keyReleased(int key) {
	if (key == 'w' || key == 's') p1Paddle.cruiseAt({0, 0});
	if (key == 'i' || key == 'k') p2Paddle.cruiseAt({0, 0});
}

//--------------------------------------------------------------
// This function will be called if the user attempts to resize the canvas.
// We can prevent the resize by overriding it back to the defaults. Kludge.
void ofApp::windowResized(int w, int h) {
	if (w != canvasWidth || h != canvasHeight) {
		ofSetWindowShape(canvasWidth, canvasHeight);
	}
}
