#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "ej3.h"
#include <set>
#include <cassert>
#include <time.h>
#include <algorithm>
#include <vector>
#include <sys/time.h>

int seed = 2;

using namespace std;

struct programador{
	int hrs,mins,segs;
	int nom;
};

void generarArchivo(string nombreArchivo);
void crearEmpresaAlAzar(int n, ostream& os);
void crearHoraAlAzar(int& hora, int& min, int& seg, int& desde);
bool menor(programador a, programador b);

int main(){

	//generarArchivo("entrada3");
	
struct timeval t1,t2;
double tiempo;

gettimeofday(&t1,NULL);


gettimeofday(&t2,NULL);
tiempo = (t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_usec - t1.tv_usec);


	Empresa::cargarEmpresasYResolver("entrada2","salida2");

	return 0;

}

#define SEGXDIA 	86400
#define SEGXHORA 	3600
#define SEGXMIN		60


void generarArchivo(string nombreArchivo){

	ofstream os;
	os.open(nombreArchivo.c_str());
	
	int cantEmpresas = 16;
	int cantProg = 2;
	
	for(int i = 1; i<= cantEmpresas; i++){
		crearEmpresaAlAzar(cantProg,os);
		cantProg = cantProg*2;
	}
	os << -1;
	
	os.close();
}


void crearEmpresaAlAzar(int n, ostream& os){
	
	int hora, desde;
	programador P;
	vector<programador> entradas;
	vector<programador> salidas;
	
	//creo 2 listas con programadores y sus horarios de salida y entrada
	for(int i = 0; i < n-1; i++){
		
		//genero cantidad de segundos entre 0 y SEGXDIA-2
		desde = 0;
		
		//creo horario de entrada para el programador i
		crearHoraAlAzar(P.hrs, P.mins, P.segs, desde);
		P.nom = i+1;
		entradas.push_back(P);

		//creo horario de salida para el programador i		
		crearHoraAlAzar(P.hrs, P.mins, P.segs, desde);
		P.nom = i+1;
		salidas.push_back(P);

	}
	P.nom = n;
	P.hrs = 23;
	P.mins = 59;
	P.segs = 58;
	entradas.push_back(P);
	P.segs = 59;
	salidas.push_back(P);

	//ordeno las listas
	sort(entradas.begin(),entradas.end(),menor);
	sort(salidas.begin(),salidas.end(),menor);

		
	
	//guardo en archivo de salida
	os << "   " << n << endl;
	
	for(int i = 0; i < n; i++){
		
		(entradas[i].hrs < 10) ? os << 0 << entradas[i].hrs  : os << entradas[i].hrs;
		os << ':';
		(entradas[i].mins < 10)? os << 0 << entradas[i].mins : os << entradas[i].mins;
		os << ':';
		(entradas[i].segs < 10)? os << 0 << entradas[i].segs : os << entradas[i].segs;
		os << " ";
		os << entradas[i].nom << endl;
	}	
	
	for(int i = 0; i < n; i++){
		
		(salidas[i].hrs < 10) ? os << 0 << salidas[i].hrs  : os << salidas[i].hrs;
		os << ':';
		(salidas[i].mins < 10)? os << 0 << salidas[i].mins : os << salidas[i].mins;
		os << ':';
		(salidas[i].segs < 10)? os << 0 << salidas[i].segs : os << salidas[i].segs;
		os << " ";
		os << salidas[i].nom << endl;
	}
}


void crearHoraAlAzar(int& hora, int& min, int& seg, int& desde){
	
	/*****************************************************|
	| La funcion devuelve la hora, min y seg de un horario|
	| determinado. Este horario, en cantidad de segundos, |
	| va de la franja entre DESDE y SEGXDIA(desde < 86399)|
	******************************************************/
	
	assert(desde < 86399);

	srand( seed );
	seed++;

	int segMaximos = SEGXDIA - desde;
	int tiempo = desde + (rand() % segMaximos);
	
	//modifico desde para que en la proxima llamada, cree una hora mayor a esta
	desde = desde + tiempo;
	
	hora = tiempo / SEGXHORA;
	tiempo = tiempo - hora*SEGXHORA;
	
	assert(tiempo < 3600);

	min = tiempo / SEGXMIN;
	tiempo = tiempo - min*SEGXMIN;

	assert(tiempo < 60);
	
	seg = tiempo;
}


bool menor(programador a, programador b){
	return (a.hrs < b.hrs) || ((a.hrs == b.hrs) && (a.mins < b.mins)) || ((a.hrs == b.hrs) && (a.mins == b.mins) && (a.segs < b.segs));
}
