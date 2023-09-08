#include "ipu_analytic.hpp"

void buildGraph(poplar::Graph &g, const utils::Options &options, graphSpecs &specs) {

  for (int i = 0; i < specs.num_tensors; i++) {
    specs.tensors.push_back( g.addVariable( specs.type[i], {get<0>(specs.dimensions[i]), get<1>(specs.dimensions[i])}, specs.debug_contexts[i]) )
    poplar::poputil::mapTensorLinearly(g, specs.tensors[i]);
  }

}