#include <iostream>
#include <stdlib.h>
#include <fstream>

// Se toma el estado del TSC antes de iniciar el procesamiento de bordes.
#define MEDIR_TIEMPO_0		__asm__ __volatile__ ("rdtsc;mov %%eax,%0" : : "g" (tscl))
// Se toma la medicion de tiempo con el TSC y se calcula la diferencia.
#define MEDIR_TIEMPO_1		__asm__ __volatile__ ("rdtsc;sub %0,%%eax;mov %%eax,%0" : : "g" (tscl))

using namespace std;


// Declaración de funciones
long long potenciacion(long long base, long long exp, long long mod);

// Implementacion de funciones
long long potenciacion(long long base, long long exp, long long mod) {
	long long res = 0;
	if (exp == 1) {
		return (base % mod);
	}else if (exp % 2 == 0) {
		long long temp = potenciacion(base, exp/2, mod);
		res = (temp*temp) % mod;
	}else {
		long long temp = potenciacion(base, (exp-1)/2, mod);
		res = (temp*temp*base) % mod;
	}return res;
}

int main(int argc, char** argv) {
	char* filename = "./inputs/Tp1Ej1.in";
	if (argc == 2)
		filename = argv[1];
	ifstream infile; 
	ofstream outfile;
	infile.open(filename); 
	outfile.open("./outputs/Tp1Ej1.out");
	bool entradaOk = infile.is_open(); 
	bool salidaOk = outfile.is_open();
	if (! entradaOk) {
		cout << "No se pudo abrir el archivo " << filename << endl;
		exit(1); 
	}else if (! salidaOk) {
		cout << "No se pudieron guardar las respuestas en el archivo Tp1Ej1.out" << endl;
		exit(1);
	}else{
		long long b = 0, n = 0, res = 0;
		int tiempo = 0, tscl = 0;
		while(infile.good()) {
			infile >> b;
			infile >> n;
			if (b != -1 and n != -1) {;
				MEDIR_TIEMPO_0;
				res = potenciacion(b, n, n);
				MEDIR_TIEMPO_1;
				tiempo += tscl;
				outfile << res << endl;
			}
		}infile.close();
		outfile.close();
		cout << "Se tardo " << tiempo/(1.6*1024*1024) << " segundos en procesar el archivo " << filename << endl;
	}return 0;	
}
