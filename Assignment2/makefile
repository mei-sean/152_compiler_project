scanner: scanner.o source.o
    g++ scanner.o source.o -o scanner

scanner.o: scanner.cpp
    g++ -c scanner.cpp

source.o: source.cpp
    g++ -c source.cpp

clean:
    rm *.o scanner