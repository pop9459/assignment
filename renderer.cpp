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
		
		static void DrawCenteredText(int screenX, int screenY, std::string text, int size, int color = 0xffffff) {
			const int baseCharSize = 5; //each char in the base font is a 5x5 grid of pixels - we multiply this with font size to get final size
			int posX = screenX - ((baseCharSize + 1) * size * text.length())/2;
			int posY = screenY - (baseCharSize * size)/2;
			gameScreen->PrintScaled(text.c_str(), posX, posY, color, size);
		}

		static void DrawBoxedText(int screenX, int screenY, std::string buttonText, int size, int width, int height, int padding, int border, int textColor = 0xffffff, int borderColor = 0xffffff) {
			//input coords will be at the center of the button
			screenX -= width / 2;
			screenY -= height / 2;
			for (int i = 0; i < border; i++)
			{
				gameScreen->Box(screenX - i, screenY - i, screenX + width + i, screenY + height + i, borderColor);
			}
			gameScreen->PrintScaled(buttonText.c_str(), screenX + padding, screenY + padding, textColor, size);
		}
		
		static void DrawSpeechBox(int height = 200, int margin = 50, int thickness = 25) {
			int startX = margin + thickness;
			int endX = gameScreen->GetWidth() - margin - thickness;

			int startY = gameScreen->GetHeight() - height - thickness;
			int endY = gameScreen->GetHeight() - margin;

			for (int i = 0; i <= thickness; i++)
			{
				if (i % 8 == 0) {
					gameScreen->Box(startX - i, startY + i, endX + i, endY - i, 0xffffff);
				}
				//debug
				//if(i == 0) gameScreen->Box(startX - i, startY + i, endX + i, endY - i, 0xff0000);
			}
		}
	};
};