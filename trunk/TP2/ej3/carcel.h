#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>

using namespace std;


struct carcel{
	int cantHabitaciones;
	vector<int> *llaves;	//la posicion i me dice que en la habitacion i, esta la llave de la habitacion llaves[i]. Si es 0, entonces no tiene.
	vector<bool> *puertas;	//la posicion i me dice si la habitacion i tiene puerta o no
	vector< vector<bool> > *pasillos; //matriz de adyacencia
	
	//constructor
	carcel(int n){
		cantHabitaciones = n;
		llaves = new vector<int>;
		puertas = new vector<bool>;
		pasillos = new vector<vector<bool> >;
		llaves->resize(n);
		puertas->resize(n);
		pasillos->resize(n);
		for(int i = 0; i < n; i++)	(*pasillos)[i].resize(n);
	}
	
	//destructor
	~carcel(){
		delete llaves;
		delete puertas;
		delete pasillos;	
	}
	void cargarCarcel(istream& is, int n, int p, int m);
	bool sonAdyacentes(int,int) const;
	bool tienePuerta(int) const;
	bool tieneLlave(int) const;
	int dameLlave(int) const;
	void mostrar() const;
	
};

bool carcel::sonAdyacentes(int a,int b) const{
	return (*pasillos)[a][b];
}

bool carcel::tienePuerta(int a) const{
	return (*puertas)[a];
}

bool carcel::tieneLlave(int a) const{
	return (*llaves)[a] != 0;
}

int carcel::dameLlave(int a) const{
	return (*llaves)[a];
}

void carcel::cargarCarcel(istream& is, int n, int p, int m){

	int habConLlave,hab,hab2;

	//actualizo todos los valores y tamaños
	cantHabitaciones = n;
	llaves->resize(n);
	llaves->clear();
	puertas->resize(n);
	puertas->clear();
	pasillos->resize(n);
	for(int i = 0; i < n; i++){
		(*pasillos)[i].resize(n);
		(*pasillos)[i].clear();
	}
	
	for(int i = 0; i < p ; i++){
	
		//cargo la habitacion que contiene una llave, y el numero de la habitacion de dicha llave
		is >> habConLlave;
		is >> hab;
		//actualizo la estructura
		(*llaves)[habConLlave-1] = hab-1;
		(*puertas)[hab-1] = true;
	}
	
	for(int i = 0; i < m ; i++){
	
		//cargo las habitaciones vecinas
		is >> hab;
		is >> hab2;
		//actualizo la estructura
		(*pasillos)[hab-1][hab2-1] = true;	
		(*pasillos)[hab2-1][hab-1] = true;
	
	}
}

void carcel::mostrar() const{

	cout << "llaves" << endl;
	for(int i = 0; i < cantHabitaciones ; i++){
		cout << "hab=" << i << "   " << "llave=" << (*llaves)[i] << endl;
	}
	
	cout << endl << "puertas" << endl;
	for(int i = 0; i < cantHabitaciones ; i++){
		cout << "hab=" << i << "   " << "tienePuerta=" << (*puertas)[i] << endl;
	}
	
	cout << "matriz de adyacencia" << endl;
	for(int i = 0; i < cantHabitaciones ; i++){
		for(int j = 0; j < cantHabitaciones ; j++){
			cout << (*pasillos)[i][j] << " ";
		}
		cout << endl;
	}

}
