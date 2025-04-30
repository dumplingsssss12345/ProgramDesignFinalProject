SOURCE := $(wildcard *.c)
EXCLUDE_LIB_SRC = ../shooter_monster.c ../passiveselect.c ../weaponselect.c
SOURCE_LIB_SRC = $(wildcard ../*.c)

LIB_SRC = $(filter-out $(EXCLUDE_LIB_SRC), $(SOURCE_LIB_SRC));

TARGETS = $(SOURCES:.c=)

CC = gcc
CFLAGS = -I../*.h -lraylib -LGL -lm -lpthread -ldl -lrt -lX11

all: $(TARGETS)
	$(CC) $(CFLAGS) $< -o $@  $(LIB_SRC)
$(TARGET): %: %.o $(LIB_SRC:.c=.o)
	$(CC) -o $@ $^ $(LIB_SRC)
%.o: %.c
	$(CC) $(CFLAGS) $@ $^ $(LIB_SRC)

clean:
	rm -f *.o $(TARGETS) $(LIB_SRC:.c=.o)
 
