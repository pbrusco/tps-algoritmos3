#ifndef __EJ3__
#define __EJ3__

using namespace std;

typedef int Programador;


struct ficha{

	string hora;
	Programador programador;
};



class Empresa{

	public:
	
		//constructor
		Empresa(int cantProgramadores);
		
		//destructor
		~Empresa();

		//resolucion del ej3
		int maxCantProgJuntos() const;
		
		//cargar empresa a mano
		void cargarEmpresa(ficha entran[], ficha salen[], int tam);			
	
		//cargar empresa desde archivo
		void cargarEmpresa(istream& is, int n);
		
		//cargar empresas y guardar salidas
		static void cargarEmpresasYResolver(string filenameIn, string filenameOut);

	private:
	
		int programadoresTotales;
		ficha* ingresos;
		ficha* egresos;
};






#endif
