/*

 * Feature.cpp
 *
 *  Created on: Jan 30, 2015
 *      Author: yuengdelahoz

 */
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <fstream>
#include <string>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "Stack.cpp"
#include <cv.h>

using namespace cv;
using namespace std;

class Features {

public:
	void getFeatures() {
		iterateOverData();
	}

	void dsFeatures(Mat *ds) {
		int cnt = 0;
		double area;
		for (int i = 0; i < 1400; i++) {
			Mat img = ds[i];
			int size = imageSize(img);
			int cc = connectedComponents(img);
			int h = Holes(img);
			cout << "Image size: " << size << endl;
			cout << "Connected components: " << cc << endl;
			cout << "Holes: " << h << endl;
			area = area + attribute(img);
			if (cnt = 100) {
				area = area/100;
				cout << "Avg. Area: "<<area<< endl;
				cnt =0;
				cin.get();
			}
			cnt++;

			/*			if (cc == 1 && h == 0) {
			 Mat dst = attribute(img);
			 Mat image;

			 namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
			 imshow("Display window", dst);
			 waitKey(0);
			 }*/

		}

	}

private:
	void iterateOverData() {

		string dir, filepath;
		DIR *dp;
		struct dirent *dirp;
		struct stat filestat;
		Mat image, src;

		dir = "src/Project One/data";
		dp = opendir(dir.c_str());
		if (dp == NULL) {
			cout << "Error(" << errno << ") opening " << dir << endl;
		}

		while ((dirp = readdir(dp))) {
			filepath = dir + "/" + dirp->d_name;

			// If the file is a directory (or is in some way invalid) we'll skip it
			if (stat(filepath.c_str(), &filestat))
				continue;
			if (S_ISDIR(filestat.st_mode))
				continue;

			cout << filepath << endl;
			src = imread(filepath, CV_8UC1);
			//src = imread("src/Project One/data/three.pgm", CV_8UC1);
			cout << "Image size: " << imageSize(src) << endl;
			image = attribute(src);
			//resize(src, image, Size(256, 256));
			namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
			imshow("Display window", image);
			waitKey(0);

			/*			resize(src, image, Size(256, 256));
			 namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
			 imshow("Display window", image);    // Show our image inside it.
			 waitKey(0);*/

		}
		closedir(dp);

	}

	int connectedComponents(Mat img) {
		Pixel *** pixImage = addImagetoStack(img);
		int connectComponents = 0;

		for (int i = 0; i < 25; ++i) {   // for each row
			for (int j = 0; j < 25; ++j) { // for each column
				Pixel *pix = pixImage[i][j];

				if (pix->pixValue == 0 && !pix->visited) { // if pixel is black and not visited
					Stack pixStack(pix);
					pix->inStack = true;
					int componentSize = 0;
					/*				cout << "Node ( " << pix->x << "," << pix->y << ")-->"
					 << endl;
					 cout << "(i,j)" << "(" << i << "," << j << ")" << endl;*/

					while (!pixStack.isEmpty()) {
						//spixStack.Print();
						Pixel *curPix = pixStack.pop();

						if (curPix->pixValue == 0 && !curPix->visited) {
							/*							cout << "Just popped (x,y)-->" << "(" << curPix->x
							 << "," << curPix->y << ")" << endl;*/

							//Set current pixel as visited
							curPix->visited = true;
							componentSize++;
							int x, y;

							// bottom neighbor
							x = curPix->x + 1;
							y = curPix->y;

							// if inside image
							if (x < 25) {
								Pixel *bNeighbor = pixImage[x][y];
								// if bottom neighbor is black and not visited
								if (bNeighbor->pixValue == 0
										&& !bNeighbor->visited) {
									if (!bNeighbor->inStack) {
										pixStack.insert(bNeighbor);
										bNeighbor->inStack = true;
										/*cout << "bottom" << endl;
										 cout << "Inserted " << "(" << x << ","
										 << y << ")" << endl;*/

									}

								}

							}
							// top neighbor
							x = curPix->x - 1;
							y = curPix->y;
							// if inside image
							if (x >= 0) {
								Pixel *tNeighbor = pixImage[x][y];
								// if right neighbor is black and not visited
								if (tNeighbor->pixValue == 0
										&& !tNeighbor->visited) {
									if (!tNeighbor->inStack) {
										tNeighbor->inStack = true;
										pixStack.insert(tNeighbor);
										/*cout << "top" << endl;
										 cout << "Inserted " << "(" << x << ","
										 << y << ")" << endl;*/
									}

								}

							}

							// left neighbor
							x = curPix->x;
							y = curPix->y - 1;
							// if inside image
							if (y >= 0) {
								Pixel *lNeighbor = pixImage[x][y];
								// if left neighbor is black and not visited
								if (lNeighbor->pixValue == 0
										&& !lNeighbor->visited) {
									if (!lNeighbor->inStack) {
										lNeighbor->inStack = true;
										pixStack.insert(lNeighbor);
										/*	cout << "left" << endl;
										 cout << "Inserted " << "(" << x << ","
										 << y << ")" << endl;*/
									}

								}

							}

							// right neighbor
							x = curPix->x;
							y = curPix->y + 1;
							// if inside image
							if (y < 25) {
								Pixel *rNeighbor = pixImage[x][y];
								// if right neighbor is black and not visited
								if (rNeighbor->pixValue == 0
										&& !rNeighbor->visited) {
									if (!rNeighbor->inStack) {
										rNeighbor->inStack = true;
										pixStack.insert(rNeighbor);
										/*		cout << "right" << endl;
										 cout << "Inserted " << "(" << x << ","
										 << y << ")" << endl;*/
									}

								}

							}

						}
					}
					if (componentSize >= 5) {
						connectComponents++;
						cout << "Component Size ***************** "
								<< componentSize << endl;
					}

				}
			}
		}
		return connectComponents;
	}

