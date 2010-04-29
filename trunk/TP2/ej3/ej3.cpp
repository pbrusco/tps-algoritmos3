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
	void vaciar();
	void cargarCarcel(istream& is, int n, int p, int m);
	bool sonAdyacentes(int,int) const;
	bool tienePuerta(int) const;
	bool tieneLlave(int) const;
	int dameLlave(int) const;
	
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
	puertas->resize(n);
	pasillos->resize(n);
	for(int i = 0; i < n; i++)	(*pasillos)[i].resize(n);
	
	
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


bool resolver(const carcel& c);
void recorrerPorBFS(queue<int>& habitacionesProximas, queue<int>& habitacionesLimites, set<int>& habitacionesYaVisitadas, set<int>& llavesEncontradas, const carcel& c);





int main(int argc, char** args){
	
	string entrada,salida;
	
	if(argc == 1){
		entrada = "Tp2Ej3.in";
		salida  = "Tp2Ej3.out";
	}
	else if(argc == 3){
		entrada = args[1];
		salida  = args[2];
	}
	else{
		cout << "El llamado al programa es: ej3 [entrada] [salida]" << endl
			 << "Los parametros son opcionales. Si no se pasan, se toma por defecto la entrada/salida dada por la materia" << endl;
		return -1;
	}
	
	ifstream is;
	ofstream os;
	is.open(entrada.c_str());
	os.open(salida.c_str());
	
	int n, p, m;
	bool res;
	
	is >> n;
	is >> p;
	is >> m;
	
	carcel c(n);

	while(n != -1 && p != -1 && m != -1){
	
		c.cargarCarcel(is,n,p,m);
		
		//resuelvo y guardo
		res = resolver(c);
		
		if(res)	os << "libre" << endl;
		else	os << "no" << endl;
		
		
		is >> n;
		is >> p;
		is >> m;
	
	}
	
	is.close();
	os.close();

	return 0;
}













bool resolver(const carcel& c){

	set<int> habitacionesYaVisitadas;
	
	//aca me voy a guardar aquellas habitaciones que no pude visitar porque tenian una puerta de la cual aún no se tiene llave
	queue<int> habitacionesLimites;
	
	set<int> llavesEncontradas;
	
	//aca guardo las habitaciones en las que se debe hacer BFS
	queue<int> habitacionesProximas;
	
	bool puedoSeguir = true;
	int contador;
	
	
	//arranco a hacer BFS con la primer habitacion
	habitacionesProximas.push(0);
	
	do{
		
		//luego de este llamado, habitacionesProximas == []
		recorrerPorBFS(habitacionesProximas, habitacionesLimites, habitacionesYaVisitadas, llavesEncontradas, c);

		
		if(!habitacionesLimites.empty()){
			
			contador = habitacionesLimites.size();
			
			//lo que hago aca es dejar como primer habitacion dentro de las "limite" a una de la cual tenga llave
			//si no tengo llave para ninguna puerta, entonces no hay solucion			
			while(  puedoSeguir && (llavesEncontradas.count(habitacionesLimites.front()) == 0) ) {
				
				habitacionesLimites.push(habitacionesLimites.front());
				habitacionesLimites.pop();
				contador--;
				if(contador == 0)	puedoSeguir = false;
			}
			
			habitacionesProximas.push(habitacionesLimites.front());
			habitacionesLimites.pop();
		}
	
	
	}while(puedoSeguir && (!habitacionesProximas.empty() || !llavesEncontradas.empty()));
	
	
	if(habitacionesYaVisitadas.count(c.cantHabitaciones-1) == 1)	return true;
	
	
	return false;

}


void recorrerPorBFS(queue<int>& habitacionesProximas, queue<int>& habitacionesLimites, set<int>& habitacionesYaVisitadas, set<int>& llavesEncontradas, const carcel& c){

/*
La idea de esta funcion es que sea una funcion boba.
Solo se dedica a recorrer las habitaciones encoladas como proximas, actualizando todos los parametros segun corresponda, hasta que la cola de "proximas" se vacie.
Los parametros se modifican asi:
1) habitacionesProximas: una vez finalizada la funcion, termina vacia.
2) habitacionesLimites: se agregan las habitaciones que resultaron vecinas de alguna de las que se visito, pero que tienen puerta y no se tiene su llave aun
3) habitacionesYaVisitadas: cuando visito una habitacion, la agrego al conjunto para no pasar 2 veces por la misma habitacion
4) llavesEncontradas: aqui voy agregando las llaves que encuentre en el camino y voy eliminando aquellas que ya use

Requiere: habitacionesProximas.front() sea "visitable", es decir, no tiene puerta o tiene puerta pero tengo su llave
*/



	int actual;
	
	do{
		//invariante: habitacionesProximas.front() es "visitable"
	
		actual = habitacionesProximas.front();	
		habitacionesProximas.pop();
		habitacionesYaVisitadas.insert(actual);
		if(c.tieneLlave(actual))	llavesEncontradas.insert(c.dameLlave(actual));

		for(int i = 0; i<c.cantHabitaciones; i++){
	
			//si son vecinas y no visite a la iesima
			if(c.sonAdyacentes(actual,i) && habitacionesYaVisitadas.count(i) == 0){
		
				//si tiene puerta y no tengo su llave
				if(c.tienePuerta(i) && llavesEncontradas.count(i) == 0){
					habitacionesLimites.push(i);
				}
				else{
					habitacionesProximas.push(i);
					
					//si tenia su llave, la elimino
					llavesEncontradas.erase(i);			
				}
				
		
			}
	
		}//end for
		
	}while(!habitacionesProximas.empty());



}

