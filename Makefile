CC = g++

all: analytic_demo fe_demo

analytic_demo: utils.h analytic_main.cpp
	$(CC) --std=c++11 analytic_main.cpp ipu_analytic.cpp ipu_gen3.cpp utils.cpp -o analytic_demo -lpoplar -lpoputil -lpoplin -lpoprand -lboost_program_options

fe_demo: fe_dummy.cpp
	$(CC) --std=c++11 fe_dummy.cpp -o fe_demo

clean:
	rm analytic_demo

