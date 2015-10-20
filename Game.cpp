#include <dlfcn.h>
#include <sstream>
#include <cstdlib>
#include "Game.hh"

#include <iostream>


Game::Game(int sizeX, int sizeY)
{
  _snake = new Snake(5, 5);
  _end = 0;
  _mapX = sizeX;
  _mapY = sizeY;
  _mov = 0;
  _score = 0;
  _level = 0;
  _point = 1;
  _foodStat = 0;
  _gameMode = 0;
  _backType = 1 + rand() % 7;
  _speed = 2;
  _itemSpeed = 5;
  _itemMax = 1 + (_mapX * _mapY) / 200;
  _itemLife = 1;
  _iaHard = 3;
  _careerMode = 0;
  _itemFreq = 1;
}

Game::Game(int level, int hard, int speed, int itemSpeed, int itemFreq)
{
  _snake = new Snake(5, 5);
  _end = 0;
  _mapX = 26;
  _mapY = 20;
  _mov = 0;
  _score = 0;
  _point = 1;
  _foodStat = 0;
  _speed = speed - 1;
  _iaHard = (hard == 4 ? 8 : (hard == 3 ? 5 : hard));
  _careerMode = (level == 0 ? 1 : 0);
  _level = (level != -1 ? level + 1 : -1);
  _itemSpeed = itemSpeed;
  _itemMax = (itemFreq != -1 || itemFreq == 10 ? itemFreq + 1:  -1);
  _itemFreq = 1;
}


Game::~Game()
{
  delete _snake;
}

void    Game::getMap(int level)
{
  std::string         fileName;
  std::string         line;
  std::stringstream   mapName;
  int                 defVal;
  int                 i;
  int                 j;

  mapName << level;
  fileName = "Map/Level-" + mapName.str();
  std::ifstream       map(fileName.c_str());
  defVal = 0;
  if (map.is_open())
  {
    _mapX = 0;
    i = 0;
    while (getline(map, line))
    {
      if (line.size() > _mapX)
        _mapX = line.size();
      if (i == 0 && line[0] == '{')
      {
	       for (j = 0; line[j]; j++)
	       {
           if (line[j] >= '0' && line[j] <= '9')
	          switch (j)
	          {
	           case 1:
	             _gameMode = (line[j] - '0');
               break;
             case 2:
              if (_iaHard == -1)
               _iaHard = (line[j] - '0');
               break;
	           case 3:
	            _backType = (line[j] - '0');
              break;
            case 5:
              if (_itemSpeed == -1)
                _itemSpeed = (line[j] - '0');
              break;
            case 6:
              if (_itemMax == -1)
                _itemMax = (line[j] - '0') + 1;
              break;
            case 7:
              _itemLife = (line[j] - '0') + 1;
              break;
            case 8:
              if (_itemFreq == -1)
                _itemFreq = (line[j] - '0') + 1;
              break;
            case 9:
              _snake->setDir((line[j] - '0'));
              break;
	         }
	       }
      }
      if (i == 0 && line[0] != '{')
        defVal = 1;
      if (line[0] != '{')
      {
	       for (j = 0; line[j]; j++)
	        {
            if (line[j] == '#')
            {
              if (_snake->getSize() == 4)
                while (_snake->getSize() != 0)
                  _snake->removeNode();
              _snake->addNode(j , i - 1);
              if (_snake->getSize() == 4)
              {
                _snake->setX(j);
                _snake->setY(i - 1);
              }
            }
	           if (line[j] >= '0' && line[j] <= '9')
	             _items.push_back(new Items(j, i - 1, line[j] - '0'));
	           if (line[j] >= 'a' && line[j] <= 'z')
               _elems.push_back(new Elems(j, i - 1,
               (line[j] - 'a' < 2 ? (((line[j] - 'a') * 4) + rand() % 4) : line[j] - 'a' + 6), 0));
             if (line[j] >= 'A' && line[j] <= 'Z')
               _elems.push_back(new Elems(j, i - 1,
               (line[j] - 'A' < 2 ? (((line[j] - 'A') * 4) + rand() % 4) : line[j] - 'A' + 6), 1));
	        }
      }
      i++;
    }
    map.close();
  }
  else
    throw errExcept("Open fail");
  _mapY = i - 1;
}

