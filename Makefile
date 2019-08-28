TARGET = ./fdo
LIB_DIR = ./

ROOTCFLAGS := $(shell root-config --cflags)
ROOTGLIBS := $(shell root-config --glibs)
CXXFLAGS   = -w $(ROOTCFLAGS)
CXXLIBS    = $(ROOTGLIBS)

SRC_C = $(wildcard *.cc )
OBJ_C = $(SRC_C:.cc=.o)
OBJS   = $(OBJ_C)

all: $(TARGET)
$(TARGET): $(OBJS)
	g++ -std=c++11 -o $@ $(addprefix $(LIB_DIR)/,$(OBJS)) $(CXXLIBS)
.cc.o:
	g++  -I ../ $(CXXFLAGS) -c $< -o $(LIB_DIR)/$@
clean:
	rm -f $(TARGET) $(addprefix $(LIB_DIR)/,$(OBJS))
cleanall:
	rm -f $(TARGET) $(OBJS) *~
