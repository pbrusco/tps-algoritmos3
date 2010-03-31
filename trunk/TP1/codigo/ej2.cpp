#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <set>

// Se toma el estado del TSC antes de iniciar el procesamiento de bordes.
#define MEDIR_TIEMPO_0		__asm__ __volatile__ ("rdtsc;mov %%eax,%0" : : "g" (tscl))

// Se toma la medicion de tiempo con el TSC y se calcula la diferencia.
#define MEDIR_TIEMPO_1		__asm__ __volatile__ ("rdtsc;sub %0,%%eax;mov %%eax,%0" : : "g" (tscl))
#define forn(i, n) for (int i = 0; i < (int)(n); i++)

using namespace std;


// Declaracion de funciones
bool hayRonda(set<int>* amigas, int ult_ubicada);
	
// Implementacion de funciones
bool hayRonda(set <int>* amigas, int ult_ubicada) {return 1;}

int main(int argc, char** argv) {
	char* filename = "./inputs/Tp1Ej2.in";
	if (argc == 2)
		filename = argv[1];
	ifstream infile; 
	ofstream outfile;
	infile.open(filename); 
	outfile.open("./outputs/Tp1Ej2.out");
	bool entradaOk = infile.is_open(); 
	bool salidaOk = outfile.is_open();
	if (! entradaOk) {
		cout << "No se pudo abrir el archivo " << filename << endl;
		exit(1); 
	}else if (! salidaOk) {
		cout << "No se pudieron guardar las respuestas en el archivo Tp1Ej2.out" << endl;
		exit(1);
	}else{
		int cant_chicas = 0, tiempo = 0, tscl = 0;
		bool ronda = 0;
		while (cant_chicas != -1) {
			set<int>* amigas = new set<int>[cant_chicas];
			int cant_amigas = 0, amiga = 0;
			forn (i, cant_chicas) {
				infile >> cant_amigas;
				forn (j, cant_amigas) {
					infile >> amiga;
					(amigas[i]).insert(amiga);
				}
			}MEDIR_TIEMPO_0;
			ronda = hayRonda(amigas, 0);
			MEDIR_TIEMPO_1;
			tiempo += tscl;
			delete []amigas;
			ronda? (outfile << "ronda" << endl) : (outfile << "no" << endl);
			infile >> cant_chicas;
		}infile.close();
		outfile.close();
	}return 0;
}
