#ifndef IGRAPH_HH_
#define IGRAPH_HH_

#include <list>
#include "Items.hh"
#include "Snake.hh"

enum eKey
{
  KNOTHING,
  KLEFT,
  KRIGHT,
  KUP,
  KDOWN,
  KSPACE,
  KQUIT
};

class IGraph
{
protected:
  int   _mapX;
  int   _mapY;
public:
  virtual void printSnake(int, int, int, int) = 0;
  virtual void printMap(int, int, int) = 0;
  virtual void printItem(int, int, int) = 0;
  virtual void printElem(int, int, int) = 0;
  virtual void printScore(int) = 0;
  virtual void printLevel(int) = 0;
  virtual void renderClear() = 0;
  virtual void freeLib() = 0;
  virtual void render() = 0;
  virtual eKey getKey() = 0;
  virtual void endAnim() = 0;
};

#endif
