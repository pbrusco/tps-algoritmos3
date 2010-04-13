#include "Ronda.h"


Ronda::Ronda(){
	gente = new list<chica>;
	enRonda   = new set<int>;
}

Ronda::~Ronda(){
	delete gente;
	delete enRonda;
}


void Ronda::cargarAmistades(istream& is,int n){
	gente->clear();	
	enRonda->clear();
	chica c;
	int m,a;
	
	
	for(int i = 1;i <= n; i++){
		is >> m;
		
		c.nombrar(i);
		c.borrarAmigas();
		
		for(int j = 1; j <= m; j++)
		{
			is >> a;
			c.amigar(a);
		}
		
		gente->push_front(c);
	
	}	
	
	gente->sort();
	
	
	
}

bool operator<(const chica &c1,const chica &c2){

return (c1.dameAmigas())->size() < (c2.dameAmigas())->size();

}

bool Ronda::resolver(){

	/***************************************************************|
	|		Comienzo eligiendo la chica con menos amigas			|
	|		para minimizar el tamaño del arbol 						|
	****************************************************************/

	chica solitaria = gente->front();

	
// la inserto en la ronda y comienzo con el backtracking:

	enRonda->insert(solitaria.dameNombre());
	
	return  probarDistintasRondas(solitaria,solitaria);

}

bool Ronda::probarDistintasRondas(const chica &prim, const chica &ult){

list<chica>::iterator it;

	if (((ult.dameAmigas())->count(prim.dameNombre())!=0) && (gente->size() == enRonda->size())) {
		return true;
	}
	else {

		bool res;
	
		for (it = gente->begin();it != gente->end();it++){

			if ( (enRonda->count(it->dameNombre()) == 0 ) && ((ult.dameAmigas())->count(it->dameNombre()) != 0)){
				
				enRonda->insert(it->dameNombre());
				res = probarDistintasRondas(prim,*it);
			
				if(res)	return true;
				else enRonda->erase(it->dameNombre());
				
			}	
		}
		return false;
	}	

}






///CLASEEEEEEEEEEEEEEEEEEEEE:



	chica::chica(){
	amigas = new set<int>;
	nombre = 0;
	}
	
	chica::~chica(){
	delete amigas;

	}
	
	int chica::dameNombre() const{
	return nombre;
	}
	
	set<int>* chica::dameAmigas() const{
	return amigas;
	}
	
	chica::chica(const chica &c){
		set<int>::iterator it;
		nombre = c.dameNombre();
		amigas = new set<int>;
		for (it = (c.dameAmigas())->begin();it != (c.dameAmigas())->end();it++){
			amigar(*it);
		}
	}

	chica& chica::operator=(const chica &c){
	set<int>::iterator it;
	amigas->clear();
	nombre = c.dameNombre();
		for (it = (c.dameAmigas())->begin();it != (c.dameAmigas())->end();it++){
			amigar(*it);
		}
	}


	void chica::nombrar(int n){
	nombre = n;
	}

	void chica::amigar(int a){
	amigas->insert(a);
	}

	void chica::borrarAmigas(){
	amigas->clear();
	}



