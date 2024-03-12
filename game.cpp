#include "game.h"
#include "surface.h"
#include <iostream>
#include <cstdio> //printf
#include "snakeGame.cpp"

namespace Tmpl8
{
	//Initialization
	static float nextFrame = 0;
	static float totalTime = 0;
	
	SnakeGame snakeGame;

	void Game::KeyDown(int key) {
		//W: 26
		//A: 4
		//S: 22
		//D: 7
		//arrU: 82
		//arrL: 80
		//arrD: 81
		//arrR: 79
		std::cout << "pressed: " << key << "\n";
		if (key == 26 || key == 82) { snakeGame.snake.ChangeDir(0); }
		if (key == 7 || key == 79) { snakeGame.snake.ChangeDir(1); }
		if (key == 22 || key == 81) { snakeGame.snake.ChangeDir(2); }
		if (key == 4 || key == 80) { snakeGame.snake.ChangeDir(3); }
	}

	void Game::Init() {
		nextFrame += snakeGame.snakeSpeed * 1000;
		snakeGame.Init(screen);
	}
	void Game::Shutdown() {}

	//MAIN
	void Game::Tick(float deltaTime) {
		totalTime += deltaTime;
		screen->Clear(0);
		

		//game input
		//snake step
		if (totalTime >= nextFrame) {
			snakeGame.snake.Move(snakeGame.tileSize);
			nextFrame += snakeGame.snakeSpeed * 1000;
			if (!snakeGame.SnakeAlive()) {
				std::cout << "dead\n";
				snakeGame.Init(screen);
			}
		}
		snakeGame.snake.Draw(screen, snakeGame.tileSize);

		//draw play area
		snakeGame.DrawPlayArea();
		//test
	}
};	