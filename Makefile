CXX = clang++
CXXFLAGS = -std=c++23 -Wall -Werror -Wextra -g

PROG = prog

$(PROG):
	$(CXX) $(CXXFLAGS) ./src/main.cpp ./src/matrix.cpp -o $(PROG)

run:
	./$(PROG)

clean:
	rm $(PROG)
