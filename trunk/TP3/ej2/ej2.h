#ifndef __EJ1__
#define __EJ1__

#include <vector>
#include <set>

using namespace std;

struct Grafo{
	//atributos
	vector<vector<bool> > matAd;
	
	//metodos
	bool sonAdyacentes(int v1, int v2) const;
	bool vecinoDeTodos(int v, const set<int>& c) const;
	void cargar(istream& is, int cantNodos);
	set<int> maxClique() const;
	void buscarMaxClique(set<int>& act, set<int>& res) const;
};

void guardarRes(ostream& os, set<int> c);





#endif
