tester: tester.o phase1.o phase2.o registerTable.o labelTable.o
	g++ tester.o phase1.o phase2.o registerTable.o labelTable.o -o tester
tester.o: tester.cpp
	g++ -c tester.cpp -o tester.o
phase1.o: phase1.cpp phase1.h
	g++ -c phase1.cpp -o phase1.o
phase2.o: phase2.cpp phase2.h
	g++ -c phase2.cpp -o phase2.o
registerTable.o: registerTable.cpp registerTable.h
	g++ -c registerTable.cpp -o registerTable.o
labelTable.o: labelTable.cpp labelTable.h
	g++ -c labelTable.cpp -o labelTable.o

.PHONY:clean

clean: 
	rm *.o tester