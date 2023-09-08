#pragma once

#include <vector>
#include <random>

#include <poputil/TileMapping.hpp>
#include <poplin/codelets.hpp>
#include <poplin/MatMul.hpp>

struct graphSpecs {
  int num_tensors;
  int num_ipus;
  int num_streams;

  std::vector<int> assigned_ipu;

  std::vector<poplar::Tensor> tensors;
  std::vector<tuple <unsigned int, unsigned int>> dimensions;
  std::vector<poplar::type> tensor_types;
  std::vector<std::string> tensor_dbs;

  std::vector<poplar::DataStream> streams;
  std::vector<std::string> strm_srcs;
  std::vector<std::string> strm_dests;
  std::vector<std::string> stream_dbs;
  std::vector<poplar::type> stream_types;
  std::vector<int> stream_lengths;
  std::vector<bool> stream_dirs; // 0 = CPU to IPU, 1 = IPU to CPU
  //std::vector<poplar::DataStreamType> stream_types;
  
  //std::vector<> mapping;
}

void buildGraph(poplar::Graph &g, const utils::Options &options, graphSpecs &specs);