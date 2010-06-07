#include <iostream>
#include <fstream>
#include "ej2.h"

using namespace std;


int main(){
	
	int cantNodos;
	int i = 1;
	Grafo g;
	set<int> cliqueMaximo;
	ifstream is;
	ofstream os;
	os.open("../out/Tp3EXACTO.out");
	is.open("../in/Tp3.in");
	is >> cantNodos;
	
	while(cantNodos != -1){
	
		g.cargar(is,cantNodos);
		cliqueMaximo = g.maxClique();
		
		//guardo o muestro el resultado
		guardarRes(os,cliqueMaximo);
		
		i++;
		cliqueMaximo.clear();
		is >> cantNodos;
	}
	
	
	is.close();
	
	return 0;
}

//implementaciones

bool Grafo::sonAdyacentes(int v1, int v2) const {
	return matAd[v1][v2];
}


void Grafo::cargar(istream& is, int cantNodos){

	int cantVecinos, v;
	
	for(int i = 0; i<matAd.size(); i++){
		matAd[i].resize(0);
	}
	matAd.resize(0);
	matAd.resize(cantNodos);
	
	
	for(int i = 0; i<matAd.size(); i++){
		matAd[i].resize(cantNodos);
	}
	
	for(int i = 0; i < cantNodos; i++){
		is >> cantVecinos;
		for(int j = 0; j < cantVecinos; j++){
			is >> v;
			matAd[i][v-1] = true;
		}
	}

}

void guardarRes(ostream& os, set<int> c){
	os << c.size() << endl << "N ";
	set<int>::iterator it;
	for(it = c.begin(); it != c.end(); it++){
		os << ((*it) + 1) << ' ';
	}
	os << endl;
}


set<int> Grafo::maxClique() const {

	set<int> temp, aux;
	
	for(int v = 0; v < matAd.size(); v++){
		aux.insert(v);
		buscarMaxClique(aux,temp);
		aux.erase(v);
	}
	return temp;	
}



void Grafo::buscarMaxClique(set<int>& act, set<int>& res) const {

	for(int v = 0; v < matAd.size(); v++){
	
		if(vecinoDeTodos(v,act)){
			act.insert(v);
			buscarMaxClique(act,res);
			act.erase(v);
		}
	}
	if(act.size() > res.size())
		res = act;
}

bool Grafo::vecinoDeTodos(int v, const set<int>& c) const {
	
	bool res = true;
	set<int>::iterator it;
	for(it = c.begin(); it != c.end(); it++){
		res = res && sonAdyacentes(v,*it);
	}
	return res;
}

