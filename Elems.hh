#ifndef ELEMS_HH_
#define ELEMS_HH_

class   Elems
{
protected:
  int   _x;
  int   _y;
  int   _type;
  bool  _solid;
public:
  Elems(int, int, int, int);
  ~Elems();

  int getX() const;
  int getY() const;
  int getType() const;
  bool getSolid() const;
  void setX(int);
  void setY(int);
  void setSolid(bool);
};

#endif
