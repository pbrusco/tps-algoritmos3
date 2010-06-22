#ifndef __GRAFO__
#define __GRAFO__

#include <iostream>
#include <queue>
#include <vector>
#include <list>
#include <set>

#define matriz vector<vector<bool > >
#define Heap priority_queue<pair<int,int> >
#define listaTabu pair<list<int>, list<set<int> > >

using namespace std;

struct Grafo {
	/* atributos */
	matriz matAd;
	vector<int> grados;

	/* metodos */
	void cargar(istream& is, int n);
	bool sonAdyacentes(int v1, int v2) const;
	bool vecinoDeTodos(int v, const set<int>& c) const;
	int cantVecinos(int v, const set<int>& c) const;
	void cliqueConstructivo(set<int>& res) const;
	void mayorFrontera(set<int>& res) const;
	void fronteraEnComun(int u, int v, set<int>& res) const;
	int masRelacionado(const set<int>& frontera) const;
	void cliqueTabu(set<int>& res) const;
	int definirCota() const;
	void diversificar(set<int>& res) const;
	bool busquedaTabu(set<int>& res) const;
	int nodoConMenorGrado(const set<int>& c) const;
	void definirVecindad(const listaTabu& T, const set<int>& c, Heap& res) const;
	void ponerEnHeap(bool maxHeap, const set<int>& c , Heap& res) const;
};

void vaciarHeap(Heap& h);
bool estaEnTabuEliminados(int v, const listaTabu& T);
bool estaEnTabuAgregados(int v, const listaTabu& T);

void printSet(ostream& os, const set<int>& c);
#endif
