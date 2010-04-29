#include <iostream>

using namespace std;


void insertarResta(set<int>& ejesUsados,const set<int>& vEjesHasta,const set<int>& wEjesHasta);	
int eje(const Grafo& G, int v1,int v2); //O(1)

struct Grafo{
	
	struct datos{
		int padre = 0;
		set<int> vecinos;
		set<int> ejesHasta;
		bool visitado = false;
		};
		
	set<int> ejesUsados; //EJes percenecientes a ALGUN ciclo.
 	map<int,datos> info;	//DADO UN VERTICE, DA LA INFO (PADRE-VECINOS-EJESHASTA-VISITADO)
	vector<vector<int> > matrizAdyNombrada;	//es una matriz de adyacencia donde en las intersecciones tiene el nombre del eje que los une.

} //Ver como inicializar


int main(){

	ifstream entrada;
	ofstream salida;
	Grafo G;
	
	entrada.open("Tp2Ej2.in");
	salida.open("miSaldo.out");

	bool sigueArchivo;
	
	do{
		sigueArchivo = cargar(G,entrada);

		if(sigueArchivo){ 
			k = dfs_ciclos(1);
			if(k < n || G.ejesUsados.size() < m) salida<< "no" << endl;}
			else salida << "fuertemente conexo" << endl;

	}while(sigueArchivo);
	


	

	//if(k < n || G.ejesUsados.size() < m) cout << "NO SE PUEDE" << endl;
	//else cout << "SI SE PUEDE; SI SE PUEDE; SI SE PUEDE" << endl;

	return 0;
}



int dfs_ciclos(int vertice){ //ESTO VA A SER LLAMADO K VECES CON K<=n)

	G.info[vertice].ejesHasta = G.info[G.info[padre]].ejesHasta  // Linear on sizes (destruction, copy construction). O(n).(recordar que los ejes hasta son la misma cant que los nodos visitados)
	G.info[vertice].ejesHasta.insert(eje(v,G.info[vertice].padre)); //( set.insert(x) ), logarithmic. + C(eje(v1,v2))
	G.info[vertice].visitado = true;	//O(1)
	
	for(set<int>::iterator it = G.info[vertice].vecinos.begin(); it != G.info[vertice].vecinos.end();it++){ //Recorre los vecinos del vertice actual //Puede ejecutarse hasta n-1 veces
	
		if(not G.info[*it].visitado){				//Si el vecino no esta visitado (O(1))
			G.info[*it].padre = vertice;			//O(1)
			return dfs_ciclos(*it) + 1;				//lo visito
		}
		else{							//Si el vecino esta visitado
		
			if(G.info[vertice].padre != (*it)){		//si no es el padre, entonces tengo un circuito O(1)
				insertarResta(G.ejesUsados,G.info[vertice].ejesHasta,G.info[*it].ejesHasta);		//O(n.log n) (VER)	
				G.ejesUsados.insert(eje(*it,vertice));		//O(log() + C(eje());
			}
		}
		
	}
	return 0;
}
	

int eje(const Grafo& G, int v1,int v2){ //O(1)

	return G.matrizAdyNombrada[v1][v2];
	
	
}



void insertarResta(set<int>& ejesUsados,const set<int>& vEjesHasta,const set<int>& wEjesHasta){

	for(set<int>::iterator it = vEjesHasta.begin();it != vEjesHasta.end();it++){ // como mucho n veces
	
		if(wEjesHasta.count(*it) == 0) ejesUsados.insert(*it); //insert: O(log n), count O(log n).
	
	}


}



bool cargar(Grafo &G,ifstream &entrada){





}


