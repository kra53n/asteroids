#include <stdio.h>

#include "score.h"
#include "config.h"
#include "window.h"
#include "texture.h"

void ScoreInit(Score& self, SDL_Rect pos, int point, char title[])
{
    self.point = point;
    self.title = title;
    self.tex.dstrect.x = pos.x;
    self.tex.dstrect.y = pos.y;

    ScoreUpdate(self);
}

void ScoreUpdate(Score& self, int point)
{
    self.point += point;

    char message[120];
    sprintf_s(message, 120, "%s%d", self.title, self.point);

    if (self.tex.tex)
        SDL_DestroyTexture(self.tex.tex);

    self.tex = loadFont(message, SCORE_FONTNAME, COLOR_OF_NON_ACTIVE_OPTION, SCORE_FONT_SIZE);
}

void ScoreDraw(Score& self)
{
    SDL_RenderCopy(ren, self.tex.tex, 0, &self.tex.dstrect);
}
