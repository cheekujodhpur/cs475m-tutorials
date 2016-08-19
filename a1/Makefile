BIN = mydraw 
GLLIBS = -lGL -lGLU -lglut
G = g++ -std=c++11

.SUFFIXES: .cpp .hpp

all: $(BIN)

clean:
	rm -f $(BIN)
	rm -f *.o
	rm -f *~

mydraw: clean
	$(G) mydraw_class.cpp mydraw.cpp -o $@ $(GLLIBS)

debug: clean
	$(G) -g mydraw_class.cpp mydraw.cpp -o $@ $(GLLIBS)

