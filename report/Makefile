all: report.pdf

%.pdf : %.tex macros_TD.tex
		@pdflatex -shell-escape -interaction batchmode $<
		@pdflatex -shell-escape -interaction batchmode $<
		@echo $@ a été mis à jour

clean:
		rm -f *.aux *.log *.out *.pdf
