#include "myarea.h"
#include <cairomm/context.h>
#include <bits/stdc++.h>

using namespace std;

MyArea::MyArea()
{
  arr =new char*[N];  for (int i = 0; i<N;i++){
    arr[i] = new char[N];
  }
  firstclick = false;
  secondclick = false;
  add_events(Gdk::BUTTON_PRESS_MASK);
  //maze.signal_size_allocate().connect(
      //sigc::mem_fun(*this, &MyArea::on_drawingarea_allocate));

}

MyArea::~MyArea()
{
  for (int i = 0; i<N;i++){
    delete [] arr[i];
  }
  delete [] arr;
}

void MyArea::setArr(char a[N][N], int brs, int kol){
  this->brs = brs;
  this->kol = kol;
  for (int i=0; i<brs; i++){
    for (int j=0; j<kol; j++){
      arr[i][j] = a[i][j];
    }
  }
  queue_draw();
}

void MyArea::setArr(char a,int i,int j){
  arr[i][j] = a;
  queue_draw();
}

void MyArea::getXY(int x,int y,int* hx,int* hy){
  *hx = x*10;
  *hy = y*10;
}

void MyArea::getIJ(int x,int y,int* hx,int* hy){
  *hx = x/10;
  *hy = y/10;
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    // coordinates for the center of the window
  int i, j,xc,yc;
  
  // Get drawing area size  
  cr->set_line_width(10.0);
  // draw red lines out from the center of the window    
    for (i = 0; i<brs; i++){    
      for (j = 0; j<kol; j++){
        getXY(i,j,&xc,&yc);      
        cr -> move_to(yc, xc);
        if (arr[i][j] == '1'){       
          cr->set_source_rgb(0.8, 0.0, 0.0);  
          cr -> line_to(yc+10,xc); 
          cr->stroke();        

        }
        else 
        if (arr[i][j] == 'X'){   
          cr->set_source_rgb(0.0, 0.0, 0.8);  
          cr -> line_to(yc+10,xc);      
          cr->stroke();  

        }   
        else 
        if (arr[i][j] == ' '){   
          cr->set_source_rgb(0.0, 0.8, 0.0);  
          cr -> line_to(yc+10,xc);      
          cr->stroke();  

        } 
      }

    }    
    cout<<"c: "<<c<<endl;
    return true;
  
} 

bool MyArea::on_button_press_event(GdkEventButton * event){
  // Check if the event is a left(1) button click.
    if( (event->type == GDK_BUTTON_PRESS) && (event->button == 1) )
    {
        //check whether this is the first click
        if(!firstclick&&!secondclick)
        {
            //the first coordinate
            x1=event->x;
            y1=event->y;            
            int i, j;
            getIJ(x1,y1,&i,&j);
            if (j<brs && i<kol&& arr[j][i] == '0') {
              firstclick=true;
              arr[j][i] = 'X'; //TITIK AWAL
              x1=j; //perbaiki baris
              y1=i; //perbaiki kolom 
              cout<<"clickedone "<<i<<' '<<j<<endl;
              queue_draw();
            }
        }
        //check whether this is the second click, and not on the same point as the previous
        if(firstclick&&!secondclick&&(int)event->x!=x1&&(int)event->y!=y1)
        {
            //the second coordinate
            x2=event->x;
            y2=event->y;            
            int i, j;
            getIJ(x2,y2,&i,&j);
            if (j<brs && i<kol && arr[j][i] == '0') {
              arr[j][i] = 'X'; //TITIK AKHIR
              secondclick=true;
              x2=j; //perbaiki baris
              y2=i; // perbaiki kolom 
              cout<<"clickedtwo"<<i<<' '<<j<<endl;
              //refresh the screen
              queue_draw();
            }
        }
        // The event has been handled.
        return true;
    }
}

int MyArea::getXAw(){return x1;}
int MyArea::getXAk(){return x2;}
int MyArea::getYAw(){return y1;}
int MyArea::getYAk(){return y2;}

void MyArea::setFirstclick(bool v){firstclick = v;}
void MyArea::setSecondclick(bool v){secondclick = v;};