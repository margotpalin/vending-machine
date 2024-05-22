CXX = g++
CXXFLAGS = -Wall -Werror -std=c++14 -O0
EXE = ftt
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -rf $(EXE) *.o *.dSYM

test: all
	@echo "Running tests..."
	@./$(EXE) < testreq4.input > output4; diff output4 testreq4.expected_output
	@./$(EXE) < testreq5.input > output5; diff output5 testreq5.expected_output
	@./$(EXE) < testreq6.input > output6; diff output6 testreq6.expected_output
	@./$(EXE) < testreq7.input > output7; diff output7 testreq7.expected_output
	@./$(EXE) < testreq8.input > output8; diff output8 testreq8.expected_output
	@./$(EXE) < testreq9.input > output9; diff output9 testreq9.expected_output

.PHONY: all clean test
