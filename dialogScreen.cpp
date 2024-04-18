#include <vector>
#include <sstream>

namespace Tmpl8
{
	class DialogLine {
	public:
		std::string textLine;
		std::string speakerName;
		Sprite& characterImage;
		int side;
		DialogLine(std::string speakerName, Sprite& characterImage, int side, std::string textLine)
			: speakerName(speakerName), characterImage(characterImage), side(side), textLine(textLine) {};
	};

	Sprite mainChar(new Surface("assets/mainCharL.png"), 1);
	Sprite arcadeOwner(new Surface("assets/arcadeOwnerL.png"), 1);

	class DialogScreen
	{
		std::vector<DialogLine> dialogLines;
		int boxHeight = 180, boxMargin = 30, boxThickness = 24, boxPadding = 14;
		int textPosX, textPosY;
		int infoTextX, infoTextY, dialogTextSize = 3, infoTextSize = 2;
		std::string infoText = "press enter";

		int currentLine = 0, currentChar = 0;
	public:
		float printSpeed = 0.025f; //delay between characters printed

		DialogScreen() {
			LoadIntroScript();
		};

		std::vector<std::string> splitStringBy(std::string inputStr, char delimiter) {
			std::vector<std::string> substrings;
			std::istringstream tokenStream(inputStr);
			std::string token;

			while (std::getline(tokenStream, token, delimiter)) {
				substrings.push_back(token);
			}

			return substrings;
		}

		void ResetDialogScreen() {
			currentLine = 0;
			currentChar = 0;
			dialogLines.clear();

		}

