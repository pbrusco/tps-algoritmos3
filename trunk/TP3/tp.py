#!/usr/bin/env python

import sys, os

def main():
	""" Algoritmo Principal  """
	
	exit = False;
	while not exit:
		opc = mostrarMenu()
		if opc not in "12345":
			pass
		elif opc == '5': 
			exit = True 
			os.system('clear')
			break
		else:
			accionarMenu(opc)


def mostrarMenu():
	""" Muestra un menu de opciones en pantalla """

	os.system('clear')
	print 	'\n',	"Por favor seleccione una opcion y presione Enter", '\n'
	print "1 - Recompilar todos los programas" 
	print "2 - Recompilar un programa en particular" 
	print "3 - Ejecutar todos los programas" 
	print "4 - Ejecutar un programa en particular" 
	print "5 - Salir"
	opcion = raw_input('\n Ingrese una opcion [1-5]:  ')	
	return opcion


def accionarMenu(opcion):
	""" Ejecuta distintas funciones segun la opcion elegida en el menu """

	print '\n'
	if opcion in "24": return {'2': compilar, '4': ejecutar}.get(opcion)(1)
	else: return {'1': compilar, '3': ejecutar}.get(opcion)()

	
def elegirInputs():
	"""Menu para elegir que archivo ejecutar """

	os.system('clear')
	archivos = os.listdir('./in') 	+ ['*.in']
	print "Archivos de prueba: ", '\n'

	for x in archivos:
		if x[-3:] != ".in": archivos.remove(x)

	archivos.sort()
	for i in range(len(archivos)):
		print str(i+1)+' - ', archivos[i]

	opcion = -1
	while opcion not in range(0,len(archivos)):
		opcion = int(raw_input('\n'"Ingrese el numero de archivo/s que desea ejecutar: [1-" + str(len(archivos)) + "]:  "))-1
	return " ../in/"+archivos[opcion]
	
		
def compilar(n=0):
	"""Compila los distintos ejercicios en la carpeta del Tp"""
			
	if n == 0: 	
		for x in "2345": os.system('cd ./ej'+x+'; make; cd ..')
		print "\n Todos los ejercicios fueron recompilados"
	
	elif n == 1:
		x = '0'
		while x not in "2345":
			x = raw_input("Indique el ejercicio que desea recompilar [2-5] : ")
		os.system('cd ./ej'+x+'; make; cd ..')
		print "\n El ejercicio %s fue recompilado"%(x)
	raw_input()
	

def ejecutar(n=0):
	"""Ejecuta los distintos ejercicios en la carpeta del Tp"""

	if n == 0: 	
		archivo = elegirInputs()
		for x in "2345": os.system('cd ej'+x+'; ./ej'+x + archivo + ' ; cd ..')
		print "\n Todos los ejercicios fueron ejecutados"

	elif n == 1:
		x = '0'
		while x not in "2345":
			x = raw_input("Indique el ejercicio que desea ejecutar [2-5]: ")
		archivo = elegirInputs()
		os.system('cd ej'+x+'; ./ej'+x + archivo + ' ; cd ..')
		print "\n El ejercicio %s fue ejecutado"%(x)
	raw_input()


if __name__ == '__main__' : main ()
