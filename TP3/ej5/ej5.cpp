#include "ej5.h"

using namespace std;


int main(){

	int cantNodos;
	int i = 1;
	Grafo g;
	set<int> cliqueMaximo;
	ifstream is;
	ofstream os;
	os.open("../out/prueba2BUSQUEDALOCAL.out");
	is.open("../in/prueba2.in");
	is >> cantNodos;
	
	while(cantNodos != -1){
	
		g.cargar(is,cantNodos);

		//solucion constructiva
		cliqueMaximo = g.cliqueConstructivo();
		
		//aca empieza la busqueda local
		g.busquedaLocal(cliqueMaximo);
		
		
		//guardo o muestro el resultado
		guardarRes(os,cliqueMaximo);
		
		i++;
		cliqueMaximo.clear();
		is >> cantNodos;
	}
	
	
	is.close();
	os.close();
	
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

set<int> Grafo::fronteraEnComun(int u, int v) const {

	set<int> res;
	for(int j = 0; j < matAd.size(); j++){
		if(sonAdyacentes(u,j) && sonAdyacentes(v,j))
			res.insert(j);
	}
	if(sonAdyacentes(u,v)){
		res.insert(u);
		res.insert(v);
	}		
	return res;
}

set<int> Grafo::losMasFronterizos(int &u, int &v) const{

	set<int> res,aux;
	u = 0;
	v = 1;
	for(int i = 0; i < matAd.size(); i++){
		for(int j = i+1; j < matAd.size(); j++){
			aux = fronteraEnComun(i,j);
			if(aux.size() > res.size()){
				res = aux;
				u = i;
				v = j;
			}
		}
	}
	return res;
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


set<int> Grafo::cliqueConstructivo() const {

	int x,y,v;
	set<int> res;
	set<int> frontera = losMasFronterizos(x,y);

	while(frontera.size() != 0){
		v = masRelacionado(frontera);
		if(vecinoDeTodos(v,res))
			res.insert(v);
		frontera.erase(v);
	}
	
	if(res.size() == 0)
		res.insert(0);
	
	return res;
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

Heap Grafo::frontera(const set<int>& clique) const{

	Heap res;
	for(set<int>::iterator it = clique.begin(); it != clique.end(); it++){
		for(int i = 0; i < matAd.size(); i++){
			if(sonAdyacentes(i,*it) && clique.count(i) == 0){
				res.push(make_pair(grados[i],i));
			}
		}
	}
	return res;
}

void Grafo::cambiarSiMaximiza(set<int>& clique, bool &cambio) const {
	
	set<int> posibleMejora;
	const set<int> copiaClique = clique;
	Heap vecindad;

	//HACER UN MIN HEAP DE GRADOS CON LOS PERTENECIENTES A LA CLIQUE E ITERAR SOBRE ESE HEAP
	for(set<int>::iterator itC = copiaClique.begin(); itC != copiaClique.end(); itC++){
		//saco de a uno de los que esta en la clique, y pruebo si puedo meter alguno/s distinto
		posibleMejora = copiaClique;
		posibleMejora.erase(*itC);
		
		//los posibles cambios se realizan sobre los vecinos de los nodos que estan en la clique
		vecindad = frontera(posibleMejora);
		
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
	}
}


void Grafo::funcionTabu(){


	//(1) mientras no se de el criterio de parada (ej: diversificar k veces)

		//planteo una solucion inicial (diversificar)

		//hago tabusearch a partir de esa solucion

			//encontrar maximo local e ir llenando la lista tabu con los ultimos n movimientos

			//busco X soluciones que empeoren
				//si no encuentro mas
					//hago tabusearch de nuevo

			//si empeore X+1 veces vuelvo al mientras(1)
}



void guardarRes(ostream& os, set<int> c){
	os << c.size() << endl << "N ";
	set<int>::iterator it;
	for(it = c.begin(); it != c.end(); it++){
		os << ((*it) + 1) << ' ';
	}
	os << endl;
}
