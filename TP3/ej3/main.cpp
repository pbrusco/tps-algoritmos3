#include <iostream>
#include <fstream>
#include <cassert>
#include <sys/time.h>
#include "grafo.h"

#define forn(i,n) for(int i=0; i<n; i++)
#define forall(it,X) for(typeof((X).begin()) it = (X).begin(); it != (X).end(); it++)

using namespace std;

void printSet(ostream& os, const set<int>& c);
double resolverConstructiva(const string& input, const string& output);
double timeval_diff(struct timeval& a, struct timeval& b); 	/* retorna "a - b " en microsegundos */


int main(int argc, char** argv) {
	string input, output;
	double time = 0.0;
	
	if (argc == 1) {
		input = "../in/Tp3.in";
		output = "../out/3 - CONSTRUCTIVA/Tp3.out";
		time = resolverConstructiva(input,output);
		cout << "El algortimo demoró " << time << " milisegundos en resolver las instancias del archivo " << input << endl;
	}
	else {
		forn(i, argc-1) {
			input = argv[i+1];
			int pos = input.rfind('/');
			output = input.substr(pos+1, input.size());
			pos = output.rfind(".in");
			if (pos!=string::npos) output.replace(pos,3,".out");
			output = "../out/3 - CONSTRUCTIVA/" + output;
			time = resolverConstructiva(input,output);
			cout << "El algortimo demoró " << time << " milisegundos en resolver las instancias del archivo " << input << endl;
		}
	}
	return 0;
}


double resolverConstructiva(const string& input, const string& output) {
	int n;
	Grafo g;
	set<int> res;
	ifstream is;	is.open(input.c_str());		assert(is.is_open());
	ofstream os;	os.open(output.c_str());	assert(os.is_open());

	double time = 0.0;
	struct timeval t1, t2;	

	is >> n;
	while(n != -1) {
		g.cargar(is,n);
		gettimeofday(&t1,NULL);
		g.cliqueConstructivo(res);
		gettimeofday(&t2,NULL);
		time += timeval_diff(t2, t1);
		printSet(os,res);
		res.clear();
		is >> n;
	}

	is.close();
	os.close();
	return time;
}


void printSet(ostream& os, const set<int>& c) {
	os << c.size() << endl << "N ";
	forall(it,c) {	os << ((*it) + 1) << ' ';	}
	os << endl;
}


double timeval_diff(struct timeval& a, struct timeval& b) {
  return (a.tv_sec + - b.tv_sec)*1000 + (a.tv_usec  - b.tv_usec)/1000;
}
