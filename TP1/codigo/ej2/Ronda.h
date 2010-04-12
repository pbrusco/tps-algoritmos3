#ifndef __RONDA__
#define __RONDA__

#include <iostream>
#include <list>
#include <set>

using namespace std;



class chica{
private:
	int nombre;
	set<int>* amigas;

public:
	chica();
	~chica();
	int dameNombre() const;
	set<int>* dameAmigas() const;
	chica(const chica&);
	chica& operator=(const chica &c1);
	void nombrar(int i);
	void amigar(int i);
};



class Ronda{

	public:
	
		Ronda();
		
		~Ronda();

		void cargarAmistades(istream& is,int n);
		bool resolver();
		bool probarDistintasRondas(const chica &prim,const chica& ult);

	private:

		set<int>* enRonda;
		list<chica>* gente;
};


bool operator<(const chica &c1,const chica &c2);


#endif
