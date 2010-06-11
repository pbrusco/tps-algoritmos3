#include <iostream>
#include <fstream>
#include "grafo.h"

#define forn(i,n) for(int i=0; i<n; i++)
#define forall(it,X) for(typeof((X).begin()) it = (X).begin(); it != (X).end(); it++)

using namespace std;

void printSet(ostream& os, set<int> c);


int main(){
	Grafo g;
	int n, cant_cc;
	set<int> res, temp;
	ifstream is; is.open("../in/Tp3.in");
	ofstream os; os.open("../out/Tp3EXACTO.out");

	is >> n;
	while(n != -1) {
		g.cargar(is,n);
		cant_cc = g.detectarCC();
		forn(i,cant_cc) {
			g.maxClique(i, res.size(), temp);
			if (temp.size() > res.size()) res = temp;			
			temp.clear();		
		}
		printSet(os,res);
		res.clear();
		is >> n;
	}

	is.close();
	return 0;
}


void printSet(ostream& os, set<int> c) {
	os << c.size() << endl << "N ";
	forall(it,c) {	os << ((*it) + 1) << ' ';	}
	os << endl;
}
