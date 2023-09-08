CC = g++

all: analytic_demo

gen_demo: analytic_main.cpp
	$(CC) --std=c++11 analytic_main.cpp

clean:
	rm analytic_demo