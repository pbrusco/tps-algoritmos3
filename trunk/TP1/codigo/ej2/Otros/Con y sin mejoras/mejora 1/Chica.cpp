#include "Ronda.h"


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

