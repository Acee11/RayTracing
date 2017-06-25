Flags = -std=c++14 -Wall -pedantic -Wextra -W -O2
CPP = g++
BIN = main
LINKS = -lsfml-graphics -lsfml-window -lsfml-system

$(BIN).out: $(BIN).o Vector3D.o Sphere.o Ray.o ArrayScene.o
	$(CPP) $(Flags) $(BIN).o Vector3D.o Sphere.o Ray.o ArrayScene.o -o $(BIN).out $(LINKS)
	
$(BIN).o: $(BIN).cpp
	$(CPP) $(Flags) -c $(BIN).cpp -o $(BIN).o

Vector3D.o: Vector3D.h Vector3D.cpp
	$(CPP) $(Flags) -c Vector3D.cpp -o Vector3D.o

Sphere.o: Sphere.h Sphere.cpp Primitive.h
	$(CPP) $(Flags) -c Sphere.cpp -o Sphere.o

Ray.o: Ray.h Ray.cpp
	$(CPP) $(Flags) -c Ray.cpp -o Ray.o

ArrayScene.o: ArrayScene.h ArrayScene.cpp Scene.h
	$(CPP) $(Flags) -c ArrayScene.cpp -o ArrayScene.o


clean:
	rm -rf *.o *.out


