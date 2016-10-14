CC = g++
LIBS = -lGL -lglut -lGLU -lm 

SRC = model.cpp functions.cpp 
BIN = model

all	:	$(BIN)

$(BIN)	:	$(SRC) 
	$(CC) $(SRC) -o $(BIN) $(LIBS)

clean	:
	rm -f $(BIN) *~ *.aux *.log
