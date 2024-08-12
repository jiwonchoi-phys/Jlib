CC = g++-13
CXXFLAGS = -std=c++17 -O3 -DPARALLEL -fopenmp
SRC_DIR = ./src
OBJ_DIR = ./obj
TARGET = main

SRCS = $(notdir $(wildcard $(SRC_DIR)/*.cpp))
OBJS = $(SRCS:.cpp=.o)
OBJECTS = $(patsubst %.o,$(OBJ_DIR)/%.o,$(OBJS))
DEPS = $(OBJECTS:.o=.d)


all: main

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

$(TARGET) : $(OBJECTS) 
	$(CC) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

.PHONY: clean all
clean:
	rm -f $(OBJECTS) $(DEPS) $(TARGET)

