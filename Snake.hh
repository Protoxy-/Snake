#ifndef SNAKE_HH_
#define SNAKE_HH_

#include <string>
#include <iostream>
#include <list>
#include <cstdlib>

#include "Items.hh"

class   Items;
class   Elems;

class   SnakeNode{
private:
  int   _x;
  int   _y;
public:
  SnakeNode();
  SnakeNode(int, int);
  ~SnakeNode();

  int   getX() const;
  int   getY() const;
  void  setX(int);
  void  setY(int);
};

class                   Snake{
private:
  std::list<SnakeNode*> _nodes;
  int                   _speed;
  int                   _eat;
  int                   _dir;
  int                   _lastDir;
  int                   _x;
  int                   _y;

public:
  Snake(int const, int const);
  ~Snake();

  int        getSize() const;
  int        getDir() const;
  void       setDir(int dir);
  int        getDirPos(int, int, int, int);
  int        getX() const;
  int        getY() const;
  void       setX(int);
  void       setY(int);

  std::list<SnakeNode*>  getNode() const;
  void                   addNode(int x, int y);
  void                   removeNode();
  void                   move();
  void                   moveTo(int, int);
  void                   eat();
  void                   dammage();
};

#endif /* SNAKE_HPP_ */
