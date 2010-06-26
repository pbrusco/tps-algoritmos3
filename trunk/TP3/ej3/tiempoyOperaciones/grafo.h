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
	bool vecinoDeTodos(int v, const set<int>& c, unsigned long long int &) const;
	int cantVecinos(int v, const set<int>& c, unsigned long long int &) const;
	void cliqueConstructivo(set<int>& res, unsigned long long int &) const;
	void mayorFrontera(set<int>& res, unsigned long long int &) const;
	void fronteraEnComun(int u, int v, set<int>& res, unsigned long long int &) const;
	int masRelacionado(const set<int>& frontera, unsigned long long int &) const;
};

#endif
