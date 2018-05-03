.PHONY: clean, mrproper
.SUFFIXES:

EXEC     = Fract3D
CXX      = g++
CXXFLAGS = -W -O3 -std=c++11
INCLUDE  = src
SRC      = $(wildcard src/*.cpp)
OBJ      = $(SRC:.cpp=.o)
LIBS     = -lboost_thread -lboost_system

# all
$(EXEC): $(OBJ)
	$(CXX) $(OBJ) $(LIBS) -o $(EXEC)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# clean
clean:
	rm -f $(OBJ)

# mrproper
mrproper: clean
	rm -rf $(EXEC)
