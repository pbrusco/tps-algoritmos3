#include "grafo.h"

#define forn(i,n) for(int i=0; i<n; i++)
#define forall(it,X) for(typeof((X).begin()) it = (X).begin(); it != (X).end(); it++)

int CANTOPERACIONES;

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
	return matAd[v1][v2];CANTOPERACIONES++;
}


bool Grafo::vecinoDeTodos(int v, const set<int>& c) const {
	bool res = true;
	forall(it,c) {
		res = res && sonAdyacentes(v,*it);CANTOPERACIONES++;
	}
	return res;
}


int Grafo::detectarCC() {
	int nro_cc = 1;
	forn(i,componentes.size()) {
	CANTOPERACIONES++;
		if (componentes[i] == 0) {
			dfs(i,nro_cc);CANTOPERACIONES++;
			nro_cc++;CANTOPERACIONES++;
		}
	}
	return nro_cc-1;CANTOPERACIONES++;
}


void Grafo::dfs(int v, int nro_cc) {
	componentes[v] = nro_cc;CANTOPERACIONES++;
	forn(i,componentes.size()) {
	CANTOPERACIONES++;
		if (sonAdyacentes(v,i) and componentes[i] == 0)
			dfs(i, nro_cc);CANTOPERACIONES++;
	}
}


int Grafo::maxClique(set<int>& res) {

CANTOPERACIONES = 0;

	int cant_cc = detectarCC();	CANTOPERACIONES++;	
	
	
	bool encontre = false;	CANTOPERACIONES++;		//se va a usar para saber si ya se encontro una clique del tamaño buscado
	int v, grado_v; CANTOPERACIONES++;CANTOPERACIONES++;
	
	heap heapGrados; CANTOPERACIONES++;
	
	set<int> tempComponente, vecinosFiltrados; CANTOPERACIONES++;CANTOPERACIONES++;
	
	forn(i,cant_cc) {

		/* Creo un heap con los nodos de la cc ordenados por grados */
		crearHeapGrados(i+1, heapGrados);CANTOPERACIONES++;

		/* Mientras haya nodos y tengan grado mayor o igual al tamaño de la maxima clique actual... */ 
		while (not heapGrados.empty() and heapGrados.top().first >= res.size()) {
		CANTOPERACIONES++;CANTOPERACIONES++;
			/* Guardo la info del primer nodo del heap (v) y lo quito  */
			v = heapGrados.top().second;CANTOPERACIONES++;
			
			grado_v = heapGrados.top().first;CANTOPERACIONES++;
			heapGrados.pop();CANTOPERACIONES++;
			/* Busco si puedo formar una clique de tamaño mayor a la actual que contenga v */	 
			for (int tamCliqueABuscar = grado_v+1; tamCliqueABuscar > (int)res.size() ; tamCliqueABuscar--) {
			CANTOPERACIONES++;
				tempComponente.clear();CANTOPERACIONES++;
				vecinosFiltrados.clear();CANTOPERACIONES++;

				/* Filtro los nodos de la cc con grado mayor o igual al tamaño de la clique que busco -1 que sean vecinos de v */
				/* Menos 1 ya que la si busco una clique de tamaño n, sus nodos deben tener grados mayores a n-1*/
			 	filtrarVecinosMenores(v, tamCliqueABuscar-1, vecinosFiltrados);CANTOPERACIONES++;

				/* Si la cantidad de nodos me alcanza ... +1 por v */			
				if ((int)vecinosFiltrados.size()+1 >= tamCliqueABuscar) {
				
					tempComponente.insert(v);CANTOPERACIONES++;

					/* ... me fijo si puedo formar una clique con los nodos filtrados y v */
					encontre = false;CANTOPERACIONES++;
					cliqueK(encontre, tamCliqueABuscar, vecinosFiltrados, tempComponente);CANTOPERACIONES++;
					
					/* Si el tamaño de la clique que encontre es mayor que el de la actual la guardo*/
					if (res.size() < tempComponente.size()) {
					CANTOPERACIONES++;
						res = tempComponente;CANTOPERACIONES++;
					}
				}
			}
		
		}
		
		vaciarHeap(heapGrados);CANTOPERACIONES++;
	}
return CANTOPERACIONES++;
}


void Grafo::filtrarVecinosMenores(int v, int gradoMinimo, set<int>& res) const {
	forn(i,matAd.size()) {
	CANTOPERACIONES++;
		if (sonAdyacentes(v,i) and grados[i] >= gradoMinimo) res.insert(i);
		CANTOPERACIONES++;
	}
}


void Grafo::crearHeapGrados(int nro_cc, heap& res) const {
	forn(i,componentes.size()) {
	CANTOPERACIONES++;
		if(componentes[i] == nro_cc)
			res.push(make_pair(grados[i],i));
			CANTOPERACIONES++;
	}
}


void Grafo::cliqueK(bool& encontre, int tam, set<int> vecinosFiltrados, set<int>& res) const {
	

	int w;
CANTOPERACIONES++;
	
	while(vecinosFiltrados.empty() == false and encontre == false) {
			CANTOPERACIONES++;
			
			w = *vecinosFiltrados.begin();
			CANTOPERACIONES++;
			if (vecinoDeTodos(w,res)){	
				res.insert(w);CANTOPERACIONES++;
				vecinosFiltrados.erase(w);		CANTOPERACIONES++;
				if (res.size() < tam) cliqueK(encontre,tam,vecinosFiltrados,res);
				else encontre = true;
				CANTOPERACIONES++;
				if(!encontre) res.erase(w);CANTOPERACIONES++;
			}
			else{
				res.erase(w);CANTOPERACIONES++;
				vecinosFiltrados.erase(w);CANTOPERACIONES++;
			}
	}
	
}




void vaciarHeap(heap& h){

	while(!h.empty()){
		h.pop();CANTOPERACIONES++;
	}
}
