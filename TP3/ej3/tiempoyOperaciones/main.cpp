#include <iostream>
#include <fstream>
#include <cassert>
#include <sys/time.h>
#include "grafo.h"

#define forn(i,n) for(int i=0; i<n; i++)
#define forall(it,X) for(typeof((X).begin()) it = (X).begin(); it != (X).end(); it++)

using namespace std;

void printSet(ostream& os, const set<int>& c);
int resolverConstructiva(const string& input, const string& output, const string& outDebug);
int timeval_diff(struct timeval& a, struct timeval& b); 	/* retorna "a - b " en microsegundos */


int main(int argc, char** argv) {
	string input, output,outDebug;
	int time = 0.0;
	
	if (argc == 1) {
		input = "../../in/Tp3.in";
		output = "../../out/3 - CONSTRUCTIVA/Tp3.out";
		outDebug = "Tp3_Tiempos.ej3";
		time = resolverConstructiva(input,output,outDebug);
		cout << "El algortimo demoró " << time << " µseg en resolver las instancias del archivo " << input << endl;
	}
	else {
		forn(i, argc-1) {
			input = argv[i+1];
			int pos = input.rfind('/');
			output = input.substr(pos+1, input.size());
			pos = output.rfind(".in");
			outDebug = output;
			if (pos!=string::npos){
				output.replace(pos,3,".out");
				outDebug = outDebug.substr(0,outDebug.length()-3);
			}
			outDebug = outDebug + "_Tiempos.ej3";
			time = resolverConstructiva(input,output,outDebug);
			//cout << "El algortimo demoró " << time << " µseg en resolver las instancias del archivo " << input << endl;
		}
	}
	return 0;
}


int resolverConstructiva(const string& input, const string& output, const string& outDebug) {
	int n;
	Grafo g;
	set<int> res;
	ifstream is;	is.open(input.c_str());		assert(is.is_open());
	ofstream os;	os.open(output.c_str());	assert(os.is_open());
	ofstream contar;	contar.open(outDebug.c_str());

	int tiempoTotal;
	struct timeval t1, t2;

	is >> n;
	while(n != -1) {
		g.cargar(is,n);
		tiempoTotal = 0.0;
		for(int i = 0; i < 10; i++){
			gettimeofday(&t1,NULL);
			g.cliqueConstructivo(res);
			gettimeofday(&t2,NULL);
			tiempoTotal += timeval_diff(t2, t1);
		}
		contar << n << '\t' << tiempoTotal/10 << endl;
		printSet(os,res);
		res.clear();
		is >> n;
	}
	
	

	is.close();
	os.close();
	contar.close();
	return tiempoTotal;
}


void printSet(ostream& os, const set<int>& c) {
	os << c.size() << endl << "N ";
	forall(it,c) {	os << ((*it) + 1) << ' ';	}
	os << endl;
}


int timeval_diff(struct timeval& a, struct timeval& b) {
  return (a.tv_sec + - b.tv_sec)*1000000 + (a.tv_usec  - b.tv_usec);
}
