# Zmień nazwę pliku źródłowego na odpowiednią
SRC = main.cpp icmp_receive.cpp icmp_send.cpp
OBJ = $(patsubst %.cpp, build/%.o, $(SRC))
EXEC = build/traceroute  # Możesz zmienić nazwę wykonywalnego pliku

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
	rm -f build/*.o $(EXEC)

.PHONY: all clean
