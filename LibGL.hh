#ifndef RENDERER_GL_HH_
# define RENDERER_GL_HH_

#include <SDL/SDL.h>
#include "IGraph.hh"

class LibGL : virtual public IGraph
{
public:
  LibGL(int mapx, int mapy);
  ~LibGL();
  void		printScore(int);
  void    printLevel(int);
  void		printSnake(int , int , int , int );
  void		printMap(int , int , int);
  void		printItem(int , int , int );
  void		printElem(int , int , int );
  void		render();
  void		renderClear();
  eKey		getKey();
  void		freeLib();
  void		endAnim();
};

#endif
