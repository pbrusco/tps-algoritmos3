#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cassert>
#include <algorithm>
#include <sys/time.h>
#include <set>
#include <map>

using namespace std;


int main(){
	int seed = 2;
	ofstream salida;
	salida.open("grupoPeleador");
	srand( seed );
	seed++;
	
	
	for (int i = 2;i<= 100;i++){
	
		salida << "   " << i << endl;
		int contador = 0;
		map<int,set<int> > chicas;
	
	int cantRelaciones = ((i-4)*(i-5))/2; //mientras mas chico este numero, menos relaciones por lo tanto menos chances de que haya sol
	
		while(contador <= cantRelaciones){
		
			int x = (rand() % i)+1;
			int y = (rand() % i)+1;
			
			if((chicas[x].size() < i) && (chicas[y].size() < i) && x != y ){
				chicas[x].insert(y);
				chicas[y].insert(x);
				contador++;
			}
	
		}
		
		for(int d = 1;d<=i;d++){
		salida << chicas[d].size() << "   ";
			for(set<int>::iterator it = chicas[d].begin();it != chicas[d].end();it++){
				salida << (*it) << " ";
			}
		salida << endl;
		
		}
	salida << endl;
	}
	
	
	
	salida.close();

}










