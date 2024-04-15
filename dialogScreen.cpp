namespace Tmpl8
{
	class DialogLine {
	public:
		std::string textLine;
		std::string speakerName;
		//TODO: sprite
		DialogLine(std::string speakerName, std::string textLine) : speakerName(speakerName), textLine(textLine) {};
	};

	class DialogScreen
	{
		std::vector<DialogLine> dialogLines;
		int boxHeight = 180, boxMargin = 30, boxThickness = 24, boxPadding = 20;
		int textPosX, textPosY;
		int infoTextX, infoTextY, infoTextSize = 2;
		std::string infoText = "press enter";

		int currentLine = 0, currentChar = 0;
	public:
		float printSpeed = 0.1f; //delay between characters printed

		DialogScreen() {
		};

		void LoadIntroScript() {
			dialogLines.clear();
			dialogLines.push_back(DialogLine("fero", "fero vravi, fero vravi, fero vravi"));
			dialogLines.push_back(DialogLine("jozo", "jozo vravi, jozo vravi, jozo vravi"));
			dialogLines.push_back(DialogLine("fero", "fero vravi, fero vravi, fero vravi"));
		}

		void Draw() {
			textPosX = boxMargin + boxThickness + boxPadding;
			textPosY = Renderer::GetScreen()->GetHeight() - boxHeight + boxPadding;

			infoTextX = Renderer::GetScreen()->GetWidth() - (infoText.length() * 6 - 1) * infoTextSize - boxThickness - boxMargin - boxPadding/2;
			infoTextY = Renderer::GetScreen()->GetHeight() - infoTextSize*5 - boxThickness - boxMargin - boxPadding/2;
			
			//text
			Renderer::GetScreen()->PrintScaled(dialogLines[currentLine].textLine.substr(0, currentChar).c_str(), textPosX, textPosY, 0xffffff, 3);
			if(currentChar >= dialogLines[currentLine].textLine.length()) Renderer::GetScreen()->PrintScaled(infoText.c_str(), infoTextX, infoTextY, 0xffffff, infoTextSize);

			//decoration
			Renderer::DrawSpeechBox(boxHeight, boxMargin, boxThickness);
		}

		void NextChar() {
			if (currentChar < dialogLines[currentLine].textLine.length()) { //still printing
				currentChar++;
				Draw();
			}
		}

		//returns false if there are no more voice lines
		bool NextLine() {
			if (currentChar < dialogLines[currentLine].textLine.length()) {
				currentChar = dialogLines[currentLine].textLine.length();
				Draw();
			}
			else if(currentLine < dialogLines.size() - 1)
			{
				Renderer::GetScreen()->Clear(0);
				currentLine++;
				currentChar = 0;
			}
			else
			{
				return true;
			}
			return false;
		}
	};

};