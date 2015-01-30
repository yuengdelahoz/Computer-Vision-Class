/*

 * project_zero_thresholding.cpp
 *
 *  Created on: Jan 15, 2015
 *      Author: yuengdelahoz


#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>

using namespace cv;
using namespace std;

Mat Translate (Mat & image){
	int height, width;
	height = image.rows;
	width = image.cols;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			image.at<uchar>(i, j) = 0;
		}
	}
	return image;
}

int main(int argc, char** argv) {
	Mat image, dst;
	int height, width, th1, th2;
	uchar pixValue;
	string filename;

	if (argc == 3) {
		filename = argv[0];
		th1 = atoi(argv[1]);
		th2 = atoi(argv[2]);
	} else {
		th1 = 50;
		th2 = 175;
		filename = "src/Project Zero/Images/Lenna.png";
	}

	//Read image

	image = imread(filename, 1);

	// Convert to grayscale
	cvtColor(image, image, CV_BGR2GRAY);
	image = Translate (image);

	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Display window", image);                // Show our image inside it.

	// Wait for a keystroke in the window
	waitKey(0);
	return 0;
}

*/
