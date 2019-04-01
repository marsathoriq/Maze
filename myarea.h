#ifndef GTKMM_EXAMPLE_MYAREA_H
#define GTKMM_EXAMPLE_MYAREA_H

//#include <gtkmm/drawingarea.h>
#include <gtkmm.h>
#define N 100

class MyArea : public Gtk::DrawingArea
{
public:
  MyArea();
  virtual ~MyArea();
  void setArr(char arr[N][N],int brs,int kol);
  void setArr(char a,int i,int j);
  void setFirstclick(bool v);
  void setSecondclick(bool v);
  int getXAw();
  int getXAk();
  int getYAw();
  int getYAk();

protected:
  //Override default signal handler:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
  //void MyArea::on_drawingarea_draw(const Cairo::RefPtr<Cairo::Context>& cr,  int, int);
  // Override mouse events
  bool on_button_press_event(GdkEventButton * event);

private:
  char ** arr;
  int brs;
  int kol;
  void getXY(int x,int y,int* hx,int* hy);
  void getIJ(int x,int y,int* hx,int* hy);
  //two bools for the clicks
  bool firstclick;
  bool secondclick;
  //two coordinates
  int x1;
  int y1;
  int x2;
  int y2;
  int c; 
};

#endif // GTKMM_EXAMPLE_MYAREA_H
