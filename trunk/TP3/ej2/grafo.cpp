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


bool Grafo::sonAdyacentes(int v1, int v2) const {
	return matAd[v1][v2];
}


bool Grafo::vecinoDeTodos(int v, const set<int>& c) const {
	bool res = true;
	forall(it,c) {
		res = res && sonAdyacentes(v,*it);
	}
	return res;
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
		if (sonAdyacentes(v,i) and componentes[i] == 0)
			dfs(i, nro_cc);
	}
}


void Grafo::maxClique(set<int>& res) {

	int cant_cc = detectarCC();		//aca se guarda la cantidad de componentes conexas distintas y le asigno a cada vertice un numero de componente
	
	bool encontre = false;			//se va a usar para saber si ya se encontro una clique del tamaño buscado
	int v, grado_v;
	heap heapGrados;
	set<int> tempComponente, vecinosFiltrados;
	
	forn(i,cant_cc) {

		/* Creo un heap con los nodos de la cc ordenados por grados */
		crearHeapGrados(i+1, heapGrados);

		/* Mientras haya nodos y tengan grado mayor o igual al tamaño de la maxima clique actual... */ 
		while (not heapGrados.empty() and heapGrados.top().first >= (int)res.size()) {

			/* Guardo la info del primer nodo del heap (v) y lo quito  */
			v = heapGrados.top().second;
			grado_v = heapGrados.top().first;
			heapGrados.pop();

			/* Busco si puedo formar una clique de tamaño mayor a la actual que contenga v */	 
			for (int j = grado_v; j >= (int)res.size() ; j--) {
				tempComponente.clear();
				vecinosFiltrados.clear();

				/* Filtro los nodos de la cc con grado mayor o igual a v */ 
			 	filtrarVecinosMenores(v, j, vecinosFiltrados);

				/* Si la cantidad de nodos me alcanza ... */			
				if ((int)vecinosFiltrados.size() >= j) {
				
					tempComponente.insert(v);
					
					/* ... me fijo si puedo formar una clique con los nodos filtrados y v */
					cliqueK(encontre, j+1, vecinosFiltrados, tempComponente);

					/* Si el tamaño de la clique que encontre es mayor que el de la actual la guardo*/
					if (res.size() < tempComponente.size()) {
						res = tempComponente;
					}
				}
			}
		
		}
		
		vaciarHeap(heapGrados);
	}
}


void Grafo::filtrarVecinosMenores(int v, int k, set<int>& res) const {
	forn(i,matAd.size()) {
		if (sonAdyacentes(v,i) and grados[i] >= k) res.insert(i);
	}
}


void Grafo::crearHeapGrados(int nro_cc, heap& res) const {
	forn(i,componentes.size()) {
		if(componentes[i] == nro_cc)
			res.push(make_pair(grados[i],i));
	}
}


void Grafo::cliqueK(bool& encontre, int tam, const set<int>& vecinosFiltrados, set<int>& res) const {
	if (not encontre) {
		forall(it,vecinosFiltrados) {
			if (vecinoDeTodos(*it,res)) {
				res.insert(*it);
				if(res.size() == tam){
					encontre = true;
				}
				else{
					cliqueK(encontre, tam, vecinosFiltrados, res);
				}
				
				if(not encontre){
					res.erase(*it);
				}
			}
		}
	}
}


void vaciarHeap(heap& h){

	while(!h.empty()){
		h.pop();
	}
}
