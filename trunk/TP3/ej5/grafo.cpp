#include "grafo.h"

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

	/* Redimensiono el vector de grados */
	grados.clear();
	grados.resize(n);
	
	/* Cargo los nodos, sus grados y sus vecinos */
	forn(i,n) {
		is >> grado;
		grados[i] = grado;
		forn(j,grado) {
			is >> v;
			matAd[i][v-1] = true;
		}
	}
}


bool Grafo::sonAdyacentes(int v1, int v2) const {
	return matAd[v1][v2];
}


bool Grafo::vecinoDeTodos(int v, const set<int>& c) const {
	bool res = true;
	forall(it,c) {	res = res and sonAdyacentes(v,*it);}
	return res;
}


void Grafo::vecinos(int v, set<int>& res) const {
	forn(i,matAd.size()) {
		if (sonAdyacentes(i,v)) res.insert(i);
	}
}


int Grafo::cantVecinos(int v, const set<int>& c) const {
	int res = 0;
	forall(it,c) {
		if (sonAdyacentes(v,*it)) res++;
	}
	return res;
}


void Grafo::cliqueConstructivo(set<int>& res) const {
	int v;
	set<int> frontera;

	mayorFrontera(frontera);
	while (frontera.size() != 0) {
		v = masRelacionado(frontera);
		if (vecinoDeTodos(v,res)) res.insert(v);
		frontera.erase(v);
	}
	if (res.size() == 0) res.insert(0);
}


void Grafo::mayorFrontera(set<int>& res) const {
	set<int> aux;
	forn(i,matAd.size()) {
		for(int j =i+1; j<matAd.size(); j++) {
			aux.clear();
			fronteraEnComun(i,j,aux);
			if (aux.size() > res.size()) {
				res = aux;
			}
		}
	}
}


void Grafo::fronteraEnComun(int u, int v, set<int>& res) const {
	if (sonAdyacentes(u,v)) {
		forn(j,matAd.size()) {
			if (sonAdyacentes(u,j) and sonAdyacentes(v,j)) res.insert(j);
		}
		res.insert(u);
		res.insert(v);
	}
}


int Grafo::masRelacionado(const set<int>& frontera) const {
	int res = *frontera.begin(), vecinosRes = 0, vecinosAux;
	forall(it,frontera) {
		vecinosAux = cantVecinos(*it,frontera);
		if (vecinosAux > vecinosRes){
			res = *it;
			vecinosRes = vecinosAux;
		}
	}
	return res;
}


void Grafo::cliqueTabu(set<int>& res) const {
	set<int> cliqueAux = res;
	
	/* empiezo a partir de la solución constructiva */
	cliqueConstructivo(res); 
	cliqueAux = res;			

	/* Busco la clique maxima y diversifico n/2 veces */
	forn(i,matAd.size()/2) {
		
		/* Busco la clique mas grande que me sea posible haciendo una busqueda Tabu */
		busquedaTabu(cliqueAux);

		/* Me fijo si la clique encontrada es mejor que la que tenia como respuesta y la actualizo */ 
		if (cliqueAux.size() > res.size()) res = cliqueAux;

		/* Borro el contenido de cliqueAux y genero una solución trivial para diversificar y ver si encuentro una solucion mejor*/	
		cliqueAux.clear();
		diversificar(cliqueAux);
	} 
}


int Grafo::definirCota() const {
	int n = matAd.size();
	return 10*n;
}


void Grafo::diversificar(set<int>& res) const {
	set<int> aux;
	int v = randomNmbr(0, matAd.size());
	res.insert(v);
	vecinos(v, aux);
	if (not aux.empty()) {
		int n = randomNmbr(0, aux.size());
		set<int>::iterator it = aux.begin();
		forn(i,n) {it++;}
		res.insert(*it);
	}
}


void Grafo::busquedaTabu(set<int>& res) const {
	bool agregue = false;
	int v, u, desmejore = 0, n=matAd.size(), stop=definirCota();
	vector<unsigned long long> TabuAgregados(n);
	vector<unsigned long long> TabuEliminados(n);
	Heap vecindad;
	set<int> cliqueTemp = res;
	
	/* Mientras no se cumplan las condiciones de parada... */
	forn(nro_it, stop) {

		/* --- */
		if ((desmejore == n/4) or cliqueTemp.empty()) break;

		/* Busco en la clique temporal el nodo de menor grado que no esté en la lista Tabu-Agregados, */
		v = nodoConMenorGrado(nro_it,TabuAgregados,cliqueTemp);			

		/* Elimino el nodo de la clique y lo agrego el nodo eliminado a la lista Tabu-Eliminados*/
		if (v!=-1) {
			cliqueTemp.erase(v);
			TabuEliminados[v] = nro_it + n/2;
		}

		/* Busco los nodos que no estan en la clique y que no están en la lista Tabu-Eliminados, y que tengan como vecino */
		/* al menos a algún nodo de la clique temporal */
		vaciarHeap(vecindad);		
		definirVecindad(nro_it,TabuEliminados,cliqueTemp,vecindad);

		/* Mientras que la vecindad definida no sea vacía, evalúo si el nodo del tope de la vecindad es vecino de todos */
		/* los nodos de la clique temporal. De ser así lo agrego a esta y lo registro. Luego borro de la vecindad al nodo */
		/* que acabo de evaluar */
		while (not vecindad.empty()) {
			agregue = false;
			u = vecindad.top().second;
			vecindad.pop();
			if (vecinoDeTodos(u, cliqueTemp)) {
				agregue = true;
				cliqueTemp.insert(u);
				TabuAgregados[u] = nro_it + n/2;
			}
		}

		/* Si la clique temporal resultante tiene mayor tamaño que la que tenía como respuesta, actualizo la respuesta */
		/* y reseteo el contador de desmejora */
		if (cliqueTemp.size() > res.size()) {
			res = cliqueTemp;
			desmejore = 0;
		}
		
		/* Si saque un nodo de la clique temporal y no agregue nuevos, incremento el contador de desmejora */
		else if (v!=-1 and (not agregue)) desmejore++;
	}
}


int Grafo::nodoConMenorGrado(int nro_it, vector<unsigned long long> tAgreg, const set<int>& c) const {
	set<int> aux;
	forall(it,c) {
		if (tAgreg[*it] <= nro_it) aux.insert(*it);
	}
	if (aux.empty()) return -1;
	else {
		int res = *aux.begin();
		forall(it,aux) {
			if (grados[res] > grados[*it]) res = *it;
		}
		return res;
	}
}


void Grafo::definirVecindad(int nro_it, vector<unsigned long long> tElim, const set<int>& c, Heap& res) const {
	set<int> aux;
	forall(it,c) {
		forn(i,matAd.size()) {
			if (sonAdyacentes(i,*it) and c.count(i) == 0) aux.insert(i);
		}
	}
	
	forall(it,aux) {
		if (tElim[*it] > nro_it) aux.erase(*it);
	}
	
	ponerEnHeap(true, aux, res);
}


void Grafo::ponerEnHeap(bool maxHeap, const set<int>& c , Heap& res) const{
	if (maxHeap) forall(it,c) {res.push(make_pair(grados[*it],*it));}
	else forall(it,c) {res.push(make_pair(-grados[*it],*it));}
}


void vaciarHeap(Heap& h) {
	while(not h.empty()) {h.pop();}
}


int randomNmbr(int desde, int hasta, int x) {
	int res = x;
	while (res == x) {res = (rand() % (hasta-desde))+desde;}
	return res;
}