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
			const int baseCharSize = 5; //each char in the base font is a 5x5 grid of pixels - we multiply this with font size to get final size
			int border = size+1;
			int padding = 5;
			int height = baseCharSize * size + padding * 2;
			int length = (baseCharSize + 1) * size * buttonText.length() + padding * 2;
			
			//input coords will be at the center of the button
			screenX -= length / 2;
			screenY -= height / 2;
			for (int i = 0; i < border; i++)
			{
				gameScreen->Box(screenX - i, screenY - i, screenX + length + i, screenY + height + i, 0xffffff);
			}
			gameScreen->PrintScaled(buttonText.c_str(), screenX + padding, screenY + padding, 0xffffff, size);
		}
	};
};