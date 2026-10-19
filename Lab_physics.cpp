// Lab_physics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
using namespace std;
using namespace sf;
using namespace sfp;
int main()
{
	// Create our window and world with gravity 0,1
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));
	// Create the ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(400, 100));
	ball.setRadius(20);
	world.AddPhysicsBody(ball);
	// Create the floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);
	int thudCount(0);
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud" << " " << thudCount << endl;
		thudCount++;
		};
	PhysicsRectangle rightwall; //makes right wall
	rightwall.setSize(Vector2f(20, 600));
	rightwall.setCenter(Vector2f(790, 300));
	rightwall.setStatic(true);
	world.AddPhysicsBody(rightwall);
	PhysicsRectangle leftwall; //makes left wall
	leftwall.setSize(Vector2f(20, 600));
	leftwall.setCenter(Vector2f(10, 300));
	leftwall.setStatic(true);
	world.AddPhysicsBody(leftwall);
	PhysicsRectangle ceiling; //makes ceiling
	ceiling.setSize(Vector2f(800, 20));
	ceiling.setCenter(Vector2f(400, 10));
	ceiling.setStatic(true);
	world.AddPhysicsBody(ceiling);
	PhysicsRectangle obstacle; //makes obstacle
	obstacle.setSize(Vector2f(200, 200));
	obstacle.setCenter(Vector2f(400, 300));
	obstacle.setStatic(true);
	world.AddPhysicsBody(obstacle);
	int bangCount(1);
	obstacle.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
		cout << "bang" << " " << bangCount << endl;
		bangCount++;
		};
	Clock clock;
	Time lastTime(clock.getElapsedTime());
	while (true) {
		// calculate MS since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}
		if (bangCount == 4) { //equals 4 so it shows the correct number of bangs in the debug log which is 3 and once it equals 4 the window closes
			obstacle.setFillColor(Color(255, 0, 0));
			return 0;
		}

		window.clear(Color(0, 0, 0));
		window.draw(ball);
		window.draw(rightwall);// makes right wall visible
		window.draw(leftwall); // makes left wall visible
		window.draw(ceiling); // makes ceiling visible
		window.draw(floor);
		window.draw(obstacle); // makes obstacle visible
		window.display();
	}
}

