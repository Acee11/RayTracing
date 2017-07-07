Flags = -std=c++14 -Wall -pedantic -Wextra -W -O2
CPP = g++
BIN = main


$(BIN).out: $(BIN).o Vector3D.h Sphere.o Ray.o ArrayScene.o 
	$(CPP) $(Flags) $(BIN).o Sphere.o Ray.o ArrayScene.o -o $(BIN).out

$(BIN).o: $(BIN).cpp
	$(CPP) $(Flags) -c $(BIN).cpp -o $(BIN).o

test.out: test.o Vector3D.h Sphere.o Ray.o ArrayScene.o
	$(CPP) $(Flags) test.o Sphere.o Ray.o ArrayScene.o -o test.out

test.o: test.cpp
	$(CPP) $(Flags) -c test.cpp -o test.o
	

Sphere.o: Sphere.h Sphere.cpp Primitive.h
	$(CPP) $(Flags) -c Sphere.cpp -o Sphere.o

Ray.o: Ray.h Ray.cpp
	$(CPP) $(Flags) -c Ray.cpp -o Ray.o

ArrayScene.o: ArrayScene.h ArrayScene.cpp Scene.h
	$(CPP) $(Flags) -c ArrayScene.cpp -o ArrayScene.o


clean:
	rm -rf *.o *.out


