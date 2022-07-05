CC = gcc
LIBS = -lm -lGL -lGLU -lglut
OBJS = main.c obj_loader.c matrix.c
TARGET = gl

all: $(TARGET) 
	$(CC) $(OBJS) -o $(TARGET) $(LIBS) 

$(TARGET):
	$(CC) $(OBJS) -o $(TARGET) $(LIBS) 
	
clean:
	rm -f $(TARGET) 

run: 
	./$(TARGET)
