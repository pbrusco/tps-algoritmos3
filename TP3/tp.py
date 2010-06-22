#!/usr/bin/env python

import sys, os

def main():
	""" Algoritmo Principal  """
	
	exit = False;
	while not exit:
		opc = mostrarMenu()
		if opc not in "abcde":
			pass
		elif opc == 'e': 
			exit = True 
			os.system('clear')
			break
		else:
			accionarMenu(opc)


def mostrarMenu():
	""" Muestra un menu de opciones en pantalla """

	os.system('clear')
	print
	print "Por favor seleccione el tipo de archivo de entrada que desea generar y presione Enter", '\n'
	print "a - Recompilar todos los programas"
	print "b - Recompilar un programa en particular"
	print "c - Ejecutar todos los programas con los archivos en la carpeta '/in'"
	print "d - Ejecutar un programa en particular"
	print "e - Salir del programa"
	opcion = raw_input('\n Ingrese una opcion [a-e]:  ')	
	return opcion


def accionarMenu(opcion):
	""" Ejecuta distintas funciones segun la opcion elegida en el menu """

	print '\n'
	if opcion in "bd": return {'b': compilar, 'd': ejecutar}.get(opcion)(1)
	else: return {'a': compilar, 'c': ejecutar}.get(opcion)()

	
def compilar(n=0):
	"""Compila los distintos ejercicios en la carpeta del Tp"""

	if n == 0: 	
		for x in "2345": os.system('cd ./ej'+x+'; make; cd ..')
		os.system('echo "Todos los ejercicios fueron recompilados"')
	elif n == 1:
		x = raw_input("Indique el ejercicio que desea recompilar : ")
		os.system('cd ./ej'+x+'; make; cd ..')
		os.system('echo "El ejercicio '+x+' fue recompilado"')
	raw_input()
	

def ejecutar(n=0):
	"""Ejecuta los distintos ejercicios en la carpeta del Tp"""

	if n == 0: 	
		for x in "235": os.system('cd ej'+x+'; ./ej'+x+' ../in/*; echo "\n"; cd ..')
		os.system('echo "Todos los ejercicios fueron ejecutados"')
	elif n == 1:
		x = raw_input("Indique el ejercicio que desea ejecutar : ")
		os.system('cd ej'+x+'; ./ej'+x+' ../in/* ; cd ..')
		os.system('echo "El ejercicio '+x+' fue ejecutado"')
	raw_input()


if __name__ == '__main__' : main ()
