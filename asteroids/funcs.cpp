#include <SDL.h>
#include <math.h>

#include "funcs.h"
#include "window.h"

void sortNums(int* nums, int size, int by)
{
    for (int i = 0; i < size - 1; i++)
    {
        bool swapped = false;
        for (int j = 0; j < size - 1; j++)
        {
            bool cond;
            switch (by)
            {
            case SORTING_BY_INCREMENCE: cond = nums[j] < nums[j + 1]; break;
            case SORTING_BY_DECREMENCE: cond = nums[j] > nums[j + 1]; break;
            }
            if (cond)
                continue;
            int tmp = nums[j];
            nums[j] = nums[j+1];
            nums[j+1] = tmp;
            swapped = true;
        }
        if (!swapped)
            break;
    }
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

void fillRect(SDL_Rect& rect, const SDL_Color& col)
{
    SDL_SetRenderDrawColor(ren, col.r, col.g, col.b, col.a);
    SDL_RenderFillRect(ren, &rect);
}

SDL_Point getRectCenter(SDL_Rect& rect)
{
    return { rect.x + rect.w / 2, rect.y + rect.h / 2 };
}

float getRadius(SDL_Rect& rect)
{
    return rect.h / 2;
}

void centerizeRect(SDL_Rect& centerize, SDL_Rect& border)
{
    SDL_Point borderCenter = getRectCenter(border);
    SDL_Point centerizeCenter = getRectCenter(centerize);
    centerize.x += borderCenter.x - centerizeCenter.x;
    centerize.y += borderCenter.y - centerizeCenter.y;
}

void updateMaxValue(float& value, float maximum)
{
    if (fabs(value) > maximum)
        value = value > maximum ? maximum : -maximum;
}
