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
		snakeGame.checkForInput();

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