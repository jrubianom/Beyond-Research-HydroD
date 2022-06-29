all: plot.pdf

%.x : %.cpp EngineRigidBody.cpp EngineRigidBody.h
	g++ -o3 $^ -o $@

datos.txt : Test.x
	./$< > $@

plot.pdf : plot.gp datos.txt
	gnuplot $<
	xpdf $@

q.x : quaternions.cpp
	g++ -o3 quaternions.cpp -o q.x

datos2.txt : q.x
	./q.x > datos2.txt

plot2.pdf: plot2.gp datos2.txt
	gnuplot $<
	xpdf $@

.PHONY: clean
clean:
	rm -f *.x *.txt *.pdf
