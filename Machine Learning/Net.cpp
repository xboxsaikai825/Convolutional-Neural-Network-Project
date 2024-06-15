#include "Net.h"
#include "CImg.h"

Net::Net() {
	// creates approiate amount of layers
	for (int layer = 0; layer < NUM_LAYERS; layer++) {
		m_layers.push_back(Layer());
	}
}

void Net::convolution(int layer, int image[PIXEL_LENGTH][PIXEL_WIDTH], int bias) {

	// randomizes the values of the 5x5 kernal
	for (int r = 0; r < WEIGHT_LENGTH; r++) {
		for (int c = 0; c < WEIGHT_LENGTH; c++) {
			double random = ((double)rand() / (RAND_MAX));
			weights1[r][c] = random;
		}
	}

	// prints out the values of the kernal
	cout << "Weights" << endl;
	for (int r = 0; r < WEIGHT_LENGTH; r++) {
		for (int c = 0; c < WEIGHT_LENGTH; c++) {
			cout << weights1[r][c] << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "Convolution Layer: " << endl;
	// convolution function
	double sum = 0;
	for (int image_row = 0; image_row <= PIXEL_LENGTH - WEIGHT_LENGTH; image_row++) {
		vector<Neuron> row;
		for (int image_col = 0; image_col <= PIXEL_WIDTH - WEIGHT_LENGTH; image_col++) {
			double sum = 0;
			// dot products the weight 2d vector with the according image
			for (int weight_row = 0; weight_row < WEIGHT_LENGTH; weight_row++) {
				for (int weight_col = 0; weight_col < WEIGHT_LENGTH; weight_col++) {
					double image_value = image[image_row + weight_row][image_col + weight_col];
					double weight_value = weights1[weight_row][weight_col];
					sum += image_value * weight_value + bias;
				}
			}
			row.push_back(Neuron(relu(sum)));
		}
		m_layers[layer].push_back(row);
	}
}
void Net::convolution(int layer, int bias) {

	// randomizes the values of the 5x5 kernal
	srand(time(0));
	for (int r = 0; r < WEIGHT_LENGTH; r++) {
		for (int c = 0; c < WEIGHT_LENGTH; c++) {
			double random = ((double)rand() / (RAND_MAX));
			weights2[r][c] = random;
		}
	}

	// prints out the values of the kernal
	cout << endl << "Weights" << endl;
	for (int r = 0; r < WEIGHT_LENGTH; r++) {
		for (int c = 0; c < WEIGHT_LENGTH; c++) {
			cout << weights2[r][c] << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "Convolution Layer: " << endl;
	// convolution function
	double sum = 0;
	for (int layer_row = 0; layer_row <= m_layers[layer - 1].size() - WEIGHT_LENGTH; layer_row++) {
		vector<Neuron> row;
		for (int layer_col = 0; layer_col <= m_layers[layer - 1][0].size() - WEIGHT_LENGTH; layer_col++) {
			double sum = 0;
			// dot products the weight 2d vector with the according image
			for (int weight_row = 0; weight_row < WEIGHT_LENGTH; weight_row++) {
				for (int weight_col = 0; weight_col < WEIGHT_LENGTH; weight_col++) {
					double image_value = m_layers[layer - 1][layer_row + weight_row][layer_col + weight_col].get_value();
					double weight_value = weights2[weight_row][weight_col];
					sum += image_value * weight_value + bias;
				}
			}
			row.push_back(Neuron(relu(sum)));
		}
		m_layers[layer].push_back(row);
	}
}


void Net::print(int layer) const {
	for (int r = 0; r < m_layers[layer].size(); r++) {
		for (int c = 0; c < m_layers[layer][0].size(); c++) {
			cout << m_layers[layer][r][c].get_value() << " ";
		}
		cout << endl;
	}
}

double Net::relu(double input) {
	if (input <= 0) {
		return 0;
	}
	if (input > 0) {
		return input;
	}
}

void Net::max_pooling(int layer) {
	cout << endl << "Max Pooling Layer: " << endl;
	for (int layer_row = 0; layer_row < m_layers[layer - 1].size(); layer_row += 2) {
		vector<Neuron> row;
		for (int layer_col = 0; layer_col < m_layers[layer - 1][0].size(); layer_col += 2) {
			vector<Neuron> list;
			list.push_back(m_layers[layer - 1][layer_row][layer_col]);
			list.push_back(m_layers[layer - 1][layer_row][layer_col + 1]);
			list.push_back(m_layers[layer - 1][layer_row + 1][layer_col]);
			list.push_back(m_layers[layer - 1][layer_row + 1][layer_col + 1]);
			row.push_back(find_greatest(list));
		}
		m_layers[layer].push_back(row);
	}
}

void Net::flatten(int layer) {
	cout << endl << "Flattend Layer: " << endl;
	vector<Neuron> row;
	for (int r = 0; r < m_layers[layer - 1].size(); r++) {
		for (int c = 0; c < m_layers[layer - 1][0].size(); c++) {
			Neuron element = Neuron(m_layers[layer - 1][r][c]);
			row.push_back(element);
		}
	}
	m_layers[layer].push_back(row);
}

Neuron Net::find_greatest(vector<Neuron> list) {
	Neuron highest = list[0];
	for (int i = 0; i < list.size(); i++) {
		if (list[i].get_value() > highest.get_value()) {
			highest = list[i];
		}
	}
	return highest;
}

void Net::fully_connect(int layer) {
	cout << endl << "Fully Connected Layer: " << endl;
	double sum = 0;
	for (int i = 0; i < 160; i++) {
		double random = ((double)rand() / (RAND_MAX));
		output_weights[i] = random;
	}
	int count = 0;
	vector<Neuron> row;
	for (int num = 0; num <= 9; num++) {
		sum = 0;
		for (int r = 0; r < m_layers[layer - 1][0].size(); r++) {
			sum += m_layers[layer - 1][0][r].get_value() * output_weights[count];
			count++;
		}
		row.push_back(Neuron(relu(sum)));
	}
	m_layers[layer].push_back(row);
}

void Net::softmax(int layer) {
	int sum = 0;
	cout << endl << "Relative Percentages: " << endl;
	for (int i = 0; i < m_layers[layer][0].size(); i++) {
		sum += abs(m_layers[layer][0][i].get_value());
	}
	for (int i = 0; i < m_layers[layer][0].size(); i++) {
		cout << i << ": " << abs(m_layers[layer][0][i].get_value()) / sum << endl;
	}
}

