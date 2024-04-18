CXX = g++
CXXFLAGS = -O3 -W -Wall -ansi -pedantic -std=c++11
LDFLAGS = -lSDL -lSDLmain

SRC = $(wildcard dev/*.cpp) lib/quickcg.cpp
OBJDIR = obj
BINDIR = bin

# Ajout des fichiers .hpp dans les dépendances
DEPS = $(wildcard inc/*.hpp)

OBJ = $(addprefix $(OBJDIR)/, $(notdir $(SRC:.cpp=.o)))
TARGET = $(BINDIR)/prog

all: build run

build: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BINDIR)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Ajout des fichiers .hpp comme dépendances
$(OBJDIR)/%.o: dev/%.cpp $(DEPS)
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/quickcg.o: lib/quickcg.cpp $(DEPS)
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJDIR) $(BINDIR)

re: clean all

.PHONY: all clean
