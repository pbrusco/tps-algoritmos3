#! /usr/bin/env python

import sys, os, random
from random import randint


def main(*args):
	""" Algortimo principal """
	random.seed()
	exit = False	

	while not exit:
		opcion = mostrarMenu()
		if opcion in ['f', 'F']:
			exit = True
			break
		else:
			in_f = open('../tests/'+str(randint(1,100))+'.in', 'w')
			os.system('clear')
			nro_casos = int(raw_input("Cuantas instancias del problema desea generar?:  "))
			for _ in range(nro_casos):
				n, m = accionarMenu(opcion)
				generador(n, m, in_f)
			in_f.write(str(-1))
			in_f.close()	 

	return 0

	
def mostrarMenu():
	""" Muestra un menu de opciones en pantalla """

	os.system('clear')
	print
	print "Por favor seleccione el tipo de archivo de entrada que desea generar y presione Enter", '\n'
	print "a - Muchas esquinas conectadas por muchas calles"
	print "b - Muchas esquinas conectadas por pocas calles"
	print "c - Pocas esquinas conectadas por muchas calles"
	print "d - Pocas esquinas conectadas por pocas calles"
	print "e - Aleatorio"
	print "f - Salir del programa"
	opcion = raw_input("Ingrese una opcion [a-f]:  ")		
	return opcion


def accionarMenu(opcion):
	""" Devuelve valores distintos de n y m segun la opcion elegida en el menu """
	
	return {
	'a': (randint(1,100), 1),  
	'b': (randint(1,100), 0),
	'c': (randint(1,10), 1),
	'd': (randint(1,10), 0)
	}.get(opcion, (randint(1,50), randint(0,1)))


def generador(n, m, f):
	"""Genera un tantos grafos de n nodos y de al menos m aristas como se establezca en nro_ casos y los graba en el archivo f"""

	grafo = [set() for _ in range(n)]	
	for nodo in range(n):
		if m:
			cant_vecinos = randint((n-1)/2, n-1) - len(grafo[nodo])
		else:
			cant_vecinos = randint(0,(n-1)/2) - len(grafo[nodo])
		for _ in range(cant_vecinos):
			vecino = nodo
			while (vecino == nodo):
				vecino = randint(0,n-1)
			grafo[nodo].add(vecino+1)
			grafo[vecino].add(nodo+1)

	f.write(" " + str(n) + '\n') 
	for nodo in range(n):
		f.write('\t' + str(len(grafo[nodo])) + '\t') 
		for x in grafo[nodo]: f.write(str(x) + " ") 
		f.write('\n')



if __name__ == '__main__': main(sys.argv)
