#include "Menu.hh"
#include "Game.hh"

Menu::Menu()
{
  end = 0;
  level = 0;
  hard = -1;
  speed = 5;
  item = -1;
  number = -1;
  lib = 1;
  click = 0;

  if((SDL_Init(SDL_INIT_EVERYTHING) == -1))
    throw errGraphic("Init");
  screen = SDL_SetVideoMode(1248, 1000, 32, SDL_SWSURFACE);
  if (screen == NULL)
    throw errGraphic("Can't init the window");
  SDL_WM_SetCaption("Nibbler Menu", NULL);
  if (TTF_Init() == -1)
    throw errGraphic("Can't init TTF");
  if ((font = TTF_OpenFont("Data/Font.ttf", 80)) == NULL)
    throw errGraphic("Can't load font: Font.ttf");
  if ((back_sprt = IMG_Load("Data/MenuBack.png")) == NULL)
    throw errGraphic("Can't load img: MenuBack.png");
  if (SDL_BlitSurface(back_sprt, NULL, screen, NULL) < 0)
    throw errGraphic ("Blit Surface");
  SDL_UpdateRect(screen, 0, 0, screen->w, screen->h);
}

Menu::~Menu()
{

}

void  Menu::checkKey()
{
  if (SDL_PollEvent(&event))
  {
    switch (event.type) {
      case SDL_QUIT:
        end = 1;
      break;
      case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
        case SDLK_q:
        end = 1;
        break;
        case SDLK_RETURN:
        end = 2;
        break;
      }
      case SDL_MOUSEMOTION:
        mouseX = event.motion.x;
        mouseY = event.motion.y;
        break;
      case SDL_MOUSEBUTTONDOWN:
        click = 1;
        break;
      break;
    }
  }
}

void  Menu::interfaceIteraction()
{
  if (click == 1)
  {
    click = 0;
    if (mouseX > 250 && mouseX < 625 && mouseY > 180 && mouseY < 250)
      (level != 0 ? level-- : level);
    if (mouseX > 625 && mouseX < 1000 && mouseY > 180 && mouseY < 250)
      (level != 10 ? level++ : level);

    if (mouseX > 250 && mouseX < 625 && mouseY > 294 && mouseY < 364)
      (hard != -1 ? hard-- : hard);
    if (mouseX > 625 && mouseX < 1000 && mouseY > 294 && mouseY < 364)
      (hard != 4 ? hard++ : hard);

    if (mouseX > 250 && mouseX < 625 && mouseY > 408 && mouseY < 478)
      (speed != 1 ? speed-- : speed);
    if (mouseX > 625 && mouseX < 1000 && mouseY > 408 && mouseY < 478)
      (speed != 10 ? speed++ : speed);

    if (mouseX > 250 && mouseX < 625 && mouseY > 522 && mouseY < 592)
      (item != -1 ? item-- : item);
    if (mouseX > 625 && mouseX < 1000 && mouseY > 522 && mouseY < 592)
      (item != 9 ? item++ : item);

    if (mouseX > 250 && mouseX < 625 && mouseY > 636 && mouseY < 706)
      (number != -1 ? number-- : number);
    if (mouseX > 625 && mouseX < 1000 && mouseY > 636 && mouseY < 706)
      (number != 9 ? number++ : number);

    if (mouseX > 250 && mouseX < 625 && mouseY > 750 && mouseY < 820)
      (lib != 0 ? lib-- : lib);
    if (mouseX > 625 && mouseX < 1000 && mouseY > 750 && mouseY < 820)
      (lib != 2 ? lib++ : lib);

    if (mouseX > 0 && mouseX < 624 && mouseY > 872 && mouseY < 1000)
      end = 1;
    if (mouseX > 624 && mouseX < 1248 && mouseY > 872 && mouseY < 1000)
      end = 2;
  }
}

