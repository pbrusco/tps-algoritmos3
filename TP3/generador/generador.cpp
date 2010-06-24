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
	void guardarnuestro(ostream& os);

};

void guardarLista(ostream& os, const list<int>& l);
int numeroAlAzar(int desde, int hasta);
void generarGrafoAlAzar();
void generarGrafoConOpciones();
void tomarMenoresAN(const list<pair<int,int> > &combinacionesFijas, list<pair<int,int> > &combinaciones,int n);


int main(){

	srand(time(NULL));

	string opt = "1";
	
	while(opt == "1"){
		cout << "Si queres hacer un grafo al azar, presiona 1 y enter" << endl
			 //<< "Si queres hacer un grafo con opciones, presiona 2 y enter" << endl;
			 << "Para salir, presiona cualquier tecla ";
		cin >> opt;

		if(opt == "1")
			generarGrafoAlAzar();
	}
	//	if(opt == 2)
	//		generarGrafoConOpciones();
	

	return 0;
}

Grafo::Grafo(int V){
	listAd.resize(V);
}

void Grafo::guardarnuestro(ostream& os){

	os << listAd.size() << endl;
	for(int i = 0; i < listAd.size(); i++){
	
		os << '\t' << listAd[i].size() << '\t';
		guardarLista(os,listAd[i]);
		os << endl;	
	}
	
}

void guardarLista(ostream& os, const list<int>& l){

	for(list<int>::const_iterator it = l.begin(); it != l.end(); it++){
		os << *it+1 << " ";
	}
}


int numeroAlAzar(int desde, int hasta){
	return (rand() % (hasta-desde)) + desde;
}


void tomarMenoresAN(const list<pair<int,int> > &combinacionesFijas, list<pair<int,int> > &combinaciones,int n){

	combinaciones.clear();

	for(list<pair<int,int> >::const_iterator it = combinacionesFijas.begin(); it != combinacionesFijas.end(); it++){
		if(it->first >= n){
			break;
		}
		else{
			if(it->second < n){
				combinaciones.push_back(*it);
			}
		}
	}

}


void generarGrafoAlAzar(){

	int cantNodos,porcentajeEjes,k,cantEjes;
	list<pair<int,int> >::iterator it;
	string nombreOut;
	list<pair<int,int> > combinaciones;
	Grafo g(0);
	ofstream os;
	cout << "ingrese el nombre con el que quiere guardar el archivo ";
	cin.ignore();
	getline(cin,nombreOut);
	os.open(nombreOut.c_str());
	
	cout 	<< "Ingresar:" << endl
			<< "Cantidad de nodos maxima (se van a crear grafos desde 1 nodo hasta lo que pongas aca) ";
	cin >> cantNodos;
	
	cout << "Cantidad de ejes (porcentaje del total de ejes posible ...0% ... 100%) ";
	cin >> porcentajeEjes;
	
	porcentajeEjes = porcentajeEjes % 101; //guardo el porcentaje
	
	//me creo todos los posibles ejes
	for(int i = 0; i < cantNodos; i++){
		for(int j = i+1; j < cantNodos;j++){
			combinaciones.push_back(make_pair(i,j));
		}
	}

	const list<pair<int,int> > combinacionesFijas = combinaciones;
	
	
	//creo los grafos de tamaño n
	for(int n = 1; n < cantNodos; n++){
		g.listAd.clear();
		g.listAd.resize(n);
		cantEjes = ((n * (n-1) / 2) * porcentajeEjes) / 100; //guardo la cantidad de ejes
		tomarMenoresAN(combinacionesFijas,combinaciones,n);
	
		//busco un eje al azar, lo guardo en el grafo y lo borro de los ejes que restan
		for(int i = 0; i < cantEjes; i++){
			k = numeroAlAzar(0,((n*(n-1))/2)-i-1);
			it = combinaciones.begin();
			advance(it,k);
			g.listAd[it->second].push_back(it->first);
			g.listAd[it->first].push_back(it->second);
			it = combinaciones.erase(it);
		}
	
		g.guardarnuestro(os);
	}
	
	os << -1;
	os << endl << endl << "Porcentaje Ejes " << porcentajeEjes;
	os.close();

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
