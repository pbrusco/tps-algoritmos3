all: Informe_Tp3.pdf clean

Informe_Tp3.pdf: Informe_Tp3.tex Ejercicio*.tex  Anexos.tex ./otros/*
	(pdflatex Informe_Tp3.tex; pdflatex Informe_Tp3.tex); (reset; echo 'PDF COMPILADO!')
        
clean:
	rm -f *.vrb *.nav *.snm *.out *.toc *.aux *.idx *.log *~