		void LoadIntroScript() {
			ResetDialogScreen();
			dialogLines.push_back(DialogLine("You", mainChar, 1, "* walking down the street *"));
			dialogLines.push_back(DialogLine("You", mainChar, 1, "* thinks to himself *"));
			dialogLines.push_back(DialogLine("You", mainChar, 1, "man, what a day"));
			dialogLines.push_back(DialogLine("You", mainChar, 1, "I'm so tired, I should stop somewhere"));
			dialogLines.push_back(DialogLine("You", mainChar, 1, "* looks across the street *"));
			dialogLines.push_back(DialogLine("You", mainChar, 1, "hey I think that is the arcade Mark\ntold me to check out"));
			dialogLines.push_back(DialogLine("You", mainChar, 1, "well why not, I still have some time"));
			dialogLines.push_back(DialogLine("You", mainChar, 1, "..."));
			dialogLines.push_back(DialogLine("You", mainChar, 1, "* walks in *"));
			dialogLines.push_back(DialogLine("You", mainChar, 1, "hmm, doesn't look like it's open"));
			dialogLines.push_back(DialogLine("You", mainChar, 1, "well it was worth the try"));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "Hey! You there! Come over here!"));
			dialogLines.push_back(DialogLine("You", mainChar, 1, "What?, Uh..."));
			dialogLines.push_back(DialogLine("You", mainChar, 1, "I'm sorry I didn't..."));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "Uh, I mean..."));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "I'm sorry, let me try that again"));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "..."));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "Welcome!"));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "What can I do for you?"));
			dialogLines.push_back(DialogLine("You", mainChar, 1, "Ummm, I would like to..."));
			dialogLines.push_back(DialogLine("You", mainChar, 1, "play some games?"));
			dialogLines.push_back(DialogLine("You", mainChar, 1, "I'm sorry. Am I at the wrong place?"));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "Ah, yes, yes, right!"));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "You absolutely are at the right place"));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "If fact..."));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "You Couldn't Have Come to a better\nplace!"));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "This very arcade is the only place\nwhere you can become a certified\npro gamer!"));
			dialogLines.push_back(DialogLine("You", mainChar, 1, "Hmm, okay, that sounds...interesting"));
			dialogLines.push_back(DialogLine("You", mainChar, 1, "So what is the certificate for\nexactly?"));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "Umm, well..."));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "it is pretty cool..."));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "and it shure does look cool on your\ndesk!"));
			dialogLines.push_back(DialogLine("You", mainChar, 1, "Ahhh, yeah I think I'll just..."));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "Woah! Not so fast!"));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "I can see that you're excited but\nfirst things first"));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "It's not that simple..."));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "In order for you to become\na pro gamer you must\nfirst prove yourself!"));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "Here is the deal..."));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "I'll honor you with the certificate\nif you can beat all my highscores"));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "So why don't you try if for yourself?"));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "* starts walking away *"));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "* disapears behind a corner *"));
			dialogLines.push_back(DialogLine("You", mainChar, 1, "..."));
			dialogLines.push_back(DialogLine("You", mainChar, 1, "But sir! I don't see any games here"));
			dialogLines.push_back(DialogLine("You", mainChar, 1, "..."));
			dialogLines.push_back(DialogLine("You", mainChar, 1, "Sir?"));
			dialogLines.push_back(DialogLine("You", mainChar, 1, "..."));
			dialogLines.push_back(DialogLine("You", mainChar, 1, "* walks around the corner *"));
			dialogLines.push_back(DialogLine("You", mainChar, 1, "* sees the worker plugging in an old\narcade cabinet *"));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "There..."));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "I present to you..."));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "The worm!"));
			dialogLines.push_back(DialogLine("You", mainChar, 1, "* looks at the game *"));
			dialogLines.push_back(DialogLine("You", mainChar, 1, "Hmm, It looks like Snake"));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "Snake?"));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "Never heard of that one..."));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "Anyway..."));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "The goal is to collect theese\ncherries to grow as large\nas possible..."));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "But if you hit a wall or your tail\nyou die!"));
			dialogLines.push_back(DialogLine("You", mainChar, 1, "actually, that sounds exactly like\nsnake"));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "I still dont have any idea what\nare you talking about bud"));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "Anyway..."));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "Here you go, have fun!"));
		}

		void LoadOutroScript() {
			ResetDialogScreen();
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "Oh you did it!"));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "Nice work!"));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "..."));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "Now, this is a bit awkward..."));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "Remember when I told you that you\nmust beat all of my highscores?"));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "Well I'm going to be honest..."));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "As it happends, I'm still a bit new\nto this arcade business..."));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "And I don't really have any more\ngames here yet"));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "..."));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "But I guess that means you did it!"));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "Congratulations, you are now\nofficially a pro!"));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "* gives you the certificate *"));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "But I'll tell you the truth buddy..."));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "Being a gamer isn't about chasing\nhighscores, trying to beat anyone or\nanything like that..."));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "It's about having fun, being with\nfriends and having a good time"));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "So what do you say? Meet me here next\nweek?"));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "I should have some more games up and\nrunning by then"));
			dialogLines.push_back(DialogLine("fero", mainChar, 1, "You know what?"));
			dialogLines.push_back(DialogLine("fero", mainChar, 1, "That sounds like a great idea,\nI'll stop by with some more friends\nnext time"));
			dialogLines.push_back(DialogLine("fero", mainChar, 1, "And you are right, I really do feel\na lot more refreshed now!"));
			dialogLines.push_back(DialogLine("fero", mainChar, 1, "Thank's for the certificate!\nI'm definitely hanging this on the\nwall"));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "Glad to hear you like it"));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "Well, I guess this is it for today,\nI still got some work to do here"));
			dialogLines.push_back(DialogLine("fero", mainChar, 1, "Yea I'll be going then"));
			dialogLines.push_back(DialogLine("fero", mainChar, 1, "So see you next time"));
			dialogLines.push_back(DialogLine("Owner", arcadeOwner, 0, "Sounds like a deal!"));
			dialogLines.push_back(DialogLine("fero", mainChar, 1, "Oh and one more thing"));
			dialogLines.push_back(DialogLine("fero", mainChar, 1, "When you're going to be ordering new\ngames, dont get the snake"));
			dialogLines.push_back(DialogLine("fero", mainChar, 1, "The worm is definitely much better"));
			dialogLines.push_back(DialogLine("fero", mainChar, 1, "* hears a slight giggle as he walks\nout *"));
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
			
			std::string lineToPrint = dialogLines[currentLine].textLine.substr(0, currentChar);
			std::vector<std::string> lines = splitStringBy(lineToPrint, '\n');

			//images
			DrawAvatar(dialogLines[currentLine].characterImage, dialogLines[currentLine].side);
			
			//decoration
			Renderer::DrawSpeechBox(boxHeight, boxMargin, boxThickness);
			
			//text
			for (int i = 0; i < lines.size(); i++) {
				Renderer::GetScreen()->PrintScaled(lines[i].c_str(), textPosX, textPosY + i * 8 * dialogTextSize, 0xffffff, dialogTextSize);
			}
			if(currentChar >= dialogLines[currentLine].textLine.length()) Renderer::GetScreen()->PrintScaled(infoText.c_str(), infoTextX, infoTextY, 0xffffff, infoTextSize);
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
				Draw();
			}
			else
			{
				return true;
			}
			return false;
		}

		void Skip() {

		}
	};

};