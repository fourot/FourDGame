
all: myvc02.exe
obj: myvc02.o squarematrix.o

myvc02.exe: squarematrix.o myvc02.o
	g++ myvc02.o squarematrix.o -g -L/usr/local/lib \
 -lfltk_gl -lGLU -lGL \
 -lfltk  -lXrender -lXfixes -lXext \
 -lXft -lfontconfig -lXinerama -lpthread -ldl -lm -lX11 \
 -o myvc02.exe

myvc02.o: myvc02.cpp
	g++ -c -g -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT myvc02.cpp

squarematrix.o: squarematrix.cpp
	g++ -c -g squarematrix.cpp

clean:
	rm myvc02.o myvc02.exe squarematrix.o
