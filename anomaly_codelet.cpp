#include <poplar/Vertex.hpp>

using namespace poplar;

class AnomalyVertex : public Vertex {
public:

Input<Vector<float>> mult_out;
Output<Vector<float>> result;
//add non-numbers
    bool compute(){
        float value;

        //anomaly_store;
    for (int i = 0; i < mult_out.size(); ++i) {
         
            value = mult_out[i];
            
            // Check if the value is between [x,y]
            if (value >= 7000.0 && value <= 13000.0) {
                result[i] = value;
            }
            else {
                result[i] = 0;
            }
        }
    return true;
}

};