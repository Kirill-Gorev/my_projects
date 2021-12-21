CFLAGS =  -O2 -ftrapv -fsanitize=undefined -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op -Wmissing-field-initializers -Wcast-qual -Wwrite-strings

all: table socket clean_comp




table.o: Table.c Table.h
	gcc -c Table.c

dbms.o: dbms.cpp dbms.hpp table.o
	g++ $(CFLAGS) -c dbms.cpp

socket.o: sock_wrap.cpp sock_wrap.hpp
	g++ $(CFLAGS) -c sock_wrap.cpp

table: table.o dbms.o
	g++ $(CFLAGS) test_table.cpp Table.o dbms.o

socket: socket.o
	g++ $(CFLAGS) main1.cpp sock_wrap.o

clean:
	-rm -rf *.o
	-rm -rf *.dSYM
	-rm -rf *.out
	
clean_comp:
	-rm -rf *.dSYM
	-rm -rf *.out

test: 
	g++ $(FLAGS) main.cpp sock_wrap.cpp -g
	g++ $(FLAGS) main1.cpp sock_wrap.cpp -o b.out -g
	-./a.out & ./b.out
	-rm -rf file_socket.*
	g++ $(FLAGS) test_table.cpp dbms.cpp Table.o -o c.out -g
	-./c.out
	
