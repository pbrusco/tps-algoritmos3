#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <set>
#include <list>
#include <map>
#include <vector>
#include <cassert>
#include <sys/time.h>

using namespace std;

#define matriz vector<vector<int> >
#define diccNodo map<int,datos> 
#define forn(i, n) for(int i = 0; i < n; i++)
#define forn2(i, n) for(int i = 1; i <= n; i++)
#define forall(it, X) for(typeof((X).begin()) it = (X).begin(); it != (X).end(); it++)


/*######################################################################################################################
#															Estructuras de datos													   # ######################################################################################################################*/

struct Grafo{
	
	struct datos{
		int padre;					/* indica el nodo que fue visitado antes que él por el algoritmo que recorre el grafo */
		set<int> vecinos;			/* contiene el conjunto de ejes adyacentes al nodo */
		set<int> ejesHasta;		/* contiene los ejes que conforman el camino hasta él desde un cierto nodo raíz dado */
		bool visitado;				/* indica si el nodo ya fue visitado por el algoritmo que recorre el grafo */
	};

	int cant_aristas;
	set<int> ejesEnCiclos;			/* contiene los ejes percenecientes a algun ciclo. */
 	diccNodo info;			 		/* diccionario que la información de cada nodo  (padre, vecinos, ejes hasta él, visitado, etc) */
	matriz mAdy;			 		/* matriz de adyacencia donde se registra para cada par de nodos el eje que los une */
}; 



/*######################################################################################################################
#														Declaración de funciones													   # ######################################################################################################################*/

int eje(const Grafo& G, int v1,int v2); 
bool cargar(Grafo &G,ifstream &entrada);
void limpiar(Grafo &G);
void dfs_ciclos(int vertice,Grafo &G,int &cuenta);
void insertarResta(set<int>& ejesEnCiclos,const set<int>& vEjesHasta,const set<int>& wEjesHasta);	
void resolverInput(string& filename, int cant_veces);
double timeval_diff(struct timeval& a, struct timeval& b);


/*######################################################################################################################
#													Implementación de funciones													   # ######################################################################################################################*/

/* retorna "a - b " en microsegundos */
double timeval_diff(struct timeval& a, struct timeval& b) {
  return (a.tv_sec + - b.tv_sec)*1000000 + (a.tv_usec  - b.tv_usec);
//  return (a.tv_sec*1000 + a.tv_usec/1000) - (b.tv_sec*1000 + b.tv_usec/1000);
  
}

void resolverInput(string& filename, int cant_veces) {

	/* Abro el archivo con los datos de entrada */	
	ifstream infile; 
	infile.open(filename.c_str()); 
	assert(infile.is_open());

	/* Creo el nombre del archivo de salida el nombre del archivo con los datos necesios para graficar */

	string filename2;
	string filename3;
	
	if (filename == "Tp2Ej2.in") filename2 = "Tp2Ej2-bis.out";
	else filename2 = (filename.substr(0, filename.size()-3) + ".out");	
	filename3 = (filename.substr(0, filename.size()-3) + "_grafico.out");
	
	/* Abro el archivo para guardar las respuestas*/
	ofstream outfile;
	outfile.open(filename2.c_str());
	assert(outfile.is_open());

	/* Abro un archivo para guardar los datos necesarios para graficar */
	ofstream data_grafico;
	data_grafico.open(filename3.c_str());
	assert(data_grafico.is_open());

	/* variables para medir el tiempo de ejecución del algoritmo */
	struct timeval t1, t2;	
	double tiempo = 0.0; 
	double tiempoTotal = 0.0;

	Grafo G; 
	int n, cuenta;
	bool sigueArchivo;
	list<pair<int, double> > grafico;	
	/* para cada instancia del problema en el archivo ".in" genero cargo los datos y la resuelvo */
	do{
		sigueArchivo = cargar(G,infile);
		n = G.info.size();
		
		if (sigueArchivo ) {
			cuenta = 0; 
			tiempo = 0.0;
			
			/* resuelvo cant_veces cada instancia para calcular luego su tiempo promedio (por defecto cant_veces = 1) */
			for(int i = 0; i < cant_veces; ++i){
			
				/* medit tiempo inicial */
				gettimeofday(&t1,NULL);
			
				dfs_ciclos(1,G,cuenta);

				/* medir tiempo final */
				gettimeofday(&t2,NULL);
					
				/* calcular tiempo de resolución */
				tiempo += timeval_diff(t2, t1);
			}

			/* calculo el tiempo promedio */
			tiempo = tiempo / cant_veces;
			
			/* lo sumo al acumulador total de tiempo */
			tiempoTotal = tiempoTotal + tiempo;

			/* escribo lo resultados en los archivos ".out" */
			if (cuenta < n || G.ejesEnCiclos.size() < G.cant_aristas  || cuenta < 3) outfile << "no" << endl;
			else outfile << "fuertemente conexo" << endl;

			/* escribo en *_grafico.out la cantidad de aristas de la instancia y el tiempo promedio en resolverla cant_veces */
			grafico.push_back(make_pair(G.cant_aristas, tiempo));
		}
	}while(sigueArchivo);

	grafico.sort();
	forall(it, grafico)
		data_grafico << it ->first << '\t' << it -> second << endl;

	/* Cierro los archivos abiertos */
	infile.close();
	outfile.close();
	data_grafico.close();

	
	if (cant_veces == 1) printf ("El algoritmo tardó %.000f microsegundos en resolver todas las instancias del archivo %s.\n", tiempoTotal, filename.c_str());

	else printf ("El algoritmo tardó en promedio %.000f microsegundos en resolver %d veces todas las instancias del archivo %s.\n", tiempoTotal, cant_veces, filename.c_str());
	
}
	

