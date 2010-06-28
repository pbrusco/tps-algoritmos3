#include "tiempo.h"
#include <cassert>
#include <sys/time.h>

#define forn(i,n) for(int i=0; i<n; i++)
#define forall(it,X) for(typeof((X).begin()) it = (X).begin(); it != (X).end(); it++)

using namespace std;

unsigned long long timeval_diff(struct timeval& a, struct timeval& b);


int main(int argc, char** argv){

	string in,out;

	if(argc == 1){
		in = "../../in/Tp3.in";
		out = "Tp3LOCAL.out";
	}
	else{
		if(argc == 2){
			in = argv[1];
			int pos = in.rfind('/');
			out = in.substr(pos+1, in.size());
			pos = out.rfind(".in");
			if (pos!=string::npos)
    			out.substr(0,out.length()-3);
    		out = "tiempo_" + out + ".ej4";
		}
		else{
			cout << "Se debe dar 1 o ningún parámetro. En el caso de dar 1 parámetro, "
				 << "pasar el archivo de entrada. En el caso de no dar parámetros, "
				 << "tomará los archivos por defecto (/in/Tp3.in y /out/4 - BUSQ_LOCAL/Tp3LOCAL.out)";
			assert(argc != 2 && argc != 1);
		}
	}

	unsigned long long tiempoTotal = 0;
	struct timeval t1, t2;	

	int cantNodos;
	Grafo g;
	set<int> cliqueMaximo;
	ifstream is;
	ofstream contar;
	contar.open(out.c_str());
	is.open(in.c_str());
	is >> cantNodos;
	
	while(cantNodos != -1){
	
		g.cargar(is,cantNodos);
		tiempoTotal = 0;

		for(int i = 0; i < 10; i++){
			gettimeofday(&t1,NULL);



			//solucion constructiva
			g.cliqueConstructivo(cliqueMaximo);
		
			//aca empieza la busqueda local
			g.busquedaLocal(cliqueMaximo);



			gettimeofday(&t2,NULL);

			tiempoTotal += timeval_diff(t2, t1);
		}
		
		tiempoTotal = tiempoTotal / 10;
		
		contar << cantNodos << '\t' << tiempoTotal << endl;
		
		cliqueMaximo.clear();
		is >> cantNodos;
	}
	
	
	is.close();
	contar.close();
	
	return 0;
}

//implementaciones

void Grafo::cargar(istream& is, int cantNodos){

	int cantVecinos, v;
	
	for(int i = 0; i<matAd.size(); i++){
		matAd[i].resize(0);
	}
	matAd.resize(0);
	matAd.resize(cantNodos);
	
	
	for(int i = 0; i<matAd.size(); i++){
		matAd[i].resize(cantNodos);
	}
	
	grados.resize(cantNodos);
	
	for(int i = 0; i < cantNodos; i++){
		is >> cantVecinos;
		grados[i] = cantVecinos;
		for(int j = 0; j < cantVecinos; j++){
			is >> v;
			matAd[i][v-1] = true;
		}
	}

}

bool Grafo::sonAdyacentes(int v1, int v2) const {
	return matAd[v1][v2];
}

bool Grafo::vecinoDeTodos(int v, const set<int>& c) const {
	
	bool res = true;
	set<int>::iterator it;
	for(it = c.begin(); it != c.end(); it++){
		res = res && sonAdyacentes(v,*it);
	}
	return res;
}

void Grafo::fronteraEnComun(int u, int v, set<int>& res) const {
	res.clear();
	if (sonAdyacentes(u,v)) {
		forn(j,matAd.size()) {
			if (sonAdyacentes(u,j) && sonAdyacentes(v,j)) res.insert(j);
		}
		res.insert(u);
		res.insert(v);
	}
}

void Grafo::mayorFrontera(set<int>& res) const {
	set<int> aux;
	for(int i=0; i<matAd.size(); i++) {
		for(int j =i+1; j<matAd.size(); j++) {
			fronteraEnComun(i,j,aux);
			if (aux.size() > res.size()) {
				res = aux;
			}
		}
	}
}


