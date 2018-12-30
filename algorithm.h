#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <sstream>

using namespace std;


/*Structs*/

//struct for pairs of nodes
typedef struct nn1{
	int cost;
	int prevNode;
}pairsNode;

//struct for bucketItems Dial
typedef struct nn2{
	int node;
	int prevNode;
}bucketNode;

/*Vars*/

//vector with topology
vector < vector < int > > topology;

//vector with result
vector < pairsNode > solution;

//vector S 
//vector of nodes with path assign
vector<int> S;

//vector non S
//vector of nodes without path assign
vector<int> nonS;

//amoung of nodes
int nNodes;
//for Dial weight
int maxWeight;

//node select for algorithm
int sourceNode;

/*Function*/

//read file and set up vars
int readFiles();
void writeFile();

//set the vars with the initial values
void initValue();
//dijkstra
void dijkstra();
//help for dijkstra recalculation path
void dijkstra_recalDist();
//dial
void dial();
