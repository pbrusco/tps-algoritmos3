#ifndef __HORA__
#define __HORA__

#include <iostream>
using namespace std;

class Hora{

	public:
	
		//constructor por defecto
		Hora();
		
		//constructor
		Hora(short horas, short minutos, short segundos);
		
		//constructor, dado un string con formato HH:MM:SS
		Hora(string s);

		//destructor
		~Hora();
		
		//contructor por copia
		Hora(const Hora& hora1);
		
		//devuelve las horas
		short horas() const;
		
		//devuelve los minutos
		short minutos() const;
		
		//devuelve los segundos
		short segundos() const;
		
		//setear hora
		void setHora(short hora);
		
		//setear minutos
		void setMinutos(short min);
		
		//setear segundos
		void setSegundos(short seg);
		
		//operador =
		Hora& operator=(const Hora& hora1);
		
		//operador ==
		bool operator==(const Hora& hora1) const;
		
		//operador <
		bool operator<(const Hora& hora1) const;
		
		//operador <=
		bool operator<=(const Hora& hora1) const;
		
		//carga una hora dado un ostream del cual obtenerla
		void cargarHora(istream& is);
		
		//imprime la hora
		void imprimir(ostream& os) const;
		
		
	private:
	
		short hh;
		short mm;
		short ss;
};



#endif
