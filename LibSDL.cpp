#include "LibSDL.hh"

LibSDL::LibSDL(int x, int y)
{

  _mapX = x;
  _mapY = y;
  _anim = 0;
  if((SDL_Init(SDL_INIT_EVERYTHING) == -1))
    throw errGraphic("Init");
  screen = SDL_SetVideoMode(_mapX * 48, _mapY * 48 + 64, 32, SDL_SWSURFACE);
  if (screen == NULL)
    throw errGraphic("Can't init the window");
  SDL_WM_SetCaption("Nibbler - SDL", NULL);
  if (TTF_Init() == -1)
    throw errGraphic("Can't init TTF");
  if ((font = TTF_OpenFont("Data/Font.ttf", 60)) == NULL)
    throw errGraphic("Can't load font: Font.ttf");
  if ((back_sprt = IMG_Load("Data/BackTile.png")) == NULL)
    throw errGraphic("Can't load img: BackTile.png");
  if ((snake_sprt = IMG_Load("Data/Snake.png")) == NULL)
    throw errGraphic("Can't load img: Snake.png");
  if ((head_sprt = IMG_Load("Data/SnakeHead.png")) == NULL)
    throw errGraphic("Can't load img: SnakeHead.png");
  if ((tail_sprt = IMG_Load("Data/SnakeTail.png")) == NULL)
    throw errGraphic("Can't load img: SnakeTail.png");
  if ((items_sprt = IMG_Load("Data/Items.png")) == NULL)
    throw errGraphic("Can't load img: Items.png");
  if ((elems_sprt = IMG_Load("Data/Elems.png")) == NULL)
    throw errGraphic("Can't load img: Elems.png");
  if ((toolbar_sprt = IMG_Load("Data/Toolbar.png")) == NULL)
    throw errGraphic("Can't load img: Toolbar.png");
  if (SDL_BlitSurface(back_sprt, NULL, screen, NULL) < 0)
    throw errGraphic ("Blit Surface");
  SDL_UpdateRect(screen, 0, 0, screen->w, screen->h);
}

LibSDL::~LibSDL()
{
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_Quit();
}

void LibSDL::printSnake(int  x, int  y, int  prevDir, int  nextDir)
{
  SDL_Rect  imgPos;
  SDL_Rect  winPos;
  int       pos;
  int       dir;

  winPos.x = x * 48;
  winPos.y = y * 48;
  imgPos.y = 0;
  imgPos.w = 48;
  imgPos.h = 48;
  pos = (prevDir == -1 ? 1 : (nextDir == -1 ? 2 : 0));
  if (pos == 0)
  {
    if ((prevDir == 0 && nextDir == 2) || (prevDir == 2 && nextDir == 0))
      dir = 0;
    if ((prevDir == 1 && nextDir == 3) || (prevDir == 3 && nextDir == 1))
      dir = 1;
    if ((prevDir == 0 && nextDir == 1) || (prevDir == 1 && nextDir == 0))
      dir = 2;
    if ((prevDir == 1 && nextDir == 2) || (prevDir == 2 && nextDir == 1))
      dir = 3;
    if ((prevDir == 0 && nextDir == 3) || (prevDir == 3 && nextDir == 0))
      dir = 4;
    if ((prevDir == 3 && nextDir == 2) || (prevDir == 2 && nextDir == 3))
        dir = 5;
    imgPos.x = (1 + dir * 2 + (_anim % 4) / 2) * 48;
    if (SDL_BlitSurface(snake_sprt, &imgPos, screen, &winPos) < 0)
      throw errGraphic ("Blit Surface");
  }
  else
  {
    imgPos.x = (1 + (pos == 1 ? nextDir : prevDir) * 2 + (_anim % 4) / 2) * 48;
    if (SDL_BlitSurface((pos == 1 ? head_sprt : tail_sprt), &imgPos, screen, &winPos) < 0)
      throw errGraphic ("Blit Surface");
  }

}

