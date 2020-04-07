

CXX=g++

CXXFLAGS=-Wall -Wextra -O3 $(inc_params) -g
LDFLAGS=-lrt -lpthread


inc = $(wildcard td*/)
inc_params = $(foreach d, $(inc), -I$d)
src = $(wildcard */*.cc)
objs = $(src:.cc=.o)
products = $(td1_products) $(td2_products) $(td3_products) $(td4_products) $(td6_products)

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
td2/qa: td2/qa.o td1/libtime.o
	$(LINK.cc) $^ -o $@
td2/qb: td2/qb.o td1/libtime.o
	$(LINK.cc) $^ -o $@
td2/qc: td2/qc.o td1/libtime.o
	$(LINK.cc) $^ -o $@
.PHONY: td2
td2_products = td2/qa td2/qb td2/qc
td2: $(td2_products)


td3/qa: td3/qa.o td3/Chrono.o  td1/libtime.o
	$(LINK.cc) $^ -o $@
td3/qb: td3/qb.o td3/CountDown.o td3/PeriodicTimer.o td3/Timer.o  td1/libtime.o
	$(LINK.cc) $^ -o $@
td3/qc: td3/qc.o td3/Calibrator.o td3/Looper.o td3/CpuLoop.o td3/PeriodicTimer.o td3/Timer.o  td1/libtime.o
	$(LINK.cc) $^ -o $@
.PHONY: td3
td3_products = td3/qa td3/qb td3/qc
td3: $(td3_products)

td4/qa: td4/qa.o td4/Incrementer.o td4/PosixThread.o td4/Mutex.o td4/Thread.o td1/libtime.o
	$(LINK.cc) $^ -o $@
td4/qb: td4/qb.o td4/Incrementer.o td4/PosixThread.o td4/Mutex.o td4/Thread.o td1/libtime.o
	$(LINK.cc) $^ -o $@
td4/qc: td4/qc.o td4/Producer.o td4/Consumer.o td4/Semaphore.o td4/PosixThread.o td4/Mutex.o td4/Thread.o td1/libtime.o
	$(LINK.cc) $^ -o $@
td4/qd: td4/qd.o td4/FifoProducer.o td4/FifoConsumer.o td4/PosixThread.o td4/Mutex.o td4/Thread.o td1/libtime.o
	$(LINK.cc) $^ -o $@
.PHONY: td4
td4_products = td4/qa td4/qb td4/qc td4/qd
td4: $(td4_products)

td6/active: td6/main.o td4/Semaphore.o td4/PosixThread.o td4/Mutex.o td4/Thread.o td1/libtime.o td6/ActiveCalc.o td6/ActiveObject.o td6/Request.o td6/CrunchReq.o td6/Calculator.o
	$(LINK.cc) $^ -o $@
.PHONY: 
td6_products = td6/active
td6: $(td6_products)


.PHONY: clean
clean:
	echo $(inc_params)
	rm -f $(objs) $(products)