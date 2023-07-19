# CC:=g++
# SRC_DIRS=../src
# SRC=$(foreach TMP_SRC_DIRS, $(SRC_DIRS), $(wildcard $(TMP_SRC_DIRS)/*.cpp)) 
# OBJ:= $(SRC:.cpp=.o)
# TARGET=/home/tjh/hdr_video_fmt_convert/TSparser/src/ts_headerparser
# INCLUDE= -I/home/tjh/hdr_video_fmt_convert/TSparser/inc


# all:prebuild $(TARGET)
# prebuild:

# $(TARGET):$(OBJ)
# 	$(CC)  -Wall -g -o $(TARGET) $(OBJ);

# %.o:%.cpp
# 	$(CC) -DDEBUG -Wall -g -fPIC $(INCLUDE) -o $@ -c $<
	
# .PHONY:clean
# clean:
# 	-rm -f $(TARGET) $(OBJ)
 
EXTENSION=cpp
CC=g++
EXE=main
SUBDIR=src
OBJ = ./obj

CXXFLAGS += -I /home/code/tjh_code/tjh_test/test35_Using_A_Stack_Reversing_A_ARRAY/inc
TARGET = /home/code/tjh_code/tjh_test/test35_Using_A_Stack_Reversing_A_ARRAY/obj/main

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

   
