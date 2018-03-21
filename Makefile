all:
	make tromino floyd obst

obst:
	g++ obst.cpp -o obst.out -g -std=c++11

tromino:
	g++ tromino.cpp -o tromino.out -g -std=c++11

floyd:
	g++ floyd.cpp -o floyd.out -g -std=c++11

debug_tromino:
	gdb tromino.out

debug_obst:
	gdb obst.out

debug_floyd:
	gdb floyd.out

clean:
	rm -f *out