void LibSDL::printMap(int x, int y, int type)
{
  SDL_Rect  imgPos;
  SDL_Rect  winPos;

  imgPos.x = type * 48;
  imgPos.y = 0;
  imgPos.w = 48;
  imgPos.h = 48;
  winPos.x = x * 48;
  winPos.y = y * 48;
  if (SDL_BlitSurface(back_sprt, &imgPos, screen, &winPos) < 0)
    throw errGraphic ("Blit Surface");
}

void LibSDL::printItem(int  x, int  y, int  type)
{
  SDL_Rect  imgPos;
  SDL_Rect  winPos;

  imgPos.x = type * 48;
  imgPos.y = 0;
  imgPos.w = 48;
  imgPos.h = 48;
  winPos.x = x * 48;
  winPos.y = y * 48;
  if (SDL_BlitSurface(items_sprt, &imgPos, screen, &winPos) < 0)
    throw errGraphic ("Blit Surface");
}

void LibSDL::printElem(int  x, int  y, int  type)
{
  SDL_Rect  imgPos;
  SDL_Rect  winPos;

  imgPos.x = type * 48;
  imgPos.y = 0;
  imgPos.w = 48;
  imgPos.h = 48;
  winPos.x = x * 48;
  winPos.y = y * 48;
  if (SDL_BlitSurface(elems_sprt, &imgPos, screen, &winPos) < 0)
    throw errGraphic ("Blit Surface");
}

void   LibSDL::renderClear()
{
  SDL_Rect  winPos;
  int  i;

  for (i = 0; i * 48 < screen->w; i++)
  {
    winPos.x = i * 48;
    winPos.y = screen->h - 100;
    if (SDL_BlitSurface(toolbar_sprt, NULL, screen, &winPos) < 0)
      throw errGraphic ("Blit Surface");
  }

}

void   LibSDL::printScore(int score)
{
  SDL_Color     color = {0, 0, 0};
  SDL_Surface   *text;
  SDL_Rect      winPos;
  std::stringstream   ss;
  std::string  str;

  ss << score;
  str = "Score : " + ss.str();
  winPos.x = 20;
  winPos.y = screen->h - 70;
  text = TTF_RenderText_Blended(font, str.c_str(), color);
  if (SDL_BlitSurface(text, NULL, screen, &winPos) < 0)
    throw errGraphic ("Blit Surface");
}

void   LibSDL::printLevel(int level)
{
  SDL_Color     color = {0, 0, 0};
  SDL_Surface   *text;
  SDL_Rect      winPos;
  std::stringstream   ss;
  std::string  str;

  ss << level;
  str = "Level : " + ss.str();
  text = TTF_RenderText_Blended(font, str.c_str(), color);
  winPos.x = screen->w - text->w - 20;
  winPos.y = screen->h - 70;
  if (SDL_BlitSurface(text, NULL, screen, &winPos) < 0)
    throw errGraphic ("Blit Surface");
  }

void LibSDL::render()
{
  _anim++;
  SDL_UpdateRect(screen, 0, 0, screen->w, screen->h);
}

eKey  LibSDL::getKey()
{
  if (SDL_PollEvent(&event))
  {
    switch (event.type) {
      case SDL_QUIT:
        return (KQUIT);
        break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE:
            return (KQUIT);
            break;
          case SDLK_q:
            return (KQUIT);
            break;
          case SDLK_LEFT:
            return (KLEFT);
            break;
          case SDLK_RIGHT:
            return (KRIGHT);
            break;
          case SDLK_UP:
            return (KUP);
            break;
          case SDLK_DOWN:
            return (KDOWN);
            break;
          case SDLK_SPACE:
            return (KSPACE);
            break;
        }
    }
  }
  return (KNOTHING);
}
void LibSDL::freeLib()
{
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_Quit();
}

void LibSDL::endAnim()
{

}

extern "C"
{
  IGraph     *createRenderer(int x, int y)
  {
    return new LibSDL(x, y);
  }
}
