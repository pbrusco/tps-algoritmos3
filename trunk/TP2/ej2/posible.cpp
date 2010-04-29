#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>

using namespace std;



struct Grafo{
	
	struct datos{
		int padre;
		set<int> vecinos;
		set<int> ejesHasta;
		bool visitado;
		};
	int cant_aristas;
	set<int> ejesUsados; //EJes percenecientes a ALGUN ciclo.
 	map<int,datos> info;	//DADO UN VERTICE, DA LA INFO (PADRE-VECINOS-EJESHASTA-VISITADO)
	vector<vector<int> > matrizAdyNombrada;	//es una matriz de adyacencia donde en las intersecciones tiene el nombre del eje que los une.

} //Ver como inicializar


void insertarResta(set<int>& ejesUsados,const set<int>& vEjesHasta,const set<int>& wEjesHasta);	
int eje(const Grafo& G, int v1,int v2); //O(1)
bool cargar(Grafo &G,ifstream &entrada);
void limpiar(Grafo &G);



int main(){

	ifstream entrada;
	ofstream salida;
	Grafo G;
	
	entrada.open("Tp2Ej2.in");
	salida.open("miSaldo.out");
	int n,k;
	bool sigueArchivo;
	
	do{
		sigueArchivo = cargar(G,entrada);
		n = G.info.size();
		
		if(sigueArchivo){ 
			k = dfs_ciclos(1);
			if(k < n || G.ejesUsados.size() < G.cant_aristas) salida<< "no" << endl;}
			else salida << "fuertemente conexo" << endl;

	}while(sigueArchivo);
	


	

	entrada.close();
	salida.close();
	
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

	return G.matrizAdyNombrada[v1-1][v2-1];
	
	
}



void insertarResta(set<int>& ejesUsados,const set<int>& vEjesHasta,const set<int>& wEjesHasta){

	for(set<int>::iterator it = vEjesHasta.begin();it != vEjesHasta.end();it++){ // como mucho n veces
	
		if(wEjesHasta.count(*it) == 0) ejesUsados.insert(*it); //insert: O(log n), count O(log n).
	
	}


}



bool cargar(Grafo &G,ifstream &entrada){

	int k = 1;
	int n,a;
	limpiar(G);
	entrada >> n;
	matrizAdyNombrada.rezise(n);
	for(int s = 0;s<n;s++) 	matrizAdyNombrada[s].rezise(n);

		if (n == -1) return false;
		
		for(int i = 1;i<=n;i++){
			entrada >> cantVecinos;
			for(int j = 1;j<= cantVecinos;j++){
				entrada >> vecino;
				if(G.matrizAdyNombrada[i-1][vecino-1] == 0) {G.matrizAdyNombrada[vecino-1][i-1] = k;k++;G.cant_aristas++}
				else G.matrizAdyNombrada[vecino-1][i-1] = G.matrizAdyNombrada[i-1][vecino-1];
				G.info[i].vecinos.insert(vecino);
			}
			G.info[i].padre = 0;
			G.info[i].visitado = false;
				
		}

	return true;
}


void limpiar(Grafo &G){
	G.ejesUsados.clear()
 	G.info.clear();
	matrizAdyNombrada.rezise(0);	
	G.cant_aristas = 0;
}


