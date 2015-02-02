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

	int** dsClassify(Mat *ds) {
		int ** confusionMatrix;
		confusionMatrix = new int*[14];

		for (int i = 0; i < 14; ++i) {
			confusionMatrix[i] = new int[14];
			// each i-th pointer is now pointing to dynamic array (size 10) of actual int values
		}

		for (int i = 0; i < 14; i++)
			for (int j = 0; j < 14; j++)
				confusionMatrix[i][j] = 0;
		for (int i = 0; i < 1400; i++) {
			Mat img = ds[i];
			int size = imageSize(img);
			int cc;
			cc = connectedComponents(img);

			int h = Holes(img);

			vector<vector<Point> > contours;
			vector<Vec4i> hierarchy;
			Mat img1;
			bitwise_not(img, img1);
			resize(img1, img1, Size(512, 512));

			findContours(img1.clone(), contours, hierarchy, CV_RETR_TREE,
					CV_CHAIN_APPROX_NONE);

			int dsc = i / 100;
			int mx, my;
			switch (dsc) {
			case 0:
				mx = 0;
				break;
			case 1:
				mx = 1;
				break;
			case 2:
				mx = 2;
				break;
			case 3:
				mx = 3;
				break;
			case 4:
				mx = 4;
				break;
			case 5:
				mx = 5;
				break;
			case 6:
				mx = 6;
				break;
			case 7:
				mx = 7;
				break;
			case 8:
				mx = 8;
				break;
			case 9:
				mx = 9;
				break;
			case 10:
				mx = 10;
				break;
			case 11:
				mx = 11;
				break;
			case 12:
				mx = 12;
				break;
			case 13:
				mx = 13;
				break;
			}

			if (cc == 4) {
				my = 0;
				confusionMatrix[mx][my]++;
				continue;
			} else if (cc == 1) {
				if (h == 0) {
					double a = contourArea(contours[0], false);

					double p = arcLength(contours[0], true);

					Mat hull;
					convexHull(contours[0], hull);
					double hull_area = contourArea(hull, false);
					double contour_solidity = a / hull_area;

					double contour_perimeter = p;
					if (size < 25) {
						if (contour_perimeter < 900) {
							my = 2;
							confusionMatrix[mx][my]++;
							continue;

						} else {
							my = 7;
							confusionMatrix[mx][my]++;
							continue;
						}
					} else {
						if (contour_solidity > 0.80) {
							my = 1;
							confusionMatrix[mx][my]++;
							continue;
						} else {
							if (contour_solidity < 0.65) {
								my = 5;
								confusionMatrix[mx][my]++;
								continue;
							} else {
								if (contour_perimeter < 900) {
									my = 4;
									confusionMatrix[mx][my]++;
									continue;
								} else {
									my = 3;
									confusionMatrix[mx][my]++;
									continue;
								}

							}

						}

					}

				}
				if (h == 1) {
					double hole_area = contourArea(contours[1], false);
					if (hole_area < 4340) {
						my = 6;
						confusionMatrix[mx][my]++;
						continue;

					} else if (hole_area > 4340) {
						my = 9;
						confusionMatrix[mx][my]++;
						continue;
					}

				} else if (h == 2) {
					my = 8;
					confusionMatrix[mx][my]++;
					continue;

				}
			} else {
				if (size == 24) {
					my = 13;
					confusionMatrix[mx][my]++;
					continue;
				} else if (size == 26) {
					my = 12;
					confusionMatrix[mx][my]++;
					continue;
				} else {

					vector<vector<Point> > contours;
					vector<Vec4i> hierarchy;
					Mat img1;
					bitwise_not(img, img1);

					findContours(img1.clone(), contours, hierarchy,
							CV_RETR_TREE, CV_CHAIN_APPROX_NONE);

					RNG rng(12345);
					Mat drawing = Mat::zeros(img1.size(), CV_8UC3);
					vector<RotatedRect> minRect(contours.size());

					for (int i = 0; i < contours.size(); i++) {

						minRect[i] = minAreaRect(contours[i]);

					}
					if (minRect[0].angle < 0) {
						my = 10;
						confusionMatrix[mx][my]++;
						continue;
					} else {
						my = 11;
						confusionMatrix[mx][my]++;
						continue;
					}

				}
			}
		}
		return confusionMatrix;

		/*else {

		 int ** confusionMatrix;
		 confusionMatrix = new int*[14];
		 for (int i = 0; i < 14; ++i) {
		 confusionMatrix[i] = new int[14];
		 // each i-th pointer is now pointing to dynamic array (size 10) of actual int values
		 }

		 for (int i = 0; i < 14; i++) {
		 for (int j = 0; j < 14; j++) {
		 confusionMatrix[i][j] = 0;
		 }

		 }

		 for (int i = 0; i < 1400; i++) {
		 Mat img = ds[i];
		 int size = imageSize(img);
		 int cc;
		 cc = connectedComponents(img);
		 int h = Holes(img);
		 double *att;
		 att = attribute(img);

		 int dsc = i / 100;
		 int mx, my;
		 switch (dsc) {
		 case 0:
		 mx = 0;
		 break;
		 case 1:
		 mx = 1;
		 break;
		 case 2:
		 mx = 2;
		 break;
		 case 3:
		 mx = 3;
		 break;
		 case 4:
		 mx = 4;
		 break;
		 case 5:
		 mx = 5;
		 break;
		 case 6:
		 mx = 6;
		 break;
		 case 7:
		 mx = 7;
		 break;
		 case 8:
		 mx = 8;
		 break;
		 case 9:
		 mx = 9;
		 break;
		 case 10:
		 mx = 10;
		 break;
		 case 11:
		 mx = 11;
		 break;
		 case 12:
		 mx = 12;
		 break;
		 case 13:
		 mx = 13;
		 break;
		 }
		 double contour_solidity = att[9];
		 if (cc == 4) {
		 my = 0;
		 confusionMatrix[mx][my]++;
		 } else if (cc == 1) {
		 if (h == 0) {

		 double contour_perimeter = att[3];
		 if (size < 25) {
		 if (contour_perimeter < 900) {
		 my = 2;
		 confusionMatrix[mx][my]++;
		 continue;

		 } else {
		 my = 7;
		 confusionMatrix[mx][my]++;
		 continue;
		 }
		 } else {
		 if (contour_solidity > 0.80) {
		 my = 1;
		 confusionMatrix[mx][my]++;
		 continue;
		 } else {
		 if (contour_solidity < 0.65) {
		 my = 5;
		 confusionMatrix[mx][my]++;
		 continue;
		 } else {
		 if (contour_perimeter < 900) {
		 my = 4;
		 confusionMatrix[mx][my]++;
		 continue;
		 } else {
		 my = 3;
		 confusionMatrix[mx][my]++;
		 continue;
		 }

		 }

		 }

		 }
		 }
		 if (h == 1) {
		 int hole_area = att[1];
		 if (hole_area < 4340) {
		 my = 6;
		 confusionMatrix[mx][my]++;
		 continue;

		 } else if (hole_area > 4340) {
		 my = 9;
		 confusionMatrix[mx][my]++;
		 continue;
		 }

		 } else if (h == 2) {
		 my = 8;
		 confusionMatrix[mx][my]++;
		 continue;

		 } else if (h == 3) {

		 }
		 } else {
		 if (size == 24) {
		 my = 13;
		 confusionMatrix[mx][my]++;
		 continue;
		 } else if (size == 26) {
		 my = 12;
		 confusionMatrix[mx][my]++;
		 continue;
		 } else {
		 vector<vector<Point> > contours;
		 vector<Vec4i> hierarchy;
		 Mat img1;
		 bitwise_not(img, img1);

		 findContours(img1.clone(), contours, hierarchy,
		 CV_RETR_TREE, CV_CHAIN_APPROX_NONE);

		 RNG rng(12345);
		 Mat drawing = Mat::zeros(img1.size(), CV_8UC3);
		 vector<RotatedRect> minRect(contours.size());

		 for (int i = 0; i < contours.size(); i++) {

		 minRect[i] = minAreaRect(contours[i]);

		 }
		 if (minRect[0].angle < 0) {
		 my = 10;
		 confusionMatrix[mx][my]++;
		 continue;
		 } else {
		 my = 11;
		 confusionMatrix[mx][my]++;
		 continue;
		 }

		 }
		 }


		 cnt++;
		 cout << "Counter "<< cnt << endl;
		 cout << "Image size: " << size << endl;
		 cout << "Connected components: " << cc << endl;
		 cout << "Holes: " << h << endl;
		 cout << "Contour[0] " << "Area: " << att[0] << endl;
		 cout << "Contour[1] " << "Area: " << att[1] << endl;
		 cout << "Contour[2] " << "Area: " << att[2] << endl;
		 cout << "Contour[0] " << "Perimeter: " << att[3]
		 << endl;
		 cout << "Contour[1] " << "Perimeter: " << att[4]
		 << endl;
		 cout << "Contour[2] " << "Perimeter: " << avg[5]
		 << endl;
		 cout << "Contour[0] " << "Radius: " << att[6] << endl;
		 cout << "Contour[1] " << "Radius: " << att[7] << endl;
		 cout << "Contour[2] " << "Radius: " << att[8] << endl;
		 cout << "Contour[0] " << "Solidity: " << att[9] << endl;
		 cout << "Contour[1] " << "Solidity: " << att[10]
		 << endl;
		 cout << "Contour[2] " << "Solidity: " << att[11]
		 << endl;



		 Mat image;
		 resize(img, image, Size(256, 256));
		 namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
		 imshow("Display window", image);
		 waitKey(0);

		 }


		 for (int i = 0; i < 12; i++) {
		 avg[i] = avg[i] + att[i];
		 }

		 cout << "Image size: " << size << endl;
		 cout << "Connected components: " << cc << endl;
		 cout << "Holes: " << h << endl;
		 cout << "Contour[0] " << "Area: " << att[0] << endl;
		 cout << "Contour[1] " << "Area: " << att[1] << endl;
		 cout << "Contour[2] " << "Area: " << att[2] << endl;
		 cout << "Contour[0] " << "Perimeter: " << att[3] << endl;
		 cout << "Contour[1] " << "Perimeter: " << att[4] << endl;
		 cout << "Contour[2] " << "Perimeter: " << att[5] << endl;
		 cout << "Contour[0] " << "Radius: " << att[6] << endl;
		 cout << "Contour[1] " << "Radius: " << att[7] << endl;
		 cout << "Contour[2] " << "Radius: " << att[8] << endl;
		 cout << "Contour[0] " << "Solidity: " << att[9] << endl;
		 cout << "Contour[1] " << "Solidity: " << att[10] << endl;
		 cout << "Contour[2] " << "Solidity: " << att[11] << endl;
		 cin.get();
		 Mat image;
		 resize(img, image, Size(256, 256));
		 namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
		 imshow("Display window", image);
		 waitKey(0);

		 return confusionMatrix;
		 }*/

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
			resize(src, image, Size(256, 256));
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
						/*cout << "Component Size ***************** "
						 << componentSize << endl;*/
					}

				}
			}
		}
		return connectComponents;
	}

	int Holes(Mat ig) {
		Mat img = ig.clone();
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

	double* attribute(Mat ig) {
		Mat img = ig.clone();
		Mat src;
		// findcontours takes image with background black
		bitwise_not(img, src);
		Mat imgbig;
		resize(src, imgbig, Size(512, 512));
		double *attributes = new double[12];
		int kx = 0;

		for (int i = 0; i < 12; i++)
			attributes[i] = 0;

		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;

		findContours(imgbig.clone(), contours, hierarchy, CV_RETR_TREE,
				CV_CHAIN_APPROX_NONE);

		for (int i = 0; i < contours.size(); i++) {
			double a = contourArea(contours[i], false);
			kx = i;
			attributes[kx] = a;

			double p = arcLength(contours[i], true);
			kx = kx + 3;
			attributes[kx] = p;

			Point2f center;
			float r;
			minEnclosingCircle(contours[i], center, r);
			kx = kx + 3;
			attributes[kx] = r;

			Mat hull;
			convexHull(contours[i], hull);
			double hull_area = contourArea(hull, false);
			double s = a / hull_area;
			kx = kx + 3;
			attributes[kx] = s;

		}
		//cout << "Area: " << area << endl;

		return attributes;
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
}
;
/*
 for (int i = 0; i < 12; i++) {
 avg[i] = avg[i] + att[i];
 }

 cout << "Image size: " << size << endl;
 cout << "Connected components: " << cc << endl;
 cout << "Holes: " << h << endl;
 cout << "Contour[0] " << "Area: " << att[0] << endl;
 cout << "Contour[1] " << "Area: " << att[1] << endl;
 cout << "Contour[2] " << "Area: " << att[2] << endl;
 cout << "Contour[0] " << "Perimeter: " << att[3] << endl;
 cout << "Contour[1] " << "Perimeter: " << att[4] << endl;
 cout << "Contour[2] " << "Perimeter: " << att[5] << endl;
 cout << "Contour[0] " << "Radius: " << att[6] << endl;
 cout << "Contour[1] " << "Radius: " << att[7] << endl;
 cout << "Contour[2] " << "Radius: " << att[8] << endl;
 cout << "Contour[0] " << "Solidity: " << att[9] << endl;
 cout << "Contour[1] " << "Solidity: " << att[10] << endl;
 cout << "Contour[2] " << "Solidity: " << att[11] << endl;
 cin.get();
 Mat image;
 resize(img, image, Size(256, 256));
 namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
 imshow("Display window", image);
 waitKey(0);
 */

