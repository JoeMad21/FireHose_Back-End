#include "ipu_analytic.hpp"

enum Progs {
  WRITE_INPUTS,
  CONSUMPTION_TASK,
  READ_RESULTS,
  NUM_PROGRAMS
};

class GraphTensors {
  
    private:
        int num_tensors;

        std::vector<poplar::Tensor> tensors;
        std::vector< std::tuple<unsigned int, unsigned int> > dimensions;
        std::vector<poplar::Type> tensor_types;
        std::vector<std::string> tensor_dbs;
  
    public:
        GraphTensors (poplar::Graph &g) {
    
            this->num_tensors = 2;

            this->tensor_dbs.push_back("Streamed Matrix (Multiplicand)");
           
            this->tensor_dbs.push_back("Output Matrix (Result)");

            for (int i = 0; i < num_tensors; i++) {
                this->dimensions.push_back(std::tuple<int,int>{5,5});
                this->tensor_types.push_back(poplar::FLOAT);
        
                this->tensors.push_back( g.addVariable( 
                    this->tensor_types[i],
                    {std::get<0>(this->dimensions[i]), std::get<1>(this->dimensions[i])},
                    this->tensor_dbs[i] ) );
                poputil::mapTensorLinearly(g, tensors[i]);
            }
        }

        void addTensor (poplar::Graph &g, std::string tensor_db, poplar::Type tensor_type, long unsigned int dim1, long unsigned int dim2) {
            this->num_tensors++;

            this->tensor_dbs.push_back(tensor_db);

            this->tensors.push_back( g.addVariable( 
                    tensor_type,
                    {dim1, dim2},
                    tensor_db ) );
        }

        poplar::Tensor getTensor(int index) {
            return this->tensors[index];
        }
};

class GraphStreams {

  private:
    int num_streams;

    std::vector<poplar::DataStream> strms;
    std::vector<std::string> strm_srcs;
    std::vector<std::string> strm_dests;
    std::vector<std::string> strm_dbs;
    std::vector<poplar::Type> strm_types;
    std::vector<int> strm_lengths;
    std::vector<bool> strm_dirs; // 0 = CPU to IPU, 1 = IPU to CPU

  public:
    GraphStreams(poplar::Graph &g) {
      this->num_streams = 2;
      
      this->strm_dbs.push_back("Source_Stream");
      this->strm_srcs.push_back("CPU");
      this->strm_dests.push_back("IPU");
      this->strm_lengths.push_back(25);
      this->strm_types.push_back(poplar::FLOAT);
      this->strm_dirs.push_back(0);
      this->strms.push_back( g.addHostToDeviceFIFO(strm_dbs[0], strm_types[0], strm_lengths[0]) );

      this->strm_dbs.push_back("Read_Result_Stream");
      this->strm_srcs.push_back("IPU");
      this->strm_dests.push_back("CPU");
      this->strm_lengths.push_back(25);
      this->strm_types.push_back(poplar::FLOAT);
      this->strm_dirs.push_back(1);
      this->strms.push_back( g.addDeviceToHostFIFO(strm_dbs[1], strm_types[1], strm_lengths[1]) );
    }

    void addHostToDeviceStream(poplar::Graph &g, std::string strm_db, int strm_length, poplar::Type strm_type ) {
        this->num_streams++;

        this->strm_srcs.push_back("CPU");
        this->strm_dests.push_back("IPU");
        this->strm_lengths.push_back(strm_length);
        this->strm_types.push_back(strm_type);
        this->strm_dirs.push_back(0);
        this->strms.push_back( g.addHostToDeviceFIFO(strm_db, strm_type, strm_length) );
    }

    void addDeviceToHostStrean(poplar::Graph &g, std::string strm_db, int strm_length, poplar::Type strm_type ) {
        this->num_streams++;

        this->strm_srcs.push_back("IPU");
        this->strm_dests.push_back("CPU");
        this->strm_lengths.push_back(strm_length);
        this->strm_types.push_back(strm_type);
        this->strm_dirs.push_back(1);
        this->strms.push_back( g.addDeviceToHostFIFO(strm_db, strm_type, strm_length) );
    }

    poplar::DataStream getStream(int index) {
        return this->strms[index];
    }

};

void printMatrix_gen(std::string matrix_name, std::vector<float> matrix, int matrix_dim) {
  std::cout << matrix_name << std::endl;

  for (int i = 0; i < matrix.size(); i++) {

    std::cout << std::fixed << matrix[i] << "\t";
    
    if ( (i+1)%matrix_dim == 0 && i != 0) {
      std::cout << std::endl;
    }

  }

  std::cout << std::endl;

}
//send multiplicand to the analytic
std::vector<float> mult_matrix(long unsigned int dim) {
  std::vector<float> multiplicand(dim*dim);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> distribution(0.0f, 100.0f);
  
  for (int i = 0; i < dim*dim; i++) {
              multiplicand[i] = distribution(gen);
      }

      return multiplicand;
}

