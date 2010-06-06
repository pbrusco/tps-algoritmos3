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
	void cargar(const istream& is);
	set<int>& maxClique() const;
	void buscarMaxClique(set<int>& act, Grafo g, set<int>& res);
};







#endif
