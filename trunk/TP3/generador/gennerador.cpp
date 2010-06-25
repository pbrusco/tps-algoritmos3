#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>

int numeroAlAzar(int desde, int hasta);
void generarGrafoAlAzar();


using namespace std;


struct Grafo {

	vector<vector<int> > matrizAd;
	Grafo(int V);
	
	void guardarnuestro(ostream& os);
	void llenarAristas(int);
	

};



int main(){
	srand(time(NULL));
	generarGrafoAlAzar();
	
	return 0;
}

Grafo::Grafo(int V){
	matrizAd.clear();//ESTO LO DEJA CON TAMAÑO CERO Y DESTRUYE A LOS ELEMENTOS DE ADENTRO
	matrizAd.resize(V);
	for(int i = 0; i<V;i++) matrizAd[i].resize(V);
}

void Grafo::guardarnuestro(ostream& os){

	os << matrizAd.size() << endl;
	for(int i = 0; i < matrizAd.size(); i++){
	
		int aristasPorCol = 0;
		for(int j = 0; j < matrizAd.size();j++){
			if (matrizAd[i][j] != 0) aristasPorCol++;
		}
		
		os << '\t' << aristasPorCol << '\t';
		
		for(int j = 0; j < matrizAd.size();j++){
			//if (matrizAd[i][j] != 0) os << matrizAd[i][j]+1 << " "; //IMAGINO QUE QUISISTE PONER LO QUE SIGUE
			if (matrizAd[i][j] != 0) os << j+1 << " ";

		}
		
		
		
		os << endl;	
	}
	
}


int numeroAlAzar(int desde, int hasta){
	return (rand() % (hasta-desde)) + desde;
}



void generarGrafoAlAzar(){

	int cantNodosMax,k,cantEjes,probabilidadEje;
	
	string nombreOut;
	
	ofstream os;
	cout << "ingrese el nombre con el que quiere guardar el archivo ";
	getline(cin,nombreOut);
	os.open(nombreOut.c_str());
	
	cout 	<< "Ingresar:" << endl
			<< "Cantidad de nodos maxima (se van a crear grafos desde 5 nodos hasta lo que pongas aca.. multiplos de 5) ";//por que multiplos de 5?
	cin >> cantNodosMax;
	
	cout << "Probabilidad que aparezca un eje (de 0 a 100) ";
	cin >> probabilidadEje;
	
	probabilidadEje = probabilidadEje % 101; //guardo el porcentaje
	
	for(int n = 5; n <= cantNodosMax;n++){
		Grafo g(n);
		g.llenarAristas(probabilidadEje);
		g.guardarnuestro(os);
	}

	
	
	
	os << -1;
	os << endl << endl << "Probabilidad Ejes " << probabilidadEje;
	os.close();

}

void Grafo::llenarAristas(int probEje){

	int moneda;

	for(int i = 0; i < matrizAd.size(); i++){
		for(int j = 0; j < matrizAd.size(); j++){
			
			moneda = rand() % 101;
			moneda = moneda == 101? 0 : moneda;//para que quede entre 0 y 100
			
			if(moneda < probEje){
				matrizAd[i][j] = 1;
				matrizAd[j][i] = 1;
			}	
		}
	}
}

