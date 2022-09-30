#include <malloc.h>

#include <SDL.h>

#include "config.h"
#include "texture.h"
#include "ui_comps.h"

void UI_ComponentTextInit(UI_Component& self)
{
    if (self.textTexture.tex)
        SDL_DestroyTexture(self.textTexture.tex);
    self.textTexture = loadFont(self.text, MENU_FONTNAME, *self.nactCol, self.hgt);
}

void UI_ComponentButtonUpdate(UI_Component& self, bool selected)
{
    SDL_Color col = selected ? *self.actCol : *self.nactCol;
    if (self.textTexture.tex)
        SDL_DestroyTexture(self.textTexture.tex);
    self.textTexture = loadFont(self.text, MENU_FONTNAME, col, self.hgt);
}

void UI_ComponentCheckbuttonUpdate(UI_Component& self, bool selected)
{
}

void UI_ComponentScaleUpdate(UI_Component& self, bool selected, int move)
{
    switch (move)
    {
    case UI_SCALE_LEFT:
        self.curScale = self.curScale > 0 ? --self.curScale : 0;
        break;
    case UI_SCALE_RIGHT:
        self.curScale = self.curScale < self.maxScale ? ++self.curScale : self.maxScale;
        break;
    }
}

UI_Component* UI_GetComponent(int type, const char* text, SDL_Color& actCol,
    SDL_Color& nactCol, bool act = true, int minScale = 0, int maxScale = 0,
    int curScale = 0)
{
    UI_Component* comp = (UI_Component*)malloc(sizeof(UI_Component));

    comp->type = type;
    comp->act = act;
    comp->text = text;
    comp->actCol = &actCol;
    comp->nactCol = &nactCol;
    comp->minScale = minScale;
    comp->maxScale = maxScale;
    comp->ticks = SDL_GetTicks();

    UI_ComponentTextInit(*comp);

    switch (comp->type)
    {
    case UI_BUTTON:
        UI_ComponentButtonUpdate(*comp, false);
        break;
    case UI_CHECKBUTTON:
        UI_ComponentCheckbuttonUpdate(*comp, false);
        break;
    case UI_SCALE:
        UI_ComponentScaleUpdate(*comp, false, -1);
        break;
    }

    return comp;
}

void UI_ComponentCheckButtonDraw(UI_Component& self)
{

}

void UI_ComponentScaleDraw(UI_Component& self)
{

}

void UI_ComponentDraw(UI_Component& self)
{
    SDL_RenderCopy(ren, self.textTexture.tex, 0, &self.textTexture.dstrect);

    switch (self.type)
    {
    case UI_CHECKBUTTON:
        UI_ComponentCheckButtonDraw(self);
        break;
    case UI_SCALE:
        UI_ComponentScaleDraw(self);
        break;
    }
}
