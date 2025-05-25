CFLAGS = -std=c++20 -Wall -g

evaluator:	main.o evaluator.o
	g++ main.o evaluator.o -o postfix $(CFLAGS)

main.o:	evaluator.h main.cpp
	g++ -c main.cpp $(CFLAGS)

evaluator.o:	evaluator.cpp evaluator.h 
	g++ -c evaluator.cpp $(CFLAGS)


clean:
	rm -f *.o postfix
