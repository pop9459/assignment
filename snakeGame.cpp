#include "game.h"
#include "surface.h"
#include <iostream>
#include <vector>

namespace Tmpl8
{
	static Sprite ball(new Surface("assets/ball.png"), 1);

	// Custom
	class SnakePart {
	public:
		bool head;
		int pos_x, pos_y;
		SnakePart(int x, int y, bool isHead=false) {
			pos_x = x;
			pos_y = y;
			head = isHead;
		}
		
		void Draw(Surface* gameScreen, int tilesize, int gridPosX, int gridPosY) {
			//ball.Draw(gameScreen, pos_x * tilesize, pos_y * tilesize);
			gameScreen->Box((pos_x * tilesize) + gridPosX,
							(pos_y * tilesize) + gridPosY,
							(pos_x * tilesize + tilesize) + gridPosX,
							(pos_y * tilesize + tilesize) + gridPosY,
							0x00ff00);
			if (head) {
				gameScreen->Box((pos_x * tilesize) + gridPosX + 5,
					(pos_y * tilesize) + gridPosY + 5,
					(pos_x * tilesize + tilesize) + gridPosX - 5,
					(pos_y * tilesize + tilesize) + gridPosY - 5,
					0x00ff00);
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
		void Draw(Surface* gameScreen, int tilesize) {
			for (int i = 0; i < body.size(); i++) {
				//dont draw snake if outside of playArea
				if (body[i].pos_x < 0 || body[i].pos_y < 0 ||
					body[i].pos_x >= gridSize || body[i].pos_y >= gridSize) {
					continue;
				}
				body[i].Draw(gameScreen, tilesize, gridPosX, gridPosY);
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
		Cherry() {
			//TODO
		}
	};

	class SnakeGame {
	public:
		int gridSize, tileSize, gridPosX, gridPosY;
		float snakeSpeed;
		Snake snake;
		Surface* gameScreen;
		SnakeGame() {
			snakeSpeed = 0.5f; //seconds per step
			gridSize = 22;
			tileSize = 20;
		}
		void Init(Surface* surface ) {
			gameScreen = surface;
			gridPosX = (gameScreen->GetWidth() / 2) - ((tileSize * gridSize) / 2);
			gridPosY = 10;
			snake.Init(gridSize, gridPosX, gridPosY);
		}
		void DrawPlayArea() {
			int wallThickness = 10;

			for (int i = 1; i < wallThickness; i++)
			{
				gameScreen->Box(gridPosX - i, gridPosY - i, gridPosX + (tileSize * gridSize) + i, gridPosY + (tileSize * gridSize) + i, 0xff0000);
			}
		}
		bool SnakeAlive() {
			//is snake out of bounds?
			if (snake.pos_x < 0 || snake.pos_y < 0 ||
				snake.pos_x >= gridSize || snake.pos_y >= gridSize) {
				return false;
			}
			//is snake hitting itself?
			for each (SnakePart part in snake.body)
			{
				if (part.head == false && snake.pos_x == part.pos_x && snake.pos_y == part.pos_y) { 
					return false; 
				}
			}
			//snake is alive
			return true;
		}
	};
};