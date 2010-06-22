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
	cliqueConstructivo(res);
	bool atascado = true;
	int cota = definirCota();
	set<int> cliqueAux = res;			/* empiezo a partir de la solución constructiva */

	while ((cota > 0) and atascado) {

		/* Busco la clique mas grande que me sea posible haciendo una busqueda Tabu */
		atascado = busquedaTabu(cliqueAux);

		/* Si, me detuve porque empeoré demasiado, difersifico y busco nuevamente */
		if (atascado) diversificar(cliqueAux);

		/* Sino, me fijo si la clique encontrada es mejor que la que tenia como respuesta y la actualizo */ 
		else if (cliqueAux.size() > res.size()) res = cliqueAux;

		cota--;
	} 
}


int Grafo::definirCota() const {
	int n = matAd.size();
	return n*n;
}


void Grafo::diversificar(set<int>& res) const {
	//COMPLETAR
}


bool Grafo::busquedaTabu(set<int>& res) const {
	bool respuesta = false; 
	int nodo, empeore=0, n=matAd.size(), cota=definirCota();
	listaTabu Tabu;
	Heap vecindad;
	set<int> agregados, cliqueTemp = res;
	
	/* Mientras la clique temporal no esté vacía y no haya empeorado n veces y no haya pasado la cota... */
	while ((cota > 0) and (empeore < n) and (not cliqueTemp.empty())) {

		/* Si la lista Tabu tiene n elementos, quito el primero de a lista */
		if (Tabu.first.size() == n) {
			(Tabu.first).pop_front();
			(Tabu.second).pop_front();
		}

		/* Busco en la clique temporal el nodo de menor grado */
		nodo = nodoConMenorGrado(cliqueTemp);			
		
		/* Si no está en la lista Tabu-Agregados lo elimino de la clique y lo agrego a la lista Tabu-Eliminados */
		if (not estaEnTabuAgregados(nodo,Tabu)) {
			cliqueTemp.erase(nodo);
			Tabu.first.push_back(nodo);
		}
			
		/* Busco los nodos que no estan en la clique y que no estén en la lista Tabu-Eliminados, y que tengan como vecino */
		/* al menos a algún nodo de la clique temporal */
		agregados.clear();
		vaciarHeap(vecindad);		
		definirVecindad(Tabu,cliqueTemp,vecindad);
	
		/* Mientras que la vecindad definida no sea vacía, evalúo si el nodo del tope de la vecindad es vecino de todos */
		/* los nodos de la clique temporal. De ser así lo agrego a esta y lo registro. Luego borro de la vecindad al nodo */
		/* que acabo de evaluar */
		while (not vecindad.empty()) {
			nodo = vecindad.top().second;
			vecindad.pop();
			if (vecinoDeTodos(nodo, cliqueTemp)) {
				cliqueTemp.insert(nodo);
				agregados.insert(nodo);
			}
		}
		
		/* Registro los nodos agregados en la lista Tabu-Agregados */
		Tabu.second.push_back(agregados);
				
		/* Si no agregue ningún nodo, como quite un nodo y no agregué otros significa que empeoré */
		/* Incremento el contador de "empeoramiento" */
		if (agregados.empty()) empeore++;
		
		/* En cambio, si agregué nodos, y la clique temporal resultante tiene mayor tamaño que la que tenía como */
		/* respuesta, actualizo la respuesta y pongo en 0 el contador de "empeoramiento" */ 
		else if (cliqueTemp.size() > res.size()) {
			res = cliqueTemp;
			empeore = 0;
		}
	}
	if (empeore == n) respuesta = true;
	return respuesta;
}


int Grafo::nodoConMenorGrado(const set<int>& c) const {
	int res = grados[*c.begin()];
	forall(it,c) {
		if (grados[res] > grados[*it]) res = *it;
	}
	return res;
}


void Grafo::definirVecindad(const listaTabu& T, const set<int>& c, Heap& res) const {
	set<int> aux;
	forall(it,c) {
		forn(i,matAd.size()) {
			if (not estaEnTabuEliminados(i,T) and sonAdyacentes(i,*it) and c.count(i) == 0) aux.insert(i);
		}
	}
	ponerEnHeap(true, aux, res);
}


void Grafo::ponerEnHeap(bool maxHeap, const set<int>& c , Heap& res) const{
	if (maxHeap) forall(it,c) {res.push(make_pair(grados[*it],*it));}
	else forall(it,c) {res.push(make_pair(-grados[*it],*it));}
}


bool estaEnTabuEliminados(int v, const listaTabu& T) {
	bool res = true;
	forall(it,T.first) {res = res and (v != *it);}
	return res;
}


bool estaEnTabuAgregados(int v, const listaTabu& T) {
	bool res = true; 
	forall(it, T.second) {res = res and ((*it).count(v) == 0);}
	return res;
}


void vaciarHeap(Heap& h) {
	while(not h.empty()) {h.pop();}
}