void dfs_ciclos(int vertice,Grafo& G,int& cuenta) { 
	/* agrego al camino del nodo actual los ejes del camino hasta su padre  */
	G.info[vertice].ejesHasta = G.info[G.info[vertice].padre].ejesHasta; 

	/* agrego al camino del nodo actual el eje entre él y su padre */
	G.info[vertice].ejesHasta.insert(eje(G,vertice,G.info[vertice].padre));

	/* marco al nodo como visitado y aumento el contador de nodos visitados */
	G.info[vertice].visitado = true;
	cuenta = cuenta + 1;
	
	/* para cada uno de los nodos vecinos del nodo en el que me encuenrto */
	forall(it, G.info[vertice].vecinos) {

		/* si el vecino elegido no fue visitado */
		if (G.info[*it].visitado == false) {

			/* marco al nodo actual como padre del vecino */	
			G.info[*it].padre = vertice;
			
			/* llamo recusivamente a la función para recorrer el subgrafo que tiene por raíz al vecino que acabo de elegir */
			dfs_ciclos(*it,G,cuenta);
		}

		/* si el vecino elegido ya fue visitado y no es el padre del nodo actual entonces enontré un ciclo! Luego: */
		else if (G.info[vertice].padre != (*it)) {							
			
			/* guardo en el conj. ejesEnCiclo todos los ejes del camino desde la raíz del subgrafo que estoy recorriendo hasta el nodo actual */
			insertarResta(G.ejesEnCiclos,G.info[vertice].ejesHasta,G.info[*it].ejesHasta);

			/* guardo en el conjunto ejesEnCiclo el eje entre la raíz del subgrafo que esté recorriendo y el nodo actual*/ 
			G.ejesEnCiclos.insert(eje(G,*it,vertice));
		}
	}
}


/* Devuelve el nombre del eje que une a los nodos v1 y v2 dentro del grafo G */ 
int eje(const Grafo& G, int v1,int v2) {
	return G.mAdy[v1-1][v2-1];
}


/* COMPLETAR */
void insertarResta(set<int>& ejesEnCiclos, const set<int>& vEjesHasta, const set<int>& wEjesHasta) {
	forall(it, vEjesHasta) {
		if (wEjesHasta.count(*it) == 0) ejesEnCiclos.insert(*it);
	}
}


/* Carga los datos del archivo de entrada en una estructura Grafo */
bool cargar(Grafo& G, ifstream& entrada){
	int k = 1;
	int n, cantVecinos, vecino;
	limpiar(G);
	entrada >> n;

	if (n == -1) return false;
	
	G.mAdy.resize(n);
	forn(s,n) G.mAdy[s].resize(n);

	forn2(i, n) {
		entrada >> cantVecinos;
		forn2(j, cantVecinos){
			entrada >> vecino;
			if (G.mAdy[i-1][vecino-1] == 0) {
				G.mAdy[vecino-1][i-1] = k;
				k++;
				G.cant_aristas++;
			}
			else G.mAdy[vecino-1][i-1] = G.mAdy[i-1][vecino-1];
			G.info[i].vecinos.insert(vecino);
		}
		G.info[i].padre = 0;
		G.info[i].visitado = false;
	}
	return true;
}


/* Borra los datos de una estructura Grafo */
void limpiar(Grafo &G){
	G.ejesEnCiclos.clear();
 	G.info.clear();
	G.mAdy.resize(0);	
	G.cant_aristas = 0;
}



/*######################################################################################################################
#														Algoritmo Principal													   		    #
######################################################################################################################*/

int main(int argc, char** argv) {

	char opcion;
	int cant_veces = 1;		
	string filename = "Tp2Ej2.in";

	system("clear");

	if (argc > 1) {
		cout << "Ingrese el número de veces que desea resolver cada instancia de cada uno de los archivos:  ";
		cin >> cant_veces; cout << endl;
	
		forn(i, argc-1) {
			filename = argv[i+1];
			resolverInput(filename, cant_veces);
		}		

		cout << endl << "Las soluciones a los problemas planteados y la información para realizar los graficos fueron guardados en la carpeta '/tests'." << endl;
	}

	else {
		resolverInput(filename, cant_veces);
		cout << endl << "Las soluciones al archivo de prueba y la información para realizar su grafico fueron guardados en esta misma carpeta."
			 << endl << "La  se encuentra en la carpeta './info graficos'. " << endl << endl;
	}
		
	return 0;	
}

