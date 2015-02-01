#include <cv.h>
#include <highgui.h>
#include <stdlib.h> //rand, srand
#include <time.h>        time
#include <iostream>
#include "Dataset.cpp"
#include "Features.cpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat * orig_ds;
	Mat * noisy_5_ds;
	Mat * noisy_10_ds;
	Mat * noisy_25_ds;
	Mat * noisy_50_ds;
	Dataset db;
	orig_ds = db.CreateDS();
	noisy_5_ds = db.addNoise(orig_ds, 5);
	noisy_10_ds = db.addNoise(orig_ds, 10);
	noisy_25_ds = db.addNoise(orig_ds, 25);
	noisy_50_ds = db.addNoise(orig_ds, 50);

	Features s;
	s.dsFeatures(orig_ds);

	Mat image;

	/*	for (int i = 0; i < 1400;) {
	 resize(noisy_50_ds[i], image, Size(256, 256));
	 namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	 imshow("Display window", image);    // Show our image inside it.
	 waitKey(0);
	 i = i + 100;

	 }*/


}

