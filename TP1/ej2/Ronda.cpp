#include "Ronda.h"


Ronda::Ronda(){
	amistades = new map<chica,list<chica> >;
	enRonda   = new set<chica>;
}

Ronda::~Ronda(){
	delete amistades;
	delete enRonda;
}

void Ronda::agregarAmistades(chica c,list<chica> amigas){
	amistades->insert(pair<chica, list<chica> >(c,amigas) );
}

void Ronda::cargarAmistades(istream& is,int n){
	
	enRonda->clear();
	amistades->clear();
	
	int m,a;
	list<chica> amigas;
	
	for(int i = 1;i <= n; i++){
		is >> m;
		amigas.clear();
		for(int j = 1; j <= m; j++)
		{
			is >> a;
			amigas.push_front(a);
		}
		agregarAmistades(i,amigas);
	}	

//	for(int i = 1;i <= n; i++){
//	(*amistades)[i].sort(comparacionPorAmistades);
//	}	
	

}
/*
bool Ronda::comparacionPorAmistades(const chica& primera,const chica& segunda)
{
return ((*amistades)[primera].size() > (*amistades)[segunda].size()) ;
}
*/



bool Ronda::resolver(){

	/***************************************************************|
	|		Comienzo eligiendo la chica con menos amigas			|
	|		para maximizar el tamaño del arbol jeje					|
	****************************************************************/

	chica simpatica = 1;
	for(int i = 1;i<=amistades->size();i++)
	{
		if( (*amistades)[simpatica].size() < (*amistades)[i].size())
			simpatica = i;
	}

// la inserto en la ronda y comienzo con el backtracking:

	enRonda->insert(simpatica);
	
	return  probarDistintasRondas(simpatica,simpatica);;

}

bool Ronda::probarDistintasRondas(chica prim, chica ult){

list<chica>::iterator it,itA,itB;	

itA = (*amistades)[ult].begin();
itB =  (*amistades)[ult].end();

	if ((find(itA,itB, prim) != itB) && (amistades->size() == enRonda->size())) {
		return true;
	}
	else {

		bool res;
	
		for (it = (*amistades)[ult].begin();it != (*amistades)[ult].end();it++){

			if (enRonda->count(*it) == 0){
				enRonda->insert(*it);
				res = probarDistintasRondas(prim,*it);
			
				if(res){
					return true;
				}
				
				enRonda->erase(*it);
				
			}	
		}
		return false;
	}	

}

void Ronda::mostrar(ostream& os) const{

	map<chica,list<chica> >::iterator it;
	list<chica>::iterator it2;
		
	for(it=amistades->begin(); it != amistades->end(); it++){
		os << "Chica: " << (*it).first << "    Amigas: ";
		for(it2=((*it).second).begin(); it2 != ((*it).second).end(); it2++){
			os << (*it2) << " ";
		}
		os << endl;
	}
	os << endl;
}


ostream& operator<<(ostream& os, const Ronda &r){
	r.mostrar(os);
	return os;
}



