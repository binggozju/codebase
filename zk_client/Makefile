APP = zkcli

INCLUDES = -I/usr/local/include -I/usr/include -I/usr/local/include/zookeeper
LIBS = -L/usr/local/lib -L/usr/lib

CC = gcc
CXX = g++
CTAGS = ctags
CFLAGS = -g -Wall -O0 -c -DTHREADED $(INCLUDES) 
LDFLAGS = -lzookeeper_mt $(LIBS)

SRCDIR = .
SRCS = $(wildcard $(SRCDIR)/*.cpp)
HEADS = $(addsuffix .h, $(basename $(SRCS)))
OBJS = $(addsuffix .o, $(basename $(SRCS)))
#HEADS = $(patsubst %.cpp, %.h, $(wildcard $(SRCDIR)/*.cpp))
#OBJS = $(patsubst %.cpp, %.o, $(SRCS))

all: $(APP)

$(APP): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CFLAGS) -o $@ $<

clean:
	rm -rf *.o $(APP)

show:
	@echo $(SRCS)
	@echo "------------------------------------"
	@echo $(OBJS)
	@echo "------------------------------------"
	@echo $(HEADS)
