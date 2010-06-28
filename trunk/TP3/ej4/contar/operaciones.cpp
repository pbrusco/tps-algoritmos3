#include "operaciones.h"
#include <cassert>
#include <math.h>

#define forn(i,n) for(int i=0; i<n; i++)
#define forall(it,X) for(typeof((X).begin()) it = (X).begin(); it != (X).end(); it++)

using namespace std;


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
    		out = "operaciones_" + out + ".ej4";
		}
		else{
			cout << "Se debe dar 1 o ningún parámetro. En el caso de dar 1 parámetro, "
				 << "pasar el archivo de entrada. En el caso de no dar parámetros, "
				 << "tomará los archivos por defecto (/in/Tp3.in y /out/4 - BUSQ_LOCAL/Tp3LOCAL.out)";
			assert(argc != 2 && argc != 1);
		}
	}

	int cantNodos;
	Grafo g;
	set<int> cliqueMaximo;
	ifstream is;
	ofstream contar;
	contar.open(out.c_str());
	is.open(in.c_str());
	is >> cantNodos;
	unsigned long long cantop;
	
	while(cantNodos != -1){
	
		g.cargar(is,cantNodos);
		
		cantop = 0;

		//solucion constructiva
		g.cliqueConstructivo(cliqueMaximo,cantop);

		//aca empieza la busqueda local
		g.busquedaLocal(cliqueMaximo,cantop);

		
		contar << cantNodos << '\t' << cantop << endl;
		
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

bool Grafo::vecinoDeTodos(int v, const set<int>& c, unsigned long long int &operaciones) const {
	bool res = true;
	operaciones++;
	forall(it,c) {
		res = res && sonAdyacentes(v,*it);
		operaciones += 2;
	}
	return res;
}


int Grafo::cantVecinos(int v, const set<int>& c, unsigned long long int &operaciones) const {
	int res = 0;
	forall(it,c) {
		if (sonAdyacentes(v,*it)){
			res++;
			operaciones++;
		}
		operaciones++;
	}
	return res;
}


void Grafo::cliqueConstructivo(set<int>& res, unsigned long long int &operaciones) const {
	int v;
	set<int> frontera;
	mayorFrontera(frontera,operaciones);
	while (frontera.size() != 0) {
		operaciones += 2;
		v = masRelacionado(frontera,operaciones);
		if (vecinoDeTodos(v,res,operaciones)){
			res.insert(v);
			operaciones = operaciones + (int) log10(res.size());
		}
		operaciones = operaciones + ((int) (log10(frontera.size()))) + 1;
		frontera.erase(v);
	}
	if (res.size() == 0)
		res.insert(0);
	operaciones++;
}


void Grafo::mayorFrontera(set<int>& res, unsigned long long int &operaciones) const {
	set<int> aux;
	for(int i=0; i<matAd.size(); i++) {
		for(int j =i+1; j<matAd.size(); j++) {
			fronteraEnComun(i,j,aux,operaciones);
			if (aux.size() > res.size()) {
				res = aux;
				operaciones += 4;
			}
			operaciones += 3;
		}
	}
}


void Grafo::fronteraEnComun(int u, int v, set<int>& res, unsigned long long int &operaciones) const {

	res.clear();
	if (sonAdyacentes(u,v)) {
		forn(j,matAd.size()) {
			if (sonAdyacentes(u,j) && sonAdyacentes(v,j)){
				res.insert(j);
				operaciones += (int) log10(res.size());
			}
			operaciones += 3;
		}
		res.insert(u);
		res.insert(v);
		operaciones += (2* (int) log10(res.size()));
	}
	operaciones +=2;
}


int Grafo::masRelacionado(const set<int>& frontera, unsigned long long int &operaciones) const {
	int res = *frontera.begin(), vecinosRes = 0, vecinosAux;
	forall(it,frontera) {
		vecinosAux = cantVecinos(*it,frontera, operaciones);
		if(vecinosAux > vecinosRes){
			res = *it;
			vecinosRes = vecinosAux;
			operaciones += 2;
		}
		operaciones++;
	}
	return res;
}


void Grafo::busquedaLocal(set<int> &cliqueMaximo, unsigned long long int &cantop) const{

	bool termine = false;
	bool cambio;
	
	//mientras no encuentre maximo local
	while(!termine) {
		
		cambio = false;

		//busco combinacion que maximice el clique
		cambiarSiMaximiza(cliqueMaximo,cambio,cantop);
		
		//si no encuentro una, termino
		if(!cambio){
			termine = true;
			cantop++;
		}
		cantop += 2;
	}
	cantop += 2;

}

void Grafo::vecinosAMaxHeap(const set<int>& clique, Heap &vecinos, const int v, unsigned long long int &cantop) const{

	if(!vecinos.empty()){
		vaciarHeap(vecinos);
	}

	for(set<int>::iterator it = clique.begin(); it != clique.end(); it++){
		for(int i = 0; i < matAd.size(); i++){
			if(sonAdyacentes(i,*it) && clique.count(i) == 0 && i != v){
				vecinos.push(make_pair(grados[i],i));
				cantop += (int) log10(vecinos.size());
			}
			cantop += (int) log10(clique.size()) + 3;
		}
	}
}

void Grafo::deCliqueAMinHeap(const set<int>& clique, Heap &cliqueMenorAMayor, unsigned long long int &cantop) const{

	if(!cliqueMenorAMayor.empty()){
		vaciarHeap(cliqueMenorAMayor);
	}

	for(set<int>::iterator it = clique.begin(); it != clique.end(); it++){
		cliqueMenorAMayor.push(make_pair(-grados[*it],*it));
		cantop += (int) log10(cliqueMenorAMayor.size());
	}
}

void Grafo::cambiarSiMaximiza(set<int>& clique, bool &cambio, unsigned long long int &cantop) const {
	
	set<int> posibleMejora;
	const set<int> copiaClique = clique;
	Heap cliqueMenorAMayor, vecindad;
	deCliqueAMinHeap(copiaClique,cliqueMenorAMayor,cantop);


	while(!cliqueMenorAMayor.empty()){
	
		cantop++;
	
		//saco de a uno de los que esta en la clique en orden de menor a mayor grado, y pruebo si puedo meter alguno/s distinto/s
		posibleMejora = copiaClique;
		posibleMejora.erase(cliqueMenorAMayor.top().second);
		cantop += copiaClique.size() + (int) log10(posibleMejora.size());
		
		//los posibles cambios se realizan sobre los vecinos de los nodos que estan en la clique (que no sea el que saque)
		vecinosAMaxHeap(posibleMejora,vecindad,cliqueMenorAMayor.top().second,cantop);
		
		//voy tomando en orden de grados
		while(!vecindad.empty()){
			if(vecinoDeTodos(vecindad.top().second,posibleMejora,cantop)){
				posibleMejora.insert(vecindad.top().second);
				cantop += 1 + (int) log10(posibleMejora.size());
			}
			
			cantop += 1 + (int) log10(vecindad.size());
			vecindad.pop();
		}
		cantop++;


		if(posibleMejora.size() > clique.size()){
			clique = posibleMejora;
			cambio = true;
			cantop += 4 + posibleMejora.size();
		}
		cantop += 3;
		
		cliqueMenorAMayor.pop();
	}
	cantop++;
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
