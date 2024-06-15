#include "Neuron.h"

Neuron::Neuron() {
	value = 0;
	weight = 0;
}

Neuron::Neuron(double input) {
	value = input;
}

void Neuron::set_value(vector<double> user_inputs, vector<double> user_weights, double user_bias) {

	// summation of inputs times the weight
	double sum = 0;
	for (int i = 0; i < user_inputs.size(); i++) {
		sum += user_inputs[i] * user_weights[i];
	}
	sum += user_bias;

	value = sum;
}

double Neuron::get_value() const {
	return value;
}