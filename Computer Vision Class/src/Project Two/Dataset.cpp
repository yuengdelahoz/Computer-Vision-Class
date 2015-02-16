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
		static Mat ds[10];

		dir = "src/Project Two/input_images";
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
			ds[k] = src;
			k++;
			if (k==10) break;

		}
		closedir(dp);
		return ds;

	}

	Mat* addNoise(Mat ds[], int sigma) {

		Mat *NoisyDS= new Mat[10];

		for (int i = 0; i < 10; i++) {
			Mat img = ds[i].clone();
			Mat noise(img.size(), img.type());
			randn(noise, 0, sigma);
			img += noise;
			NoisyDS[i]=img;



		}
		return NoisyDS;
	}
private:



};

