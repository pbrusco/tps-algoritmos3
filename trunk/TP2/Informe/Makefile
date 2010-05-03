all: Informe_Tp2.pdf clean

Informe_Tp2.pdf: Informe_Tp2.tex Ejercicio*.tex  ./otros/*
	(pdflatex Informe_Tp2.tex; pdflatex Informe_Tp2.tex); (reset; echo 'PDF COMPILADO!')
        
clean:
	rm -f *.vrb *.nav *.snm *.out *.toc *.aux *.idx *.log *~
