#include <iostream>
#include <fstream>
#include "ej3.h"
#include <set>

using namespace std;


int main(int argc, char** argv){

	if(argc > 3 || argc == 2){
		cout << "La forma de utilizar el programa es:" << endl
			 << "main [archivoEntrada] [archivoSalida] (Sin corchetes)" << endl
			 << "Los archivos son opcionales. Si no se pasa ninguno como argumento, se toma como default el dado por la materia" << endl;
	}
	else if(argc == 1){
		Empresa::cargarEmpresasYResolver("Tp1Ej3.in","Tp1Ej3.out");
	}
	else{
		Empresa::cargarEmpresasYResolver(argv[1],argv[2]);
	}
	return 0;

}

