#include "LibCurses.hh"


LibCurses::LibCurses(int y, int x)
{
  int sx;
  int sy;

  _mapX = x;
  _mapY = y;
  initscr();
  keypad(stdscr, TRUE);
  curs_set(0);
  timeout(0);
  getmaxyx(stdscr, sy, sx);
  if (sx < x || sy < y)
  {
    freeLib();
    throw errGraphic("Window too small!");
    return ;
  }
  start_color();
  init_pair(1, COLOR_BLUE, COLOR_BLUE);
  init_pair(2, COLOR_GREEN, COLOR_GREEN);
  init_pair(3, COLOR_BLACK, COLOR_GREEN);
  init_pair(4, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(5, COLOR_RED, COLOR_GREEN);
  erase();
}

LibCurses::~LibCurses()
{
  erase();
  curs_set(1);
  endwin();
}

void LibCurses::printSnake(int y, int x, int prevDir, int nextDir)
{
  move(x, y);
  attron(COLOR_PAIR(1));
  addch(' '|A_REVERSE);
}

void LibCurses::printMap(int y, int x, int type)
{
  move(x, y);
  attron(COLOR_PAIR(2));
  addch(' '|A_REVERSE);
}

void LibCurses::printItem(int y, int x, int type)
{
  move(x, y);
  switch (type) {
    case 0:
    attron(COLOR_PAIR(3));
    addch(ACS_DIAMOND);
    break;
    case 1:
    attron(COLOR_PAIR(3));
    addch(ACS_CKBOARD);
    break;
    case 2:
    attron(COLOR_PAIR(3));
    addch('@');
    break;
    case 3:
    attron(COLOR_PAIR(3));
    addch('#');
    break;
    case 4:
    attron(COLOR_PAIR(3));
    addch(ACS_PLMINUS);
    break;
    case 5:
    attron(COLOR_PAIR(3));
    addch(ACS_NEQUAL);
    break;
    case 6:
    attron(COLOR_PAIR(5));
    addch((rand() % 2 == 0 ? ACS_LEQUAL : ACS_GEQUAL));
    break;
    case 7:
    attron(COLOR_PAIR(5));
    addch((rand() % 2 == 0 ? '{' : '}'));
    break;
  }
}

void LibCurses::printElem(int y, int x, int type)
{
  move(x, y);
  attron(COLOR_PAIR(4));
  addch(' '|A_REVERSE);
}

void LibCurses::printScore(int score)
{
  attron(COLOR_PAIR(3));
  move(_mapY, 0);
  printw("Score: %d", score);
}

void LibCurses::printLevel(int level)
{
  attron(COLOR_PAIR(3));
  move(_mapY, (_mapX - 8 < 18 ? 18 : _mapX - 8));
  printw("Level: %d", level);
}

void LibCurses::renderClear()
{
refresh();
}

void LibCurses::render()
{
  refresh();
}

void LibCurses::freeLib()
{
  erase();
  curs_set(1);
  endwin();
}

eKey LibCurses::getKey()
{

  int key;

  key = getch();
  switch (key)
  {
    case KEY_LEFT:
      return KLEFT;
    case KEY_RIGHT:
      return KRIGHT;
    case 27:
      return KQUIT;
    default:
      return KUP;
  }
}

void LibCurses::endAnim()
{

}

extern "C"
{
  IGraph     *createRenderer(int y, int x)
  {
    return new LibCurses(x, y);
  }
}
