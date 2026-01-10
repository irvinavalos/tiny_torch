CXX = clang++
CXXFLAGS = -std=c++23 -Wall -Werror -Wextra -g

PROG = prog

$(PROG):
	$(CXX) $(CXXFLAGS) main.cpp -o $(PROG)

run:
	./$(PROG)

clean:
	rm $(PROG)
