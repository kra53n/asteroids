#include "funcs.h"

bool isPointInRect(const SDL_Rect& rect, SDL_Point& point)
{
	return (rect.x <= point.x && point.x <= rect.x + rect.w) &&
		(rect.y <= point.y && point.y <= rect.y + rect.h);
}
