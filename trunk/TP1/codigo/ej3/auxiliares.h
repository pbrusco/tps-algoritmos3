#ifndef __AUX__
#define __AUX__

////////////////////////	DEFINICIONES	////////////////////////



//saltea todos los espacios en blanco
void saltearEspacios(istream& is);





////////////////////////	IMPLEMENTACIONES	////////////////////////



void saltearEspacios(istream& is){
	while((is.peek() == (int)(' ')) || (is.peek() == (int)('\n')) || (is.peek() == (int)('\r')) ){
		is.ignore(1);
	}
}

#endif
