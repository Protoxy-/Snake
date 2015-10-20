#ifndef LIBSDL_HH_
#define LIBSDL_HH_

#include "Exception.hh"
#include "IGraph.hh"
#include "Items.hh"
#include "Snake.hh"
#include "Game.hh"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <list>

class LibSDL : virtual public IGraph
{
private:
  int           _mapX;
  int           _mapY;
  int           _anim;
  TTF_Font      *font;
  SDL_Event     event;
  SDL_Surface   *screen;
  SDL_Surface   *back_sprt;
  SDL_Surface   *snake_sprt;
  SDL_Surface   *head_sprt;
  SDL_Surface   *tail_sprt;
  SDL_Surface   *items_sprt;
  SDL_Surface   *elems_sprt;
  SDL_Surface   *toolbar_sprt;

public:
  LibSDL(int mapX, int mapY);
  ~LibSDL();
  void printSnake(int, int, int, int);
  void printMap(int, int, int);
  void printItem(int, int, int);
  void printElem(int, int, int);
  void printScore(int);
  void printLevel(int);
  void renderClear();
  void freeLib();
  void render();
  eKey getKey();
  void endAnim();
};

#endif
