#include "CImg.h"
#include "Net.h"

using namespace cimg_library;

int main() {
	int img[28][28];
	CImg<float> image("61.jpg");

	// get width, height, number of channels
	int w = image.width();
	int h = image.height();
	int c = image.spectrum();
	cout << "Dimensions: " << w << "x" << h << " " << c << " channels" << endl;

	// dump all pixels
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			img[y][x] = (int)image(x, y);
		}
	}
	
	Net test = Net();
	for (int r = 0; r < PIXEL_LENGTH; r++) {
		for (int c = 0; c < PIXEL_WIDTH; c++) {
			if (img[r][c] > 0)
				cout << "1 ";
			else
				cout << "0 ";
		}
		cout << endl;
	}
	

	
	
	cout << endl;
	test.convolution(0, img, 0);
	test.print(0);
	test.max_pooling(1);
	test.print(1);
	test.convolution(2, 0);
	test.print(2);
	test.max_pooling(3);
	test.print(3);
	test.flatten(4);
	test.print(4);
	test.fully_connect(5);
	test.print(5);
	test.softmax(5);
}

