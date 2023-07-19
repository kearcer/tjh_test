EXTENSION=cpp
CC=g++
EXE=main
SUBDIR=src
OBJ = ./obj

CXXFLAGS += -I /home/code/tjh_code/tjh_test/test19-testing-cpluplus-new/inc
TARGET = /home/code/tjh_code/tjh_test/test19-testing-cpluplus-new/obj/main

CXX_SOURCES =$(foreach dir,$(SUBDIR), $(wildcard $(dir)/*$(EXTENSION)))
CXX_OBJECTS=$(patsubst  %.$(EXTENSION), ${OBJ}/%.o, $(notdir $(CXX_SOURCES)))

all:prebuild $(TARGET)
prebuild:

# $(EXE): $(CXX_OBJECTS)
# 	$(CC)  $(CXX_OBJECTS) -o $(EXE)

${OBJ}/%.o: ${SUBDIR}/%.$(EXTENSION)
	$(CC)  -Wall -L/lib -lpthread -g -c $(CXXFLAGS)  $<  -o  $@

$(TARGET): $(CXX_OBJECTS)
	$(CC)  -Wall -L/lib -lpthread -Wall -g -o $(TARGET) $(CXX_OBJECTS)

%.o:%.cpp
	$(CC) -DDEBUG -Wall -g -fPIC $(CXXFLAGS) -o $@ -c $<

clean:
	rm  -rf  $(CXX_OBJECTS) $(TARGET)

   
