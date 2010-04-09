#include "Ronda.h"


Ronda::Ronda(){
	amistades = new map<chica,set<chica> >;
	enRonda   = new set<chica>;
}

Ronda::~Ronda(){
	delete amistades;
	delete enRonda;
}

void Ronda::agregarAmistades(chica c,set<chica> amigas){
	amistades->insert(pair<chica, set<chica> >(c,amigas) );
}

void Ronda::cargarAmistades(istream& is,int n){
	
	enRonda->clear();
	amistades->clear();
	
	int m,a;
	set<chica> amigas;
	
	
	for(int i = 1;i <= n; i++){
		is >> m;
		amigas.clear();
		for(int j = 1; j <= m; j++)
		{
			is >> a;
			amigas.insert(a);
		}
		agregarAmistades(i,amigas);
	}	
	

}

bool Ronda::resolver(){
	bool aux;
	for(int i = 1;i<=amistades->size();i++)
	{
		enRonda->insert(i);
		aux = probarDistintasRondas(i,i);
		if(aux) {
			return true;
		}
		enRonda->erase(i);

	}
	
	return false;

}

bool Ronda::probarDistintasRondas(chica prim, chica ult){

	if (((*amistades)[ult].count(prim) == 1) && (amistades->size() == enRonda->size())) {
		return true;
	}
	else {
		set<int>::iterator it;
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

void Ronda::mostrar(ostream& os){}
		
ostream& Ronda::operator<<(const Ronda &r){}

void Ronda::cargarRelacion(istream& is){



}



