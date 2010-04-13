#ifndef __RONDA__
#define __RONDA__

#include <iostream>
#include <map>
#include <list>
#include <set>
#include <algorithm>

using namespace std;

typedef int chica;

class Ronda{

	public:
	
		Ronda();
		
		~Ronda();
		
		void agregarAmistades(chica c,list<chica> amigas);
		
		void cargarAmistades(istream& is,int n);
		
		bool resolver();

		bool probarDistintasRondas(chica prim, chica ult);
		
		void mostrar(ostream& os) const ;

		bool comparacionPorAmistades(const chica& primera,const chica& segunda);

	private:
	
		//de aca voy a saber si una chica esta o no en la ronda que estoy armando
		set<chica>* enRonda;
		
		//contiene las relaciones entre las chicas
		map<chica,list<chica> >* amistades;
		
		void cargarRelacion(istream& is);

};

ostream& operator<<(ostream& os, const Ronda &r);

#endif
