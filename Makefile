# Variables
CXX = g++
CXXFLAGS = -Wall -std=c++17
TARGET = main
SRCDIR = src
BINDIR = bin

# Build target
$(BINDIR)/$(TARGET): $(SRCDIR)/main.cpp
	mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $< -o $@

# Run target
.PHONY: run
run: $(BINDIR)/$(TARGET)
	./$(BINDIR)/$(TARGET)

# Clean target
.PHONY: clean
clean:
	rm -f $(BINDIR)/$(TARGET)