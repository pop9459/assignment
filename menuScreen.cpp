namespace Tmpl8
{
	class MenuScreen{
	public:
		MenuScreen() {
		}
		void DrawMenu() {
			Renderer::DrawButton(100, 100, "text", 3);
		}
	};

};