	int Holes(Mat img) {
		Mat src;
		int holesCount = 0;
		// findcontours takes image with background black
		bitwise_not(img, src);
		resize(src, src, Size(256, 256));

		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;

		findContours(src.clone(), contours, hierarchy, CV_RETR_CCOMP,
				CV_CHAIN_APPROX_NONE);
		/*for (vector<Vec4i>::size_type idx = 0; idx < hierarchy.size(); ++idx) {
		 for (int i = 0; i < 4; i++) {
		 cout << hierarchy[idx][i] << " ";
		 }
		 cout << endl;
		 }*/
		//cout << "Hierarchy size : "<< hierarchy.size()<<endl;
		if (hierarchy.size() == 1) {
			holesCount = 0;
		} else {
			int c = 0;
			for (vector<Vec4i>::size_type idx = 0; idx < hierarchy.size();
					++idx) {
				if (hierarchy[idx][3] != -1)
					c++;

			}
			if (c == 0)
				holesCount = 0;
			else if (c == 1)
				holesCount = 1;
			else if (c == 2)
				holesCount = 2;

		}

		return holesCount;

	}

	double attribute(Mat img) {
		Mat src;
		// findcontours takes image with background black
		bitwise_not(img, src);
		resize(src, src, Size(512, 512));

		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;
		double area = 0;

		Mat singleLevelHoles = Mat::zeros(src.size(), src.type());

		findContours(src.clone(), contours, hierarchy, CV_RETR_LIST,
				CV_CHAIN_APPROX_NONE);
		for (vector<Vec4i>::size_type idx = 0; idx < hierarchy.size(); ++idx) {
			drawContours(singleLevelHoles, contours, idx, Scalar::all(255),
			CV_FILLED, 8, hierarchy);
		}
		RNG rng(12345);

		Mat drawing = Mat::zeros(src.size(), CV_8UC3);
		for (int i = 0; i < contours.size(); i++) {
			area = area + contourArea(contours[i], false);

			double p = arcLength(contours[i], true);
			Point2f center;
			float radius;

			minEnclosingCircle(contours[i], center, radius);

			Mat hull;
			convexHull(contours[i], hull);
			double hull_area = contourArea(hull, false);
			double solidity = area / hull_area;

			/*	cout << "Contour[" << i << "] " << "Area: " << a << endl;
			 cout << "Contour[" << i << "] " << "Perimeter: " << p << endl;
			 cout << "Contour[" << i << "] " << "Minimum Enclosing radius: "
			 << radius << endl;
			 cout << "Contour[" << i << "] " << "Solidity: " << solidity << endl;*/

			Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255),
					rng.uniform(0, 255));
			drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0,
					Point());
		}
		//cout << "Contours: " << contours.size() << endl;

		return area;
	}

	Pixel*** addImagetoStack(Mat img) {
		Pixel ***pixels;
		pixels = new Pixel**[25];
		for (int i = 0; i < 25; i++) {
			pixels[i] = new Pixel*[25];
		}

		for (int i = 0; i < 25; ++i) {   // for each row
			for (int j = 0; j < 25; ++j) { // for each column
				Pixel *pix = new Pixel(i, j);
				pix->pixValue = img.at<uchar>(i, j);
				pixels[i][j] = pix;
			}
		}
		return pixels;
	}

	int imageSize(Mat img) {
		int count = 0;
		for (int i = 0; i < 25; ++i) {   // for each row
			for (int j = 0; j < 25; ++j) {
				if (img.at<uchar>(i, j) == 0)
					count++;
			}
		}
		return count;
	}

	void imageIteration(Mat img) {
		Pixel *** pixImage = addImagetoStack(img);
		for (int i = 0; i < 25; ++i) {   // for each row
			for (int j = 0; j < 25; ++j) { // for each column
				Pixel *pix = pixImage[i][j];
				if (pix->pixValue == 255)
					cout << "1-";
				else
					cout << pix->pixValue << "-";

			}
			cout << endl;
		}
	}
};

