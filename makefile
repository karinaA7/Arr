CC = gcc
CFLAGC = -Wall -Wextra
RM = rm -f
TARGET = arr

SRC = new.c main.c
OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGC) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(CFLAGC) $(OBJ) -o $(TARGET) 
	
all: $(TARGET)

clean: 
	$(RM) $(TARGET) $(OBJ)
	 
