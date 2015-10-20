#include "Items.hh"

Items::Items(int x, int y, int type)
{
  _x = x;
  _y = y;
  _type = type;
  _step = 0;
}

Items::~Items()
{
}

int Items::getX() const
{
  return _x;
}

int Items::getY() const
{
  return _y;
}

int Items::getType() const
{
  return _type;
}

int Items::getStep() const
{
  return _step;
}

void Items::setX(int  x)
{
  _x = x;
}

void Items::setY(int y)
{
  _y = y;
}

void Items::setType(int type)
{
  _type = type;
  _step = 0;
}

void Items::setStep(int step)
{
  _step += step;
}
