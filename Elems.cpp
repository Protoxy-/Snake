#include "Elems.hh"

Elems::Elems(int x, int y, int type, int solid)
{
    _x = x;
    _y = y;
    _type = type;
    _solid = solid;
}

Elems::~Elems()
{

}

int Elems::getX() const
{
  return _x;
}

int Elems::getY() const
{
  return _y;
}

int Elems::getType() const
{
  return _type;
}

bool Elems::getSolid() const
{
  return _solid;
}

void Elems::setX(int x)
{
  _x = x;
}

void Elems::setY(int y)
{
  _y = y;
}

void Elems::setSolid(bool solid)
{
  _solid = solid;
}
