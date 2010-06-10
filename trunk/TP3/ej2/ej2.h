#ifndef __EJ1__
#define __EJ1__

#include <vector>
#include <set>
#include <list>
#include <priority_queue>
#include <utility>

using namespace std;

struct Grafo{
	//atributos
	vector<vector<bool> > matAd;
	vector<int> componentes;
	vector<int> grados;
	//metodos
	bool sonAdyacentes(int v1, int v2) const;
	bool vecinoDeTodos(int v, const set<int>& c) const;
	void cargar(istream& is, int cantNodos);
	void dfs(int vi, int);
	int detectarComponentesConexas();
	
	
	void maxClique(int comp,set<int>& clique,int tamCliqueActual);
	void cliqueK(int v0,set<int>& vecinosFiltrados, int k, set<int>& resultado);
	void crearHeapGrados(priority_queue<pair<int,int> >& ,int comp);


};

void guardarRes(ostream& os, set<int> c);




#endif
