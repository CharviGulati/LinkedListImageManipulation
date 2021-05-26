EXEMAIN = pa1
OBJS  = main.o PNG.o HSLAPixel.o lodepng.o gridlist.o gridlist_given.o block.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpthread -lm

all : pa1

$(EXEMAIN) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXEMAIN)

main.o : main.cpp gridlist.h cs221util/PNG.h cs221util/HSLAPixel.h block.h
	$(CXX) $(CXXFLAGS) main.cpp

gridlist.o : gridlist.cpp gridlist.h block.h
	$(CXX) $(CXXFLAGS) gridlist.cpp

gridlist_given.o : gridlist_given.cpp gridlist.h block.h
	$(CXX) $(CXXFLAGS) gridlist_given.cpp

block.o : block.cpp block.h cs221util/PNG.h cs221util/HSLAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) block.cpp

PNG.o : cs221util/PNG.cpp cs221util/PNG.h cs221util/HSLAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/PNG.cpp

HSLAPixel.o : cs221util/HSLAPixel.cpp cs221util/HSLAPixel.h
	$(CXX) $(CXXFLAGS) cs221util/HSLAPixel.cpp

lodepng.o : cs221util/lodepng/lodepng.cpp cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/lodepng/lodepng.cpp

clean :
	-rm -f *.o $(EXEMAIN)