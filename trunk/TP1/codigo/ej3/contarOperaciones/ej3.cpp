#include <iostream>
#include <fstream>
#include <set>
#include <math.h>
#include <cassert>

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
			cantOp += 4;
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
				cantOp += 4;
			}
			cantOp += 2;
		}
		cantOp++;
		cantOp++;
	}
	cantOp++;
	
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



void Empresa::cargarEmpresasYResolver(string filenameIn, string filenameOut, string graf){

	ifstream is;
	ofstream os;
	ofstream grafico;
	
	is.open(filenameIn.c_str());
	assert(is.is_open());
	
	os.open(filenameOut.c_str());
	assert(os.is_open());
	
	grafico.open(graf.c_str());
	assert(grafico.is_open());
	
	
	Empresa e(0);
	
	int cantProg,cantOp,res;
	
	is >> cantProg;

	while(cantProg != -1){
	
		e.cargarEmpresa(is,cantProg);
		
		//calculo y guardo resultado y salto de linea
		res = e.maxCantProgJuntos(cantOp);
		os << res << endl;
		
		//guardo res para grafico
		grafico << cantProg << '\t' << cantOp << endl;
		
		is >> cantProg;
	}
	
	is.close();
	os.close();
	grafico.close();


}


