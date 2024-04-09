namespace Tmpl8
{
	class MenuScreen{
	public:
		MenuScreen() {
		}
		void DrawMenu() {
			Renderer::DrawButton(100, 50, "text text so much text", 1);
			Renderer::DrawButton(100, 100, "text text so much text", 2);
			Renderer::DrawButton(100, 150, "text text so much text", 3);
			Renderer::DrawButton(100, 200, "text text so much text", 4);
		}
	};

};