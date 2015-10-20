#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <iostream>
#include "LibGL.hh"
#include "Exception.hh"

LibGL::LibGL(int x, int y)
{
  SDL_Surface	*screen;

  if (SDL_Init(SDL_INIT_VIDEO) == -1
      || (screen = SDL_SetVideoMode(800, 600, 32, SDL_OPENGL)) == NULL)
    throw errGraphic(SDL_GetError());
  SDL_WM_SetCaption("Nibbler - OpenGL", NULL);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(67,(double)800/600,1,1000);
  glEnable(GL_DEPTH_TEST);
  if (x < y)
    gluLookAt((x/2),-(y/2),(y)/2,(x/2),(y/2),0,0,0,1);
  else
    gluLookAt((x/2),-(y/2),(x)/2,(x/2),(y/2),0,0,0,1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glBegin(GL_QUADS);
}

LibGL::~LibGL()
{
  glEnd();
  SDL_Quit();
}

void	LibGL::printScore(int score)
{

}

void	LibGL::printLevel(int score)
{

}

void	LibGL::printSnake(int x, int y, int prevDir, int nextDir)
{
  glColor3ub(40,40,100);
  glVertex3d(x + 1, y + 1, 1);
  glVertex3d(x + 1, y, 1);
  glVertex3d(x, y, 1);
  glVertex3d(x, y + 1, 1);

  glColor3ub(0,0,200);
  glVertex3d(x + 1, y + 1, 0);
  glVertex3d(x + 1, y, 0);
  glVertex3d(x + 1, y, 1);
  glVertex3d(x + 1, y + 1, 1);

  glColor3ub(0,0,200);
  glVertex3d(x, y + 1, 1);
  glVertex3d(x, y, 1);
  glVertex3d(x, y, 0);
  glVertex3d(x, y + 1, 0);

  glColor3ub(0,0,200);
  glVertex3d(x + 1, y, 1);
  glVertex3d(x + 1, y, 0);
  glVertex3d(x, y, 0);
  glVertex3d(x, y, 1);
}

void	LibGL::printItem(int x, int y, int type)
{
  int color[3];

  if (type < 8)
  {
    color[0] = (type >= 6 ? 150 + ((6 - type) * 100) : (type == 2 || type == 5 ? 150 + ((2 - type) * 50) : 0));
    color[1] = (type == 3 || type == 4 ? 150 + ((2 - type) * 50) : (type < 2 ? 128 : 0));
    color[2] = (type < 2 ? 150 + (type * 100) : (type == 2 || type == 5 ? 150 + ((2 - type) * 50) : 0));
    glColor3ub(color[0], color[1], color[2]);
    glVertex3d(x + 1, y + 1, 1);
    glVertex3d(x + 1, y, 1);
    glVertex3d(x, y, 1);
    glVertex3d(x, y + 1, 1);

    glColor3ub(color[0], color[1], color[2]);
    glVertex3d(x + 1, y + 1, 0);
    glVertex3d(x + 1, y, 0);
    glVertex3d(x + 1, y, 1);
    glVertex3d(x + 1, y + 1, 1);

    glColor3ub(color[0], color[1], color[2]);
    glVertex3d(x, y + 1, 1);
    glVertex3d(x, y, 1);
    glVertex3d(x, y, 0);
    glVertex3d(x, y + 1, 0);

    glColor3ub(color[0], color[1], color[2]);
    glVertex3d(x + 1, y, 1);
    glVertex3d(x + 1, y, 0);
    glVertex3d(x, y, 0);
    glVertex3d(x, y, 1);
  }
}

void	LibGL::printElem(int x, int y, int type)
{
  glColor3ub(150 + (type * 10), 150 + (type * 10), 0);
  glVertex3d(x + 1, y + 1, 1);
  glVertex3d(x + 1, y, 1);
  glVertex3d(x, y, 1);
  glVertex3d(x, y + 1, 1);

  glColor3ub(150 + (type * 10), 150 + (type * 10), 0);
  glVertex3d(x + 1, y + 1, 0);
  glVertex3d(x + 1, y, 0);
  glVertex3d(x + 1, y, 1);
  glVertex3d(x + 1, y + 1, 1);

  glColor3ub(150 + (type * 10), 150 + (type * 10), 0);
  glVertex3d(x, y + 1, 1);
  glVertex3d(x, y, 1);
  glVertex3d(x, y, 0);
  glVertex3d(x, y + 1, 0);

  glColor3ub(150 + (type * 10), 150 + (type * 10), 0);
  glVertex3d(x + 1, y, 1);
  glVertex3d(x + 1, y, 0);
  glVertex3d(x, y, 0);
  glVertex3d(x, y, 1);
}

void	LibGL::printMap(int x, int y, int type)
{
  glColor3ub(100,40,40);
  glVertex3d(x, y+1, 0);
  glVertex3d(x, y, 0);
  glVertex3d(x+1, y, 0);
  glVertex3d(x+1, y+1, 0);
}

eKey	LibGL::getKey()
{
  SDL_Event e;

  if ((SDL_PollEvent(&e)) && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
    {
      if (e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT)
	       return (KQUIT);
      else if (e.key.keysym.sym == SDLK_RIGHT)
	     return (KLEFT);
      else if (e.key.keysym.sym == SDLK_LEFT)
	     return (KRIGHT);
    }
  return (KNOTHING);
}

void	LibGL::render()
{
  glEnd();
  glFlush();
  SDL_GL_SwapBuffers();
}

void	LibGL::renderClear()
{
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glBegin(GL_QUADS);
}

void	LibGL::endAnim()
{

}

void	LibGL::freeLib()
{
  glEnd();
  SDL_Quit();
}

extern "C"
{
  IGraph	*createRenderer(int x, int y)
  {
    return new LibGL(x, y);
  }
}
