CC = g++

all: analytic_demo

analytic_demo: analytic_main.cpp
	$(CC) --std=c++11 analytic_main.cpp -o analytic_demo

clean:
	rm analytic_demo