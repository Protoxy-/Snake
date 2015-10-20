#ifndef GAME_HH_
#define GAME_HH_

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <unistd.h>
#include <string.h>

#include "Snake.hh"
#include "IGraph.hh"
#include "Items.hh"
#include "Elems.hh"
#include "Exception.hh"

class LibSDL;
class Snake;
class Items;
class Elems;
class IGraph;

class Game
{
private:
  Snake               *_snake;
  unsigned long int   _stp;
  int                 _end;
  int                 _mapX;
  int                 _mapY;
  int                 _mov;
  int                 _score;
  int                 _level;
  int                 _point;
  int                 _speed;
  int                 _careerMode;
  int                 _gameMode;
  int                 _backType;
  int                 _foodStat;
  int                 _iaHard;
  int                 _itemMax;
  int                 _itemLife;
  int                 _itemSpeed;
  int                 _itemFreq;
  IGraph  *renderer;
  std::list<Items*>    _items;
  std::list<Elems*>    _elems;

public:
  Game(int, int);
  Game(int, int, int, int, int);
  ~Game();

  void    getMap(int);
  void    changeMap();
  int     checkContact(int, int);
  void    keyAction();
  int     getNbItems(int);
  int     headContact();
  void    generateItems();
  void    itemsAction();
  void    snakeAction();
  void    envIteraction();
  void    gameLoop();
  void    display();
  void    displaySnake();
  void    initLib(std::string lib);
};
#endif
