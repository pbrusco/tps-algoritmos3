#ifndef __GRAFO__
#define __GRAFO__

#include <iostream>
#include <vector>
#include <set>

#define matriz vector<vector<bool > >

using namespace std;

struct Grafo {
	/* atributos */
	matriz matAd;

	/* metodos */
	void cargar(istream& is, int n);
	bool sonAdyacentes(int v1, int v2) const;
	bool vecinoDeTodos(int v, const set<int>& c) const;
	int cantVecinos(int v, const set<int>& c) const;
	void cliqueConstructivo(set<int>& res) const;
	void mayorFrontera(set<int>& res) const;
	void fronteraEnComun(int u, int v, set<int>& res) const;
	int masRelacionado(const set<int>& frontera) const;
};

#endif
