#include <string.h>
#include <time.h>
#include "Game.hh"
#include "Menu.hh"

int   main(int ac, char **av)
{
  int sizeX;
  int sizeY;

  if (ac != 4 && ac != 1)
  {
    std::cout << "Usage: ./nibbler mapWidth mapHeight <lib.so>" << std::endl;
    return (-1);
  }
  srand(time(NULL));
  if (ac == 1)
  {
    Menu    menu;

    try
    {
      menu.start();
    }
    catch (errExcept &e)
    {
      std::cout << "Error: " << e.what() << std::endl;
      return (-1);
    }
    catch (errGraphic &e)
    {
      std::cout << "Graphic error: " << e.what() << std::endl;
      return (-1);
    }
    return (0);
  }
  std::istringstream (av[1]) >> sizeX;
  std::istringstream (av[2]) >> sizeY;
  if (sizeX < 10 || sizeY < 10)
  {
    std::cout << "You have to put a larger map" << std::endl;
    return (-1);
  }
  if (sizeX > 50 || sizeY > 50)
  {
    std::cout << "You have to put a smaller map" << std::endl;
    return (-1);
  }
  Game  game(sizeX, sizeY);
  try
  {
    game.initLib(av[3]);
    game.gameLoop();
  }
  catch (errExcept &e)
  {
    std::cout << "Error: " << e.what() << std::endl;
    return (-1);
  }
  catch (errGraphic &e)
  {
    std::cout << "Graphic error: " << e.what() << std::endl;
    return (-1);
  }
  return (0);
}
