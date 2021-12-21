COMPILER=g++
FLAGS=-std=c++14 -g -ftrapv -fsanitize=undefined -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op -Wmissing-field-initializers -Wcast-qual -Wwrite-strings -lm -L.

all: main

try:
	-clear
	-rm main1
	$(COMPILER) $(FLAGS) matrix.cpp matrix.hpp main1.cpp -g -o main1
	./main

main: matrix.o main1.o
	$(COMPILER) $(FLAGS) matrix.o main1.o -g -o main1


main1.o: main1.cpp
	g++ -c main1.cpp

matrix.o: matrix.cpp matrix.hpp
	g++ -c matrix.cpp matrix.hpp


test:
	-rm main1
	$(COMPILER) $(FLAGS) matrix.cpp matrix.hpp main1.cpp -g
	-./a.out
	$(COMPILER) $(FLAGS) matrix.cpp matrix.hpp main2.cpp -g
	-./a.out
	-rm a.out
	-rm -rf *.o
	-rm *.hpp.gch
	-rm -rf *.dSYM


clean:
	-rm
	-rm main1
	-rm a.out
	-rm -rf *.o
	-rm *.hpp.gch
	-rm -rf *.dSYM
	-clear
