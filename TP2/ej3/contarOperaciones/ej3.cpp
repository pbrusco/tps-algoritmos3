#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include "../carcel.h"
#include <sys/time.h>

using namespace std;



bool resolver(const carcel& c, int& cantOp);

void recorrerPorBFS(int proximaHabitacion, queue<int>& habitacionesLimites, vector<bool>& habitacionesYaVisitadas, vector<bool>& llavesEncontradas, const carcel& c, int& cantOp);





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
	int cantOp = 0;

	while(n != -1 && p != -1 && m != -1){
	
		c.cargarCarcel(is,n,p,m);
		
		//resuelvo y guardo
		res = resolver(c,cantOp);

		os << n << "	" << cantOp << endl;
		
		cantOp = 0;
		
		is >> n;
		is >> p;
		is >> m;
	
	}
	
	is.close();
	os.close();

	return 0;
}













bool resolver(const carcel& c, int& cantOp){

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
	
	/*TOMO CANTOP*/
	cantOp = c.cantHabitaciones * 2 + 8;


	do{
		
		
		recorrerPorBFS(proximaHabitacion, habitacionesLimites, habitacionesYaVisitadas, llavesEncontradas, c,cantOp);
			
		
		//me fijo si ya recorri todas las habitaciones
		termine = habitacionesLimites.empty();

		/*TOMO CANTOP*/
		cantOp += 2;

		if(!termine){//O(1)
			
			contador = habitacionesLimites.size();

			/*TOMO CANTOP*/
			cantOp++;
			
			
			while(  puedoSeguir && (!llavesEncontradas[habitacionesLimites.front()]) ) {
				
				habitacionesLimites.push(habitacionesLimites.front());
				habitacionesLimites.pop();
				contador--;
				
				/*TOMO CANTOP*/
				cantOp += 6;
				
				if(contador == 0){
					puedoSeguir = false;

					/*TOMO CANTOP*/
					cantOp += 2;
				}

				/*TOMO CANTOP*/
				cantOp++;

			}

			/*TOMO CANTOP*/
			cantOp += 2;
			
			proximaHabitacion = habitacionesLimites.front();
			habitacionesLimites.pop();

			/*TOMO CANTOP*/
			cantOp += 3;
		}

		/*TOMO CANTOP*/
		cantOp++;
			
	
	}while( puedoSeguir && (!termine) && !habitacionesYaVisitadas[c.cantHabitaciones-1]);

	/*TOMO CANTOP*/
	cantOp += 3;
		
	

	if(habitacionesYaVisitadas[c.cantHabitaciones-1])	return true;
	
	
	return false;

}


void recorrerPorBFS(int proximaHabitacion, queue<int>& habitacionesLimites, vector<bool>& habitacionesYaVisitadas, vector<bool>& llavesEncontradas, const carcel& c, int& cantOp){



	queue<int> habitacionesProximas;
	habitacionesProximas.push(proximaHabitacion);
	habitacionesYaVisitadas[proximaHabitacion] = true;
	int actual;

	/*TOMO CANTOP*/
	cantOp += 4;
	
	do{
	
		actual = habitacionesProximas.front();	
		habitacionesProximas.pop();

		/*TOMO CANTOP*/
		cantOp += 3;

				
		if(c.tieneLlave(actual)){
			llavesEncontradas[c.dameLlave(actual)] = true;
			/*TOMO CANTOP*/
			cantOp += 3;
		}

		/*TOMO CANTOP*/
		cantOp ++;
		
		for(int i = 0; i<c.cantHabitaciones; i++){
	
			/*TOMO CANTOP*/
			cantOp  += 2;

			if(c.sonAdyacentes(actual,i) && !habitacionesYaVisitadas[i]){
				/*TOMO CANTOP*/
				cantOp  += 3;
		
				if(c.tienePuerta(i) && !llavesEncontradas[i]){
					habitacionesLimites.push(i);
				}
				else{
					habitacionesProximas.push(i);

				}
				habitacionesYaVisitadas[i] = true;

				/*TOMO CANTOP*/
				cantOp  += 6;
			}
	
			/*TOMO CANTOP*/
			cantOp  += 3;

		}
		/*TOMO CANTOP*/
		cantOp  ++;
	}while(!habitacionesProximas.empty() && !habitacionesYaVisitadas[c.cantHabitaciones-1]);

	/*TOMO CANTOP*/
	cantOp  ++;

}

