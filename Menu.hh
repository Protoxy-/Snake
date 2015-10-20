#ifndef MENU_HH_
#define MENU_HH_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "Game.hh"

class   Menu
{
  int           mouseX;
  int           mouseY;
  int           click;
  int           end;
  int           lib;
  int           level;
  int           hard;
  int           speed;
  int           item;
  int           number;
  TTF_Font      *font;
  SDL_Event     event;
  SDL_Surface   *screen;
  SDL_Surface   *back_sprt;

public:
  Menu();
  ~Menu();

  void  checkKey();
  void  interfaceIteraction();
  void  display();
  void  loop();
  void  start();
};


#endif
