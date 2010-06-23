#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;

struct Grafo{

	vector<list<int> > adList;
	
	Grafo(){
		adList.clear();
	}
	void cargardimacs(string in);
	void guardarnuestro(string out);

};

void guardarLista(ostream& os, const list<int>& l);


int main(int argc, char** argv){

	//pasarle 2 argumentos, el archivo del benchmark (tipo dimacs) y el de salida para nuestro formato

	//los benchmarks los saque de: http://www.nlsde.buaa.edu.cn/~kexu/benchmarks/graph-benchmarks.htm
	
	string in = argv[1];
	string out = argv[2];
	
	Grafo g;
	
	g.cargardimacs(in);
	
	g.guardarnuestro(out);

	return 0;
}

void Grafo::cargardimacs(string in){

	ifstream is;
	is.open(in.c_str());
	
	char c;
	string e;
	int V,X,u,v;

	is >> c; //me salteo la letra p
	is >> e; //me salteo el string "edge"
	is >> V; //cargo cantidad de nodos
	is >> X; //cargo cantidad de aristas
	
	adList.resize(V);
	
	for(int i = 0; i < X; i++){

		is >> c; //salteo la e
		is >> u;
		is >> v;
		
		u--;
		v--;
		
		adList[u].push_back(v);
		adList[v].push_back(u);
	}
	
	is.close();
}

void Grafo::guardarnuestro(string out){

	ofstream os;
	os.open(out.c_str());
	
	os << adList.size() << endl;
	for(int i = 0; i < adList.size(); i++){
	
		os << adList[i].size() << " ";
		guardarLista(os,adList[i]);
		os << endl;	
	}
	
	os << -1;
	
	os.close();

}

void guardarLista(ostream& os, const list<int>& l){

	for(list<int>::const_iterator it = l.begin(); it != l.end(); it++){
		os << *it << " ";
	}

}
