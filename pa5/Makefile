CC := g++
CFLAGS := -std=c++11
BLD := ./build
SRC := ./src

SRCDIR = src
OBJDIR=obj
BINDIR=bin
#INCDIR=include

# Sources and objects
SOURCES=$(SRCDIR)/Robot.cpp $(SRCDIR)/Grid.cpp $(SRCDIR)/Humanic.cpp $(SRCDIR)/Roomba.cpp $(SRCDIR)/Robocop.cpp $(SRCDIR)/Bulldozer.cpp $(SRCDIR)/Optimusprime.cpp #$(SRCDIR)/main.cpp
OBJECTS=$(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

# Targets
TARGET=$(BINDIR)/pa5


$(TARGET): main.cpp $(OBJECTS)  
 #$(OBJDIR)/main.o $(OBJECTS)
	$(CC) $(CFLAGS)  $^ -o $@
	
#$(OBJDIR)/main.o: main.cpp 
#	$(CC) $(CFLAGS) -c $< -o $@
		
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@
	
# Run the program	
run: 
	cd bin && ./pa5

# Clean rule
clean:
	rm -f $(OBJECTS) $(OBJDIR)/main.o $(TARGET)


