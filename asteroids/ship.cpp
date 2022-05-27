#include <SDL.h>
#include <math.h>

#include "ship.h"
#include "window.h"
#include "texture.h"
#include "structs.h"
#include "constants.h"

#define RADIANS 180 * M_PI

void ShipInit(Game& game, int wdt)
{
	game.ship.tex = loadTexture(SHIP_FILENAMES_TEXTURES[0]);

	game.ship.tex.dstrect.x = winWdt / 2;
	game.ship.tex.dstrect.y = winHgt / 2;
	float coeff = game.ship.tex.dstrect.w / game.ship.wdt;
	game.ship.tex.dstrect.w /= coeff;
	game.ship.tex.dstrect.h /= coeff;
}

void ShipUpdate(Game& game)
{
	if (game.keysStatus.up)
	{
		game.ship.tex.dstrect.y += sin(game.ship.tex.angle / RADIANS) * game.ship.speedMovement;
		game.ship.tex.dstrect.x += cos(game.ship.tex.angle / RADIANS) * game.ship.speedMovement;
	}

	if (game.keysStatus.left)
	{
		game.ship.tex.angle -= game.ship.speedRotation;
	}
	if (game.keysStatus.right)
	{
		game.ship.tex.angle += game.ship.speedRotation;
	}
}

void ShipDraw(Game& game)
{
	SDL_RenderCopyEx(ren, game.ship.tex.tex, NULL, &game.ship.tex.dstrect, game.ship.tex.angle, NULL, SDL_FLIP_NONE);
}