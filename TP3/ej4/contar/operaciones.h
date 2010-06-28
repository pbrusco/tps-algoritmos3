#ifndef __EJ1__
#define __EJ1__

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
	bool vecinoDeTodos(int v, const set<int>& c, unsigned long long int &) const;
	int cantVecinos(int v, const set<int>& c, unsigned long long int &) const;
	void cliqueConstructivo(set<int>& res, unsigned long long int &) const;
	void mayorFrontera(set<int>& res, unsigned long long int &) const;
	void fronteraEnComun(int u, int v, set<int>& res, unsigned long long int &) const;
	int masRelacionado(const set<int>& frontera, unsigned long long int &) const;
	

	void busquedaLocal(set<int> &cliqueMaximo,unsigned long long int &) const;
	void vecinosAMaxHeap(const set<int>& clique, Heap &vecinos, const int v,unsigned long long int &) const;
	void deCliqueAMinHeap(const set<int>& clique, Heap &cliqueDeMenorAMayor,unsigned long long int &) const;
	void cambiarSiMaximiza(set<int>& clique, bool &cambio,unsigned long long int &) const;
};

void guardarRes(ostream& os, set<int> c);
void vaciarHeap(Heap& h);




#endif
