

CXX=g++

CXXFLAGS=-Wall -Wextra -O3 $(inc_params) -g
LDFLAGS=-lrt -lpthread


inc = $(wildcard td*/)
inc_params = $(foreach d, $(inc), -I$d)
src = $(wildcard */*.cc)
obj = $(src:.cc=.o)
product = $(td1_products) td2/thread td3/countdown td4/incr td6/active

all: td1 td2 td3 td4 td6

# td1
td1/qa: td1/qa.o td1/libtime.o
	$(LINK.cc) $^ -o $@
td1/qb: td1/qb.o td1/libtime.o
	$(LINK.cc) $^ -o $@
td1/qc: td1/qc.o td1/libtime.o
	$(LINK.cc) $^ -o $@
td1/qd: td1/qd.o td1/libtime.o
	$(LINK.cc) $^ -o $@
.PHONY: td1
td1_products = td1/qa td1/qb td1/qc td1/qd
td1: $(td1_products)

# td2
td2/thread: td2/thread.o td1/libtime.o
	$(LINK.cc) $^ -o $@
.PHONY: td2
td2: td2/thread


td3/countdown: td3/main.o td3/CountDown.o td3/PeriodicTimer.o td3/Timer.o  td1/libtime.o
	$(LINK.cc) $^ -o $@
.PHONY: td3
td3: td3/countdown

td4/incr: td4/main.o td4/Incrementer.o td4/PosixThread.o td4/Mutex.o td4/Thread.o td1/libtime.o
	$(LINK.cc) $^ -o $@
.PHONY: td4
td4: td4/incr

td6/active: td6/main.o td4/Fifo.o td4/Semaphore.o td4/PosixThread.o td4/Mutex.o td4/Thread.o td1/libtime.o td6/ActiveCalc.o td6/ActiveObject.o td6/Request.o td6/CrunchReq.o td6/Calculator.o
	$(LINK.cc) $^ -o $@
.PHONY: td6
td6: td6/active


.PHONY: clean
clean:
	echo $(inc_params)
	rm -f $(obj) $(product)