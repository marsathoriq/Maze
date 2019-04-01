#include "myarea.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

char arr[N][N];
int brs;
int kol; 
Gtk::Button *btnload;
Gtk::Button *btnBFS;
Gtk::Button *btnASTAR;
Gtk::Button *btnReset;
Gtk::Entry *m_Entry;
MyArea *area;


void readInput(){
	string nama;
	int i;
	
	//cin >> nama;
	ifstream inFile;
	inFile.open(m_Entry->get_text());
	// File not found
	if (!inFile) {
    	cerr << "Gagal membuka "+nama;
    	//exit(1);   // call system to stop
	} 
	//Baca file line by line
	i = 0;
	string line;
	for(line; getline( inFile, line ); )
	{
		for (int j = 0; j<line.length();j++){
			arr[i][j] = (int)line[j];
		}
		i++;
	}
	kol = line.length();
	brs = i;
	//cout<<"berhasil"<<endl;
}


//------------------------BFS ASTAR--------------------------//
//Inisialisasi Kondisi Maze
void init(bool visit[N][N]){
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			visit[i][j]=false;
		}	
	}
}

int Delay(int ms)
{
    clock_t starting = clock();
    while( clock() - starting < ms ) {}
    return 0;
}
// Prosedur mengepush nilai agar terurut
void pushSort(pair <int,int> x,float bobot[N][N],deque < pair <int,int> >* simpul){
	bool found=false;
	pair <int,int> tmp;
	deque< pair <int,int> > save;
	//Mengeluarkan simpul yang kurang dari x dan menaruh ke deque save
	while(!found&&!simpul->empty()){
		tmp = simpul->back();
		if(bobot[x.ff][x.ss]>bobot[tmp.ff][tmp.ss]){
			found=true;
		}else{
			simpul->pop_back();
			save.push_back(tmp);
		}
	}
	//Mengembalikan ke deque sebelumnya
	simpul->push_back(x);
	while(!save.empty()){
		tmp = save.back();
		save.pop_back();
		simpul->push_back(tmp);
	}
}
// Menghitung jarak dengan euclidian
float jarakAkhir(int x1,int x2,int y1,int y2){
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
//Algoritma BFS
void BFS(char arr[N][N], int posX, int posY, int hslX, int hslY) {
	//Semua koordinat tetangga
	int mx[4]={1,0,-1,0};
	int my[4]={0,1,0,-1};
	pair <int,int> node,nextnode;
	vector< pair<int,int> > path[N][N];
	deque < pair <int,int> > simpul; 	
	bool visit[N][N];
	
	init(visit);
	//isi deque simpul aktif
	simpul.push_back(make_pair(posX,posY));
	visit[posX][posY]=true;
	node=simpul.front();
	//Meyimpan jalur
	path[node.ff][node.ss].push_back(node);
	//arr[posX][posY] = ' '; //awal
	while (node!=make_pair(hslX,hslY)){		
		simpul.pop_front();	
		if (node!=make_pair(hslX,hslY))
		for(int i = 0;i < 4;i++){
			nextnode.ff = node.ff + mx[i];
			nextnode.ss = node.ss + my[i];
			//break;
			if(!visit[nextnode.ff][nextnode.ss]&&arr[nextnode.ff][nextnode.ss]=='0'){
				path[nextnode.ff][nextnode.ss].assign(path[node.ff][node.ss].begin(), path[node.ff][node.ss].end());
				visit[nextnode.ff][nextnode.ss] = true;
				//arr[nextnode.ff][nextnode.ss] = 'X'; 
            area->setArr('X',nextnode.ff,nextnode.ss);                
				simpul.push_back(nextnode);
			}
		}
		node=simpul.front();
		path[node.ff][node.ss].push_back(node);
		//break;
	}
	//Menyimpan jalur
	for(int i=0;i<path[hslX][hslY].size();i++){
		//arr[path[hslX][hslY][i].ff][path[hslX][hslY][i].ss] = ' ';
      area->setArr(' ',path[hslX][hslY][i].ff,path[hslX][hslY][i].ss);
      //Delay(2000);  
		//cout<<path[xAk][yAk][i].ff<<" "<<path[xAk][yAk][i].ss<<endl;
	} 
}
//Algoritma AStar
void AStar(char arr[N][N], int posX, int posY, int hslX, int hslY) {
	int mx[4]={1,0,-1,0};
	int my[4]={0,1,0,-1};
	pair <int,int> node,nextnode;
	vector< pair<int,int> > path[N][N];
	deque < pair <int,int> > simpul; 	
	float bobot[N][N];
	bool visit[N][N];
	int jarak[N][N];
	
	init(visit);
	pushSort(make_pair(posX,posY),bobot,&simpul);
	visit[posX][posY]=true;
	node=simpul.front();
	//Meyimpan jalur
	path[node.ff][node.ss].push_back(node);
		
	while (node!=make_pair(hslX,hslY)){
		simpul.pop_front();
		for(int i = 0;i < 4;i++){
			nextnode.ff = node.ff + mx[i];
			nextnode.ss = node.ss + my[i];
			if(!visit[nextnode.ff][nextnode.ss]&&arr[nextnode.ff][nextnode.ss]=='0'){
				path[nextnode.ff][nextnode.ss].assign(path[node.ff][node.ss].begin(), path[node.ff][node.ss].end());
				visit[nextnode.ff][nextnode.ss] = true;
				//Menghitung bobot titik
				jarak[nextnode.ff][nextnode.ss] = jarak[node.ff][node.ss] + 1;
				bobot[nextnode.ff][nextnode.ss] = jarak[nextnode.ff][nextnode.ss] + jarakAkhir(node.ff,hslX,node.ss,hslY);
				//arr[nextnode.ff][nextnode.ss] = 'X'; 
            area->setArr('X',nextnode.ff,nextnode.ss);  
				pushSort(nextnode,bobot,&simpul);
			}
		}
		node=simpul.front();
		path[node.ff][node.ss].push_back(node);
	}
	//Menyimpan jalur
	for(int i=0;i<path[hslX][hslY].size();i++){
		//arr[path[hslX][hslY][i].ff][path[hslX][hslY][i].ss] = ' ';
      area->setArr(' ',path[hslX][hslY][i].ff,path[hslX][hslY][i].ss);      
      //Delay(200); 
		//cout<<path[xAk][yAk][i].ff<<" "<<path[xAk][yAk][i].ss<<endl;
	} 
}

//---------------------Event Handling---------------------//

void btnloadClicked(){
   readInput();
   area->setArr(arr,brs,kol);   
   btnBFS->set_sensitive(true);
   btnASTAR->set_sensitive(true);
   btnReset->set_sensitive(true);
} 

void btnBFSClicked(){	
	int xAw = area->getXAw();
   int yAw = area->getYAw();
	int xAk = area->getXAk();
   int yAk = area->getYAk();
   BFS(arr,xAw,yAw,xAk,yAk);
   btnBFS->set_sensitive(false);
   btnASTAR->set_sensitive(false);
   
   //area->setArr(arr,brs,kol);   
} 

void btnAStarClicked(){	
	int xAw = area->getXAw();
   int yAw = area->getYAw();
	int xAk = area->getXAk();
   int yAk = area->getYAk();
   AStar(arr,xAw,yAw,xAk,yAk);
   btnBFS->set_sensitive(false);
   btnASTAR->set_sensitive(false);
   
   //area->setArr(arr,brs,kol);   
} 

void btnResetClicked(){
   area->setFirstclick(false);
   area->setSecondclick(false);
   btnBFS->set_sensitive(true);
   btnASTAR->set_sensitive(true);
   area->setArr(arr,brs,kol);  
} 


int main(int argc, char** argv)
{  
   auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
   Gtk::Window win;  
   Gtk::Box m_VBox;
   Gtk::Paned m_VPaned;
   Gtk::Frame mazeframe;
   win.add(m_VPaned);   
   win.set_default_size(500,500);
   win.set_border_width(10);
   win.set_title("Maze");  

   m_Entry = new Gtk::Entry;
   m_Entry->set_max_length(100);

   m_Entry->select_region(0, m_Entry->get_text_length());
   m_VBox.pack_start(*m_Entry);
   
   //btnload.set_max_length(90);
   btnload = new Gtk::Button;
   btnload->set_label("Load");
   btnload->set_can_default();
   btnload->grab_default();
   m_VBox.pack_start(*btnload,Gtk::PACK_SHRINK,4);

   //btnload.set_max_length(90);
   btnBFS = new Gtk::Button;
   btnBFS->set_label("BFS");
   btnBFS->set_can_default();   
   btnBFS->grab_default();
   btnBFS->set_sensitive(false);
   m_VBox.pack_start(*btnBFS,Gtk::PACK_SHRINK,4);

   btnASTAR = new Gtk::Button;
   btnASTAR->set_label("AStar");
   btnASTAR->set_can_default();   
   btnASTAR->grab_default();
   btnASTAR->set_sensitive(false);
   m_VBox.pack_start(*btnASTAR,Gtk::PACK_SHRINK,4);

   btnReset = new Gtk::Button;
   btnReset->set_label("Reset");
   btnReset->set_can_default();   
   btnReset->grab_default();
   btnReset->set_sensitive(false);
   m_VBox.pack_start(*btnReset,Gtk::PACK_SHRINK,4);

   mazeframe.set_size_request(500,470);
   
   m_VPaned.set_orientation(Gtk::ORIENTATION_VERTICAL);
   m_VPaned.pack1(m_VBox,false,false);
   m_VPaned.pack2(mazeframe,true,false);

   area = new MyArea;
   
   
   mazeframe.add(*area);
   area->set_hexpand(true);
   area->set_halign(Gtk::ALIGN_FILL);
   area->set_vexpand(true);
   area->set_valign(Gtk::ALIGN_FILL);     
   

   //m_button1.signal_clicked().connect( sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &HelloWorld::on_button_clicked), "button 1") );
   btnload->signal_clicked().connect(sigc::ptr_fun(btnloadClicked));

   btnBFS->signal_clicked().connect(sigc::ptr_fun(btnBFSClicked));

   btnASTAR->signal_clicked().connect(sigc::ptr_fun(btnAStarClicked));

   btnReset->signal_clicked().connect(sigc::ptr_fun(btnResetClicked));

      /*
   while( Gtk::Main::events_pending() )
         Gtk::Main::iteration(); */
         

   win.show_all_children();  
   return app->run(win);
}
