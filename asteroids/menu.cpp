#include <SDL.h>
#include <stdio.h>
#include <malloc.h>

#include "game.h"
#include "menu.h"
#include "funcs.h"
#include "music.h"
#include "window.h"
#include "config.h"
#include "texture.h"

void changeTextureOptionColor(Menu& self)
{
    for (int opt = 0; opt < self.num; opt++)
    {
        SDL_DestroyTexture(self.textures[opt].tex);
        SDL_Color color = opt == self.choice ? COLOR_OF_ACTIVE_OPTION : COLOR_OF_NON_ACTIVE_OPTION;
        self.textures[opt] = loadFont(self.info[opt].name, MENU_FONTNAME, color, MENU_FONT_SIZE);
    }
}

void MenuDestroy(Menu& self)
{
    if (!self.textures) return;

    for (int opt = 0; opt < self.num; opt++)
    {
        SDL_DestroyTexture(self.textures[opt].tex);
    }
    free(self.textures);

    self.textures = NULL;
}

void MenuInit(Menu& self, const MENU_INFO* info, int optionsNum)
{
    MenuDestroy(self);

    self.ticks = SDL_GetTicks();
    self.info = info;
    self.num = optionsNum;
    self.choice = 0;

    self.textures = (Texture*)malloc(sizeof(Texture) * self.num);
    if (!self.textures)
    {
        printf("\nError in malloc for textures in MenuInit");
        deInit(1);
    }

    for (int opt = 0; opt < self.num; opt++)
        self.textures[opt] = loadFont(info[opt].name, MENU_FONTNAME, COLOR_OF_ACTIVE_OPTION, MENU_FONT_SIZE);

    self.textBlockY = (winHgt - ((MENU_FONT_SIZE + MENU_FONT_VERTICAL_DISTANCE) * self.num - MENU_FONT_VERTICAL_DISTANCE)) / 2;
    changeTextureOptionColor(self);
}

void MenuChooseOptionByMouse(Menu& self, Keys& keys, bool& cursorUnderTexture)
{
    for (int opt = 0; opt < self.num; opt++)
    {
        SDL_Point point = { keys.mouse_x, keys.mouse_y };
        cursorUnderTexture = SDL_PointInRect(&point, &self.textures[opt].dstrect);
        if (cursorUnderTexture)
        {
            self.choice = opt;
            changeTextureOptionColor(self);
            break;
        }
    }
}

void MenuChooseOptionByKbd(Menu& self, Keys& keys, int& ticks)
{
    if ((keys.up || keys.down || keys.w || keys.s) && ticks - self.ticks >= MENU_DELAY_BUTTONS)
    {
        self.ticks = ticks;
        if (keys.up || keys.w)
        {
            self.choice = self.choice ? self.choice - 1 : self.num - 1;
        }
        if (keys.down || keys.s)
        {
            self.choice = (self.choice + 1) % self.num;
        }
        changeTextureOptionColor(self);
    }
}

void MenuChangeOption(Menu& self, Keys& keys, int& gameState, int& ticks, bool& cursorUnderTexture)
{
    bool oneOfBtns = keys.space || keys.enter || (keys.leftClick && cursorUnderTexture);

    if (oneOfBtns && ticks - self.ticks >= MENU_DELAY_BUTTONS)
    {
        self.ticks = ticks;
        gameState = self.info[self.choice].mode;
        MusicEffectsPlay(MUSIC_BUTTON);

        switch (gameState)
        {
        case GAME_STATE_PLAY:
            MenuInit(self, MODE_MENU, MODE_MENU_NUM);
            break;
        }
    }
}

void MenuUpdate(Menu& self, Keys& keys, int& gameState)
{
    int ticks = SDL_GetTicks();
    bool cursorUnderTexture = false;
    bool switched = false;

    MenuChooseOptionByMouse(self, keys, cursorUnderTexture);
    if (!cursorUnderTexture)
        MenuChooseOptionByKbd(self, keys, ticks);
    
    MenuChangeOption(self, keys, gameState, ticks, cursorUnderTexture);
}

void MenuDraw(Menu& self)
{
    SDL_Rect drawRect = { 0, self.textBlockY, 0, 0};

    for (int i = 0; i < self.num; i++)
    {
        drawRect.w = self.textures[i].dstrect.w;
        drawRect.h = self.textures[i].dstrect.h;
        drawRect.x = (winWdt - drawRect.w) / 2;
        self.textures[i].dstrect = drawRect;
        SDL_RenderCopy(ren, self.textures[i].tex, NULL, &drawRect);
        drawRect.y += drawRect.h + MENU_FONT_VERTICAL_DISTANCE;
    }
}
