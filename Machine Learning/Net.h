#ifndef Net_H
#define Net_H

#include "Neuron.h"

int const NUM_LAYERS = 6;
int const PIXEL_LENGTH = 28;
int const PIXEL_WIDTH = 28;
int const WEIGHT_LENGTH = 5;
int const POOL_LENGTH = 2;

typedef vector<vector<Neuron>> Layer;

class Net {
public:
	// default constructer of the CNN architecture
	Net();

	// function to call convolution on the first layer only
	void convolution(int, int[PIXEL_LENGTH][PIXEL_WIDTH], int);

	// function to call convolution on a layer
	void convolution(int, int);

	// fucntion to do max pooling on a layer
	void max_pooling(int);

	Neuron find_greatest(vector<Neuron>);

	// print the layer 
	void print(int) const;

	// flatten the layer
	void flatten(int);

	// output layer
	void fully_connect(int);

	// makes the output values into percentages
	void softmax(int);

	// reLu function
	double relu(double);
private:
	vector<Layer> m_layers;
	double weights1[WEIGHT_LENGTH][WEIGHT_LENGTH];
	double weights2[WEIGHT_LENGTH][WEIGHT_LENGTH];
	double output_weights[160];
};
#endif Net_H
