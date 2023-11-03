#pragma once

//#include <cstdlib>
#include <vector>
#include <random>
//#include <iomanip>
#include "utils.h"
//#include <iostream>
#include <unistd.h>
#include <tuple>

//#include <poplar/type.hpp>

#include <poputil/TileMapping.hpp>

#include <poplin/codelets.hpp>
#include <poplin/MatMul.hpp>

#include <poprand/codelets.hpp>
#include <poprand/RandomGen.hpp>


std::vector<poplar::program::Program> buildGraphAndPrograms(poplar::Graph &g, const utils::Options &options, long unsigned int dim);

std::vector<float> mult_matrix(long unsigned int dim);

void executeGraphProgram(poplar::Device &device, poplar::Executable &exe, const utils::Options &options, long unsigned int dim);

void launchOnIPU(long unsigned matrix_dim, int argc, char **argv);

void result_gen(long unsigned int matrix_dim, int argc, char **argv);
