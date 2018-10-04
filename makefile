CC    = g++

FLAGS = -std=c++14 -g -pedantic -Wall -pedantic

normal:
	$(CC) $(FLAGS) matris.cpp -o matris.out
	./matris.out

valgrind:
	  $(CC) $(FLAGS) matris.cpp -o matris.out
		valgrind --tool=memcheck --track-origins=yes --leak-check=yes ./matris.out

test:
		/mnt/c/cxxtest/cxxtestgen.py --error-printer -o simple_testrunner.cpp simple.cxxtest.cpp
		g++ -std=c++14 -g -Wall -c matris.cpp -o matris.out
		g++ -std=c++14 -o simple_test.out -I /mnt/c/cxxtest/ simple_testrunner.cpp matris.out
		./simple_test.out
gdb:
		$(CC) $(FLAGS) matris.cpp -o matris.out
		gdb matris.out


clean:
	rm -f *.o *.out
