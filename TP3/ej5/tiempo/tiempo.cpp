#include <iostream>
#include <fstream>
#include <cassert>
#include <sys/time.h>
#include "../grafo.h"

#define forn(i,n) for(int i=0; i<n; i++)
#define forall(it,X) for(typeof((X).begin()) it = (X).begin(); it != (X).end(); it++)

using namespace std;

void printSet(ostream& os, const set<int>& c);
double resolverBusqTabu(const string& input, const string& output, const string& data);
double timeval_diff(struct timeval& a, struct timeval& b); 	/* retorna "a - b " en milisegundos */


int main(int argc, char** argv) {
	srand(time(NULL));

	string input, output, data;
	double time = 0.0;
	
	if (argc == 1) {
		input = "../../in/Tp3.in";
		output = "./out/Tp3.out";
		data = "./data/Tp3.data";
		time = resolverBusqTabu(input,output,data);
		cout << "El algortimo demoró en promedio " << time << " milisegundos en resolver las instancias del archivo " << input << endl;
	}
	else {
		forn(i, argc-1) {
			input = argv[i+1];
			int pos = input.rfind('/');
			output = input.substr(pos+1, input.size());
			data = output;
			pos = output.rfind(".in");
			if (pos!=string::npos) {
				output.replace(pos,3,".out");
				data.replace(pos,3,".data");
			}
			output = "./out/" + output;
			data = "./data/" + data;
			time = resolverBusqTabu(input,output,data);
			cout << "El algortimo demoró en promedio " << time << " milisegundos en resolver las instancias del archivo " << input << endl;
		}
	}
	return 0;
}


double resolverBusqTabu(const string& input, const string& output, const string& data) {
	int n;
	Grafo g;
	set<int> res;
	ifstream is;	is.open(input.c_str());		assert(is.is_open()); 
	ofstream os;	os.open(output.c_str());	assert(os.is_open());
	ofstream gf;	gf.open(data.c_str());		assert(os.is_open());

	struct timeval t1, t2;	
	double time = 0.0, t = 0.0;
	list<pair<int, double> > grafico;	

	is >> n;
	while(n != -1) {
		t = 0.0;
		g.cargar(is,n);
		forn(i,10) {
			gettimeofday(&t1,NULL);
			g.cliqueTabu(res);
			gettimeofday(&t2,NULL);
			t += timeval_diff(t2, t1);
		}
		t = t/10;
		grafico.push_back(make_pair(n, t));
		time += t;
		printSet(os,res);
		res.clear();
		is >> n;
	}

	grafico.sort();
	forall(it, grafico) {gf << it ->first << '\t' << it -> second << endl;}
	is.close();
	os.close();
	gf.close();
	return time;
}


void printSet(ostream& os, const set<int>& c) {
	os << c.size() << endl << "N ";
	forall(it,c) {	os << ((*it) + 1) << ' ';	}
	os << endl;
}


double timeval_diff(struct timeval& a, struct timeval& b) {
  return (a.tv_sec + - b.tv_sec)*1000 + (a.tv_usec - b.tv_usec)/1000;
}
