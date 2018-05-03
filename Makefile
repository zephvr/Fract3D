.PHONY: clean, mrproper
.SUFFIXES:

EXEC     = Fract3D
CXX      = g++
CXXFLAGS = -Wall -O3 -std=c++11
SRCDIR   = src
INCDIR   = src
OBJDIR   = obj
LIBS     = -lboost_thread -lboost_system

SRC      = $(shell find $(SRCDIR) -type f -name *.cpp)
OBJ      = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SRC:.cpp=.o))

# all
$(EXEC): $(OBJ)
	$(CXX) $(OBJ) $(LIBS) -o $(EXEC)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# clean
clean:
	rm -rf $(OBJDIR)

# mrproper
mrproper: clean
	rm -rf $(EXEC)
