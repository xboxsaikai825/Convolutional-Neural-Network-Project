#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

class Neuron {
public:
	// default constructer that sets the neuron equal to 0
	Neuron();

	// constructer that sets the value of the neuron
	Neuron(double);

	// function to enter a vector of values and weights and calculates the summation
	void set_value(vector<double>, vector<double>, double);

	// returns value of neuron
	double get_value() const;
private:
	double value;
	double weight;
};
#endif NEURON_H