int Grafo::masRelacionado(const set<int>& frontera) const {

	int res, vecinosRes = 0, vecinosAux;
	set<int>::iterator it = frontera.begin();
	res = *it;
	for(it; it != frontera.end(); it++){
		vecinosAux = cantVecinos(*it,frontera);
		if(vecinosAux > vecinosRes){
			res = *it;
			vecinosRes = vecinosAux;
		}
	}
	return res;
}


int Grafo::cantVecinos(int v, const set<int>& vecindad) const {

	int res = 0;
	for(set<int>::iterator it = vecindad.begin(); it != vecindad.end(); it++){
		if(sonAdyacentes(v,*it))	res++;
	}
	return res;
}


void Grafo::cliqueConstructivo(set<int>& res) const {
	int v;
	set<int> frontera;
	mayorFrontera(frontera);
	while (frontera.size() != 0) {
		v = masRelacionado(frontera);
		if (vecinoDeTodos(v,res)) res.insert(v);
		frontera.erase(v);
	}
	if (res.size() == 0) res.insert(0);
}


void Grafo::busquedaLocal(set<int> &cliqueMaximo) const{

	bool termine = false;
	bool cambio;
	
	//mientras no encuentre maximo local
	while(!termine) {
		
		cambio = false;	

		//busco combinacion que maximice el clique
		cambiarSiMaximiza(cliqueMaximo,cambio);
		
		//si no encuentro una, termino
		if(!cambio){
			termine = true;
		}
	}

}

void Grafo::vecinosAMaxHeap(const set<int>& clique, Heap &vecinos, const int v) const{

	if(!vecinos.empty()){
		vaciarHeap(vecinos);
	}

	for(set<int>::iterator it = clique.begin(); it != clique.end(); it++){
		for(int i = 0; i < matAd.size(); i++){
			if(sonAdyacentes(i,*it) && clique.count(i) == 0 && i != v){
				vecinos.push(make_pair(grados[i],i));
			}
		}
	}
}

void Grafo::deCliqueAMinHeap(const set<int>& clique, Heap &cliqueMenorAMayor) const{

	if(!cliqueMenorAMayor.empty()){
		vaciarHeap(cliqueMenorAMayor);
	}

	for(set<int>::iterator it = clique.begin(); it != clique.end(); it++){
		cliqueMenorAMayor.push(make_pair(-grados[*it],*it));
	}
}

void Grafo::cambiarSiMaximiza(set<int>& clique, bool &cambio) const {
	
	set<int> posibleMejora;
	const set<int> copiaClique = clique;
	Heap cliqueMenorAMayor, vecindad;
	deCliqueAMinHeap(copiaClique,cliqueMenorAMayor);


	while(!cliqueMenorAMayor.empty()){
		//saco de a uno de los que esta en la clique en orden de menor a mayor grado, y pruebo si puedo meter alguno/s distinto/s
		posibleMejora = copiaClique;
		posibleMejora.erase(cliqueMenorAMayor.top().second);
		
		//los posibles cambios se realizan sobre los vecinos de los nodos que estan en la clique (que no sea el que saque)
		vecinosAMaxHeap(posibleMejora,vecindad,cliqueMenorAMayor.top().second);
		
		//voy tomando en orden de grados
		while(!vecindad.empty()){
			if(vecinoDeTodos(vecindad.top().second,posibleMejora)){
				posibleMejora.insert(vecindad.top().second);
			}
			vecindad.pop();
		}


		if(posibleMejora.size() > clique.size()){
			clique = posibleMejora;
			cambio = true;
		}
		
		cliqueMenorAMayor.pop();
	}
}


void guardarRes(ostream& os, set<int> c){
	os << c.size() << endl << "N ";
	set<int>::iterator it;
	for(it = c.begin(); it != c.end(); it++){
		os << ((*it) + 1) << ' ';
	}
	os << endl;
}

void vaciarHeap(Heap& h){

	while(!h.empty()){
		h.pop();
	}
}












unsigned long long timeval_diff(struct timeval& a, struct timeval& b) {
  return (a.tv_sec + - b.tv_sec)*1000000 + (a.tv_usec  - b.tv_usec);
}






