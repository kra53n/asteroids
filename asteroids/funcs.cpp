#include <SDL.h>
#include <math.h>

#include "funcs.h"
#include "window.h"
#include "vector.h"

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

void drawBorderLine(int x1, int y1, int x2, int y2, int size, SDL_Color& col)
{
    Vec vec;
    VecSetLenByCoords(vec, { x1, y1 }, { x2, y2 });
    VecSetAngleByCoords(vec, { x1, y1 }, { x2, y2 });

    int len = VecGetLen(vec);
    int step = len / size;

    VecSetLen(vec, 1);

    int size2 = size / 2;
    SDL_FRect rect = { 0, 0, size, size };
    SDL_SetRenderDrawColor(ren, col.r, col.g, col.b, col.a);
    for (; VecGetLen(vec) <= len; VecSetLen(vec, VecGetLen(vec) + size2))
    {
        rect.x = x1 + vec.x - size2;
        rect.y = y1 + vec.y - size2;
        SDL_RenderFillRectF(ren, &rect);
    }
    SDL_SetRenderDrawColor(ren, 255, col.g, col.b, col.a);
    SDL_RenderDrawLine(ren, x1, y1, x2, y2);
}

void drawBorderRect(SDL_Rect& rect, int size, SDL_Color& col)
{
    drawBorderLine(rect.x, rect.y, rect.x + rect.w, rect.y, size, col);
    drawBorderLine(rect.x + rect.w, rect.y, rect.x + rect.w, rect.y + rect.h, size, col);
    drawBorderLine(rect.x, rect.y + rect.h, rect.x + rect.w, rect.y + rect.h, size, col);
    drawBorderLine(rect.x, rect.y, rect.x, rect.y + rect.h, size, col);
}
