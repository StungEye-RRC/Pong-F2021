#pragma once

#include "ofMain.h"

class Sprite {
public:
	float width, height;
	glm::vec2 position;

	Sprite(float xPosition, float yPosition, float width, float height)
		: width{width}, height{height}, position{xPosition, yPosition} {
	}

	void warpTo(glm::vec2 destination) {
		position = destination;
	}

	void moveVertically(float offset) {
		position.y += offset;
	}

	void clampToBoundary(glm::vec2 min, glm::vec2 max) {
		position.x = ofClamp(position.x, min.x + width / 2, max.x - width / 2);
		position.y = ofClamp(position.y, min.y + height / 2, max.y - height / 2);
	}

	void draw() {
		ofPushStyle();
		ofSetRectMode(OF_RECTMODE_CENTER);
		ofDrawRectangle(position.x, position.y, width, height);
		ofPopStyle();
	}

};

class ofApp : public ofBaseApp {

public:
	void setup() override;
	void update() override;
	void draw() override;

	void keyPressed(int key) override;
	void keyReleased(int key) override;
	void windowResized(int w, int h) override;

private:
	const int canvasWidth{800}, canvasHeight{500};

	bool startRally{true};
	bool p1Serves{ofRandom(0, 100) < 50};

	bool p1UpPressed{false}, p1DownPressed{false}, p2UpPressed{false}, p2DownPressed{false};

	float ballXPosition{0.0f}, ballYPosition{0.0f};
	float ballXSpeed{0.0f}, ballYSpeed{0.0f};

	float p1YPosition{0.0f}, p2YPosition{0.0f};

	short p1Score{0}, p2Score{0};

	const int paddleWidth{20};
	const int paddleHeight{100};
	const int paddleEdgeBuffer{50};

	Sprite p1Paddle{0, 0, paddleWidth, paddleHeight};
	Sprite p2Paddle{0, 0, paddleWidth, paddleHeight};
};
