SRC = main_mw.cpp functions.cpp
OBJ = $(patsubst %.cpp, build/%.o, $(SRC))
EXEC = transport

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

all: $(EXEC)

$(EXEC): $(OBJ)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJ)

build/%.o: %.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build output $(EXEC)

.PHONY: all clean
