#ifndef _NEURAL_NETWORK_H__
#define _NEURAL_NETWORK_H__

#include <iostream>
#include <vector>
#include "weights.h"
#include "Layer.h"
#include <string>
#include <list>

struct LayerEdge;
struct LayerNode;

struct LayerEdge //Struct for edges in graph.
{
  struct LayerNode* l; //Pointer to the LayerNode endpoint of the edge.

  LayerEdge()
  {
    l=NULL;
  }
};


struct LayerNode //Struct for each node in the graph representing a layer in the nerual network.
{
  Layer* layer; //Pointer to layer object which contains all the metadata.
  std::vector<LayerEdge> edges; //Output edges of the node.
  std::vector<LayerNode*> inputs; //Input edges of the node.
  bool visited;

  LayerNode()
  {
    layer=NULL;
    visited=false;
  }
  LayerNode& operator=(const LayerNode& a){
      // Copying edges:
      std::copy(a.edges.begin(), a.edges.end(), back_inserter(edges));
      visited= a.visited;
      layer = a.layer;
  }
};

class NeuralNetwork
{
  private:
  public:
    std::vector<LayerNode*> layers; //All layers in graph
    std::vector<LayerNode*> input; //Input layers for graph.

    std::vector<LayerNode*> nodes_ord; //Ordered list of nodes.
    std::vector<Weight*> weights; //Weights

    LayerNode* findNode(std::string ID); //Finds node in graph
    void DFS(LayerNode* start); //Call to recursive DFS

    int idx_n; //Current index for nodes_ord.
    int idx_w; //Current index for weights.

  public:
    NeuralNetwork(); //Constructor
    ~NeuralNetwork(); //Destructor

    void addLayer(Layer* layer); //Adds a layer
    void addEdge(Layer* start, Layer* end); //Adds an edge from start to end.

    void reset(); //Resets indices and visited boolean.
    void BFS(); //BFS traversal and builds ordered layer and weight vector
    void DFSPrint(); //Recursive DFS

    LayerNode* getNextNode(); //Returns next layer
    Weight* getNextWeight(); //Returns next weight
};

#endif