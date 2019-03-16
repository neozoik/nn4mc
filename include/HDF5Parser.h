#ifndef __HDF5_PARSER_H__
#define __HDF5_PARSER_H__

#include <iostream>
#include <string>
#include <map>
#include "NeuralNetwork.h"
#include <vector>
#include <sstream>
#include "LayerFactory.h"
#include <nlohmann/json.hpp>

#else
#include <iostream>
#endif
#include <string>
#include "datastructures/tensor.h"
#include <vector>

#ifndef H5_NO_NAMESPACE
#ifndef H5_NO_STD
    using std::cout;
    using std::cerr;
    using std::endl;
#endif  // H5_NO_STD
#endif

#include "H5Cpp.h"
#include "Parser.h"
#include <iomanip>
#include <sstream>
#include "LayerBuilder.h"
#ifndef H5_NO_NAMESPACE

using namespace H5;
using json=nlohmann::json;

#endif
struct opdata{
            std::map<std::string, LayerFactory *> BM;
            std::vector<LayerFactory*> lBV;
            std::vector<std::string> layer_ids;
            std::vector<std::pair<std::string, std::string>> layer_edges;
            };

struct opdataWeights{
        std::string layer_id;
        std::map<std::string, Weights> WM;
                    };


class HDF5Parser : public Parser{
    public: 
        int parse();
        NeuralNetwork NN;
        typedef std::map<std::string, LayerFactory*> builder_map;
        builder_map BuilderMap;
        std::vector<LayerFactory*> layerBuilderVector;
        std::vector<std::string> layer_ids; // layer_ids
        std::vector<std::pair<std::string, std::string>> layer_edges; // edge pairs
        std::map<std::string, Weights> weightsMap;
        json model_config;
        HDF5Parser(std::string file_name_str){
            this->file_name= file_name_str;
        }
        json parseModelConfig();
        //void parseNeuralNetworkArchitecture();
        void parseWeights();
        void constructBuilderMap();
        void callLayerBuilders();
        void buildEdges();
        void restructureLayerIds();
};


