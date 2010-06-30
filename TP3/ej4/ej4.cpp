#include <iostream>
#include <fstream>
#include <cassert>
#include <sys/time.h>
#include "ej4.h"


#define forn(i,n) for(int i=0; i<n; i++)
#define forall(it,X) for(typeof((X).begin()) it = (X).begin(); it != (X).end(); it++)

using namespace std;


int main(int argc, char** argv) {
	string input, output;
	double time = 0.0;
	
	if (argc == 1) {
		input = "../in/Tp3.in";
		output = "../out/4 - BUSQ_LOCALTp3.out";
		time = resolverBusqLocal(input,output);
		cout << "El algortimo demoró " << time << " milisegundos en resolver las instancias del archivo " << input << endl;
	}
	else {
		forn(i, argc-1) {
			input = argv[i+1];
			int pos = input.rfind('/');
			output = input.substr(pos+1, input.size());
			pos = output.rfind(".in");
			if (pos!=string::npos) output.replace(pos,3,".out");
			output = "../out/4 - BUSQ_LOCAL/" + output;
			time = resolverBusqLocal(input,output);
			cout << "El algortimo demoró " << time << " milisegundos en resolver las instancias del archivo " << input << endl;
		}
	}
	return 0;
}


/*################## 	IMPLEMENTACIONES 	################### */


double resolverBusqLocal(const string& input, const string& output) {
	int n;
	Grafo g;
	set<int> res;
	ifstream is;			is.open(input.c_str());		assert(is.is_open());
	ofstream os;		os.open(output.c_str());	assert(os.is_open());

	double t = 0.0;
	struct timeval t1, t2;

	is >> n;
	while(n != -1) {
		g.cargar(is,n);
		gettimeofday(&t1,NULL);
		g.cliqueConstructivo(res);
		g.busquedaLocal(res);
		gettimeofday(&t2,NULL);		
		t += timeval_diff(t2, t1);
		guardarRes(os,res);
		res.clear();
		is >> n;
	}

	is.close();
	os.close();
	return t;
}


double timeval_diff(struct timeval& a, struct timeval& b) {
  return (a.tv_sec + - b.tv_sec)*1000 + (a.tv_usec  - b.tv_usec)/1000;
}


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