void    Game::changeMap()
{
  if (_score > 100 * _level)
  {
    while (_items.size() != 0)
      _items.pop_front();
    while (_elems.size() != 0)
      _elems.pop_front();
    while (_snake->getSize() != 0)
      _snake->removeNode();
    std::cout << _elems.size() << std::endl;
    if (_level == 10)
    {
      std::cout << "Congradulation you win !\n You are the best !!!" << std::endl;
      _end = 1;
      return;
    }
    getMap(++_level);
  }
}

int     Game::checkContact(int x, int y)
{
  std::list<SnakeNode*>           nodes;
  std::list<SnakeNode*>::iterator nodeIt;
  std::list<Items*>::iterator     itemIt;
  std::list<Elems*>::iterator     elemIt;

  if (x < 0 || x == _mapX || y < 0 || y == _mapY)
    return (1);
  for (itemIt = _items.begin(); itemIt != _items.end(); itemIt++)
  {
    if (x == (*itemIt)->getX() && y == (*itemIt)->getY())
      return ((*itemIt)->getType() + 2);
  }
  for (elemIt = _elems.begin(); elemIt != _elems.end(); elemIt++)
  {
    if (x == (*elemIt)->getX() && y == (*elemIt)->getY() && (*elemIt)->getSolid() == true)
      return (1);
  }
  nodes = _snake->getNode();
  for (nodeIt = nodes.begin(); nodeIt != nodes.end(); nodeIt++)
  {
    if (x == (*nodeIt)->getX() && y == (*nodeIt)->getY())
      return (1);
  }
  return (0);
}

void    Game::keyAction()
{
  eKey key;
  int  dir;

  key = renderer->getKey();
  if (key == KLEFT)
    _mov--;
  if (key == KRIGHT)
    _mov++;
  if (_mov >= -1 && _mov <= 1)
  {
    dir = _snake->getDir() + (key == KLEFT ? -1 : (key == KRIGHT ? +1 : 0));
    dir = (dir < 0 ? 3 : (dir > 3 ? 0 : dir));
    _snake->setDir(dir);
    if (key == KQUIT)
      _end = 1;
  }
}

int     Game::getNbItems(int type)
{
  std::list<Items*>::iterator     itemIt;
  int                             i;

  i = 0;
  for (itemIt = _items.begin(); itemIt != _items.end(); itemIt++)
  {
    if ((*itemIt)->getType() == type)
      i++;
  }
  return (i);
}


int    Game::headContact()
{
  std::list<SnakeNode*>           nodes;
  std::list<SnakeNode*>::iterator nodeIt;
  std::list<Items*>::iterator     itemIt;
  std::list<Elems*>::iterator     elemIt;
  int                             i;
  int                             x;
  int                             y;


  x = _snake->getX();
  y = _snake->getY();
  if ((_gameMode == 0 && (x < 0 || x >= _mapX || y < 0 || y >= _mapY)) ||
      (_gameMode == 2 && (y < 0 || y >= _mapY)) ||
      (_gameMode == 3 && (x < 0 || x >= _mapX)))
    return (1);
  for (itemIt = _items.begin(); itemIt != _items.end(); itemIt++)
  {
    if ((*itemIt)->getType() == 8 && (*itemIt)->getStep() > 1)
      (*itemIt)->setType(9);
    if ((*itemIt)->getType() == 9 && (*itemIt)->getStep() > 2)
      (*itemIt)->setType(10);
    if ((*itemIt)->getType() != 8 && x == (*itemIt)->getX() && y == (*itemIt)->getY())
    {
      i = (*itemIt)->getType() + 2;
      (*itemIt)->setType(8);
      return (i);
    }
    if ((*itemIt)->getType() == 10 && (*itemIt)->getStep() > 20)
    {
      _items.remove(*itemIt);
      break;
    }
  }
  for (elemIt = _elems.begin(); elemIt != _elems.end(); elemIt++)
  {
    if (x == (*elemIt)->getX() && y == (*elemIt)->getY() && (*elemIt)->getSolid() == true)
      return (1);
  }
  nodes = _snake->getNode();
  i = 0;
  for (nodeIt = nodes.begin(); nodeIt != nodes.end(); nodeIt++)
  {
    if (i > 1 && x == (*nodeIt)->getX() && y == (*nodeIt)->getY())
      return (1);
    i++;
  }
  return (0);
}

