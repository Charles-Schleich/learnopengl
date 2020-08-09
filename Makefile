CC = g++
OBJ = main.o glad.o stb_image.o
HEADER = include/ 
CFLAGS = -std=c++17 -c -Wall -Iinclude 
LIBS = -L./lib -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl


program: $(OBJ) 
	$(CC) $(OBJ) -o $@ $(LIBS)

main.o: main.cpp stb_image.c glad.c  $(HEADER)
	$(CC) $(CFLAGS) $< -o $@ 

clean: 
	rm -rf *o program

run: 
	./program
