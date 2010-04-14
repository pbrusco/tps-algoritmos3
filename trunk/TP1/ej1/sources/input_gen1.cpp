#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cmath>
#include <time.h>
#include <cassert>
#include <algorithm>

#define forn(i, n) for(int i = 0; i < n; i++)
#define forall(it, X)	for(typeof((X).begin()) it = (X).begin(); it != (X).end(); it++)

using namespace std;


// ********************************************************** Declaración de funciones ******************************************************************

void MenuPrincipal();
char LeerOpcion(char desde, char hasta);
bool esPrimo(long long int n);
void generarArchivo(int modo);


// ******************************************************** Implementacion de funciones ***************************************************************

void MenuPrincipal() {

    bool exit = false;

    while (!exit) {
        system("clear");
        cout << endl << "Menu Principal" << endl ;
        cout << endl
            << "Por favor seleccione el tipo de archivo de entrada que desea generar y presione Enter"<< endl << endl

			// n grande
			<< "a. Casos con n entre 1.000.000 y 1000.000.000 " << endl

            // n pequeño
            << "b. Casos con n entre 1 y 1.000.000" << endl

			// b multiplo de n
            << "c. Casos con b multiplo de n , con n entre 1 y 1.000.000" << endl

			// n impar
            << "d. Casos con n = 2^k - 1, con k entre 2 y 30" << endl

			// n primo
            << "e. Casos con n primo con n entre 1 y 1000.000.000" << endl

			// b primo y b cualquiera
            << "f. Casos con b primo" << endl

			// exit
            << "g. Salir del programa" << endl << endl
            
            << "*Aclaración: En todos los casos b es un numero entre 0 y 1.000.000." << endl;
            
        char opcion = LeerOpcion('a','g');
		int cant_casos = 0;

        switch(opcion) 
        {
            case 'a': generarArchivo(1);
			break;

            case 'b': generarArchivo(2);
			break;

            case 'c': generarArchivo(3);
			break;

            case 'd': generarArchivo(4);
			break;

            case 'e': generarArchivo(5);
			break;

            case 'f': generarArchivo(6);
			break;

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

bool esPrimo(long long int n) {
	if (n == 1)
		return 0;
	
	else if (n < 4)
		return 1;							// 2 y 3 son primos
	
	else if (n % 2 == 0)
		return 0;

	else if (n < 9)
		return 1;  					 		// ya excluimos a 4,6 y 8

	else if (n % 3 == 0)
		return 0;

	else {
		long long int r = floor(sqrt(n)); 		// parte entera de la raíz de n
		long long int f = 5;
		
		while (f <= r) {
		    if ((n % f == 0) or (n % (f + 2) == 0))
				return 0;
		    f += 6;
		}
	}

	return 1;
}

void generarArchivo(int modo) {
	
	system("clear");
	string filename = "prueba.in";		

	cout << "Ingrese el nombre del archivo que quiere generar: " ;
	cin >> filename;
	
	ofstream outfile;
	outfile.open(filename.c_str());
	assert(outfile.is_open());

	int cant_casos = 0;
	long long b = 0, n = 0;
	
	/* inicializo la semilla para generara nros aleatorios */
	srand ( time(NULL) );

	cout << endl << "Ingrese la cantidad de casos de prueba que quiere generar: " ;
	cin >> cant_casos;
	
	switch(modo)
	{
		// n grande
		case 1: {
			forn(i, cant_casos) {
				b = (rand() % 1000000);
				n = (1000000 + rand() % 1000000000);
				outfile << b << "\t" << n << endl;
			}
		}break;

		// n pequeño
		case 2: {
			forn(i, cant_casos) {
				b = (rand() % 1000000);
				n = (1 + rand() % 1000000);
				outfile << b << "\t" << n << endl;
			}
		}break;

		// b multiplo de n
		case 3: {
			forn(i, cant_casos) {
				b = (rand() % 1000000);
				n = (1 + rand() % 1000000);
				while (b == 0 or b % n != 0) 
					b = (rand() % 1000000);
				outfile << b << "\t" << n << endl;
			}
		}break;

		// n = 2^k -1
		case 4: {
			forn(i, cant_casos) {
				b = (rand() % 1000000);
				n = (1 + rand() % 30);
				n = pow(2,n) - 1;
				outfile << b << "\t" << n << endl;
			}
		}break;

		// n primo
		case 5: {
			forn(i, cant_casos) {
				b = (rand() % 1000000);
				n = (1 + rand() % 1000000);
				while(! esPrimo(n))
					n = (1 + rand() % 1000000000);
				outfile << b << "\t" << n << endl;
			}
		}break;

		// b primo y n cualquiera
		case 6: {
			forn(i, cant_casos) {
				b = (rand() % 1000000);
				n = (1 + rand() % 1000000);
				while(! esPrimo(b))
					b = (rand() % 1000000);
				outfile << b << "\t" << n << endl;
			}
		}break;
		
	}
	outfile << -1 << "\t" << -1 << endl;
	outfile.close();
}


// **************************************************************** Algortimo principal *******************************************************************

int main(int argc, char** argv) {
	
	MenuPrincipal();
	return 0;	
}