void    Game::generateItems()
{
  int   chk;
  int   x;
  int   y;


  if (getNbItems(0) < _itemMax)
  {
    while (checkContact((x = rand() % _mapX), (y = rand() % _mapY)) != 0);
    _items.push_back(new Items(x, y, 0));
    _foodStat++;
  }
  if (getNbItems(1) < _itemMax && _foodStat == 15)
  {
    _foodStat = 0;
    while (checkContact((x = rand() % _mapX), (y = rand() % _mapY)) != 0);
    _items.push_back(new Items(x, y, 1));
  }
  if (getNbItems(2) < _itemMax && _stp % 400 == 0)
  {
    while (checkContact((x = rand() % _mapX), (y = rand() % _mapY)) != 0);
    _items.push_back(new Items(x, y, 2));
  }
  if (getNbItems(3) < _itemMax && _stp % 300 == 0)
  {
    while (checkContact((x = rand() % _mapX), (y = rand() % _mapY)) != 0);
    _items.push_back(new Items(x, y, 3));
  }
  if (getNbItems(4) < _itemMax && _stp > 500 && _stp % 400 == 0)
  {
    while (checkContact((x = rand() % _mapX), (y = rand() % _mapY)) != 0);
    _items.push_back(new Items(x, y, 4));
  }
  if (getNbItems(5) < _itemMax && _stp > 500 && _stp % 500 == 0)
  {
    while (checkContact((x = rand() % _mapX), (y = rand() % _mapY)) != 0);
     _items.push_back(new Items(x, y, 5));
  }
  if (_iaHard > 1 && getNbItems(6) < _itemMax &&
      (_stp % (100 * (10 - _iaHard)) == 0 || _stp % (150 * (10 - _iaHard)) == 0))
  {
    if (_snake->getX() < _mapX / 2 && _snake->getY() < _mapY / 2)
      while (checkContact((x = (_mapX / 2) + rand() % (_mapX / 2)), (_mapY / 2) + (y = rand() % (_mapY / 2))) != 0);
    else if (_snake->getX() > _mapX / 2 && _snake->getY() < _mapY / 2)
      while (checkContact((x = rand() % (_mapX / 2)), (y = (_mapY / 2) + rand() % (_mapY / 2))) != 0);
    else if (_snake->getX() < _mapX / 2 && _snake->getY() > _mapY / 2)
      while (checkContact((x = (_mapX / 2) + rand() % (_mapX / 2)), (y = rand() % (_mapY / 2))) != 0);
    else
      while (checkContact((x = rand() % (_mapX / 2)), (y = rand() % (_mapY / 2))) != 0);
    if (_stp % (100 * (10 - _iaHard)) == 0)
      _items.push_back(new Items(x, y, 6));
    if (_iaHard > 3 && _stp % (150 * (10 - _iaHard)) == 0)
      _items.push_back(new Items(x, y, 7));
    }
}

