CXX = clang++
CXXFLAGS = -Wall -O2

# Target utama
program: imp.o
	$(CXX) $(CXXFLAGS) imp.o -o program

# Compile implementation.cpp jadi object file
imp.o: implementation/implementation.cpp
	$(CXX) $(CXXFLAGS) -c implementation/implementation.cpp -o imp.o

# Bersihin file object & binary
clean:
	rm -f *.o program
