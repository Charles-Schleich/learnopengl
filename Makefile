CC = g++
OBJ = main.o src/glad.o src/stb_image.o
HEADER = include/ 
CFLAGS = -std=c++17 -c -Wall -Iinclude 
LIBS = -L./lib -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl


program: $(OBJ) 
	$(CC) $(OBJ) -o $@ $(LIBS)

main.o: main.cpp src/stb_image.c src/glad.c  $(HEADER)
	$(CC) $(CFLAGS) $< -o $@ 

clean: 
	rm -rf *o program

run: 
	./program