void    Game::itemsAction()
{
  std::list<SnakeNode*>           nodes;
  std::list<SnakeNode*>::iterator nodeIt;
  std::list<Items*>::iterator     itemIt;
  int                             randChk;
  int                             chkX;
  int                             chkY;
  int                             chkType;
  int                             chkStep;
  int                             x;
  int                             y;
  int                             vx;
  int                             vy;
  int                             vmin;
  int                             i;

  for (itemIt = _items.begin(); itemIt != _items.end(); itemIt++)
  {
    chkX = (*itemIt)->getX();
    chkY = (*itemIt)->getY();
    chkType = (*itemIt)->getType();
    chkStep = (*itemIt)->getStep();
    if (_stp % ((10 - _itemSpeed) + (rand() % (10 - _itemSpeed))) == 0 &&
      ((chkType == 1 && _iaHard >= 1) || ((chkType == 6 || chkType == 7) && _iaHard >= 2) ||
       (chkType >= 2 && chkType <= 5 && _iaHard >= 7) || (chkType == 0 && _iaHard >= 8)))
    {
        i = 0;
        while (i < 9 && checkContact((x = (chkX - 1) + rand() % 3), (y = (chkY - 1) + rand() % 3)) != 0)
          i++;
          (*itemIt)->setX(x);
          (*itemIt)->setY(y);
    }


    if (_stp % ((10 - _itemSpeed) + (rand() % (10 - _itemSpeed))) == 0 &&
       ((_iaHard > 2 && chkType == 6 || chkType == 7)))
    {
      nodes = _snake->getNode();
      vmin = 1000000;
      if (_iaHard == 3)
      {
        for (nodeIt = nodes.begin(); nodeIt != nodes.end(); nodeIt++)
        {
          x = chkX - (*nodeIt)->getX();
          y = chkY - (*nodeIt)->getY();
         if (vmin > (x < 0 ? x * (-1) : x) + (y < 0 ? y * (-1) : y))
         {
           vx = x;
           vy = y;
           vmin = (x < 0 ? x * (-1) : x) + (y < 0 ? y * (-1) : y);
         }
       }
     }
     if (_iaHard > 4)
     {
       nodeIt = nodes.begin();
       vx = chkX - (*nodeIt)->getX();
       vy = chkY - (*nodeIt)->getY();
     }
       x = chkX + (vx < 0 ? 1 : -1);
       y = chkY + (vy < 0 ? 1 : -1);
      if (checkContact(x, y) == 0)
      {
        (*itemIt)->setX(x);
        (*itemIt)->setY(y);
      }
    }
    (*itemIt)->setStep(1);


  }
  for (itemIt = _items.begin(); itemIt != _items.end(); itemIt++)
  {
    if ((chkType == 1 && chkStep < _itemLife * 120) ||
        (chkType >= 2 && chkType <= 5 && chkStep < _itemLife * 200) ||
        (chkType >= 6 && chkType <= 7 && chkStep < _itemLife * 50 * _iaHard))
    {
      _items.remove(*itemIt);
      return ;
    }
  }
}

void    Game::snakeAction()
{
  int   x;
  int   y;

  _mov = 0;
  _snake->move();
  x = _snake->getX();
  y = _snake->getY();
  if ((_gameMode == 1 && (x < 0 || x >= _mapX || y < 0 || y >= _mapY)) ||
      (_gameMode == 2 && (x < 0 || x >= _mapX)) ||
      (_gameMode == 3 && (y < 0 || y >= _mapY)))
  {
    if (x < 0)
	    _snake->moveTo(_mapX - 1, -1);
    if (x == _mapX)
	    _snake->moveTo(0, -1);
    if (y < 0)
	    _snake->moveTo(-1, _mapY - 1);
    if (y == _mapY)
	    _snake->moveTo(-1, 0);
    x = _snake->getX();
    y = _snake->getY();
  }
}

void    Game::envIteraction()
{
  int              contactType;

  contactType = headContact();
  switch (contactType)
  {
    case 1:
      _end = 1;
      break;
    case 2:
      _snake->eat();
      _score += _point;
      break;
    case 3:
      _snake->eat();
      _snake->eat();
      _score += _point * 20;
      break;
    case 4:
      _snake->eat();
      _speed += 2;
      if (_speed > 9)
	       _speed = 9;
      _score += _point * 10;
      break;
    case 5:
      _speed -= 2;
      if (_speed < 0)
	       _speed = 0;
      _score += _point;
      break;
    case 6:
      _snake->eat();
      _point += 10;
      if (_point > 100)
	       _point = 100;
      _score += _point;
      break;
    case 7:
      _snake->eat();
      _point -= 10;
      if (_point < 0)
	       _point = 1;
      _score += _point;
      break;
    case 8:
      if (_snake->getSize() < 10 || _iaHard > 7)
        _end = 1;
      else
        _snake->dammage();
      _score -= 10;
      if (_score < 0)
        _score = 0;
      break;
    case 9:
      _end = 1;
      break;
  }

}