void  Menu::display()
{
  SDL_Color     color_back = {128, 0, 0};
  SDL_Color     color_princ = {255, 0, 0};
  SDL_Color     color = {255, 64, 64};
  SDL_Surface   *text;
  SDL_Rect      winPos;
  std::stringstream num;
  std::string   str;
  int           i;

  if (SDL_BlitSurface(back_sprt, NULL, screen, NULL) < 0)
    throw errGraphic ("Blit Surface");
  str = "DeatH      SnakE";
  text = TTF_RenderText_Blended(font, str.c_str(), color_back);
  winPos.x = screen->w / 2 - text->w / 2 + ((rand() % 40) - 20);
  winPos.y = 10 + ((rand() % 20) - 10);
  if (SDL_BlitSurface(text, NULL, screen, &winPos) < 0)
    throw errGraphic ("Blit Surface");
  text = TTF_RenderText_Blended(font, str.c_str(), color_princ);
  winPos.x = screen->w / 2 - text->w / 2;
  winPos.y = 10;
  if (SDL_BlitSurface(text, NULL, screen, &winPos) < 0)
    throw errGraphic ("Blit Surface");
  str = "Quit";
  winPos.x = 40;
  winPos.y = screen->h - 105;
  text = TTF_RenderText_Blended(font, str.c_str(), color_princ);
  if (SDL_BlitSurface(text, NULL, screen, &winPos) < 0)
    throw errGraphic ("Blit Surface");
  str = "Start";
  text = TTF_RenderText_Blended(font, str.c_str(), color_princ);
  winPos.x = screen->w - text->w - 40;
  if (SDL_BlitSurface(text, NULL, screen, &winPos) < 0)
    throw errGraphic ("Blit Surface");
  for (i = 0; i < 6; i++)
  {
    str = "<";
    text = TTF_RenderText_Blended(font, str.c_str(), color);
    winPos.x = 260;
    winPos.y = 162 + i * 114;
    if (SDL_BlitSurface(text, NULL, screen, &winPos) < 0)
      throw errGraphic ("Blit Surface");
    str = ">";
    text = TTF_RenderText_Blended(font, str.c_str(), color);
    winPos.x = 944;
    if (SDL_BlitSurface(text, NULL, screen, &winPos) < 0)
      throw errGraphic ("Blit Surface");
  }
  num << level;
  str = (level == 0 ? "Career Mode" : "Level ");
  if (level != 0)
    str += num.str();
  text = TTF_RenderText_Blended(font, str.c_str(), color);
  winPos.x = screen->w / 2 - text->w / 2;
  winPos.y = 162;
  if (SDL_BlitSurface(text, NULL, screen, &winPos) < 0)
    throw errGraphic ("Blit Surface");
  switch (hard)
  {
    case -1:
      str = "Relative";
      break;
    case 0:
      str = "Novice";
      break;
    case 1:
      str = "Easy";
      break;
    case 2:
      str = "Normal";
      break;
    case 3:
      str = "Hard";
      break;
    case 4:
      str = "HardCore";
      break;
  }
  text = TTF_RenderText_Blended(font, str.c_str(), color);
  winPos.x = screen->w / 2 - text->w / 2;
  winPos.y = 276;
  if (SDL_BlitSurface(text, NULL, screen, &winPos) < 0)
    throw errGraphic ("Blit Surface");

  num.str("");
  num << speed;
  str = "Speed:  " + num.str();
  text = TTF_RenderText_Blended(font, str.c_str(), color);
  winPos.x = screen->w / 2 - text->w / 2;
  winPos.y = 390;
  if (SDL_BlitSurface(text, NULL, screen, &winPos) < 0)
    throw errGraphic ("Blit Surface");
  num.str("");
  num << (item + 1);
  str = "Object Speed:  ";
  str += (item == -1 ? "Relative" : num.str());
  text = TTF_RenderText_Blended(font, str.c_str(), color);
  winPos.x = screen->w / 2 - text->w / 2;
  winPos.y = 504;
  if (SDL_BlitSurface(text, NULL, screen, &winPos) < 0)
    throw errGraphic ("Blit Surface");
  num.str("");
  num << (number + 1);
  str = "Object Numbers:  ";
  str += (number == -1 ? "Relative" : num.str());
  text = TTF_RenderText_Blended(font, str.c_str(), color);
  winPos.x = screen->w / 2 - text->w / 2;
  winPos.y = 618;
  if (SDL_BlitSurface(text, NULL, screen, &winPos) < 0)
    throw errGraphic ("Blit Surface");
  str = "Display Mode:  ";
  str += (lib == 0 ? "Text  (Ncurses)" : (lib == 1 ? "2D  (SDL)" : "3D  (OpenGL)"));
  text = TTF_RenderText_Blended(font, str.c_str(), color);
  winPos.x = screen->w / 2 - text->w / 2;
  winPos.y = 732;
  if (SDL_BlitSurface(text, NULL, screen, &winPos) < 0)
    throw errGraphic ("Blit Surface");
  SDL_UpdateRect(screen, 0, 0, screen->w, screen->h);
}

void  Menu::loop()
{
  while (42)
  {
    checkKey();
    interfaceIteraction();
    display();
    if (end == 1)
      break;
    if (end == 2)
    {
      break;
    }
    usleep(2000);
  }
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_Quit();
}

void  Menu::start()
{
  std::string   libName;

  loop();
  if (end != 1)
  {
    Game  game(level, hard, speed, item, number);
    game.getMap((level == 0 ? 1 : level));
    switch (lib)
    {
      case 0:
        libName = "lib_nibbler_curses.so";
        break;
      case 1:
        libName = "lib_nibbler_sdl.so";
        break;
      case 2:
        libName = "lib_nibbler_gl.so";
        break;
    }
    game.initLib(libName);
    game.gameLoop();
  }
}
