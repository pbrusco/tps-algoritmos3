#include <iostream>

using namespace std;


struct Grafo{

	struct datos{
		int padre;
		set<int> vecinos;
		set<int> ejesHasta;
		bool visitado;
		};
		
	set<int> ejesUsados;
	map<int,datos> info;
} //Ver como inicializar


int main(){

	Grafo G;

	cargarGrafo(G);

	dfs_ciclos(1);

	return 0;
}



int dfs_ciclos(int vertice){

	G.info[vertice].ejesHasta = G.info[G.info[padre]].ejesHasta + eje(v,G.info[vertice].padre);
	G.info[vertice].visitado = true;
	
	for(set<int>::iterator it = G.info[vertice].vecinos.begin(); it != G.info[vertice].vecinos.end();it++){
	
		if(not G.info[*it].visitado){
			G.info[*it].padre = vertice;
		}
		else{
		
			if(G.info[vertice].padre != (*it)){
				G.ejesUsados.insert( G.info[vertice].ejesHasta - G.info[*it].ejesHasta + eje(*it,vertice);
			}
		}
		
	}
}
	
	