void    Game::gameLoop()
{
  _stp = 0;
  while (42)
  {
    keyAction();
    snakeAction();
    envIteraction();
    itemsAction();
    generateItems();
    if (_careerMode == 1)
      changeMap();
    if (_end == 1)
    {
      renderer->endAnim();
      usleep(1000000);
      renderer->freeLib();
      std::cout << "You lose !" << std::endl;
      std::cout << "You have scored " << _score << " points." << std::endl;
      return ;
    }
    try
    {
      display();
    }
    catch(errGraphic &e)
    {
      std::cout << "Graphic err: " << e.what() << std::endl;
      return ;
    }
    if (_stp == 0)
      usleep(500000);
    _stp++;
  }

}

void    Game::display()
{
  std::list<Items*>::iterator     itemIt;
  std::list<Elems*>::iterator     elemIt;
  int                             i;

  renderer->renderClear();
  for (int i = 0; i < _mapX; i++)
  {
    for (int j = 0; j < _mapY; j++)
      renderer->printMap(i, j, _backType);
  }
  for (itemIt = _items.begin(); itemIt != _items.end(); itemIt++)
  {
    renderer->printItem((*itemIt)->getX(), (*itemIt)->getY(), (*itemIt)->getType());
  }
  for (elemIt = _elems.begin(); elemIt != _elems.end(); elemIt++)
  {
    renderer->printElem((*elemIt)->getX(), (*elemIt)->getY(), (*elemIt)->getType());
  }
  renderer->printScore(_score);
  renderer->printLevel(_level);
  displaySnake();
  renderer->render();
  for (i = 0; i < 5 * (10 - _speed); i++)
  {
    keyAction();
    usleep(2000);
  }
  renderer->render();
  for (i = 0; i < 5 * (10 - _speed); i++)
  {
    keyAction();
    usleep(2000);
  }
}

void    Game::displaySnake()
{
  std::list<SnakeNode*>           nodes;
  std::list<SnakeNode*>::iterator nodeIt;
  int                             prevDir = 0;
  int                             nextDir = 0;
  int                             prevX = 0;
  int                             prevY = 0;
  int                             instX = 0;
  int                             instY = 0;
  int                             nextX = 0;
  int                             nextY = 0;

  nodes = _snake->getNode();
  nodeIt = nodes.begin();
  while (nodeIt != nodes.end())
  {
    prevX = instX;
    prevY = instY;
    instX = (*nodeIt)->getX();
    instY = (*nodeIt)->getY();
    prevDir = (nodeIt == nodes.begin() ? -1 : _snake->getDirPos(instX, instY, prevX, prevY));
    nodeIt++;
    nextX = (*nodeIt)->getX();
    nextY = (*nodeIt)->getY();
    nextDir = (nodeIt == nodes.end() ? -1 : _snake->getDirPos(instX, instY, nextX, nextY));
    if (instX < _mapX && instY < _mapY)
      renderer->printSnake(instX, instY, prevDir, nextDir);
  }
}

void Game::initLib(std::string lib)
{
  IGraph *(*external_creator)(int, int);
  IGraph *libPtr;
  void *dlhandle;
  std::stringstream ss;

  ss << "./" << lib;
  ss >> lib;
  dlhandle = dlopen(lib.c_str(), RTLD_LAZY);
  if (dlhandle == NULL)
    throw errExcept(dlerror());
  external_creator = reinterpret_cast<IGraph *(*)(int, int)>(dlsym(dlhandle, "createRenderer"));
  if(external_creator == NULL)
    throw errExcept(dlerror());
  libPtr = external_creator(_mapX, _mapY);
  this->renderer = libPtr;
}
