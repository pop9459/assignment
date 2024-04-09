namespace Tmpl8
{
	class Button
	{
		int posX, posY, size, width, height, border, padding, textColor, borderColor;
		std::string buttonText;
	public:
		bool mouseOver = false;
		Button(int centerX, int centerY, std::string text, int scale, int textColor=0xffffff, int borderColor = 0xffffff) {
			posX = centerX;
			posY = centerY;
			buttonText = text;
			size = scale;
			Button::textColor = textColor;
			Button::borderColor = borderColor;
			const int baseCharSize = 5; //each char in the base font is a 5x5 grid of pixels - we multiply this with font size to get final size
			border = scale + 1;
			padding = 5;
			height = baseCharSize * scale + padding * 2;
			if (width == 0) { width = (baseCharSize + 1) * scale * text.length() + padding * 2; } //auto calculate width based on text length if not 
		}
		void Draw() {
			Renderer::DrawBoxedText(posX, posY, buttonText, size, width, height, padding, border, textColor, borderColor);
		}
		bool MouseOver(int mouseX, int mouseY) {
			bool mouseOn = mouseX >= posX - width / 2 && mouseX <= posX + width / 2 && mouseY >= posY - height / 2 && mouseY <= posY + height / 2;
			if (mouseOn != mouseOver) {
				mouseOn ? OnMouseEnter() : OnMouseExit();
				mouseOver = mouseOn;
			}
			return mouseOn;
		}
		void OnMouseEnter() {
			std::cout << "entered\n";
			borderColor = 0x0000ff;
		}
		void OnMouseExit() {
			std::cout << "exit\n";
			borderColor = 0x000000;
		}
	};

	class MenuScreen{
	public:
		std::vector<Button> buttons;
		MenuScreen() {}
		void Init() {
			buttons.push_back(Button(Renderer::GetScreen()->GetWidth() / 2, Renderer::GetScreen()->GetHeight() / 2, "Start button", 4));
		}
		void DrawMenu() {
			for each (Button button in buttons)
			{
				button.Draw();
			}
		}
	};
};