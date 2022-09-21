parser: parser.o symboltable.o scanner.o source.o
	g++ parser.o symboltable.o scanner.o source.o -o parser
parser.o: parser.cpp
	g++ -c parser.cpp parser.h node.h
symboltable.o: symboltable.cpp
	g++ -c symboltable.cpp symboltable.h
scanner.o: scanner.cpp
	g++ -c scanner.cpp scanner.h
source.o: source.cpp
	g++ -c source.cpp
node.o: node.h
	g++ -c node.h
clean:
	rm *.o parser