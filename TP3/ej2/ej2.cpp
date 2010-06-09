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
		g.maxClique(cliqueMaximo);
		
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


void Grafo::maxClique(set<int>& resultado){
	int cantPuentesEliminados = 0;	
	
	set<int> setAux;

	list<int>* listaComponentes = vInicialesComponentesConexas();
	cantPuentesEliminados = limpiarPuentes(listaComponentes);
	
	if (cantPuentesEliminados > 0)	listaComponentes = vInicialesComponentesConexas();	
	
	
	for(list<int>::iterator comp = listaComponentes->begin(); comp != listaComponentes->end();comp++){
		maxCliqueEnComp(*comp,resultado);
		if (resultado.size() > setAux.size()){
			setAux = resultado;
		}
	}

	resultado = setAux;

}

int Grafo::limpiarPuentes(list<int>* listaComponentes){
	int cantPuentesEliminados = 0;

	return cantPuentesEliminados;
}


list<int>* Grafo::vInicialesComponentesConexas(){
	
	list<int>* lista = new list<int>();

	for(int i = 0; i<usados.size();i++){
		if (usados[i] != true){
			lista->push_back(i);
			dfs(i);
		}
	}
	

	return lista;

}

void Grafo::dfs(int vi){

	usados[vi] == true;
	
	for(int i = 0;i<usados.size();i++){
		if(usados[i] == false and sonAdyacentes(vi,i)) dfs(i);
	}



}


void Grafo::maxCliqueEnComp(int v0,set<int> & resultado){
	

}
