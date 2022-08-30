#include <SDL.h>

#include "window.h"
#include "health.h"
#include "config.h"

void HealthInit(Health& self, SDL_Rect rect, float point)
{
	self.point = point > 100 ? 100 : point;
	self.rect = rect;
}

void HealthUpdate(Health& self, float point)
{
	self.point -= point;
}

void HealthDraw(Health& self)
{
	SDL_Color c;

	c = COLOR_OF_NON_ACTIVE_OPTION;
	SDL_SetRenderDrawColor(ren, c.r, c.g, c.b, c.a);
	SDL_RenderFillRect(ren, &self.rect);

	SDL_Rect rect = self.rect;
	rect.w = rect.w * self.point / 100;

	c = COLOR_OF_ACTIVE_OPTION;
	SDL_SetRenderDrawColor(ren, c.r, c.g, c.b, c.a);
	SDL_RenderFillRect(ren, &rect);
}
