#include<bits/stdc++.h>

#define ff first
#define ss second
#define N 100

using namespace std;

void init(bool visit[N][N]){
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			visit[i][j]=false;
		}	
	}
}
void readInput(char arr[N][N],int* brs,int*kol){
	string nama;
	int i;
	
	cin >> nama;
	ifstream inFile;
	inFile.open(nama);
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
	*kol = line.length();
	*brs = i;
	cout<<"berhasil"<<endl;
}

void printMaze(char arr[N][N],int brs,int kol){
	for (int i =0;i<brs;i++){
		for (int j=0; j<kol;j++){
			cout<<arr[i][j];
			if (j == kol-1) cout<<endl;
		}
	}
} 

void pushSort(pair <int,int> x,float bobot[N][N],deque < pair <int,int> >* simpul){
	bool found=false;
	pair <int,int> tmp;
	deque< pair <int,int> > save;
	while(!found&&!simpul->empty()){
		tmp = simpul->back();
		if(bobot[x.ff][x.ss]>bobot[tmp.ff][tmp.ss]){
			found=true;
		}else{
			simpul->pop_back();
			save.push_back(tmp);
		}
	}
	simpul->push_back(x);
	while(!save.empty()){
		tmp = save.back();
		save.pop_back();
		simpul->push_back(tmp);
	}
}

float jarakAkhir(int x1,int x2,int y1,int y2){
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void BFS(char arr[N][N], int posX, int posY, int hslX, int hslY) {
	int mx[4]={1,0,-1,0};
	int my[4]={0,1,0,-1};
	pair <int,int> node,nextnode;
	vector< pair<int,int> > path[N][N];
	deque < pair <int,int> > simpul; 	
	bool visit[N][N];
	
	init(visit);
	simpul.push_back(make_pair(posX,posY));
	visit[posX][posY]=true;
	node=simpul.front();
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
				arr[nextnode.ff][nextnode.ss] = 'X'; 
				simpul.push_back(nextnode);
			}
		}
		node=simpul.front();
		path[node.ff][node.ss].push_back(node);
		//break;
	}
	for(int i=0;i<path[hslX][hslY].size();i++){
		arr[path[hslX][hslY][i].ff][path[hslX][hslY][i].ss] = ' ';
		//cout<<path[xAk][yAk][i].ff<<" "<<path[xAk][yAk][i].ss<<endl;
	} 
}

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
	path[node.ff][node.ss].push_back(node);
		
	while (node!=make_pair(hslX,hslY)){
		simpul.pop_front();
		for(int i = 0;i < 4;i++){
			nextnode.ff = node.ff + mx[i];
			nextnode.ss = node.ss + my[i];
			if(!visit[nextnode.ff][nextnode.ss]&&arr[nextnode.ff][nextnode.ss]=='0'){
				path[nextnode.ff][nextnode.ss].assign(path[node.ff][node.ss].begin(), path[node.ff][node.ss].end());
				visit[nextnode.ff][nextnode.ss] = true;
				jarak[nextnode.ff][nextnode.ss] = jarak[node.ff][node.ss] + 1;
				bobot[nextnode.ff][nextnode.ss] = jarak[nextnode.ff][nextnode.ss] + jarakAkhir(node.ff,hslX,node.ss,hslY);
				arr[nextnode.ff][nextnode.ss] = 'X'; 
				pushSort(nextnode,bobot,&simpul);
			}
		}
		node=simpul.front();
		path[node.ff][node.ss].push_back(node);
	}
	
	for(int i=0;i<path[hslX][hslY].size();i++){
		arr[path[hslX][hslY][i].ff][path[hslX][hslY][i].ss] = ' ';
		//cout<<path[xAk][yAk][i].ff<<" "<<path[xAk][yAk][i].ss<<endl;
	} 
}
 
int main(){	
	int brs,kol,menu;		
	char arr[N][N];	
	int xAw,yAw;
	int xAk,yAk;
	
	
	readInput(arr,&brs,&kol);
	printMaze(arr,brs,kol);	
	cout<<"input titik awal:"<<endl;
	cin>>xAw>>yAw;
	cout<<"input titik akhir:"<<endl;
	cin>>xAk>>yAk;	
	
	cout<<"pilih algoritma"<<endl;
	cout<<"1. BFS"<<endl;
	cout<<"2. A*"<<endl;
	cin>>menu;
	if (menu == 1) BFS(arr,xAw,yAw,xAk,yAk);
	else if (menu == 2) AStar(arr,xAw,yAw,xAk,yAk);	
		
	cout<<"Jalur:"<<endl;	
	printMaze(arr,brs,kol);
	return 0; 
}
