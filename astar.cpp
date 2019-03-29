#include<bits/stdc++.h>
#define ff first
#define ss second

using namespace std;
int brs,kol,xAw,xAk,langkah;
pair <int,int> node,nextnode;
deque < pair <int,int> > simpul; 
vector< pair<int,int> > path[100][100];
int mx[4]={1,0,-1,0};
int my[4]={0,1,0,-1};
char arr[100][100];
int jarak[100][100];
float bobot[100][100];
bool visit[100][100];

void init(){
	for(int i=0;i<100;i++){
		for(int j=0;j<100;j++){
			visit[i][j]=false;
			arr[i][j]=' ';
		}	
	}
}

void readInput(){
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
	kol = line.length();
	brs = i;
	cout<<"berhasil"<<endl;
}

float jarakAkhir(int x,int y){
	return sqrt((x-xAk)*(x-xAk)+(y-kol)*(y-kol));
}

void pushSort(pair <int,int> x){
	bool found=false;
	pair <int,int> tmp;
	deque< pair <int,int> > save;
	while(!found&&!simpul.empty()){
		tmp = simpul.back();
		if(bobot[x.ff][x.ss]>bobot[tmp.ff][tmp.ss]){
			found=true;
		}else{
			simpul.pop_back();
			save.push_back(tmp);
		}
	}
	simpul.push_back(x);
	while(!save.empty()){
		tmp = save.back();
		save.pop_back();
		simpul.push_back(tmp);
	}
}

void printMaze(){
	for (int i =0;i<brs;i++){
		for (int j=0; j<kol;j++){
			cout<<arr[i][j];
			if (j == kol-1) cout<<endl;
		}
	}
} 

int main(){
	int yAw;
	int yAk;
	readInput();
	printMaze();
	cin>>xAw>>yAw>>xAk>>yAk;
	pushSort(make_pair(xAw,yAw));
	visit[xAw][yAw]=true;
	do{
		node=simpul.front();
		path[node.ff][node.ss].push_back(node);
		simpul.pop_front();
		for(int i = 0;i < 4;i++){
			nextnode.ff = node.ff + mx[i];
			nextnode.ss = node.ss + my[i];
			if(!visit[nextnode.ff][nextnode.ss]&&arr[nextnode.ff][nextnode.ss]=='0'){
				path[nextnode.ff][nextnode.ss].assign(path[node.ff][node.ss].begin(), path[node.ff][node.ss].end());
				visit[nextnode.ff][nextnode.ss] = true;
				jarak[nextnode.ff][nextnode.ss] = jarak[node.ff][node.ss] + 1;
				bobot[nextnode.ff][nextnode.ss] = jarak[nextnode.ff][nextnode.ss] + jarakAkhir(node.ff,node.ss);
				pushSort(nextnode);
			}
		}
		//break;
	}while(node!=make_pair(xAk,yAk));
	for(int i=0;i<path[xAk][yAk].size();i++){
		arr[path[xAk][yAk][i].ff][path[xAk][yAk][i].ss] = 'x';
		//cout<<path[xAk][yAk][i].ff<<" "<<path[xAk][yAk][i].ss<<endl;
	} 
	printMaze();
	return 0; 
}
