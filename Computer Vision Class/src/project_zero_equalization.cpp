#include <cv.h>
#include <highgui.h>

using namespace cv;

int main(int argc, char** argv) {
	Mat image, equalized;
	//Read image
	image = imread("Lenna.png", 1);

	// Convert to grayscale
	cvtColor(image, image, CV_BGR2GRAY);

	// Apply Histogram Equalization
	equalizeHist(image, equalized);

	//Write Results
	imwrite("Equalized.png", equalized);

	waitKey(0);

	return 0;
}
