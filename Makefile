# Name of the executable file
TARGET := game

# Tool chain arguments
CXXFLAGS := -Wall -Wextra
LDLIBS := -lncurses

# Project sources
SOURCE_FILES := $(shell find -name '*.cpp')
OBJECT_FILES := $(patsubst %.cpp, %.o, $(SOURCE_FILES))

# The dependency file names
DEPS := $(OBJECT_FILES:.o=.d)

# Create the executable file
$(TARGET): $(OBJECT_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECT_FILES) $(LDLIBS)

# Let make read the dependency files and handle them
-include $(DEPS)

# Generate object files
%.o: %.cpp
	$(CXX)  $(CXXFLAGS) -MMD -MP -c $< -o $@

.PHONY: all rebuild clean

all: $(TARGET)

rebuild: clean all

clean:
	$(RM) $(OBJECT_FILES) $(DEPS) $(TARGET)
