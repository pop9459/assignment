#include "game.h"
#include "surface.h"


namespace Tmpl8
{
	Surface tiles("assets/snakeR.jpg");
	
	class Renderer
	{
	public:
		Renderer() {
		};
		
		void DrawTile(int screenX, int screenY, Surface* gameScreen, int tx, int ty) {
			Pixel* src = tiles.GetBuffer() + tx * 32 + (ty * 32) * 512;
			Pixel* dst = gameScreen->GetBuffer() + screenX + screenY * 800;
			for (int i = 0; i < 32; i++, src += 512, dst += 800)
				for (int j = 0; j < 32; j++)
					dst[j] = src[j];
		}
	};
};