#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <sys/time.h>

using namespace std;
void mostrar(const vector<int >& v);
unsigned int escalerar(vector<int>& v);
unsigned int maximoDes(vector<unsigned int>& descenso,vector<int>& v,unsigned int i);
unsigned int maximoAsc(vector<unsigned int>& ascenso,vector<int>& v,unsigned int i);
void completar_descensos(vector<unsigned int>& descenso, vector<int>& v);
void completar_ascensos(vector<unsigned int>& ascenso, vector<int>& v);
bool cargar(vector<int>& v,ifstream &entrada);

int main(){
	ifstream entrada;
	entrada.open("Tp2Ej1.in");
	ofstream salida;
	salida.open("tiempos.out");
	unsigned int res;
	struct timeval t1,t2;
	double tiempo,tiempoTotal;
	cout.precision(10);
	tiempoTotal = 0;
	
		
	vector<int> v; 
	bool sigueArchivo;
	
	do{
		sigueArchivo = cargar(v,entrada);
				
		if(sigueArchivo) {
			//tomarTiempo.
			gettimeofday(&t1,NULL);

			res = escalerar(v);
			//dejarDeTomarTiempo.
			gettimeofday(&t2,NULL);

			tiempo = (t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_usec - t1.tv_usec);
			tiempoTotal = tiempoTotal + tiempo;
			salida.precision(0);
			salida << fixed << v.size() << " " <<  tiempoTotal << endl;

		}
	}while(sigueArchivo);
	
	
	entrada.close();
	salida.close();
	return 0;
}





bool cargar(vector<int>& v,ifstream &entrada){
	int n,a;
	v.clear();
	entrada >> n;
	if (n == -1) return false;
	
		for(int i = 0;i<n;i++){
			entrada >> a;
			v.push_back(a);
		}

	return true;
}





//Escalerar() devuelve la minima cantidad de borrados que hay que efectuar para convertir en escalera a v.
unsigned int escalerar(vector<int>& v){
	int max = 0;
	vector<unsigned int> ascenso(v.size());
	vector<unsigned int> descenso(v.size());

	
	completar_ascensos(ascenso,v);
	completar_descensos(descenso,v);	
	
	//obtengo el max, que es el punto en donde hay mayor ascenso a izq y mayor desc a der.
	for(int i = 0;i<v.size();i++){
		if(ascenso[i] + descenso[i] > max) max = ascenso[i] + descenso[i];
	}
	
	
	return  v.size() - max + 1;

}

void completar_descensos(vector<unsigned int>& descenso, vector<int>& v){
	for(int i = v.size()-1;i>=0;i--){
		//en descenso se va guardando , en la posicion i, la longitud del mayor descenso desde i hasta el final de v;
		descenso[i] = maximoDes(descenso,v,i) + 1;

	}
}


void completar_ascensos(vector<unsigned int>& ascenso, vector<int>& v){
	for(int i = 0;i<v.size();i++){
			//en ascenso se va guardando , en la posicion i, la longitud del mayor ascenso hasta i;
			ascenso[i] = maximoAsc(ascenso,v,i) + 1;
	}
}



unsigned int maximoAsc(vector<unsigned int>& ascenso,vector<int>& v,unsigned int i){
	unsigned int res = 0;
	for(int j = 0;j<i;j++){
		//ver teorica de maximo ascenso para entender esta parte.
		//basicamente se fija la maxima longitud de ascenso hasta una posicion de algun valor menor que en el que estoy parado
		if(v[j] < v[i] && res < ascenso[j])	res = ascenso[j]; 
	}
	return res;
}



unsigned int maximoDes(vector<unsigned int>& descenso,vector<int>& v,unsigned int i){

	unsigned int res = 0;
	for(int j = v.size()-1;j>i;j--){
		if(v[j] < v[i] && res < descenso[j]) res = descenso[j]; 
	}
	return res;
}


void mostrar(const vector<int>& v){
	cout << endl << "[";
	for(int i = 0;i<v.size();i++) cout << v[i]<< " ";
	cout << "]" << endl;

}






