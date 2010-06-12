#include "grafo.h"

#define forn(i,n) for(int i=0; i<n; i++)

using namespace std;

bool Grafo::sonAdyacentes(int v1, int v2) const {
	return matAd[v1][v2];
}


void Grafo::cargar(istream& is, int n) {
	int grado, v;

	/* Borro la matriz de adyacencia */
	forn(i,matAd.size()) {matAd[i].resize(0);}
	matAd.clear();

	/* Redimensiono la matriz de adyacencia */
	matAd.resize(n);
	forn(i,matAd.size()) {matAd[i].resize(n);}

	/* Borro y redimensiono el vector de componentes conexas */
	componentes.clear();
	componentes.resize(n);

	/* Borro y redimensiono el vector de grados de los nodos */
	grados.clear();
	grados.resize(n);

	/* Cargo los nodos, sus grados y sus vecinos */
	forn(i,n) {
		is >> grado;
		grados[i] = grado;
		forn(j,grado){
			is >> v;
			matAd[i][v-1] = true;
		}
	}
}


int Grafo::detectarCC() {
	int nro_cc = 1;
	forn(i,componentes.size()) {
		if (componentes[i] == 0) {
			dfs(i,nro_cc);
			nro_cc++;
		}
	}
	return nro_cc-1;
}


void Grafo::dfs(int v, int nro_cc) {
	componentes[v] = nro_cc;
	forn(i,componentes.size()) {
		if (sonAdyacentes(v,i) and componentes[i] == 0) dfs(i, nro_cc);
	}
}


void Grafo::maxClique(int nro_cc, int tamCliqueActual, set<int>& res) const{
	int v, grado_v;
	set<int> temp, vecinosFiltrados;
	heap heapGrados;

	crearHeapGrados(nro_cc, heapGrados);

	while(not heapGrados.empty() and heapGrados.top().first > tamCliqueActual) {
		v = heapGrados.top().second;
		grado_v = heapGrados.top().first;
		heapGrados.pop();
			 
		for(int i = grado_v; i>tamCliqueActual; i--) {
			temp.clear();
			vecinosFiltrados.clear();

		 	filtrarVecinosMenores(v, i, vecinosFiltrados);
			cliqueK(v, vecinosFiltrados, i, temp);

			if (tamCliqueActual < temp.size()) {
				tamCliqueActual = temp.size();
				res = temp;			
			}
		}
	}	 
}


void Grafo::filtrarVecinosMenores(int v, int k, set<int>& res) const {
	forn(i,matAd.size()) {
		if (sonAdyacentes(v,i) and grados[i] >= k and componentes[v] == componentes[i]) res.insert(i);
	}
}

void Grafo::cliqueK(int v, set<int>& vecinosFiltrados, int k, set<int>& res) const {

}


void Grafo::crearHeapGrados(int nro_cc, heap& res) const {
	forn(i,componentes.size()) {
		if (componentes[i] == nro_cc) res.push(make_pair(grados[i],i));
	}
}




