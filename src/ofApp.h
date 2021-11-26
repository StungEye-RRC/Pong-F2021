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

class MotionSprite : public Sprite {
private:
	glm::vec2 velocity;
public:
	MotionSprite(float xPosition, float yPosition, float width, float height,
	             float xSpeed, float ySpeed)
		: Sprite{xPosition, yPosition, width, height}, velocity{xSpeed, ySpeed} {
	}

	// A setter for velocity.
	void cruiseAt(glm::vec2 newVelocity) {
		velocity = newVelocity;
	}

	// Apply the velocity to the position.
	void move(float deltaTime) {
		position += velocity * deltaTime;
	}

	void bounceHorizontalWithEdge(float ceilingY, float floorY) {
		// Adjust ceiling and floor positions for the ball size.
		ceilingY += height / 2.0f;
		floorY -= height / 2.0f;

		if (position.y <= ceilingY || position.y >= floorY) {
			velocity.y *= -1;
			position.y = ofClamp(position.y, ceilingY, floorY);
		}
	}

	void bounceVerticalWith(Sprite other) {
		float dy{position.y - other.position.y};
		float hitDistanceY{0.5f * (height + other.height)};

		// Is this sprite inline with the other sprite vertically?
		if (std::abs(dy) < hitDistanceY) {
			float dx{position.x - other.position.x};
			float hitDistanceX{0.5f * (width + other.width)};

			// Is this sprite inline with the other sprite horizontall? If yes, a collision! 
			if (std::abs(dx) < hitDistanceX) {
				// Reverse the x speed.
				velocity.x *= -1;
				float direction = dx / std::abs(dx); // Either 1 or -1
				// Push the sprite away from the other sprite horizontally.
				position.x = other.position.x + (hitDistanceX * direction);

				accelerate({0, position.y - other.position.y});
			}
		}
	}

	// This impulse will be applied to the velocity.
	void accelerate(glm::vec2 impulse) {
		velocity += impulse;
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

	short p1Score{0}, p2Score{0};

	const int paddleWidth{20};
	const int paddleHeight{100};
	const int paddleEdgeBuffer{50};
	const int ballWidth{20};
	const int ballHeight{20};
	const int gameSpeed{300};

	MotionSprite p1Paddle{0, 0, paddleWidth, paddleHeight, 0, 0};
	MotionSprite p2Paddle{0, 0, paddleWidth, paddleHeight, 0, 0};
	MotionSprite ball{0, 0, ballWidth, ballHeight, 0, 0};
};
