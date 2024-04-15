#include "game.h"
#include "surface.h"
#include <iostream>
#include <cstdio> //printf

#include "renderer.cpp"
#include "snakeGame.cpp"
#include "menuScreen.cpp"
#include "dialogScreen.cpp"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace Tmpl8
{
	//########################################## INITIALIZATION ##########################################
	static bool showDebugInfo = false; //disable for production release!!!
	static const bool enableDebugKeys = true; //disable for production release!!!
	
	static float totalTime = 0;
	
	static int mouseX = 0;
	static int mouseY = 0;
	static bool lMouseDown = false;

	static int gameState = 0; //0-menu //1-dialog //2-game
	static int laststate = 0; 

	SnakeGame snakeGame;
	MenuScreen menuScreen;
	DialogScreen dialogScreen;
	
	//vars for main menu
	float pulseSpeed = 0.00075f;
	int colorR, colorG, colorB;
	u_int color;

	//vars for dialog screen
	int skipKey = VK_RETURN;
	bool skipKeyLastState;
	static float nextChar = 0;

	//vars for snake game screen
	static float nextFrame = 0;

	//########################################## EVENTS ##########################################
	void Game::Init() {
		Renderer::SetScreen(screen); //always init first
		menuScreen.Init();
		snakeGame.Init();
		dialogScreen.LoadIntroScript();
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

	//########################################## MAIN ##########################################
	void Game::Tick(float deltaTime) {
		//keep track of uptime
		totalTime += deltaTime;
		
		//this will run when switching screens
		if (gameState != laststate) {
			screen->Clear(0);
			laststate = gameState;
			nextFrame = totalTime;
			nextChar = totalTime;
		}

		//game logic
		switch (gameState)
		{
		case 0: //menu ##########################################
			colorR = std::abs(std::sin(pulseSpeed * totalTime)) * 256;
			colorG = std::abs(std::sin(pulseSpeed * totalTime - 2)) * 256;
			colorB = std::abs(std::sin(pulseSpeed * totalTime - 4)) * 256;

			color = (colorR * 256 * 256) + (colorG * 256) + colorB;
			menuScreen.DrawMenu(color);

			//if start button is pressed
			if (lMouseDown && menuScreen.buttons[0].mouseOver) gameState = 1; 
			break;
		case 1: //dialog ##########################################
			//skip key pressed
			if (skipKeyLastState != GetAsyncKeyState(skipKey)) {
				if (skipKeyLastState == FALSE) {
					if (dialogScreen.NextLine()) gameState++;
				}
				skipKeyLastState = GetAsyncKeyState(skipKey);
			}
			//slow text print
			if (totalTime >= nextChar) {
				dialogScreen.NextChar();
				nextChar += dialogScreen.printSpeed * 1000;
			}
			break;
		case 2: //snage minigame ##########################################
			//before game start - wait for user input
			if (skipKeyLastState != GetAsyncKeyState(skipKey)) {
				if (skipKeyLastState == FALSE) {
					nextFrame = totalTime;
					snakeGame.started = true;
				}
				skipKeyLastState = GetAsyncKeyState(skipKey);
			}
			if (!snakeGame.started) {
				snakeGame.DrawPlayArea();
				break;
			}

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
			}
			break;
		default:
			std::cout << "Error: Invalid game state!\n";
			break;
		}

		//########################################## DEBUG UTILS ##########################################
		if (showDebugInfo) {
			//info
			char printBuffer[60]; 
			Renderer::GetScreen()->PrintScaled("Debug mode - (numbers not on numpad)", 5, 5, 0xffffff, 2);
			Renderer::GetScreen()->PrintScaled("0 - show this info", 5 ,20 , 0xffffff, 2);
			Renderer::GetScreen()->PrintScaled("1-3 - switch game state", 5, 35, 0xffffff, 2);
			//game state -  what content should be displayed
			std::sprintf(printBuffer, "GameState: %d", gameState);
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
			if (GetAsyncKeyState(0x33)) gameState = 2;
		}
	}
};	