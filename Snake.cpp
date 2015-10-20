#include "Snake.hh"

SnakeNode::SnakeNode()
{
  _x = 0;
  _y = 0;
}

SnakeNode::SnakeNode(int x, int y)
{
  _x = x;
  _y = y;
}

SnakeNode::~SnakeNode()
{
}

int    SnakeNode::getX() const
{
  return (_x);
}

int   SnakeNode::getY() const
{
  return (_y);
}

void           SnakeNode::setX(int x)
{
  _x = x;
}

void           SnakeNode::setY(int y)
{
  _y = y;
}

Snake::Snake(int x, int y)
{
  int   i = 0;

  _x = x;
  _y = y;
  _eat = 0;
  _speed = 1;
  while (i < 4)
  {
    addNode(_x, _y++);
    i++;
  }
  _lastDir = 0;
  _y--;
}

Snake::~Snake()
{
}

int    Snake::getSize() const
{
  return (_nodes.size());
}

int    Snake::getDir() const
{
  return (_dir);
}

int     Snake::getDirPos(int x1, int y1, int x2, int y2)
{
  int   x;
  int   y;

  x = x1 - x2;
  y = y1 - y2;
  if (x == -1)
    return (0);
  if (y == -1)
    return (1);
  if (x == 1)
    return (2);
  if (y == 1)
    return (3);
  if (x1 > x2)
    return (0);
  if (y1 > y2)
    return (1);
  if (x1 < x2)
    return (2);
  if (y1 < y2)
    return (3);

}

int           Snake::getX() const
{
  return (_x);
}

int           Snake::getY() const
{
  return (_y);
}

void           Snake::setX(int x)
{
  _x = x;
}

void           Snake::setY(int y)
{
  _y = y;
}

void          Snake::setDir(int dir)
{
  _dir = dir;
}

std::list<SnakeNode*>   Snake::getNode() const
{
  return (_nodes);
}

void          Snake::addNode(int x, int y)
{
  SnakeNode   *add = new SnakeNode(x, y);

  _nodes.push_front(add);
}

void          Snake::removeNode()
{
  _nodes.pop_back();
}

void          Snake::move()
{
  _lastDir = _dir;
  if (_eat == 0)
    removeNode();
  else
    _eat = (_eat - 1 < 0 ? 0 : _eat - 1);
  if (_dir == 0)
    addNode(--_x, _y);
  if (_dir == 2)
    addNode(++_x, _y);
  if (_dir == 1)
    addNode(_x, --_y);
  if (_dir == 3)
    addNode(_x, ++_y);
}

void          Snake::moveTo(int x, int y)
{
  removeNode();
  addNode((x == -1 ? _x : (_x = x)), (y == -1 ? _y : (_y = y)));
}

void          Snake::eat()
{
  _eat++;
}

void          Snake::dammage()
{
  while (_nodes.size() > 4)
    removeNode();
}
