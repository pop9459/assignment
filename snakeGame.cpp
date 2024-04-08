#include "game.h"
#include "surface.h"
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <windows.h>
#include "renderer.cpp"

namespace Tmpl8
{
	Renderer renderer;

	class SnakePart {
	public:
		bool head;
		int pos_x, pos_y;
		SnakePart(int x, int y, bool isHead=false) {
			pos_x = x;
			pos_y = y;
			head = isHead;
		}
		
		void Draw(Surface* gameScreen, int tilesize, int gridPosX, int gridPosY, int dir) {
			if (head) {
				int headTile = 0;
				if (dir == 0) { headTile = 1; }
				if (dir == 1) { headTile = 4; }
				if (dir == 2) { headTile = 3; }
				if (dir == 3) { headTile = 2; }
				renderer.DrawTile((pos_x * tilesize) + gridPosX, (pos_y * tilesize) + gridPosY, gameScreen, headTile, 3);
			}
			else
			{
				renderer.DrawTile((pos_x * tilesize) + gridPosX, (pos_y * tilesize) + gridPosY, gameScreen, 5, 3);
			}
		}
	};

	class Snake	{
	public:
		int length, dir, currentDir, pos_x, pos_y, gridPosX, gridPosY, gridSize; 
		std::vector<SnakePart> body;
		Snake() {
		};
		void Init(int gridSize, int gridPosX, int gridPosY) {
			this->gridPosX = gridPosX;
			this->gridPosY = gridPosY;
			this->gridSize = gridSize;

			length = 4;
			dir = 1; //direction the snake will head towards on next step
			currentDir = 1; //direction of the snake on the last step
			pos_x = 0;
			pos_y = 0;

			body.clear();
			for (int i = 0; i < length; i++)
			{
				body.push_back(SnakePart(pos_x - i, pos_y));
			}
			body[0].head = true;
		}
		void growBody() {
			length++;
			body.push_back(SnakePart(body[body.size()-1].pos_x, body[body.size()-1].pos_y));
		}
		void Draw(Surface* gameScreen, int tilesize) {
			for (int i = 0; i < body.size(); i++) {
				//dont draw snake if outside of playArea
				if (body[i].pos_x < 0 || body[i].pos_y < 0 ||
					body[i].pos_x >= gridSize || body[i].pos_y >= gridSize) {
					continue;
				}
				body[i].Draw(gameScreen, tilesize, gridPosX, gridPosY, dir);
			}
		}
		void Move(int stepSize) {
			//Decide next position
			//0-UP, 1-LEFT, 2-DOWN, 3-LEFT
			switch (dir)
			{
			case 0:
				pos_y--;
				break;
			case 1:
				pos_x++;
				break;
			case 2:
				pos_y++;
				break;
			case 3:
				pos_x--;
				break;
			default:
				printf("Error: undefined direction. Cannot move!");
				break;
			}
			currentDir = dir;
			//modify body
			body.insert(body.begin(), SnakePart(pos_x, pos_y, true));
			body[1].head = false;
			body.pop_back();
		}
		void ChangeDir(int newDir) {
			//check if dir change is possible - snake is not allowed to do a 180 turn
			if (newDir == (currentDir + 2) % 4) {
				std::cout << "Cannot change direction";
			}
			else
			{
				dir = newDir;
			}
		}
	};

	class Cherry
	{
	public:
		int posX, posY;
		Cherry() {}
		void newCherry(int gridSize, std::vector<SnakePart> snakeBody) {
			std::random_device rd;
			std::mt19937 gen(rd());

			std::vector<int> possibleCords;
			possibleCords.clear();

			//determine all emply positions
			for (int x = 0; x < gridSize; x++) {
				for (int y = 0; y < gridSize; y++) {
					bool isEmpty = true;
					for each (SnakePart part in snakeBody)
					{
						if (part.pos_x == x && part.pos_y == y) { isEmpty = false; } //exclude space occupied by snake
						if (posX == x && posY == y) { isEmpty = false; } //exclude previous pos
					}
					if (isEmpty) { possibleCords.push_back((x * 10) + y); } //add pos if empty
				}
			}

			//pick a random empty position
			std::uniform_int_distribution<int> dist(0, possibleCords.size()-1);
			int position = possibleCords[dist(gen)];

			//assign new values
			posX = position / 10;
			posY = position % 10;
		}
		void draw(int tileSize, int gridPosX, int gridPosY, Surface* gameScreen) {
			renderer.DrawTile(posX * tileSize + gridPosX, posY * tileSize + gridPosY, gameScreen, 6, 3);
		}
	};

	class SnakeGame {
	public:
		int gridSize, tileSize, wallThickness, gridPosX, gridPosY;
		float snakeSpeed;
		Snake snake;
		Cherry cherry;
		Surface* gameScreen;
		SnakeGame() {
			snakeSpeed = 0.5f; //seconds per step
			gridSize = 11; //11
			tileSize = 32;
			wallThickness = 25;
		}
		void Init(Surface* surface ) {
			gameScreen = surface;
			gridPosX = (gameScreen->GetWidth() / 2) - ((tileSize * gridSize) / 2);
			gridPosY = tileSize;
			snake.Init(gridSize, gridPosX, gridPosY);
			cherry.newCherry(gridSize, snake.body);
		}
		void checkForInput() {
			if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState(0x57)) snake.ChangeDir(0);;
			if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(0x44)) snake.ChangeDir(1);;
			if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(0x53)) snake.ChangeDir(2);;
			if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(0x41)) snake.ChangeDir(3);;
		}
		void DrawPlayArea() {
			int bottomY = gridPosY + (gridSize * tileSize) + wallThickness;
			
			//walls
			for (int i = 1; i < wallThickness; i++)
			{
				if(i % 3==0) gameScreen->Box(gridPosX - i, gridPosY - i, gridPosX + (tileSize * gridSize) + i - 1, gridPosY + (tileSize * gridSize) + i - 1, 0xff0000);
			}

			//scorebox
			int scoreboxHeight = bottomY + wallThickness;
			for (int i = 0; i < wallThickness/1.5f; i++)
			{
				if (i % 3 == 0) gameScreen->Box(gridPosX-i, scoreboxHeight-i, gridPosX + (tileSize * gridSize) + i, bottomY + tileSize*2 + i, 0xffff00);
			}

			//print score text
			char scoreBuffer[20]; // Allocate a buffer for the character array
			std::sprintf(scoreBuffer, "Score: %d", snake.length-4); // Format the integer into the character buffer
			gameScreen->PrintScaled(scoreBuffer, gridPosX + 10, scoreboxHeight + 10, 0xffffff, 4); //print score to the screen
		}
		bool SnakeAlive() {	
			//is snake out of bounds?
			if (snake.pos_x < 0 || snake.pos_y < 0 ||
				snake.pos_x >= gridSize || snake.pos_y >= gridSize) {
				return false;
			}
			//is snake hitting itself?
			for (SnakePart part : snake.body)
			{
				if (part.head == false && snake.pos_x == part.pos_x && snake.pos_y == part.pos_y) { 
					return false; 
				}
			}
			//snake is alive
			return true;
		}
		bool snakeOnCherry() {
			if (snake.pos_x == cherry.posX && snake.pos_y == cherry.posY) {
				snake.growBody();
				snake.Draw(gameScreen, tileSize);
				cherry.newCherry(gridSize, snake.body);
				return true;
			}
			return false;
		}
	};
};