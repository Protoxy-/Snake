#ifndef LIBCURSES_HH_
#define LIBCURSES_HH_

#include "Exception.hh"
#include "IGraph.hh"
#include "Items.hh"
#include "Snake.hh"
#include "Game.hh"
#include <curses.h>
#include <list>

class LibCurses : virtual public IGraph
{
private:
  int   _mapX;
  int   _mapY;
public:
  LibCurses(int mapX, int mapY);
  ~LibCurses();
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
