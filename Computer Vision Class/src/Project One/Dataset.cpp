/*
 * Dataset.cpp
 *
 *  Created on: Jan 27, 2015
 *      Author: yuengdelahoz
 */

#include <fstream>
#include <iostream>
#include <string>

#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdlib.h> //rand, srand

using namespace cv;
using namespace std;

class Dataset {
	int k;

public:
	Mat* CreateDS() {

		string dir, filepath;
		DIR *dp;
		struct dirent *dirp;
		struct stat filestat;
		Mat image, src;
		static Mat ds[1400];

		dir = "src/Project One/data";
		dp = opendir(dir.c_str());
		if (dp == NULL) {
			cout << "Error(" << errno << ") opening " << dir << endl;
		}
		k = 0;
		while ((dirp = readdir(dp))) {
			filepath = dir + "/" + dirp->d_name;

			// If the file is a directory (or is in some way invalid) we'll skip it
			if (stat(filepath.c_str(), &filestat))
				continue;
			if (S_ISDIR( filestat.st_mode ))
				continue;

			cout << filepath << endl;
			src = imread(filepath, CV_8UC1);

			for (int i = 0; i < 100; i++) {
				ds[k] = Translate(src);
				++k;

			}

		}
		closedir(dp);
		return ds;

	}

	Mat* addNoise(Mat ds[], double NoisePercentage) {
		int pixels_with_noise = (NoisePercentage / 100) * (25 * 25);
		//cout << "Pixels with noise :" << pixels_with_noise << endl;
		int x, y;
		Mat *NoisyDS= new Mat[1400];

		for (int i = 0; i < 1400; i++) {
			Mat noisyImage;
			ds[i].copyTo(noisyImage);
			bool visited[25][25];
			for (int q = 0; q < 25; q++)
				for (int w = 0; w < 25; w++) {
					visited[q][w] = false;
				}

			for (int j = 0; j < pixels_with_noise; j++) {
				do {
					x = rand() % 25;
					srand(k++);
					y = rand() % 25;
				} while (visited[x][y] == true);

				int pix1 = noisyImage.at<uchar>(x, y);

				if (pix1 == 0)
					noisyImage.at<uchar>(x, y) = 255;
				else
					noisyImage.at<uchar>(x, y) = 0;
				visited[x][y] = true;
			}
			NoisyDS[i] = noisyImage;


		}
		return NoisyDS;
	}
private:

	Mat Translate(Mat image) {
		int height, width;
		int top, left;
		bool tflag = false;
		top = 0;
		left = 25;

		height = image.rows;
		width = image.cols;
		int pixValue;

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				pixValue = image.at<uchar>(i, j);
				if (pixValue == 0) {
					if (!tflag) {
						top = i;
						tflag = true;
					}

					if (j < left)
						left = j;
				}

			}
		}
		// Find the maximun vertical and horizontal shift taking into account images original size is 25x25
		int maxVerticalShift = 25 - (top + 11);
		int maxHorizontalShift = 25 - (left + 8);

		/*cout << " Top " << top << "\n" << "Left " << left << endl;
		 cout << maxVerticalShift << " - " << maxHorizontalShift << endl;*/

		Mat dst = Mat::ones(height, width, image.type()) * 255;
		int shiftv = rand() % maxVerticalShift;
		int shifth = rand() % maxHorizontalShift;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (image.at<uchar>(i, j) == 0) {

					dst.at<uchar>(i + shiftv, j + shifth) = image.at<uchar>(i,
							j);
				}

			}
		}
		return dst;
	}

};

