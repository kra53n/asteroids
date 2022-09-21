#include <SDL.h>

#include "funcs.h"
#include "window.h"
#include "health.h"
#include "config.h"

void HealthInit(Health& self, SDL_Rect rect, float point)
{
    self.point = point;
    self.rect = rect;
}

void HealthUpdate(Health& self, float point)
{
    self.point -= point;
}

void HealthDraw(Health& self)
{
    SDL_Rect curHpRect = self.rect;
    curHpRect.w = curHpRect.w * self.point / 100;

    fillRect(self.rect, COLOR_OF_NON_ACTIVE_OPTION);
    fillRect(curHpRect, COLOR_OF_ACTIVE_OPTION);
}
