#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <utility>//pair
#include <set>
#include <list>
#include <vector>
#include <time.h>



using namespace std;


struct Grafo {

	vector<list<int> > listAd;


	Grafo(int V);
	void guardarnuestro(string out);

};

void guardarLista(ostream& os, const list<int>& l);
int numeroAlAzar(int desde, int hasta);
void generarGrafoAlAzar();
void generarGrafoConOpciones();



int main(){

	srand(time(NULL));

	int opt;
/*	
	cout << "Si queres hacer un grafo al azar, presiona 1 y enter" << endl
		 << "Si queres hacer un grafo con opciones, presiona 2 y enter" << endl;
		 
	cin >> opt;
*/
	opt = 1;

	if(opt == 1)
		generarGrafoAlAzar();
	if(opt == 2)
		generarGrafoConOpciones();
	if(opt != 1 && opt != 2){
		cout << "Opcion invalida" << endl;
		return -1;
	}


	return 0;
}

Grafo::Grafo(int V){
	listAd.resize(V);
}

void Grafo::guardarnuestro(string out){

	ofstream os;
	os.open(out.c_str());
	
	os << listAd.size() << endl;
	for(int i = 0; i < listAd.size(); i++){
	
		os << listAd[i].size() << " ";
		guardarLista(os,listAd[i]);
		os << endl;	
	}
	
	os << -1;
	
	os.close();

}

void guardarLista(ostream& os, const list<int>& l){

	for(list<int>::const_iterator it = l.begin(); it != l.end(); it++){
		os << *it+1 << " ";
	}
}


int numeroAlAzar(int desde, int hasta){
	return (rand() % (hasta-desde)) + desde;
}

void generarGrafoAlAzar(){

	int cantNodos,cantEjes,k;
	set<pair<int,int> >::iterator it;
	string nombreOut;
	
	
	cout 	<< "Ingresar:" << endl
			<< "Cantidad de nodos ";
	cin >> cantNodos;
	
	cout << "Cantidad de ejes (porcentaje del total de ejes posible ...0% ... 100%) ";
	cin >> cantEjes;
	
	cantEjes = cantEjes % 101; //guardo el porcentaje
	cantEjes = ((cantNodos * (cantNodos-1) / 2) * cantEjes) / 100; //guardo la cantidad de ejes
	
	//me creo todos los posibles ejes
	set<pair<int,int> > combinaciones;
	for(int i = 0; i < cantNodos; i++){
		for(int j = i+1; j < cantNodos;j++){
			combinaciones.insert(make_pair(i,j));
		}
	}

	Grafo g(cantNodos);
	
	//busco un eje al azar, lo guardo en el grafo y lo borro de los ejes que restan
	for(int i = 0; i < cantEjes; i++){
		k = numeroAlAzar(0,combinaciones.size());
		it = combinaciones.begin();
		while(k > 0){
			k--;
			it++;
		}
		g.listAd[it->second].push_back(it->first);
		g.listAd[it->first].push_back(it->second);
		combinaciones.erase(*it);
	}
	
	cout << "ingrese el nombre con el que quiere guardar el archivo ";
	cin.ignore();
	getline(cin,nombreOut);
	g.guardarnuestro(nombreOut);

}

void generarGrafoConOpciones(){

	int menorClique, mayorClique,cantIntermedias;

	cout 	<< "Ingresar:" << endl
			<< "Tamaño de la menor clique ";
	cin >> menorClique;
	
	cout << "Tamaño de la mayor clique ";
	cin >> mayorClique;
	
	cout << "Cantidad de cliques intermedias ";
	cin >> cantIntermedias;
	cantIntermedias = ( cantIntermedias % (mayorClique-menorClique) ) + menorClique;
	
	cout << "Cantidad de ejes (aparte de los de las cliques)";
	cin >> mayorClique;

}
