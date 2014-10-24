CCFLAGS = -Wno-deprecated
UNAME_S := $(shell uname -s)
TARGET = Assgn
CPPS = source/*.cpp

ifeq ($(UNAME_S),Linux)
    CCFLAGS += -lglut -lGLU -lGL
endif
ifeq ($(UNAME_S),Darwin)
    CCFLAGS += -framework GLUT -framework OpenGL
endif

test: $(CPPS)
	g++ $(CCFLAGS) $(CPPS) -o $(TARGET)
	./$(TARGET)
clean:
	rm source/*.o $(TARGET); clear
