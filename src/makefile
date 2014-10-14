#CC = g++
CC = clang++
CFLAGS = -g -Wall
INCLUDES = -I../include
LFLAGS = -L../lib
LIBS = -lm
SRCS = nbody.cpp nbody_rk4.cpp integrate.cpp
OBJS = $(SRCS:.cpp=.o)
MAIN = integrate

.PHONY: depend clean

all : $(MAIN)

$(MAIN) : $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LIBS)

.cpp.o :
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean :
	rm *.o $(MAIN)
