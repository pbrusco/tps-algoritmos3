#ifndef __EJ4__
#define __EJ4__

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <utility>
#include <set>

using namespace std;


typedef priority_queue<pair<int,int> > Heap;

struct Grafo{
	//atributos
	vector<vector<bool> > matAd;
	vector<int> grados;
	
	//metodos
	
	void cargar(istream& is, int n);
	bool sonAdyacentes(int v1, int v2) const;
	bool vecinoDeTodos(int v, const set<int>& c) const;
	int cantVecinos(int v, const set<int>& c) const;
	void cliqueConstructivo(set<int>& res) const;//cambio
	void mayorFrontera(set<int>& res) const;//cambio, era losMasFronterizos
	void fronteraEnComun(int u, int v, set<int>& res) const;//cambio
	int masRelacionado(const set<int>& frontera) const;
	

	void busquedaLocal(set<int> &cliqueMaximo) const;
	void vecinosAMaxHeap(const set<int>& clique, Heap &vecinos, const int v) const;
	void deCliqueAMinHeap(const set<int>& clique, Heap &cliqueDeMenorAMayor) const;
	void cambiarSiMaximiza(set<int>& clique, bool &cambio) const;
};

double timeval_diff(struct timeval& a, struct timeval& b);
double resolverBusqLocal(const string& input, const string& output);
void guardarRes(ostream& os, set<int> c);
void vaciarHeap(Heap& h);

#endif
