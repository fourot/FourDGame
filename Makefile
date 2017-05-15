
all: myvc02.exe

myvc02.exe: squarematrix.o myvc02.o
	g++ myvc02.o squarematrix.o -g -L/usr/local/lib -lfltk \
-lXfixes -lXext -lpthread -lX11 -lm -ldl -lX11 \
-lfltk_gl -lGL -lGLU -lglut -lfltk -lfltk_forms -lfltk_images -o myvc02.exe 

myvc02.o: myvc02.cpp
	g++ -c -g -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT myvc02.cpp

squarematrix.o: squarematrix.cpp
	g++ -c -g squarematrix.cpp

clean:
	rm myvc02.o myvc02.exe squarematrix.o


# g++ hellofltk1.cpp  -L/usr/local/lib -lfltk -lXfixes -lXext -lpthread -lX11 -lm -ldl -lX11 -o hellofltk1.exe


#all: hellofltk1.exe

#hellofltk1.exe: hellofltk1.o
#	g++ hellofltk1.o -L/usr/local/lib -lfltk -lXfixes -lXext -lpthread -lX11 -lm -ldl -lX11 -o hellofltk1.exe 

#hellocpp.o: hellofltk1.cpp
#	g++ -c hellofltk1.cpp
     
#clean:
#	rm hellofltk1.o hellofltk1.exe
