#include "funcs.h"

bool isPointInRect(const SDL_Rect& rect, SDL_Point& point)
{
	return (rect.x <= point.x && point.x <= rect.x + rect.w) &&
		(rect.y <= point.y && point.y <= rect.y + rect.h);
}

bool isCircsColliding(SDL_Point p1, float r1, SDL_Point p2, float r2)
{
	int x = p2.x - p1.x;
	int y = p2.y - p1.y;
	int r = r2 + r1;
	return x*x + y*y < r*r;
}

bool isPointInCirc(SDL_Point circ, float r, SDL_Point p)
{
    int x = circ.x - p.x;
    int y = circ.y - p.y;
    return x*x + y*y < r*r;
}
