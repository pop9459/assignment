namespace Tmpl8
{
	class MenuScreen{
	public:
		MenuScreen() {
		}
		void DrawMenu() {
			Renderer::DrawButton(Renderer::GetScreen()->GetWidth()/2, Renderer::GetScreen()->GetHeight() / 2, "this button is centered", 4);
		}
	};

};