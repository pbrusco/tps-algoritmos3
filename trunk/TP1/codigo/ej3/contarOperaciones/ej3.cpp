#include <iostream>
#include <fstream>
#include <set>
#include <math.h>
#include <cassert>
#include <sys/time.h>
#include "ej3.h"



//constructor
Empresa::Empresa(int cantProgramadores){

	programadoresTotales = cantProgramadores;
	ingresos = new ficha[cantProgramadores];
	egresos  = new ficha[cantProgramadores];
}

//destructor
Empresa::~Empresa(){
	delete []ingresos;
	delete []egresos;
}

//resolucion del ej3 (debe ser una empresa ya inicializada)
int Empresa::maxCantProgJuntos(int& cantOp) const{

	bool termine = false;
	int maxJuntos = 0;
	int juntosActualmente = 0;
	int i = 0, j = 0;

	cantOp = 0;
	
	while(!termine){

		while(i<programadoresTotales && ingresos[i].hora <= egresos[j].hora){
			juntosActualmente++;
			i++;
			cantOp += 2;
		}
		
		cantOp += 2;

		if(i == programadoresTotales){
			termine = true;
			cantOp++;
		}

		cantOp++;

		if(juntosActualmente > maxJuntos){
			maxJuntos = juntosActualmente;
			cantOp++;
		}

		cantOp++;

		if(!termine){
		
			while(j<programadoresTotales && egresos[j].hora < ingresos[i].hora){
				juntosActualmente--;
				j++;
				cantOp += 2;
			}

			cantOp += 2;
		}
		cantOp++;
	}
	
	return maxJuntos;
}

//cargar empresa a mano
void Empresa::cargarEmpresa(ficha entran[], ficha salen[], int tam){

	delete []ingresos;
	delete []egresos;
	ingresos = new ficha[tam];
	egresos  = new ficha[tam];
	programadoresTotales = tam;
	
	int i;
	for(i = 0;i < tam;i++){
		ingresos[i] = entran[i];
	}
	for(i = 0;i < tam;i++){
		egresos[i] = salen[i];
	}
	
}		

//cargar empresa desde archivo
void Empresa::cargarEmpresa(istream& is, int n){

	programadoresTotales = n;
	
	ficha entran[programadoresTotales];
	ficha salen[programadoresTotales];
	ficha aux;
		
	
	for(int i = 0; i < programadoresTotales; i++){
		
		is >> aux.hora;

		is >> aux.programador;
		
		entran[i] = aux;	
	}


	for(int i = 0; i < programadoresTotales; i++){
		
		is >> aux.hora;
		
		is >> aux.programador;
		
		salen[i] = aux;	
	}
	
	cargarEmpresa(entran,salen,programadoresTotales);
	
}



void Empresa::cargarEmpresasYResolver(string filenameIn, string filenameOut, string gr){

	ifstream is;
	ofstream os;
	ofstream grafico;
	
	is.open(filenameIn.c_str());
	assert(is.is_open());
	
	os.open(filenameOut.c_str());
	assert(os.is_open());
	
	grafico.open(gr.c_str());
	assert(grafico.is_open());

	Empresa e(0);
	
	int cantProg, cantOp, res;
	
	is >> cantProg;

	//declaro variables para el tiempo
	struct timeval t1,t2;
	double tiempo;

tiempo = (t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_usec - t1.tv_usec);




	while(cantProg != -1){
	
		e.cargarEmpresa(is,cantProg);
		
		//guardo resultado y salto de linea

		gettimeofday(&t1,NULL);

		res = e.maxCantProgJuntos(cantOp);

		gettimeofday(&t2,NULL);

		tiempo = (t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_usec - t1.tv_usec);

		os << res << endl;

		//guardo info de los graficos
		grafico << cantProg << '\t' << cantOp << '\t' << tiempo << endl;
		
		is >> cantProg;
	}
	
	is.close();
	os.close();
	grafico.close();

}


