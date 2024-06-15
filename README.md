# CNN Project

This program creates the structure of a convolutional neural network. The architecture was based off of the LeNet-5 CNN architecture, where it contains five layers with three hidden layers. The input of the network is a 28x28 image of a digit from MNIST and outputs a guess from zero to nine. Back propogation hasn't been implemented into the program, so it cannot perform machine learning with training data.

## How It's Made:

**Tech used:** C++

The neural network was implemented through classes, with one class holding all of the layers and one class for each neuron. Convolution and pooling are performed on the layer by the network, where all of the neurons are fully connected in the last layer. Convolution was performed with a 5x5 kernal and relu as the activation function. Max pooling was used in order to focus on essential features of the image, such as the circle of an eight.

## Lessons Learned:

The hardest part of this project was implementing a convolutional neural network from scratch. This forced me to learn how the entire neural network worked and their purpose. My biggest take away from this project was learning how machine learning worked and its complexity.



