#ifndef __EJ1__
#define __EJ1__

#include <vector>
#include <set>

using namespace std;

struct Grafo{
	//atributos
	vector<vector<bool> > matAd;
	
	//metodos
	int cantVecinos(int v, const set<int>& vecindad) const;
	bool sonAdyacentes(int v1, int v2) const;
	bool vecinoDeTodos(int v, const set<int>& c) const;
	void cargar(istream& is, int cantNodos);
	set<int> fronteraEnComun(int u, int v) const;
	set<int> losMasFronterizos(int &u, int &v) const;
	int masRelacionado(const set<int>& frontera) const;
	set<int> cliqueConstructivo() const;

	void busquedaLocal(set<int> &cliqueMaximo) const;
	set<int> frontera(const set<int>& clique) const;
	void cambiarSiMaximiza(set<int>& clique, const set<int>& vecindad, bool &cambio) const;
};

void guardarRes(ostream& os, set<int> c);





#endif
