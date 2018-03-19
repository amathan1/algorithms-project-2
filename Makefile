all:
	make tromino floyd obst

obst:
	g++ obst.cpp -o obst.out -g -std=c++11

tromino:
	g++ tromino.cpp -o tromino.out -g -std=c++11

floyd:
	g++ floyd.cpp -o floyd.out -g -std=c++11

clean:
	rm -f *out