#ifndef __AUX__
#define __AUX__

////////////////////////	DEFINICIONES	////////////////////////


//cargar un numero de un istream
void cargarNumero(istream& is, string &s);

//pasar string a numero
int pasarStringANumero(string s);

//saltea todos los espacios en blanco
void saltearEspacios(istream& is);





////////////////////////	IMPLEMENTACIONES	////////////////////////




void cargarNumero(istream& is, string &s){

	char c;
	s.clear();
	while(48 <= is.peek() && is.peek() <= 57){
		is.get(c);
		s += c;
	}
}


int pasarStringANumero(string s){

	int potencia = s.size()-1;
	int res = 0;
	
	for(potencia;potencia>=0;potencia--){	
		res = res + pow(10,potencia) * (int)(s[s.size()-potencia-1]-'0');	
	}
	
	return res;
}

void saltearEspacios(istream& is){
	while((is.peek() == (int)(' ')) || (is.peek() == (int)('\n')) || (is.peek() == (int)('\r')) ){
		is.ignore(1);
	}
}

#endif
