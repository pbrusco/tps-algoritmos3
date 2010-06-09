#ifndef __EJ1__
#define __EJ1__

#include <vector>
#include <set>
#include <list>

using namespace std;

struct Grafo{
	//atributos
	vector<vector<bool> > matAd;
	vector<bool> usados;
	//metodos
	bool sonAdyacentes(int v1, int v2) const;
	bool vecinoDeTodos(int v, const set<int>& c) const;
	void cargar(istream& is, int cantNodos);
	void maxClique(set<int> &resultado);
	list<int> vInicialesComponentesConexas() const;
	int limpiarPuentes(list<int>* listaComponentes);
	list<int>* vInicialesComponentesConexas();
	void maxCliqueEnComp(int v0,set<int> & resultado);
	void dfs(int vi);


};

void guardarRes(ostream& os, set<int> c);




#endif
