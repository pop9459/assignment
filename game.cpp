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

	static int gameState = 0; //0-menu 1-dialog 2-game 3-endScreen
	static int laststate = 0; 

	SnakeGame snakeGame;
	MenuScreen menuScreen;
	EndScreen endScreen;
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
		endScreen.Init();
	}
	void Game::Shutdown() {}

	void Game::MouseMove(int x, int y) {
		mouseX += x;
		mouseY += y; 

		//put all mouse colision detections here
		if (gameState == 0) { //buttons on start screen
			for(int i = 0; i < menuScreen.buttons.size(); i++)
			{
				menuScreen.buttons[i].MouseOver(mouseX, mouseY);
			}
		}
		if (gameState == 3) { //buttons on end screen
			for (int i = 0; i < endScreen.buttons.size(); i++)
			{
				endScreen.buttons[i].MouseOver(mouseX, mouseY);
			}
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
			switch (gameState)
			{
			case 1:
				dialogScreen.LoadIntroScript();
				nextChar = totalTime;
				dialogScreen.Draw();
				break;
			case 2:
				nextFrame = totalTime;
				snakeGame.Reset();
				break;
			case 3:
				dialogScreen.LoadOutroScript();
				nextChar = totalTime;
				dialogScreen.Draw();
				break;
			default:
				break;
			}
		}

		//game logic
		switch (gameState)
		{
		case 0: //################# menu #################
			colorR = std::abs(std::sin(pulseSpeed * totalTime)) * 256;
			colorG = std::abs(std::sin(pulseSpeed * totalTime - 2)) * 256;
			colorB = std::abs(std::sin(pulseSpeed * totalTime - 4)) * 256;

			color = (colorR * 256 * 256) + (colorG * 256) + colorB;
			menuScreen.DrawMenu(color);

			//if start button is pressed
			if (lMouseDown && menuScreen.buttons[0].mouseOver) {
				gameState = 1;
			}
			break;
		case 1: //################# dialog #################
		case 3:
			//skip key pressed
			if (skipKeyLastState != GetAsyncKeyState(skipKey)) {
				if (skipKeyLastState == FALSE) {
					if (GetAsyncKeyState(VK_CONTROL) || dialogScreen.NextLine()) {
						if (snakeGame.gameWon) {
							gameState = 3;
						}
						else {
							gameState = 2;
						}
					}
				}
				skipKeyLastState = GetAsyncKeyState(skipKey);
			}
			//slow text print
			if (totalTime >= nextChar) {
				dialogScreen.NextChar();
				nextChar += dialogScreen.printSpeed * 1000;
			}
			break;
		case 2: //################# snake minigame #################
			//game in paused state = before start / after hitting score goal
			if (!snakeGame.started) {
				if (skipKeyLastState != GetAsyncKeyState(skipKey)) {
					if (skipKeyLastState == FALSE) {
						if (snakeGame.gameWon) {
							gameState = 3;
						}
						nextFrame = totalTime;
						snakeGame.started = true;
					}
					skipKeyLastState = GetAsyncKeyState(skipKey);
				}

				snakeGame.DrawPlayArea();
				break; //dont proceed with game logic
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
					//game failed - reset
					snakeGame.Restart();
					std::cout << "dead\n";
				}
				if (!snakeGame.endless && snakeGame.snake.length - 4 >= snakeGame.scoreGoal) {
					//game won
					snakeGame.started = false;
					snakeGame.gameWon = true;
					std::cout << "win\n";
				}
				snakeGame.snake.Draw(snakeGame.tileSize);
				snakeGame.cherry.draw(snakeGame.tileSize, snakeGame.gridPosX, snakeGame.gridPosY);
				
				snakeGame.DrawPlayArea(); //draw play area
			}
			break;
		case 4: //################# end screen #################
			endScreen.DrawMenu();

			//if start button is pressed
			if (lMouseDown && endScreen.buttons[0].mouseOver) {
				gameState = 0;
				snakeGame.Reset();
			}
			if (lMouseDown && endScreen.buttons[1].mouseOver) {
				gameState = 2;
				snakeGame.Reset();
				snakeGame.setGoal(-1);
			}
			if (lMouseDown && endScreen.buttons[2].mouseOver) {
				exit(0);
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
			Renderer::GetScreen()->PrintScaled("1-5 - switch game state", 5, 35, 0xffffff, 2);
			//game state -  what content should be displayed
			std::sprintf(printBuffer, "GameState: %d", gameState);
			Renderer::GetScreen()->PrintScaled(printBuffer, 5, 50, 0xffffff, 2);
			std::sprintf(printBuffer, "SnakeSpeed: %.2f", snakeGame.snakeSpeed);
			Renderer::GetScreen()->PrintScaled(printBuffer, 5, 65, 0xffffff, 2);
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
			if (GetAsyncKeyState(0x34)) gameState = 3;
			if (GetAsyncKeyState(0x35)) gameState = 4;
			if (GetAsyncKeyState(0x43)) {
				snakeGame.cherry.newCherry(snakeGame.gridSize, snakeGame.snake.body);
				snakeGame.cherry.draw(snakeGame.tileSize, snakeGame.gridPosX, snakeGame.gridPosY);
			}
		}
	}
};	