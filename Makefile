ODIR = obj
CPPDIR = src

FLAGS = -std=c++14 -fopenmp -Wall -MMD -pedantic -Wextra -W -O3 -I $(CPPDIR)
CPP = g++

ALL_CPP_FILES = $(wildcard $(CPPDIR)/*.cpp)
EXEC_CPP_FILES = src/main.cpp src/test.cpp
CPP_FILES = $(filter-out $(EXEC_CPP_FILES), $(ALL_CPP_FILES))

OBJ_FILES = $(addprefix $(ODIR)/,$(notdir $(CPP_FILES:.cpp=.o)))
ALL_OBJ_FILES = $(addprefix $(ODIR)/,$(notdir $(ALL_CPP_FILES:.cpp=.o)))

all: main.out test.out


main.out: $(OBJ_FILES) obj/main.o
	$(CPP) $(OBJ_FILES) obj/main.o -o main.out $(FLAGS) 

test.out: $(OBJ_FILES) obj/test.o
	$(CPP) $(OBJ_FILES) obj/test.o -o test.out $(FLAGS) -lboost_unit_test_framework 

$(ODIR)/%.o : $(CPPDIR)/%.cpp
	$(CPP) -c -o $@ $< $(FLAGS) 


.PHONY: clean

clean:
	rm -rf $(ODIR)/*.o *.out

-include $(ALL_OBJ_FILES:.o=.d)

