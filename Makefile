
all: fourot
obj: myvc02.o squarematrix.o

fourot: squarematrix.o myvc02.o
	g++ myvc02.o squarematrix.o -g -L/usr/local/lib \
 -lhpdf \
 -lfltk_gl -lGLU -lGL \
 -lfltk  -lXrender -lXfixes -lXext \
 -lXft -lfontconfig -lXinerama -lpthread -ldl -lm -lX11 \
 -o fourot

myvc02.o: myvc02.cpp trackball.h
	g++ -c -g -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT    -I/~Downloads/libharu-libharu-d84867e  myvc02.cpp

squarematrix.o: squarematrix.cpp squarematrix.h
	g++ -c -g squarematrix.cpp

clean:
	rm myvc02.o fourot squarematrix.o
