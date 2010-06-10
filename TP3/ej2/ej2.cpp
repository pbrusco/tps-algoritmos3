#include <iostream>
#include <fstream>
#include "ej2.h"

using namespace std;


int main(){
	
	int cantNodos,cantComp;
	Grafo g;
	set<int> cliqueMaximo;
	set<int> auxClique;
	ifstream is;
	ofstream os;
	os.open("../out/Tp3EXACTO.out");
	is.open("../in/Tp3.in");
	is >> cantNodos;
	
	while(cantNodos != -1){
	
		g.cargar(is,cantNodos);
		cantComp = g.detectarComponentesConexas();
		
				
		
		for(int i = 1;i<=cantComp;i++){
			g.maxClique(i,auxClique,cliqueMaximo.size());
			if (auxClique.size() > cliqueMaximo.size()){
				cliqueMaximo = auxClique;			
			}			
			auxClique.clear();		
		}
		
		//guardo o muestro el resultado
		guardarRes(os,cliqueMaximo);
		
	
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
	matAd.clear();
	matAd.resize(cantNodos);
	
	
	for(int i = 0; i<matAd.size(); i++){
		matAd[i].resize(cantNodos);
	}
	
	componentes.clear();
	componentes.resize(cantNodos);
	
	grados.clear();
	grados.resize(cantNodos);
	
	for(int i = 0; i < cantNodos; i++){
		is >> cantVecinos;
		grados[i] = cantVecinos;
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



int Grafo::detectarComponentesConexas(){
	int comp = 1;
	for(int i = 0; i<componentes.size();i++){
		if (componentes[i] == 0){
			dfs(i,comp);
			comp++;
		}
	}
	
	return comp-1;
}

void Grafo::dfs(int vi,int comp){
	componente[vi] = comp;
	
	for(int i = 0;i<componentes.size();i++){
		if(componentes[i] == 0 and sonAdyacentes(vi,i)) dfs(i);
	}

}


void Grafo::maxClique(int comp,set<int>& maxCliqueComponente,int tamCliqueActual){
	priority_queue<pair<int,int> > heapGrados;
	crearHeapGrados(heapGrados,comp);
	set<int> cliqueAux;
	int v0,grado_v0;
	set<int> vecinosFiltrados;

//si no se entiende , ver el pseudo! (pag. 82 de la carpeta 3 de pablo (2))
	while(not heapGrados.empty() and heapGrados.top().first() > tamCliqueActual)
	{

		v0 = heapGrados.top().second();
		grado_v0 = heapGrados.top().first();
		heapGrados.pop();
			 
		for(int i = grado_v0; i > tamCliqueActual;i--){
			vecinosFiltrados.clear();
		 	filtrarVecinosMenores(v0,i,vecinosFiltrados);
		 	
			cliqueAux.clear();
			cliqueK(v0,vecinosFiltrados,i,cliqueAux);
			if(tamCliqueActual < cliqueAux.size()){
				tamCliqueActual = cliqueAux.size();
				maxCliqueComponente = cliqueAux;			
			}
		}
	}	 
}
void Grafo::filtrarVecinosMenores(int v0,int i,set<int> & vecinosFiltrados);
void Grafo::cliqueK(int v0,set<int>& vecinosFiltrados, int k, set<int>& resultado);
void Grafo::crearHeapGrados(priority_queue<pair<int,int> >& ,int comp);

