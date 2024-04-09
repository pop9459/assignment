#include "game.h"
#include "surface.h"
#include <iostream>
#include <cstdio> //printf

#include "renderer.cpp"
#include "snakeGame.cpp"
#include "menuScreen.cpp"

namespace Tmpl8
{
	//Initialization
	static bool showDebugInfo = true; //disable for production release!!!
	static const bool enableDebugKeys = true; //disable for production release!!!
	
	static float nextFrame = 0;
	static float totalTime = 0;
	
	static int mouseX = 0;
	static int mouseY = 0;
	static bool lMouseDown = false;

	static int gameState = 0; //0-menu //1-game
	static int laststate = 0; 

	SnakeGame snakeGame;
	MenuScreen menuScreen;

	//EVENTS
	void Game::Init() {
		Renderer::SetScreen(screen); //always init first
		menuScreen.Init();
		snakeGame.Init();
		
		nextFrame += snakeGame.snakeSpeed * 1000;
	}
	void Game::Shutdown() {}

	void Game::MouseMove(int x, int y) { 
		mouseX += x;
		mouseY += y; 
		for(int i = 0; i < menuScreen.buttons.size(); i++)
		{
			menuScreen.buttons[i].MouseOver(mouseX, mouseY);
		}
	}
	void Game::MouseUp(int button) {
		if (button == VK_LBUTTON) lMouseDown = false;
	}
	void Game::MouseDown(int button) {
		if (button == VK_LBUTTON) lMouseDown = true;
	}

	//MAIN
	void Game::Tick(float deltaTime) {
		//keep track of uptime
		totalTime += deltaTime;
		
		//clear after game state change
		if (gameState != laststate) {
			screen->Clear(0);
			laststate = gameState;
		}

		//game logic
		switch (gameState) 
		{
		case 0: //menu
			menuScreen.DrawMenu();
			if (lMouseDown && menuScreen.buttons[0].mouseOver) gameState = 1;
			break;
		case 1: //snage minigame
			//game input
			snakeGame.checkForInput();

			//snake step
			if (totalTime >= nextFrame) {
				nextFrame += snakeGame.snakeSpeed * 1000;
				
				screen->Clear(0); //todo optimize drawing times
				snakeGame.snake.Move(snakeGame.tileSize);
				
				snakeGame.snakeOnCherry();
				if (!snakeGame.SnakeAlive()) {
					std::cout << "dead\n";
					snakeGame.Init();
				}
				snakeGame.snake.Draw(snakeGame.tileSize);
				snakeGame.cherry.draw(snakeGame.tileSize, snakeGame.gridPosX, snakeGame.gridPosY);
				
				snakeGame.DrawPlayArea(); //draw play area
				std::cout << totalTime/1000 << "\n"; //debug
			}
			break;
		default:
			std::cout << "Error: Invalid game state!\n";
			break;
		}

		//debug utils
		if (showDebugInfo) {
			//info
			char printBuffer[60]; 
			Renderer::GetScreen()->PrintScaled("Debug mode - (numbers not on numpad)", 5, 5, 0xffffff, 2);
			Renderer::GetScreen()->PrintScaled("0 - show this info", 5 ,20 , 0xffffff, 2);
			Renderer::GetScreen()->PrintScaled("1-2 - switch game state", 5, 35, 0xffffff, 2);
			//game state -  what content should be displayed
			std::sprintf(printBuffer, "GameState: % d", gameState);
			Renderer::GetScreen()->PrintScaled(printBuffer, 5, 50, 0xffffff, 2);
			//mouse pos
			//std::cout << mouseX << " - " << mouseY << "\n";
		}

		if (enableDebugKeys) {
			if (GetAsyncKeyState(0x30)) {
				showDebugInfo = !showDebugInfo; 
				if (showDebugInfo == false)
				{
					screen->Clear(0);
				}
				while (GetAsyncKeyState(0x30)) {} //wait for key unpress
			}
			if (GetAsyncKeyState(0x31)) gameState = 0;
			if (GetAsyncKeyState(0x32)) gameState = 1;
		}
	}
};	