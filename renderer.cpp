namespace Tmpl8
{
	Surface tiles("assets/snakeR.jpg");
	Surface* gameScreen;

	static class Renderer
	{
	public:
		Renderer() {
		};

		static void SetScreen(Surface* screen) { //always init first
			gameScreen = screen;
		}
		
		static Surface* GetScreen() { 
			return gameScreen;
		}

		static void DrawTile(int screenX, int screenY, int tx, int ty) {
			Pixel* src = tiles.GetBuffer() + tx * 32 + (ty * 32) * 512;
			Pixel* dst = gameScreen->GetBuffer() + screenX + screenY * 800;
			for (int i = 0; i < 32; i++, src += 512, dst += 800)
				for (int j = 0; j < 32; j++)
					dst[j] = src[j];
		}

		static void DrawButton(int screenX, int screenY, std::string buttonText, int size) {
			int borderThickness = 5;
			for (int i = 0; i < borderThickness; i++)
			{
				gameScreen->Box(screenX - i, screenY - i, screenX + 100 + i, screenY + 50 + i, 0xffffff);
			}
			gameScreen->PrintScaled(buttonText.c_str(), screenX, screenY, 0xffffff, size);
		}
	};
};