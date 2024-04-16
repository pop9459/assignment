namespace Tmpl8
{
	class DialogLine {
	public:
		std::string textLine;
		std::string speakerName;
		Sprite& characterImage;
		int side;
		//TODO: sprite
		DialogLine(std::string speakerName, Sprite& characterImage, int side, std::string textLine)
			: speakerName(speakerName), characterImage(characterImage), side(side), textLine(textLine) {};
	};

	Sprite mainChar(new Surface("assets/mainCharL.png"), 1);
	Sprite arcadeOwner(new Surface("assets/arcadeOwnerL.png"), 1);

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
			LoadIntroScript();
			
		};

		void ResetDialogScreen() {
			currentLine = 0;
			currentChar = 0;
			dialogLines.clear();

		}

		void LoadIntroScript() {
			ResetDialogScreen();
			dialogLines.push_back(DialogLine("You", mainChar, 1, "fero vravi, fero vravi, fero vravi"));
			dialogLines.push_back(DialogLine("jozo", arcadeOwner, 0, "jozo vravi, jozo vravi, jozo vravi"));
			dialogLines.push_back(DialogLine("fero", mainChar, 1, "fero vravi, fero vravi, fero vravi"));
		}

		void LoadOutroScript() {
			ResetDialogScreen();
			dialogLines.push_back(DialogLine("fero", mainChar, 1, "outro text, outro text"));
		}

		void DrawAvatar(Sprite& avatar, int pos) {
			int posX, posY;

			posY = Renderer::GetScreen()->GetHeight() - boxHeight - boxThickness - avatar.GetHeight();
			if (pos == 0) posX = boxMargin * 2; //left
			else posX = Renderer::GetScreen()->GetWidth() - boxMargin * 2 - avatar.GetWidth(); //right

			avatar.Draw(Renderer::GetScreen(), posX, posY);
		}

		void Draw() {
			//positional variables
			textPosX = boxMargin + boxThickness + boxPadding;
			textPosY = Renderer::GetScreen()->GetHeight() - boxHeight + boxPadding;

			infoTextX = Renderer::GetScreen()->GetWidth() - (infoText.length() * 6 - 1) * infoTextSize - boxThickness - boxMargin - boxPadding/2;
			infoTextY = Renderer::GetScreen()->GetHeight() - infoTextSize*5 - boxThickness - boxMargin - boxPadding/2;
			
			//text
			Renderer::GetScreen()->PrintScaled(dialogLines[currentLine].textLine.substr(0, currentChar).c_str(), textPosX, textPosY, 0xffffff, 3);
			if(currentChar >= dialogLines[currentLine].textLine.length()) Renderer::GetScreen()->PrintScaled(infoText.c_str(), infoTextX, infoTextY, 0xffffff, infoTextSize);


			//decoration
			Renderer::DrawSpeechBox(boxHeight, boxMargin, boxThickness);

			//images
			DrawAvatar(dialogLines[currentLine].characterImage, dialogLines[currentLine].side);
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