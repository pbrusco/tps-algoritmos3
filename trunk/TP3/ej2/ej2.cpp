#include <iostream>
#include "ej2.h"

using namespace std;


int main(){

	return 0;
}

//implementaciones

bool Grafo::sonAdyacentes(int v1, int v2) const {
	return matAd[v1][v2];
}


void Grafo::cargar(const istream& is){

	int cantNodos, cantVecinos, v;
	for(int i = 0; i<=matAd.size(); i++){
		matAd[i].resize(0);
	}
	matAd.resize(0);
	is >> cantNodos;

}


set<int>& Grafo::maxClique() const{}
void Grafo::buscarMaxClique(set<int>& act, Grafo g, set<int>& res){}

