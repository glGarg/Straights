CXX = g++-5 -std=c++14
CXXFLAGS = -Wall -O -g -MMD  # use -MMD to generate dependencies
LIBFLAGS = 
GTKFLAGS = `pkg-config gtkmm-3.0 --cflags --libs`
GSTFLAGS = `pkg-config gstreamer-1.0 --cflags --libs`
SOURCES = $(wildcard *.cc)   # list of all .cc files in the current directory
OBJECTS = ${SOURCES:.cc=.o}  # .o files depend upon .cc files with same names
DEPENDS = ${OBJECTS:.o=.d}   # .d file is list of dependencies for corresponding .cc file
EXEC=straights

# First target in the makefile is the default target.
# Note that the LIBFLAGS must come last in the command
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)  $(LIBFLAGS) $(GTKFLAGS) $(GSTFLAGS)

%.o: %.cc 
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(LIBFLAGS) $(GTKFLAGS) $(GSTFLAGS)

-include ${DEPENDS}

.PHONY: clean
clean:
	rm  -f $(OBJECTS) $(DEPENDS) $(EXEC)
