#ifndef __GRAFO__
#define __GRAFO__

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <set>
#include <list>

#define matriz vector<vector<bool > >
#define heap priority_queue<pair<int,int> >

using namespace std;

struct Grafo{
	/* atributos */
	matriz matAd;
	vector<int> grados;
	vector<int> componentes;

	/* metodos */
	void cargar(istream& is, int n);
	void dfs(int v, int nro_cc);
	int detectarCC();

	bool sonAdyacentes(int v1, int v2) const;
	bool vecinoDeTodos(int v, const set<int>& c) const;
	void maxClique(int nro_cc, int tamCliqueActual, set<int>& res) const;
	void cliqueK(int v, set<int>& vecinosFiltrados, int k, set<int>& res) const;
	void crearHeapGrados(int nro_cc, heap& res) const;
	void filtrarVecinosMenores(int v, int k, set<int>& res) const;
};

#endif
