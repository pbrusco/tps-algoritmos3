#ifndef __RONDA__
#define __RONDA__

#include <iostream>
#include <map>
#include <set>

using namespace std;

typedef int chica;

class Ronda{

	public:
	
		Ronda();
		
		~Ronda();
		
		void agregarAmistades(chica c,set<chica> amigas);
		
		void cargarAmistades(istream& is,int n);
		
		bool resolver();

		bool probarDistintasRondas(chica prim, chica ult);
		
		void mostrar(ostream& os);
		
		ostream& operator<<(const Ronda &r);



	private:
	
		//de aca voy a saber si una chica esta o no en la ronda que estoy armando
		set<chica>* enRonda;
		
		//contiene las relaciones entre las chicas
		map<chica,set<chica> >* amistades;
		
		void cargarRelacion(istream& is);
		
};



#endif
