#ifndef ITEM_HH_
#define ITEM_HH_

#include "Game.hh"

enum eType {
  NOTHING,
  SPEED,
  SLOW,
  SCORE_MULT,
  SCORE_DECREMENT,
};

class Items {
protected:
  int     _x;
  int     _y;
  int     _type;
  int     _step;

public:
  Items(int, int, int);
  ~Items();
  int getX() const;
  int getY() const;
  int getType() const;
  int getStep() const;
  void setX(int);
  void setY(int);
  void setType(int);
  void setStep(int);
};

#endif
