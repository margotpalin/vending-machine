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

backup:
	cp coins.dat coins.dat.backup

restore:
	cp coins.dat.backup coins.dat

test: backup all
	@echo "Running tests..."
	@./$(EXE) < testreq4.input > testreq4.actual_output; diff -w testreq4.actual_output testreq4.expected_output; diff -w -y testreq4.expected_coins coins.dat;
	@./$(EXE) < testreq5.input > testreq5.actual_output; diff -w testreq5.actual_output testreq5.expected_output; diff -w -y testreq5.expected_coins coins.dat;

	@$(MAKE) restore
	@./$(EXE) < testreq6.input > testreq6.actual_output; diff -w testreq6.actual_output testreq6.expected_output; diff -w -y testreq6.expected_coins coins.dat;
	@./$(EXE) < testreq7.input > testreq7.actual_output; diff -w testreq7.actual_output testreq7.expected_output; diff -w -y testreq7.expected_coins coins.dat;
	@./$(EXE) < testreq8.input > testreq8.actual_output; diff -w testreq8.actual_output testreq8.expected_output; diff -w -y testreq8.expected_coins coins.dat;
	@./$(EXE) < testreq9.input > testreq9.actual_output; diff -w testreq9.actual_output testreq9.expected_output; diff -w -y testreq9.expected_coins coins.dat;

.PHONY: all clean backup restore test
