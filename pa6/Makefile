CXX = g++
CFLAGS = -std=c++11 -Wall

# Directories
SRCDIR = src
OBJDIR = obj
BINDIR = bin
INCDIR = include

all: directories $(TARGET)

TARGET = $(BINDIR)/pa6

# Source files
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

all: $(TARGET)
# Run the program
run:
	cd bin && ./pa6

$(TARGET): $(OBJS)
	$(CXX) $(CFLAGS) $(INCLUDES) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@

directories:
	mkdir -p $(OBJDIR) $(BINDIR)
	
# Clean rule to remove object files and the target executable
clean:
	rm -f $(OBJS) $(TARGET)
	rmdir $(OBJDIR) $(BINDIR) 2>/dev/null || true




