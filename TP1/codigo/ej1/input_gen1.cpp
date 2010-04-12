#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <cassert>
#include <algorithm>

#define forn(i, n) for(int i = 0; i < n; i++)
#define forall(it, X)	for(typeof((X).begin()) it = (X).begin(); it != (X).end(); it++)

using namespace std;


// ********************************************************** Declaración de funciones ******************************************************************

void MenuPrincipal();
char LeerOpcion(char desde, char hasta);
void generarArchivo(string filename, int modo);


// ******************************************************** Implementacion de funciones ***************************************************************

void MenuPrincipal() {

    bool exit = false;

    while (!exit) {
        system("cls");
        cout << endl << "Menu Principal" << endl ;
        cout << endl
            << "Por favor seleccione el tipo de archivo de entrada que desea generar y presione Enter"<< endl << endl

			// b y n grandes
			<< "a. |b| <= 1000000 y 1000000 <= |n| <= 1000000000 " << endl

            // b y n pequeños
            << "b. |b| <= 1000 y |n| <= 1000000" << endl

			// b multiplo de n
            << "c. b mod (n) = 0" << endl

			// b cualquiera y n impar
            << "d. b cualquiera y n impar" << endl

			// b cualquiera y n primo
            << "e. b cualquiera y n primo" << endl

			// b primo y b cualquiera
            << "f. b primo y n cualquiera" << endl

			// exit
            << "g. Salir del programa" << endl;

        char opcion = LeerOpcion('a','g');
		int cant_casos = 0;

        switch(opcion) 
        {
            case 'a': {
            			generarArchivo("prueba.in", 1);
			}break;

            case 'b': {
            			generarArchivo("prueba.in", 2);
			}break;

            case 'c': {
            			generarArchivo("prueba.in", 3);
			}break;

            case 'd': {
            			generarArchivo("prueba.in", 4);
			}break;

            case 'e': {
            			generarArchivo("prueba.in", 5);
			}break;

            case 'f': {
            			generarArchivo("prueba.in", 6);
			}break;

            case 'g': exit = true;
            break;
        }
    }
}

char LeerOpcion(char desde, char hasta){

	cout << endl << endl << "  Ingrese una opcion [" << desde << "-" << hasta << "]: ";

	string opt;
    bool ok = false;

    while (!ok) {
		cin >> opt;
		ok = (opt.length() == 1 && desde <= opt[0] && opt[0] <= hasta);
		if (!ok) cout << "  Opcion incorrecta. Ingrese una opcion [" << desde << "-" << hasta << "]: ";
    }

    return opt[0];
}

void generarArchivo(string filename, int modo) {

	ofstream outfile;
	outfile.open(filename.c_str());
	assert(outfile.is_open());

	int cant_casos = 0;
	int b = 0, n = 1;
	
	/* inicializo la semilla para generara nros aleatorios */
	srand ( time(NULL) );

	cout << "Ingrese la cantidad de casos de prueba que quiere generar: " ;
	cin >> cant_casos;
	
	switch(modo)
	{
		// b y n grandes
		case 1: {
			forn(i, cant_casos) {
				b = (rand() % 1000000);
				n = (1000000 + rand() % 1000000000);
				outfile << b << "\t" << n << endl;
			}
		}break;

		// b y n pequeños
		case 2: {
			forn(i, cant_casos) {
				b = (rand() % 1000);
				n = (1 + rand() % 1000000);
				outfile << b << "\t" << n << endl;
			}
		}break;

		// b multiplo de n
		case 3: {
			forn(i, cant_casos) {
				b = (rand() % 1000);
				n = (1 + rand() % 1000);
				while (b == 0 or b % n != 0) 
					b = (rand() % 1000);
				outfile << b << "\t" << n << endl;
			}
		}break;

		// b cualquiera y n impar
		case 4: {
			forn(i, cant_casos) {
				b = (rand() % 1000);
				while(n % 2 == 0)
					n = (1 + rand() % 1000000);
				outfile << b << "\t" << n << endl;
			}
		}break;

		// b cualquiera y n primo
		case 5: {
			forn(i, cant_casos) {
				b = (rand() % 1000);
				n = (1 + rand() % 1000000);
				outfile << b << "\t" << n << endl;
			}
		}break;

		// b primo y b cualquiera
		case 6: {
			forn(i, cant_casos) {
				b = (rand() % 1000);
				n = (1 + rand() % 1000000);
				outfile << b << "\t" << n << endl;
			}
		}break;
	}

	outfile.close();
}


// **************************************************************** Algortimo principal *******************************************************************

int main(int argc, char** argv) {
	
	MenuPrincipal();
	return 0;	
}
