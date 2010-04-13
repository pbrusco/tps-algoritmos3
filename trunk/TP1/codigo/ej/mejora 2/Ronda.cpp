#include "Ronda.h"


Ronda::Ronda(){
	gente = new list<chica>;
	enRonda   = new set<int>;
	amigasPrimera = new set<int>;
}

Ronda::~Ronda(){
	delete gente;
	delete enRonda;
	delete amigasPrimera;
}


void Ronda::cargarAmistades(istream& is,int n){
	gente->clear();	
	enRonda->clear();
	amigasPrimera->clear();
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
	
	//para la mejora(1). Ordeno todas las amigas por cantidad de amigas, de menor a mayor.	
//	gente->sort();

	//para la mejora (2). inserto todas las amigas de la primera en un conjunto.
	set<int>::iterator it;
	for (it = ((gente->front()).dameAmigas())->begin();it != ((gente->front()).dameAmigas())->end();it++){
		amigasPrimera->insert(*it);
	}	
}

bool operator<(const chica &c1,const chica &c2){
	//para mejora (1) una chica es menor que otra si tiene menos amigas.
	return (c1.dameAmigas())->size() < (c2.dameAmigas())->size();
}

bool Ronda::resolver(){
	
	//	Comienzo eligiendo la chica con menos amigas			
	//	para minimizar el tamaño del arbol, es decir,						
	//	si la mejora (1) esta activada, gente->front(); devuelve la chica con menos amigas.
	//	si no esta activada devuelve cualquier chica para empezar la ronda.
	chica solitaria = gente->front();

	
	// inserto su nombre en la ronda y comienzo con el backtracking:
	enRonda->insert(solitaria.dameNombre());
	return  probarDistintasRondas(solitaria,solitaria);

}

bool Ronda::probarDistintasRondas(const chica &prim, const chica &ult){

	list<chica>::iterator it;

	//si en las amigas de la ultima que tome para la ronda aparece la primera y el tamaño de la ronda
	// es la cantidad de gente, entonces puedo cerrar la ronda y por lo tanto terminar satifactoriamente:
	
	if (((ult.dameAmigas())->count(prim.dameNombre())!=0) && (gente->size() == enRonda->size())) {
		return true;
	}
	else {

		bool res;
		bool eraAmiga = false;
		//si no recorro toda la gente, desde el principio (si la mejora (1) esta activada, 
		// siempre agarrara primero las mas solitarias) y compruebo que no este en la ronda y sea amiga de la
		// ultima que inserte. En caso que esto se cumpla la meto a la ronda e intento continuar.
	
		for (it = gente->begin();it != gente->end();it++){

			int estaEnRonda = enRonda->count(it->dameNombre());
			int esAmigaDeLaUltima = (ult.dameAmigas())->count(it->dameNombre());
			int restantesAmigasPrimera  = (amigasPrimera->size());
			int esAmigaDeLaPrimera = amigasPrimera->count(it->dameNombre());
			
			if ( (estaEnRonda == 0) && (esAmigaDeLaUltima != 0) && (restantesAmigasPrimera != 0) ){
				
				//el siguiente if y la ultima condicion del if anterior son para la mejora (2)
				//comprueba antes de intentar probar soluciones si aun quedan amigas de la primera sin usar.
				//y en caso de poder, actualiza las amigas de la primera "usadas" para la ronda.

				if (esAmigaDeLaPrimera != 0) {
					eraAmiga = true;
					amigasPrimera->erase(it->dameNombre());
				}
				else 
				{
					eraAmiga = false;
				}

				enRonda->insert(it->dameNombre());
				res = probarDistintasRondas(prim,*it);
			
				if(res)
				{
					return true;
				}
				else {
					enRonda->erase(it->dameNombre());
					if(eraAmiga) amigasPrimera->insert(it->dameNombre());
					//el if anterior sirve para la mejora (2) y se encarga de volver a insertar amigas de la 
					//primera que quisimos utilizar pero no funcionaron para que puedan ser usadas en otra
					//combinacion.	
						}
			//en caso que no pude formar una solución con la rama anterior, vuelvo a las condiciones necesarias para
			// ir por las demas ramas, es decir, sacarla de la ronda e intentar con la siguiente.		
			}	
		}
		return false;
		//si termino el ciclo y no se puede formar por la rama actual se devuelve false 
		//para que el algoritmo termine o deje de buscar sobre esa rama.
	}	
}





