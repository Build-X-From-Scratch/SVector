CXX = clang++
CXXFLAGS = -Wall -O2 -std=c++20
BINDIR = binary_excetuble

# Pastikan folder output ada
$(BINDIR):
	mkdir -p $(BINDIR)

# Target utama
program: $(BINDIR)/imp.o | $(BINDIR)
	$(CXX) $(CXXFLAGS) $(BINDIR)/imp.o -o $(BINDIR)/program

# Compile implementation.cpp jadi object file
$(BINDIR)/imp.o: implementation/implementation.cpp | $(BINDIR)
	$(CXX) $(CXXFLAGS) -c implementation/implementation.cpp -o $(BINDIR)/imp.o

# Bersihin file object & binary
.PHONY: clean
clean:
	rm -rf $(BINDIR)