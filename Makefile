.PHONY: clean

flags = -O3 -g -Wall --std=c++17

tester: tester.o
	g++ $(flags) -o $@ $^

%.o: %.cpp
	g++ $(flags) -c -o $@ $^

clean:
	rm tester *.o