

CXX=g++

CXXFLAGS=-Wall -Wextra -O3 $(inc_params)
LDFLAGS=-lrt -lpthread

LINK.o=$(LINK.cc)

inc = $(wildcard td*/)
inc_params = $(foreach d, $(inc), -I$d)
src = $(wildcard */*.cc)
obj = $(src:.cc=.o)
product = td1/timer td2/thread td3/countdown

all: td1 td2 td3

# td1
td1/timer: td1/timer.o td1/libtime.o
.PHONY: td1
td1: td1/timer

# td2
td2/thread: td2/thread.o td1/libtime.o
.PHONY: td2
td2: td2/thread


td3/countdown: td3/main.o td3/CountDown.o td3/PeriodicTimer.o td3/Timer.o  td1/libtime.o
.PHONY: td3
td3: td3/countdown

.PHONY: clean
clean:
	echo $(inc_params)
	rm -f $(obj) $(product)