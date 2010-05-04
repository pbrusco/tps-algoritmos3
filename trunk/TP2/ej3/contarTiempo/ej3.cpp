#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include "../carcel.h"
#include <sys/time.h>

using namespace std;



bool resolver(const carcel& c);

void recorrerPorBFS(int proximaHabitacion, queue<int>& habitacionesLimites, vector<bool>& habitacionesYaVisitadas, vector<bool>& llavesEncontradas, const carcel& c);





int main(int argc, char** args){
	
	string entrada,salida;
	
	if(argc == 1){
		entrada = "Tp2Ej3.in";
		salida  = "Tp2Ej3NUESTRO.out";
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

	//declaro variables para el tiempo
	struct timeval t1,t2;
	double tiempo;
	int repes = 20;
	int tiempoTotal = 0;

	while(n != -1 && p != -1 && m != -1){
	
		c.cargarCarcel(is,n,p,m);
		
		//resuelvo y guardo
		//tomo un promedio del tiempo que tarda (promedio por "repes" veces)
		for(int i = 0; i < repes ; i++){
			gettimeofday(&t1,NULL);
			res = resolver(c);
			gettimeofday(&t2,NULL);
			tiempo = (t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_usec - t1.tv_usec);
			tiempoTotal = tiempoTotal + tiempo;
		}
		os << n << "	" << tiempoTotal/repes << endl;
		tiempoTotal = 0;
		
		is >> n;
		is >> p;
		is >> m;
	
	}
	
	is.close();
	os.close();

	return 0;
}













bool resolver(const carcel& c){

	vector<bool> habitacionesYaVisitadas(c.cantHabitaciones);
	
	//aca me voy a guardar aquellas habitaciones que no pude visitar porque tenian una puerta de la cual aún no se tiene llave
	queue<int> habitacionesLimites;
	
	vector<bool> llavesEncontradas(c.cantHabitaciones);
	
	int proximaHabitacion;

	bool puedoSeguir = true;
	int contador;
	bool termine;
	
	//arranco a hacer BFS con la primer habitacion
	proximaHabitacion = 0;
	
	do{
		
		
		recorrerPorBFS(proximaHabitacion, habitacionesLimites, habitacionesYaVisitadas, llavesEncontradas, c);//O(n^2)		
		
		//me fijo si ya recorri todas las habitaciones
		termine = habitacionesLimites.empty();
		if(!termine){//O(1)
			
			contador = habitacionesLimites.size();//O(1)
			
			//lo que hago aca es dejar como primer habitacion dentro de las "limite" a una de la cual tenga llave
			//si no tengo llave para ninguna puerta, entonces veo si encontre solucion o no		
			while(  puedoSeguir && (!llavesEncontradas[habitacionesLimites.front()]) ) {//O(n)
				
				habitacionesLimites.push(habitacionesLimites.front());
				habitacionesLimites.pop();
				contador--;
				if(contador == 0)	puedoSeguir = false;
			}
			
			proximaHabitacion = habitacionesLimites.front();
			habitacionesLimites.pop();
		}
			
	
	}while( puedoSeguir && (!termine) && !habitacionesYaVisitadas[c.cantHabitaciones-1]);
	//Esto corta cuando se recorrieron todas las habitaciones o cuando no hay llaves disponibles para las que quedaron sin recorrer
	//Esto se balancea con recorrerPorBFS, haciendo que la complejidad nunca supere O(n^2), ya que si por ej,BFS recorre todos los nodos va a tener complejidad n^2, pero entonces el do-while solo se ejecuta una sola vez.
	
	
	if(habitacionesYaVisitadas[c.cantHabitaciones-1])	return true;
	
	
	return false;

}


void recorrerPorBFS(int proximaHabitacion, queue<int>& habitacionesLimites, vector<bool>& habitacionesYaVisitadas, vector<bool>& llavesEncontradas, const carcel& c){

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

	queue<int> habitacionesProximas;
	habitacionesProximas.push(proximaHabitacion);
	habitacionesYaVisitadas[proximaHabitacion] = true;
	int actual;
	
	do{
		//invariante: habitacionesProximas.front() es "visitable"
	
		actual = habitacionesProximas.front();	
		habitacionesProximas.pop();
				
		if(c.tieneLlave(actual)){
			llavesEncontradas[c.dameLlave(actual)] = true;
		}
		
		for(int i = 0; i<c.cantHabitaciones; i++){//O(n)
	
			//si son vecinas y no visite a la iesima
			if(c.sonAdyacentes(actual,i) && !habitacionesYaVisitadas[i]){
		
				//si tiene puerta y no tengo su llave
				if(c.tienePuerta(i) && !llavesEncontradas[i]){
					habitacionesLimites.push(i);
				}
				else{
					habitacionesProximas.push(i);
				}
				habitacionesYaVisitadas[i] = true;
			}
	
		}//end for
		
	}while(!habitacionesProximas.empty() && !habitacionesYaVisitadas[c.cantHabitaciones-1]);



}

