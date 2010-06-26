#include "grafo.h"
#include <math.h>

#define forn(i,n) for(int i=0; i<n; i++)
#define forall(it,X) for(typeof((X).begin()) it = (X).begin(); it != (X).end(); it++)

using namespace std;

void Grafo::cargar(istream& is, int n) {
	int grado, v;

	/* Borro la matriz de adyacencia */
	forn(i,matAd.size()) {matAd[i].resize(0);}
	matAd.clear();

	/* Redimensiono la matriz de adyacencia */
	matAd.resize(n);
	forn(i,matAd.size()) {matAd[i].resize(n);}

	/* Cargo los nodos, sus grados y sus vecinos */
	forn(i,n) {
		is >> grado;
		forn(j,grado){
			is >> v;
			matAd[i][v-1] = true;
		}
	}
}


bool Grafo::sonAdyacentes(int v1, int v2) const {
	return matAd[v1][v2];
}


bool Grafo::vecinoDeTodos(int v, const set<int>& c, unsigned long long int &operaciones) const {
	bool res = true;
	operaciones++;
	forall(it,c) {
		res = res && sonAdyacentes(v,*it);
		operaciones += 2;
	}
	return res;
}


int Grafo::cantVecinos(int v, const set<int>& c, unsigned long long int &operaciones) const {
	int res = 0;
	forall(it,c) {
		if (sonAdyacentes(v,*it)){
			res++;
			operaciones++;
		}
		operaciones++;
	}
	return res;
}


void Grafo::cliqueConstructivo(set<int>& res, unsigned long long int &operaciones) const {
	int v;
	set<int> frontera;
	mayorFrontera(frontera,operaciones);
	while (frontera.size() != 0) {
		operaciones += 2;
		v = masRelacionado(frontera,operaciones);
		if (vecinoDeTodos(v,res,operaciones)){
			res.insert(v);
			operaciones = operaciones + (int) log10(res.size());
		}
		operaciones = operaciones + ((int) (log10(frontera.size()))) + 1;
		frontera.erase(v);
	}
	if (res.size() == 0)
		res.insert(0);
	operaciones++;
}


void Grafo::mayorFrontera(set<int>& res, unsigned long long int &operaciones) const {
	set<int> aux;
	for(int i=0; i<matAd.size(); i++) {
		for(int j =i+1; j<matAd.size(); j++) {
			fronteraEnComun(i,j,aux,operaciones);
			if (aux.size() > res.size()) {
				res = aux;
				operaciones += 4;
			}
			operaciones += 3;
		}
	}
}


void Grafo::fronteraEnComun(int u, int v, set<int>& res, unsigned long long int &operaciones) const {

	res.clear();
	if (sonAdyacentes(u,v)) {
		forn(j,matAd.size()) {
			if (sonAdyacentes(u,j) && sonAdyacentes(v,j)){
				res.insert(j);
				operaciones += log10(res.size());
			}
			operaciones += 3;
		}
		res.insert(u);
		res.insert(v);
		operaciones += (2*log10(res.size()));
	}
	operaciones +=2;
}


int Grafo::masRelacionado(const set<int>& frontera, unsigned long long int &operaciones) const {
	int res = *frontera.begin(), vecinosRes = 0, vecinosAux;
	forall(it,frontera) {
		vecinosAux = cantVecinos(*it,frontera, operaciones);
		if(vecinosAux > vecinosRes){
			res = *it;
			vecinosRes = vecinosAux;
			operaciones += 2;
		}
		operaciones++;
	}
	return res;
}
