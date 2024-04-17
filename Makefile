CXX = g++
CXXFLAGS = -O3 -W -Wall -ansi -pedantic
LDFLAGS = -lSDL -lSDLmain

SRC = $(wildcard dev/*.cpp) lib/quickcg.cpp
OBJDIR = obj
BINDIR = bin

OBJ = $(addprefix $(OBJDIR)/, $(notdir $(SRC:.cpp=.o)))
TARGET = $(BINDIR)/prog

all: build run

build: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BINDIR)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: dev/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/quickcg.o: lib/quickcg.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJDIR) $(BINDIR)

re: clean all

.PHONY: all clean
